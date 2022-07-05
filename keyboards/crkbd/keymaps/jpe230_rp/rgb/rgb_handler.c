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

#include "jpe230.h"

extern LED_TYPE rgb_matrix_ws2812_array[DRIVER_LED_TOTAL];

void rgb_matrix_indicators_user(void) {
    if(!is_keyboard_master()){
        
        /* Obtain LED values and multiply it by 2 */
        uint8_t r =  rgb_matrix_ws2812_array[TRACKBALL_LED_IDX].r;
        uint8_t g =  rgb_matrix_ws2812_array[TRACKBALL_LED_IDX].g;
        uint8_t b =  rgb_matrix_ws2812_array[TRACKBALL_LED_IDX].b;

        /* Send to trackball */
        trackball_set_rgbw(r, g, b, true);
    }
}