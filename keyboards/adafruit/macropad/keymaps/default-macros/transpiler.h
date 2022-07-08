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

#define TRANS_LAYER_NO 2

#define TRANS_KEYCODES_ENUM 

#define TRANS_CUSTOM_KEYCODES 

#define TRANS_LAYER_STRINGS "Macro Layer 1","Macro Layer 2"

#define TRANS_KEYMAP_STRINGS {{"","","RGBTOG"},{"SHOWRGB","SHOWIND","KEY C"},{"KEY D","KEY E","KEY F"},{"KEY G","KEY H","KEY I"},{"KEY J","KEY K","KEY L"}},{{"","","RGBTOG"},{"KEY A","KEY B","KEY C"},{"KEY D","KEY E","KEY F"},{"KEY G","KEY H","KEY I"},{"KEY J","KEY K","KEY L"}}

#define TRANS_INDICATORS {{{0x000000},{0x000000},{0x000000}},{{0x000000},{0x000000},{0x000000}},{{0x000000},{0x000000},{0x000000}},{{0x000000},{0x000000},{0x000000}}},{{{0x000000},{0x000000},{0x000000}},{{0x000000},{0x000000},{0x000000}},{{0x000000},{0x000000},{0x000000}},{{0x000000},{0x000000},{0x000000}}}

#define TRANS_KEYMAP [0] = LAYOUT(RGB_TOG,MC_SHWA,MC_INDI,KC_C,KC_D,KC_E,KC_F,KC_G,KC_H,KC_I,KC_J,KC_K,KC_L),[1] = LAYOUT(RGB_TOG,KC_A,KC_B,KC_C,KC_D,KC_E,KC_F,KC_G,KC_H,KC_I,KC_J,KC_K,KC_L)

