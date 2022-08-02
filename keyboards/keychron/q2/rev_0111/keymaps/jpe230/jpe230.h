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

/* Layers: Notice there is no MAC layers */
enum layer_names {
  BASE = 0,
  FN1,
  FN2,
  FN3 // Currently unaccesible
};

/* User Start (For custom keycodes) */
#ifdef VIA_ENABLE
  #define USER_START USER00
#else
  #define USER_START SAFE_RANGE
#endif

/* Custom keycodes */
enum custom_keycodes { KC_SBOB = USER_START };

/* Variables for custom logics */
bool tog_sbob, tog_via, uppercase, is_showing_indicators;
uint8_t prev_upper, prev_lower, prev_mode;
HSV prev_hsv;

/* Custom Macros for readability */
#define KC_LTCF LT(FN2, KC_CAPS)
#define KC_MSDN KC_MS_WH_DOWN
#define KC_MSUP KC_MS_WH_UP
#define SHOW_DEFAULT 1000
