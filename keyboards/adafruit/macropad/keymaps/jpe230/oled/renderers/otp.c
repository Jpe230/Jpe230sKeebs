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

#include "keymap.h"

extern char otp_string[10];

void render_authenticator(int layer)
{   
    /* Print Title */
    char title[CHARS_PER_LINE];
    center_text(layer_strings[layer], title, CHARS_PER_LINE);
    oled_write_ln((const char *)title, true);

    /* Print OTP */
    char tmp[CHARS_PER_LINE];
    center_text((const char *)otp_string, tmp, CHARS_PER_LINE);
    oled_write((const char*)tmp, false);

    /* Print Keys */
    for(uint8_t row = 1; row < MATRIX_ROWS; row++)
    {
        for(uint8_t col = 0; col < MATRIX_COLS; col++)
        {
            char name[CHARS_PER_KEY];
            center_text(key_strings[layer][row][col], name, CHARS_PER_KEY);
            bool invert = key_strings[layer][row][col][0] != '\0' && indicator_oled_state[row][col];
            oled_write((const char*)name, invert);
        }
    }

    /* Empty Line */
    oled_write_ln("", false);
}