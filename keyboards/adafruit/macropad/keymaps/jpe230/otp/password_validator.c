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
#include "../lib/security/sha256/sha256.h"

char user_input[PASSWORD_LEN + 1] = {0};
uint8_t passcode_pos = 0;
char hashed[SHA256_BLOCK_SIZE] = {PASSWORD};

void validate_passcode(void) {
    char buf[SHA256_BLOCK_SIZE];

    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, user_input, strlen(user_input));
    sha256_final(&ctx, buf);

    bool result = !memcmp(hashed, buf, SHA256_BLOCK_SIZE);
    
    if(result) {
        /* Move to the authenticator layer if password correct */
        handle_layer_move(TOTP_LAYER);
    }
}

void handle_passcode(uint16_t keycode) {
    /* Sanity check: Dont overflow the user_input array */
    if (passcode_pos > PASSWORD_LEN)
        return;

    /* Crude backspace */
    if (keycode == LS_BACK) {
        /* Sanity check: Dont roll-over if we backspace in pos. 0 */
        if (passcode_pos > 0) {
            passcode_pos--;
        }
        return;
    }

    /* Calculate char value from custom Keycode */
    char num = (keycode - LS_BTN0) + '0';
    user_input[passcode_pos++] = num;

    /* Validate the password once the user input all the chars */
    if (passcode_pos == PASSWORD_LEN) {
        user_input[passcode_pos] = '\0';
        passcode_pos = 0;
        validate_passcode();
    }
}