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

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xE230
#define PRODUCT_ID      0x7175
#define DEVICE_VER      0x0001
#define MANUFACTURER    Jpe230
#define PRODUCT         BigKey

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 3

#define DIRECT_PINS { {F5, F7, F6} }

#define RGB_DI_PIN D3
#define RGBLED_NUM 16

#define RGBLIGHT_SLEEP
#define RGBLIGHT_ANIMATIONS

#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_EFFECT_BREATHING + 2
#define RGBLIGHT_DEFAULT_HUE 152
#define RGBLIGHT_DEFAULT_SAT 232
#define RGBLIGHT_DEFAULT_VAR 255
#define RGBLIGHT_DEFAULT_SPD 2

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
