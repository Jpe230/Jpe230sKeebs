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

#include QMK_KEYBOARD_H

#include "transpiler.h"
#include "oled/oled_handler.h"
#include "rgb/rgb_handler.h"

#ifdef VIA_ENABLE
    #define USER_START USER00
#else
    #define USER_START SAFE_RANGE
#endif

enum MACROPAD_KEYCODES {
    MC_OLED = USER_START,// Toggle OLED
    MC_INDI,             // Show Indicators
    MC_MSKI,             // Mask Indicators
    MC_SHWA,             // Show Anim
    MC_ODEF,             // Select Default OLED
    MC_OBNC,             // Select Bongo Cat OLED
    MC_OLOG,             // Select Logo OLED,
    TRANS_KEYCODES_ENUM
};

/* -----------------------
 * Custom Configuration
 * -----------------------
 */
#define SHOW_DEFAULT 1500
#define RGB_IDLE_TIMEOUT 1500