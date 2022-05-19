/* Copyright 2021 @ Keychron (https://www.keychron.com)
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

#include QMK_KEYBOARD_H

#ifdef VIA_ENABLE
    #define USER_START USER00
#else
    #define USER_START SAFE_RANGE
#endif

enum layer_names {
    WIN_BASE = 0,
    WIN_FN1  = 1,
    MAC_BASE = 2,
    MAC_FN1  = 3,
    FN2      = 4,
};

#define KC_LTCF LT(FN2, KC_CAPS)

#define KC_MSDN KC_MS_WH_DOWN
#define KC_MSUP KC_MS_WH_UP

#ifdef VIA_ENABLE
    #define USER_START USER00
#else
    #define USER_START SAFE_RANGE
#endif

enum custom_keycodes {
    KC_SBOB = USER_START,
    KC_TVIA
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [WIN_BASE] = LAYOUT_all(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,     KC_EQL,  KC_BSPC,          KC_VOLD, KC_MUTE, KC_VOLU,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,     KC_RBRC, KC_BSLS,          KC_DEL,
        KC_LTCF, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,              KC_ENT,           KC_HOME,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,              KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT,  TT(WIN_FN1), MO(FN2), KC_LEFT, KC_DOWN, KC_RGHT),

    [WIN_FN1] = LAYOUT_all(
        KC_GRV,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______, _______,          KC_MSDN, RGB_TOG, KC_MSUP,
        EEP_RST, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,               _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,               _______, RGB_VAI,
        _______, _______, _______,                            _______,                            _______, TO(WIN_BASE), _______, RGB_MOD, RGB_HUI, RGB_SAI),

    [MAC_BASE] = LAYOUT_all(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,     KC_EQL,  KC_BSPC,          KC_VOLD, KC_MUTE, KC_VOLU,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,     KC_RBRC, KC_BSLS,          KC_DEL,
        KC_LTCF, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,              KC_ENT,           KC_HOME,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,              KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT,  TT(MAC_FN1), TT(FN2), KC_LEFT, KC_DOWN, KC_RGHT),

    [MAC_FN1] = LAYOUT_all(
        KC_GRV,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______, _______,          KC_MSDN, RGB_TOG, KC_MSUP,
        EEP_RST, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                _______, RGB_VAI,
        _______, _______, _______,                            _______,                            _______, TO(MAC_BASE),  _______, RGB_MOD, RGB_HUI, RGB_SAI),

    [FN2] = LAYOUT_all(
        KC_GRV,  KC_F1,       KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_DEL,          KC_MSDN, RESET, KC_MSUP,
        _______, _______,     KC_UP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, KC_DOWN,   KC_DOWN, KC_DOWN, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        KC_TVIA, _______,   KC_SBOB,                            _______,                            _______, _______, _______, KC_HOME, _______, KC_END),
};

#if defined(VIA_ENABLE) && defined(ENCODER_ENABLE)

#define ENCODERS 1
static uint8_t  encoder_state[ENCODERS] = {0};
static keypos_t encoder_cw[ENCODERS]    = {{ 8, 4 }};
static keypos_t encoder_ccw[ENCODERS]  = {{ 7, 4 }};

void encoder_action_register(uint8_t index, bool clockwise) {
    keyevent_t encoder_event = (keyevent_t) {
        .key = clockwise ? encoder_cw[index] : encoder_ccw[index],
        .pressed = true,
        .time = (timer_read() | 1)
    };
    encoder_state[index] = (clockwise ^ 1) | (clockwise << 1);
    action_exec(encoder_event);
}

void encoder_action_unregister(void) {
    for (int index = 0; index < ENCODERS; ++index) {
        if (encoder_state[index]) {
            keyevent_t encoder_event = (keyevent_t) {
                .key = encoder_state[index] >> 1 ? encoder_cw[index] : encoder_ccw[index],
                .pressed = false,
                .time = (timer_read() | 1)
            };
            encoder_state[index] = 0;
            action_exec(encoder_event);
        }
    }
}

void matrix_scan_user(void) {
    encoder_action_unregister();
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    encoder_action_register(index, clockwise);
    return false;
};

#endif

bool tog_sbob;
bool tog_via;
uint8_t prev_upper;
uint8_t prev_lower;
bool uppercase;

HSV prev_hsv;
uint8_t prev_mode;

void keyboard_post_init_kb(void) {
    tog_sbob       = false;
    tog_via        = false;
    uppercase      = false;
    prev_upper     = 0;
    prev_lower     = 0;
    prev_hsv       = rgb_matrix_get_hsv();
    prev_mode      = 0;
}

bool dip_switch_update_user(uint8_t index, bool active){
  switch(index){
    case 0:
      if(active){ //Mac/iOS mode
        layer_move(WIN_BASE);
      }
      else{ // Win/Android mode
        layer_move(MAC_BASE);
      }
      break;
  }

  return false;
}

bool process_record_spongebob(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_ENTER && record->event.pressed) {
        uppercase = false;
        return true;
    }

    if (uppercase == false && record->event.pressed )  {
        uppercase = true;
        return true;
    }

    if((KC_A <= keycode) && (keycode <= KC_Z)) {
        if ( record->event.pressed ) {
            bool press = rand() % 2;

            if (prev_upper > 2) {           // if more than 3 lower's in a row print upper
                prev_upper = 0;
                press = false;
            } else if (prev_lower > 2) {    // if more than 3 upper's in a row print lower
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
                    dprint("Enabling spongebob mode\n");
                    prev_hsv = rgb_matrix_get_hsv();
                    prev_mode = rgb_matrix_get_mode();
                    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_MULTISPLASH);
                    rgb_matrix_sethsv_noeeprom(HSV_YELLOW);
                }
                else{
                    rgb_matrix_mode_noeeprom(prev_mode);
                    rgb_matrix_sethsv_noeeprom(prev_hsv.h, prev_hsv.s, prev_hsv.v);
                }

                uppercase = false;
                prev_upper = 0;
                prev_lower = 0;
            }
            return false;
        case KC_TVIA:
            if (record->event.pressed) {
                tog_via = !tog_via;
            }
            return false;

    }

    if (tog_sbob) {
        return process_record_spongebob(keycode, record);
    }

    return true;
}
