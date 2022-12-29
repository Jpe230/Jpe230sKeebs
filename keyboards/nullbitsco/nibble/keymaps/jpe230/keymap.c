// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "animation_frames.h"
#include "jpe230.h"

enum layers { BASE, FN1, FN2 };

#define KC_LTCF LT(FN2, KC_CAPS)

enum custom_keycodes {
  JIGGLER = SAFE_RANGE,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_all(
              KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
    MACRO00,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_F10,
    MACRO01,  KC_LTCF, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_F11,
    MACRO02,  KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_F12,
    MACRO03,  KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, TT(FN1), MO(FN2), KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [FN1] = LAYOUT_all(
               KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12, _______, RGB_TOG,
    QK_BOOT,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    EE_CLR,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_VAI, _______,
    DB_TOGG,  _______, _______, _______,                            _______,                   _______,TO(BASE), _______, RGB_MOD, RGB_HUI, RGB_SAI
  ),

  [FN2] = LAYOUT_all(
               KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12, _______, QK_BOOT,
    _______,  _______, _______,   KC_UP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_MAKE,
    _______,  _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    KC_F23,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_F24,   _______, _______, _______,                            JIGGLER,                   _______, _______, _______, KC_HOME, _______, KC_END
  )
};
// clang-format on

#ifdef OLED_ENABLE
#define IDLE_FRAME_DURATION 200 // Idle animation iteration rate in ms

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_90;
}

uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;
uint8_t current_idle_frame = 0;

bool tap_anim = false;
bool tap_anim_toggle = false;

// Decompress and write a precompressed bitmap frame to the OLED.
// Documentation and python compression script available at:
// https://github.com/nullbitsco/squeez-o
#ifdef USE_OLED_BITMAP_COMPRESSION
static void oled_write_compressed_P(const char *input_block_map,
                                    const char *input_block_list) {
  uint16_t block_index = 0;
  for (uint16_t i = 0; i < NUM_OLED_BYTES; i++) {
    uint8_t bit = i % 8;
    uint8_t map_index = i / 8;
    uint8_t _block_map = (uint8_t)pgm_read_byte(input_block_map + map_index);
    uint8_t nonzero_byte = (_block_map & (1 << bit));
    if (nonzero_byte) {
      const char data =
          (const char)pgm_read_byte(input_block_list + block_index++);
      oled_write_raw_byte(data, i);
    } else {
      const char data = (const char)0x00;
      oled_write_raw_byte(data, i);
    }
  }
}
#endif

static void render_anim(void) {
  // Idle animation
  void animation_phase(void) {
    if (!tap_anim) {
      current_idle_frame = (current_idle_frame + 1) % NUM_IDLE_FRAMES;
      uint8_t idx = abs((NUM_IDLE_FRAMES - 1) - current_idle_frame);
#ifdef USE_OLED_BITMAP_COMPRESSION
      oled_write_compressed_P(idle_block_map[idx], idle_frames[idx]);
#else
      oled_write_raw_P(idle_frames[idx], NUM_OLED_BYTES);
#endif
    }
  }

  // Idle behaviour
  if (get_current_wpm() != 000) { // prevent sleep
    oled_on();
    if (timer_elapsed32(anim_timer) > IDLE_FRAME_DURATION) {
      anim_timer = timer_read32();
      animation_phase();
    }
    anim_sleep = timer_read32();
  } else { // Turn off screen when timer threshold elapsed or reset time since
           // last input
    if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
      oled_off();
    } else {
      if (timer_elapsed32(anim_timer) > IDLE_FRAME_DURATION) {
        anim_timer = timer_read32();
        animation_phase();
      }
    }
  }
}

bool oled_task_user(void) {
  render_anim();
  oled_set_cursor(0, 14);

  uint8_t n = get_current_wpm();
  char wpm_counter[6];
  wpm_counter[5] = '\0';
  wpm_counter[4] = '0' + n % 10;
  wpm_counter[3] = '0' + (n /= 10) % 10;
  wpm_counter[2] = '0' + n / 10;
  wpm_counter[1] = '0';
  wpm_counter[0] = '>';
  oled_write_ln(wpm_counter, false);

  return false;
}
#endif

void keyboard_post_init_user(void) { debug_enable = true; }

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  if (host_keyboard_led_state().caps_lock) {
    rgb_matrix_set_color(0, RGB_BLUE);
  } else {
    rgb_matrix_set_color(0, 0, 0, 0);
  }
  return false;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
  // Encoder is mapped to volume functions by default
  if (clockwise) {
    tap_code(KC_VOLD);
  } else {
    tap_code(KC_VOLU);
  }
  return true;
}

// static bool button_down = false;
static bool direction = false; // false = left, true = left
static bool jiggler_active = false;

bool jiggle_mouse(void) {
  uint8_t keycode_prev = !direction ? KC_MS_LEFT : KC_MS_RIGHT;
  uint8_t keycode_curr = direction ? KC_MS_LEFT : KC_MS_RIGHT;

  dprintf("Registering Keycode: %d, remove %d\n", keycode_curr, keycode_prev);

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  dprintf("proccess record user %d\n", keycode);

#ifdef OLED_ENABLE
  // Check if non-mod
  if ((keycode >= KC_A && keycode <= KC_0) ||
      (keycode >= KC_TAB && keycode <= KC_SLASH)) {
    if (record->event.pressed) {
      // Display tap frames
      tap_anim_toggle = !tap_anim_toggle;
#ifdef USE_OLED_BITMAP_COMPRESSION
      oled_write_compressed_P(tap_block_map[tap_anim_toggle],
                              tap_frames[tap_anim_toggle]);
#else
      oled_write_raw_P(tap_frames[tap_anim_toggle], NUM_OLED_BYTES);
#endif
    }
  }
#endif

  if (record->event.pressed) {
    switch (keycode) {
    case RGB_MATRIX_TOGGLE:
      rgb_matrix_toggle();
      return false;
    case JIGGLER:
      if (record->event.pressed) {
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
    default:
      break;
    }
  }
  return true;
}
