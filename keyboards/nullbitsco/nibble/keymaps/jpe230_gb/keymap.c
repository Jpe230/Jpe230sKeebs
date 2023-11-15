// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "jpe230.h"

#define KC_LTCF LT(FN2, KC_CAPS)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_all(
              KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
    _______,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_F10,
    _______,  KC_LTCF, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_F11,
    _______,  KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_F12,
    _______,  KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    DF(FN3), TT(FN1), MO(FN2), KC_LEFT, KC_DOWN, KC_RGHT
  ),
  

  [FN1] = LAYOUT_all(
               KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12, _______, RGB_TOG,
    QK_BOOT,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    EE_CLR,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_VAI, _______,
    DB_TOGG,  _______, _______, _______,                            _______,                   _______,TO(BASE), _______, RGB_MOD, RGB_HUI, RGB_SAI
  ),

  [FN2] = LAYOUT_all(
               KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12,  KC_DEL, QK_BOOT,
    _______,  _______, _______,   KC_UP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_MAKE,
    _______,  _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    KC_F23,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  SCR_ON, _______,
    KC_F24,   _______, _______, _______,                            JIGGLER,                   _______, _______, _______, KC_HOME, SCR_OFF, KC_END
  ),

  [FN3] = LAYOUT_all(
              GKEY_SP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, GKEY_SL, _______,
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          GKEY_ST, _______,
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  GKEY_U, _______,
    _______,   GKEY_A,  GKEY_B, _______,                            _______,                   DF(FN1), _______, _______,  GKEY_L,  GKEY_D, GKEY_R
  )
};
// clang-format on

painter_device_t display;

void keyboard_post_init_user(void) 
{
  debug_enable=true;

  // Turn on display backlight
  setPinOutput(LCD_BLK_PIN);
  writePin(LCD_BLK_PIN, 1);

  // Init QP display
  display = qp_st7789_make_spi_device(QP_SCR1_Y, QP_SCR1_X, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 2, 2);
  qp_init(display, QP_ROTATION_90);
  qp_power(display, true);
  qp_set_viewport_offsets(display, 0, 35);
  qp_rect(display, 0, 0, QP_SCR1_X - 1, QP_SCR1_Y - 1, 0, 0, 0, true);
  qp_flush(display);
}


/* Game Logic */

bool game_keys[16] = {0};
static bool game_started = false;
static bool game_paused  = false;

void housekeeping_task_user(void) {
  static uint32_t last_draw = 0;
  if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
    last_draw = timer_read32();
    if(!game_paused && game_started)
    {
       game_loop();
    }
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  
  if(keycode >= GKEY_U && keycode <= GKEY_SL)
  {
    game_keys[keycode - GKEY_U] = record->event.pressed;
  }

  if(keycode == GKEY_ST && record->event.pressed && !game_started)
  {
    game_started = true;
    layer_move(FN3);
    gb_main();
    return false;
  }

  if(keycode == GKEY_SP && record->event.pressed && game_started)
  {
    layer_move(FN1);
    game_paused = !game_paused;
    return false;
  }

  return true;
}

// Nullbits stuff that needs to be added (ignore for other keebs)
void set_bitc_LED(uint8_t a){}