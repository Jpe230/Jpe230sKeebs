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

/* Keychron hackery stuff for Encoder */
#if defined(VIA_ENABLE) && defined(ENCODER_ENABLE)
#define ENCODERS 1
static uint8_t encoder_state[ENCODERS] = {0};
static keypos_t encoder_cw[ENCODERS] = {{8, 4}};
static keypos_t encoder_ccw[ENCODERS] = {{7, 4}};

void encoder_action_register(uint8_t index, bool clockwise) {
  keyevent_t encoder_event =
      (keyevent_t){.key = clockwise ? encoder_cw[index] : encoder_ccw[index],
                   .pressed = true,
                   .time = (timer_read() | 1)};
  encoder_state[index] = (clockwise ^ 1) | (clockwise << 1);
  action_exec(encoder_event);
}

void encoder_action_unregister(void) {
  for (int index = 0; index < ENCODERS; ++index) {
    if (encoder_state[index]) {
      keyevent_t encoder_event =
          (keyevent_t){.key = encoder_state[index] >> 1 ? encoder_cw[index]
                                                        : encoder_ccw[index],
                       .pressed = false,
                       .time = (timer_read() | 1)};
      encoder_state[index] = 0;
      action_exec(encoder_event);
    }
  }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
  encoder_action_register(index, clockwise);
  return false;
};
#endif

void matrix_scan_user(void) {
  /* Keychron hackery stuff for Encoder */
#if defined(VIA_ENABLE) && defined(ENCODER_ENABLE)
  encoder_action_unregister();
#endif
}

bool dip_switch_update_user(uint8_t index, bool active) {
  return false;
}


/* SpongeBob */
bool process_record_spongebob(uint16_t keycode, keyrecord_t *record) {
  if (keycode == KC_ENTER && record->event.pressed) {
    uppercase = false;
    return true;
  }
  if (uppercase == false && record->event.pressed) {
    uppercase = true;
    return true;
  }
  if ((KC_A <= keycode) && (keycode <= KC_Z)) {
    if (record->event.pressed) {
      bool press = rand() % 2;
      if (prev_upper > 2) { // if more than 3 lower's in a row print upper
        prev_upper = 0;
        press = false;
      } else if (prev_lower >
                 2) { // if more than 3 upper's in a row print lower
        prev_lower = 0;
        press = true;
      }
      if (press) {
        prev_upper++;
        tap_code16(S(keycode));
        clear_mods();
      } else {
        prev_lower++;
        tap_code16(keycode);
      }
    }
    return false;
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_SBOB:
    if (record->event.pressed) {

      tog_sbob = !tog_sbob;

      if (tog_sbob) {
        prev_hsv = rgb_matrix_get_hsv();
        prev_mode = rgb_matrix_get_mode();
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_MULTISPLASH);
        rgb_matrix_sethsv_noeeprom(HSV_YELLOW);
      } else {
        rgb_matrix_mode_noeeprom(prev_mode);
        rgb_matrix_sethsv_noeeprom(prev_hsv.h, prev_hsv.s, prev_hsv.v);
      }

      uppercase = false;
      prev_upper = 0;
      prev_lower = 0;
    }
    return false;
  case RESET:
    if (record->event.pressed) {
      rgb_matrix_set_color_all(0, 0, 0);
      rgb_matrix_driver.flush();
      rgb_matrix_disable_noeeprom();
      eeconfig_init();
    }
    return true;
  }

  if (tog_sbob) {
    return process_record_spongebob(keycode, record);
  }

  return true;
}