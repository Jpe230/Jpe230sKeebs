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

/* Code adapted from this repo: https://github.com/Netthaw/TOTP-MCU */

#include "sha1.h"
#include <string.h>

#define SHA1_K0 0x5a827999
#define SHA1_K20 0x6ed9eba1
#define SHA1_K40 0x8f1bbcdc
#define SHA1_K60 0xca62c1d6

uint8_t sha1_init_state[] = {
    0x01, 0x23, 0x45, 0x67, // H0
    0x89, 0xab, 0xcd, 0xef, // H1
    0xfe, 0xdc, 0xba, 0x98, // H2
    0x76, 0x54, 0x32, 0x10, // H3
    0xf0, 0xe1, 0xd2, 0xc3  // H4
};

void init(void) {
    memcpy(sha1_state.b, sha1_init_state, HASH_LENGTH);
    byte_count = 0;
    buffer_offset = 0;
}

uint32_t rol32(uint32_t number, uint8_t bits) {
    return ((number << bits) | (uint32_t)(number >> (32 - bits)));
}

void hashblock(void) {
    uint8_t i;
    uint32_t a, b, c, d, e, t;

    a = sha1_state.w[0];
    b = sha1_state.w[1];
    c = sha1_state.w[2];
    d = sha1_state.w[3];
    e = sha1_state.w[4];
    for (i = 0; i < 80; i++) {
        if (i >= 16) {
        t = buffer.w[(i + 13) & 15] ^ buffer.w[(i + 8) & 15] ^
            buffer.w[(i + 2) & 15] ^ buffer.w[i & 15];
        buffer.w[i & 15] = rol32(t, 1);
        }
        if (i < 20) {
        t = (d ^ (b & (c ^ d))) + SHA1_K0;
        } else if (i < 40) {
        t = (b ^ c ^ d) + SHA1_K20;
        } else if (i < 60) {
        t = ((b & c) | (d & (b | c))) + SHA1_K40;
        } else {
        t = (b ^ c ^ d) + SHA1_K60;
        }
        t += rol32(a, 5) + e + buffer.w[i & 15];
        e = d;
        d = c;
        c = rol32(b, 30);
        b = a;
        a = t;
    }
    sha1_state.w[0] += a;
    sha1_state.w[1] += b;
    sha1_state.w[2] += c;
    sha1_state.w[3] += d;
    sha1_state.w[4] += e;
}

void add_uncounted(uint8_t data) {
    buffer.b[buffer_offset ^ 3] = data;
    buffer_offset++;
    if (buffer_offset == BLOCK_LENGTH) {
        hashblock();
        buffer_offset = 0;
    }
}

void write(uint8_t data) {
    ++byte_count;
    add_uncounted(data);

    return;
}

void write_array(uint8_t *buffer, uint8_t size) {
    while (size--) {
        write(*buffer++);
    }
}

void pad(void) {
    // Implement SHA-1 padding (fips180-2 ˜5.1.1)

    // Pad with 0x80 followed by 0x00 until the end of the block
    add_uncounted(0x80);
    while (buffer_offset != 56)
        add_uncounted(0x00);

    // Append length in the last 8 bytes
    add_uncounted(0);                // We're only using 32 bit lengths
    add_uncounted(0);                // But SHA-1 supports 64 bit lengths
    add_uncounted(0);                // So zero pad the top bits
    add_uncounted(byte_count >> 29); // Shifting to multiply by 8
    add_uncounted(byte_count >> 21); // as SHA-1 supports bitstreams as well as
    add_uncounted(byte_count >> 13); // byte.
    add_uncounted(byte_count >> 5);
    add_uncounted(byte_count << 3);
}

uint8_t *result(void) {
    // Pad to complete the last block
    pad();

    // Swap byte order back
    uint8_t i;
    for (i = 0; i < 5; i++) {
        uint32_t a, b;
        a = sha1_state.w[i];
        b = a << 24;
        b |= (a << 8) & 0x00ff0000;
        b |= (a >> 8) & 0x0000ff00;
        b |= a >> 24;
        sha1_state.w[i] = b;
    }

    // Return pointer to hash (20 characters)
    return sha1_state.b;
}

#define HMAC_IPAD 0x36
#define HMAC_OPAD 0x5c

void init_hmac(const uint8_t *key, uint8_t keyLength) {
    uint8_t i;
    memset(key_buffer, 0, BLOCK_LENGTH);
    if (keyLength > BLOCK_LENGTH) {
        // Hash long keys
        init();
        for (; keyLength--;)
        write(*key++);
        memcpy(key_buffer, result(), HASH_LENGTH);
    } else {
        // Block length keys are used as is
        memcpy(key_buffer, key, keyLength);
    }
    // Start inner hash
    init();
    for (i = 0; i < BLOCK_LENGTH; i++) {
        write(key_buffer[i] ^ HMAC_IPAD);
    }
}

uint8_t *result_hmac(void) {
    uint8_t i;
    // Complete inner hash
    memcpy(inner_hash, result(), HASH_LENGTH);
    // Calculate outer hash
    init();
    for (i = 0; i < BLOCK_LENGTH; i++)
        write(key_buffer[i] ^ HMAC_OPAD);
    for (i = 0; i < HASH_LENGTH; i++)
        write(inner_hash[i]);
    return result();
}