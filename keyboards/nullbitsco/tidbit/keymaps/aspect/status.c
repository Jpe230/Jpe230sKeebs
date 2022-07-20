/* Copyright 2021 Chris Tanaka <https://github.com/christanaka>
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

#include "status.h"
#include QMK_KEYBOARD_H

void status_render_layer(uint8_t x, uint8_t y) {
  oled_set_cursor(x, y);
  uint8_t layer = get_highest_layer(layer_state);
  oled_write("Layer ", false);
  oled_write(get_u8_str(layer, '0'), false);
}

void status_render_caps_lock(uint8_t x, uint8_t y) {
  led_t led_usb_state = host_keyboard_led_state();

  oled_set_cursor(x, y);
  if (led_usb_state.caps_lock) {
    oled_write("CPSLK", true);
  } else {
    oled_write("     ", false);
  }
}
