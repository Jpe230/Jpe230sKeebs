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

void trackball_set_rgb(uint8_t r,uint8_t g,uint8_t b, bool adjust_brightness) {

    /* Only send on slave half */
    if(is_keyboard_master()) {
        return;
    }

    /* Board uses 127 as max value, multiply the values otherwise
     * the trackball will be dim
     */
    if(adjust_brightness){
        r <<= 1;
        g <<= 1;
        b <<= 1;
    }
    
    /* Determine lowest value in all three colors, put that into
     * the white channel and then shift all colors by that amount
     */
    uint8_t w = MIN(r, MIN(g, b));
    r -= w;
    g -= w;
    b -= w;

    pimoroni_trackball_set_rgbw(r, g, b, w);
}