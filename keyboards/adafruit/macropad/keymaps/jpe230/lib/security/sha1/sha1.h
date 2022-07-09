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

#pragma once

#include "keymap.h"

#define HASH_LENGTH 20
#define BLOCK_LENGTH 64

union _buffer {
    uint8_t b[BLOCK_LENGTH];
    uint32_t w[BLOCK_LENGTH/4];
} buffer;

union _state {
    uint8_t b[HASH_LENGTH];
    uint32_t w[HASH_LENGTH/4];
} state;

uint8_t buffer_offset;
uint32_t byte_count;
uint8_t key_buffer[BLOCK_LENGTH];
uint8_t inner_hash[HASH_LENGTH];

void init(void);
void init_hmac(const uint8_t* secret, uint8_t secretLength);
uint8_t* result(void);
uint8_t* result_hmac(void);
void write(uint8_t);
void write_array(uint8_t *buffer, uint8_t size);