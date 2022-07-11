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

/* ---------------------------
 * Custom OLED Region
 * ---------------------------
 */
extern bool turn_oled_off;

/* ---------------------------
 * Custom OLED Fncs Prototypes
 * ---------------------------
 */
void render_slave_oled(void);
void render_master_oled(void);
void oled_timer_reset(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
