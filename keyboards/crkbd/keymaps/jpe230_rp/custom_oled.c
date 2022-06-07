/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "./oled/master/master_graphics.h"
#include <stdio.h>

// #ifdef OLED_ENABLE

static uint8_t logged_row = 0, logged_col = 0;
uint32_t oled_timer = 0;

void oled_timer_reset(void) { oled_timer = timer_read32(); }

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_270;
}

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  logged_row = record->event.key.row;
  logged_col = record->event.key.col;
}

void oled_render_layer_state(void) {
  oled_write_raw_P(
      numbers_array[get_highest_layer(layer_state | default_layer_state)],
      GRAPHIC_SIZE);
}

void oled_render_logo(void) {
  static const char PROGMEM number0[] = {
      0x05, 0x02, 0xe5, 0xe2, 0xe5, 0xf2, 0xf5, 0xf2, 0xf5, 0xf2, 0xf5, 0xf2,
      0xf5, 0xf2, 0xf5, 0xf2, 0xf5, 0xf2, 0xf5, 0xf2, 0xf5, 0xf2, 0xf5, 0xf2,
      0xf5, 0xf2, 0xf5, 0xe2, 0xe5, 0xe2, 0x05, 0x02, 0x00, 0xff, 0xff, 0xff,
      0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xfc, 0xff, 0xff,
      0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x80, 0xf0, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x00,
      0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xfc, 0xff, 0xff, 0xff,
      0x1f, 0x03, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff,
      0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0xe0, 0xfe, 0xff, 0xff, 0xff, 0x0f, 0x01, 0x00, 0x00, 0x00, 0xff,
      0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xf8, 0xff, 0xff, 0xff, 0x3f,
      0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00,
      0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0xe0, 0xfc, 0xff, 0xff, 0xff, 0x1f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff,
      0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xfe, 0xff, 0xff, 0x7f, 0x0f,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
      0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xc0,
      0xf8, 0xff, 0xff, 0xff, 0x3f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00,
      0x00, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xfc, 0xff, 0xff, 0xff, 0x1f, 0x01,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x3f, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xc7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
      0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xff,
      0xff, 0xff, 0x3f, 0x00, 0x28, 0x10, 0x29, 0x11, 0x29, 0x13, 0x2b, 0x13,
      0x2b, 0x13, 0x2b, 0x13, 0x2b, 0x13, 0x2b, 0x13, 0x2b, 0x13, 0x2b, 0x13,
      0x2b, 0x13, 0x2b, 0x13, 0x2b, 0x13, 0x2b, 0x11, 0x29, 0x11, 0x28, 0x10};
  oled_write_raw_P(number0, 400);
}

bool oled_task_user(void) {

  if (is_keyboard_master()) {

    if (timer_elapsed32(oled_timer) > OLED_TIMEOUT) {
      oled_off();
      return false;
    } else {
      oled_on();
    }

    oled_render_layer_state();
    oled_set_cursor(0, 12);

    char col_str[4] = {0};
    sprintf(col_str, "%02d", logged_col);

    char row_str[4] = {0};
    sprintf(row_str, "%02d", logged_row);

    static const char PROGMEM separator[] = {4, 4, 4, 4, 4, 0};

    // char scan_str[13] = {0};
    // sprintf(row_str, "%ld", get_matrix_scan_rate());
    oled_write(separator, false);
    oled_write(col_str, false);
    oled_write(PSTR("x"), false);
    oled_write(row_str, false);
    oled_write(separator, false);
    oled_write(get_u16_str(get_matrix_scan_rate(), ' '), false);

  } else {
    oled_render_logo();
  }
  return false;
}

// #endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
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
  }
#endif

  return true;
}
