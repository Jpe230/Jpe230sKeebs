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
#include "oled/slave/ocean_dream.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        oled_timer_reset();
        set_keylog(keycode, record);

        switch (keycode) {
            case QK_BOOT:
                rgb_matrix_set_color_all(30, 0, 0);
                rgb_matrix_driver.flush();
                oled_off();
                return true;
        }
        if (!is_keyboard_master() && (keycode == KC_LCTL || keycode == KC_RCTL)) {
            is_calm = (record->event.pressed) ? true : false;
        }
    }
    return true;
}