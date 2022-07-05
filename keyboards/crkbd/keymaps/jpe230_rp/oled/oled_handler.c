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

uint8_t logged_row = 0, logged_col = 0;
uint32_t oled_timer = 0;
bool turn_oled_off = false;

void oled_timer_reset() { oled_timer = timer_read32(); }

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    logged_row = record->event.key.row;
    logged_col = record->event.key.col;
}

bool oled_task_user(void) {

    turn_oled_off = false;
    if (timer_elapsed32(oled_timer) > OLED_TIMEOUT) {
            turn_oled_off = true;
    }

    if (is_keyboard_master()) {
        render_master_oled();
    } else {
        render_slave_oled();
    }
    return false;
}
