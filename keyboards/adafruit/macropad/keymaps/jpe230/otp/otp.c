/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "otp.h"

uint8_t PROGMEM keys[][20] = {
    TOTP_KEYS
};

char otp_string[10];

uint32_t generate_topt(uint8_t hmac_key) {
    ds3231_time_t t;
    ds3231_get_time(&t);
    
    uint32_t time_stamp = t.unixtime;
    uint32_t steps = time_stamp / TIMESTEPS;

    // STEP 0, map the number of steps in a 8-bytes array (counter value)
    uint8_t byte_array[8];
    byte_array[0] = 0x00;
    byte_array[1] = 0x00;
    byte_array[2] = 0x00;
    byte_array[3] = 0x00;
    byte_array[4] = (uint8_t)((steps >> 24) & 0xFF);
    byte_array[5] = (uint8_t)((steps >> 16) & 0xFF);
    byte_array[6] = (uint8_t)((steps >> 8) & 0XFF);
    byte_array[7] = (uint8_t)((steps & 0XFF));

    // STEP 1, get the HMAC-SHA1 hash from counter and key
    uint8_t* key = keys[hmac_key];
    init_hmac(key, 20);
    write_array(byte_array, 8);
    uint8_t* hash = result_hmac();

    // STEP 2, apply dynamic truncation to obtain a 4-bytes string
    uint32_t truncated_hash = 0;
    uint8_t offset = hash[20 - 1] & 0xF;
    uint8_t j;
    for (j = 0; j < 4; ++j) {
        truncated_hash <<= 8;
        truncated_hash  |= hash[offset + j];
    }

    // STEP 3, compute the OTP value
    truncated_hash &= 0x7FFFFFFF;
    truncated_hash %= 1000000;

    return truncated_hash;
}

void handle_TOPT(uint16_t key_index) {
    key_index -= OTPBTN0;
    uint32_t otp = generate_topt(key_index);
    sprintf(otp_string, "%06ld", otp);
    send_string(otp_string);
    SEND_STRING("\n");
}