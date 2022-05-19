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

#include "bigkey.h"

led_config_t g_led_config = { {
    { NO_LED, NO_LED, NO_LED }
}, {
    {112,0  }, { 84,8  }, {140,8  }, { 56,16 }, {168,16 }, { 28,24 }, {196,24 }, {  0,32 },
    {224,32 }, { 28,40 }, {196,40 }, { 56,48 }, {168,48 }, { 84,56 }, {140,56 }, {112,64 }
}, {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
} };
