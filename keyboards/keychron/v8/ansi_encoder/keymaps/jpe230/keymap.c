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

enum layers { BASE, FN1, FN2, FN3 };

#define KC_LTCF LT(FN2, KC_CAPS)
#define KC_MSDN KC_MS_WH_DOWN
#define KC_MSUP KC_MS_WH_UP

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT_ansi_69(
        KC_ESC,     KC_1,    KC_2,   KC_3,     KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9, KC_0,    KC_MINS,  KC_EQL, KC_BSPC,          KC_MUTE,
        KC_TAB,     KC_Q,    KC_W,   KC_E,     KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O, KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_F10,
        KC_LTCF,    KC_A,    KC_S,   KC_D,     KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,           KC_ENT,          KC_F11,
        KC_LSFT,             KC_Z,   KC_X,     KC_C,    KC_V,    KC_B,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,   KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,           KC_SPC,          MO(FN3), TT(FN1),           KC_SPC,          MO(FN2),          KC_LEFT, KC_DOWN, KC_RGHT),

    [FN1] = LAYOUT_ansi_69(
        KC_GRV,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_TOG,
        EE_CLR,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  RGB_VAI,
        _______, _______, _______,          _______,          _______, _______,          _______,         TO(BASE),          RGB_MOD,  RGB_HUI,RGB_SAI),

    [FN2] = LAYOUT_ansi_69(
        KC_GRV,  KC_F1,     KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_DEL,          QK_BOOT,
        _______, _______,   KC_UP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          QK_MAKE,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,          JIGGLER,          _______, _______,          JIGGLER,          _______,          KC_HOME, _______,  KC_END),

    [FN3] = LAYOUT_ansi_69  (
        _______, KC_SCR1, KC_SCR2, KC_SCR3, KC_SCR4, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,          _______,          _______, _______,          _______,          _______,          _______, _______, _______)
};  


const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [FN1]  = { ENCODER_CCW_CW(KC_MSDN, KC_MSUP) },
    [FN2]  = { ENCODER_CCW_CW(KC_MSDN, KC_MSUP) },
    [FN3]  = { ENCODER_CCW_CW(_______, _______) },
};
// clang-format on

bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        debug_enable = active;
    }
    return false;
}

// static bool button_down = false;
static bool direction = false; // false = left, true = left
static bool jiggler_active = false;

bool jiggle_mouse(void) {
    uint8_t keycode_prev = !direction ? KC_MS_LEFT : KC_MS_RIGHT;
    uint8_t keycode_curr =  direction ? KC_MS_LEFT : KC_MS_RIGHT;

    dprintf("Registering Keycode: %d, remove %d\n", keycode_curr, keycode_prev);

    unregister_code(keycode_prev);
    register_code(keycode_curr);

    direction = !direction;

    return true;
}

uint32_t mouse_callback(uint32_t trigger_time, void *cb_arg) {
    bool repeat = jiggle_mouse();
    return repeat ? 25 : 0;
}

deferred_token mouse_token;

__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case QK_BOOT:
        //     if (record->event.pressed) {
        //         rgb_matrix_set_color_all(0, 0, 0);
        //         rgb_matrix_driver.flush();
        //         rgb_matrix_disable_noeeprom();
        //         eeconfig_init();
        //     }
        //     return true;
        case JIGGLER:
            if (record->event.pressed){
                jiggler_active = !jiggler_active;

                if(jiggler_active){
                    mouse_token = defer_exec(1, mouse_callback, NULL);
                }
                else{
                    cancel_deferred_exec(mouse_token);
                    unregister_code(KC_MS_LEFT);
                    unregister_code(KC_MS_RIGHT);
                }
            }
            return false;
    }

    return process_record_secrets(keycode, record);
}
