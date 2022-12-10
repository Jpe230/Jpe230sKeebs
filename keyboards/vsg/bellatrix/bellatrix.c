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

#include "bellatrix.h"

#ifdef RGB_MATRIX_ENABLE

#define NA NO_LED

led_config_t g_led_config = { {
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15},
    { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, NA, 29, 30},
    { 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46},
    { 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, NA, 59, 60, 61},
    { 62, 63, 64, NA, NA, NA, 65, NA, NA, NA, 66, 67, 68, 69, 70, 71}
    // Underglow
    //,{ 72, 73, 74, 75, 76, 77}
}, {
    {0  ,  0}, {12 ,  0}, {25 ,  0}, {37 ,  0}, {50 ,  0}, {62 ,  0}, {75 ,  0}, {87 ,  0}, {100,  0}, {112,  0}, {124,  0}, {137,  0}, {149,  0}, {162,  0}, {174,  0}, {187,  0},
    {0  , 13}, {12 , 13}, {25 , 13}, {37 , 13}, {50 , 13}, {62 , 13}, {75 , 13}, {87 , 13}, {100, 13}, {112, 13}, {124, 13}, {137, 13}, {149, 13},            {174, 13}, {187, 13},
    {3  , 26}, {19 , 26}, {31 , 26}, {44 , 26}, {56 , 26}, {68 , 26}, {81 , 26}, {93 , 26}, {106, 26}, {118, 26}, {131, 26}, {143, 26}, {156, 26}, {168, 26}, {174, 26}, {187, 26},
    {5  , 38}, {22 , 38}, {34 , 38}, {47 , 38}, {59 , 38}, {72 , 38}, {84 , 38}, {96 , 38}, {109, 38}, {121, 38}, {134, 38}, {146, 38},            {166, 38}, {174, 38}, {187, 38},
    {2  , 51}, {17 , 51}, {33 , 51},                                  {79 , 51},                                  {124, 51}, {137, 51}, {149, 51}, {162, 51}, {174, 51}, {187, 51}
    // Underglow
    //,{190, 51}, {190, 45}, {190, 39}, {190, 33}, {190, 27}, {190, 21}
}, {
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4, 4,
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4, 4, 4,
   4, 4, 4,          4,          4, 4, 4, 4, 4, 4
   // Underglow
   //,2, 2, 2, 2, 2, 2
} };

#endif
