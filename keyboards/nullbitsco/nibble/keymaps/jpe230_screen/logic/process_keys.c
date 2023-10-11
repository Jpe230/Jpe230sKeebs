// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "jpe230.h"
#include "bongo/main_screen.h"

void screen_blk(bool state)
{
  writePin(LCD_BLK_PIN, state);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (clockwise) {
    tap_code(KC_VOLD);
  } else {
    tap_code(KC_VOLU);
  }
  return true;
}

static bool direction = false; // false = left, true = left
static bool jiggler_active = false;

bool jiggle_mouse(void) {
  uint8_t keycode_prev = !direction ? KC_MS_LEFT : KC_MS_RIGHT;
  uint8_t keycode_curr = direction ? KC_MS_LEFT : KC_MS_RIGHT;

  //dprintf("Registering Keycode: %d, remove %d\n", keycode_curr, keycode_prev);

  unregister_code(keycode_prev);
  register_code(keycode_curr);

  direction = !direction;

  return true;
}

uint32_t mouse_callback(uint32_t trigger_time, void *cb_arg) {
  /* do something */
  bool repeat = jiggle_mouse();
  return repeat ? 25 : 0;
}

deferred_token mouse_token;
extern void print_screen(void);

__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    make_bongo_dance();
    switch (keycode) {
    case JIGGLER:
      if (record->event.pressed) {
        print_screen();
        jiggler_active = !jiggler_active;

        if (jiggler_active) {
          mouse_token = defer_exec(1, mouse_callback, NULL);
        } else {
          cancel_deferred_exec(mouse_token);
          unregister_code(KC_MS_LEFT);
          unregister_code(KC_MS_RIGHT);
        }
      }
      return false;
    case SCR_ON:
      screen_blk(true);
      return false;
    case SCR_OFF:
      screen_blk(false);
      return false;
    default:
      break;
    }
  }
  return process_record_secrets(keycode, record);
}

void set_bitc_LED(uint8_t a){}