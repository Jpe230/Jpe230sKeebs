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

#include "dev.h"
#include "../../bindings/bindings.h"

void dev_qk_boot(void) {
    qmk_lv_tap_keycode(QK_BOOT);
}
void dev_dbg_toggle(void) {
    qmk_lv_tap_keycode(DB_TOGG);
}
void dev_clr_eeprom(void) {
    qmk_lv_tap_keycode(EE_CLR);
}
