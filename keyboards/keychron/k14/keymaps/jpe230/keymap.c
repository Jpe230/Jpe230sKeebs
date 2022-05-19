/*
Copyright 2020 Dimitris Mantzouranis
Copyright 2022 Pablo Ramirez

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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    WIN_BASE = 0,
    WIN_FN1  = 1,
    MAC_BASE = 2,
    MAC_FN1  = 3,
    FN2      = 4,
};

#define KC_TASK LGUI(KC_TAB)        // Task viewer
#define KC_FLXP LGUI(KC_E)          // Windows file explorer

#define KC_MSSN LGUI(KC_F3)         // Mission Control
#define KC_FIND LALT(LGUI(KC_SPC))  // Finder
#define KC_MSNP LSFT(LGUI(KC_4))    // Mac snip tool

#ifdef VIA_ENABLE
    #define USER_START USER00
#else
    #define USER_START SAFE_RANGE
#endif

// Keycode to toggle Sarcasm Mode
enum custom_keycodes {
    KC_SCASM = USER_START
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

        /*
        +--------------------------------------------------------------------------+----+----+
        | ESC |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = | BACKSP | INS| RGB|
        +--------------------------------------------------------------------------+----+----+
        |  TAB  |  Q |  W |  E |  R |  T |  Y |  U |  I |  O |  P |  [ |  ] |   \  | END| DEL|
        +--------------------------------------------------------------------------+----+----+
        | CAPSLCK |  A |  S |  D |  F |  G |  H |  J |  K |  L |  ; |  ' |  RETURN | HME|PDUP|
        +--------------------------------------------------------------------------+----+----+
        | LSHIFT   |  Z |  X |  C |  V |  B |  N |  M |  , |  . |  / |   RSHIFT    | UP |PDDN|
        +--------------------------------------------------------------------------+----+----+
        |LCTRL| LGUI|  LALT|            SPACE             |RALT|LCTL| FN1| FN2| DWN| RGT|LEFT|
        +--------------------------------------------------------------------------+----+----+
        */
    [WIN_BASE] = LAYOUT_70_ansi(
        KC_ESC,    KC_1,      KC_2,      KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,      KC_0,      KC_MINS,      KC_EQL,   KC_BSPC,   KC_INS,    RGB_MOD ,
        KC_TAB,    KC_Q,      KC_W,      KC_E,    KC_R,    KC_T,    KC_Y,     KC_U,    KC_I,    KC_O,      KC_P,      KC_LBRC,      KC_RBRC,  KC_BSLS,   KC_END,    KC_DEL  ,
        KC_CAPS,   KC_A,      KC_S,      KC_D,    KC_F,    KC_G,    KC_H,     KC_J,    KC_K,    KC_L,      KC_SCLN,   KC_QUOT,                KC_ENT,    KC_HOME,   KC_PGUP ,
        KC_LSFT,              KC_Z,      KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M,    KC_COMM,   KC_DOT,    KC_SLSH,                KC_RSFT,   KC_UP,     KC_PGDN ,
        KC_LCTL,   KC_LGUI,   KC_LALT,                              KC_SPC,                     KC_RALT,   KC_RCTL,   MO(WIN_FN1),  MO(FN2),  KC_LEFT,   KC_DOWN,   KC_RGHT
    ),

        /*
        +--------------------------------------------------------------------------+----+----+
        |GRV   |BRI| BRI|TASK|FLXP| VAD| VAI|MPRV|MPLY|MNXT|MUTE|VOLD|VOLD|        |    |RTOG|
        +--------------------------------------------------------------------------+----+----+
        |       |    |    |    |    |    |    |    |    |    |    |    |    |      |    |    |
        +--------------------------------------------------------------------------+----+----+
        |         |    |    |    |    |    |    |    |    |    |    |    |         |    |RSPI|
        +--------------------------------------------------------------------------+----+----+
        |          |    |    |    |    |    |    |    |    |    |    |             |RSAI|RSPD|
        +--------------------------------------------------------------------------+----+----+
        |     |     |      |                              |    |    |    |    |RHUD|RSAD|RHUI|
        +--------------------------------------------------------------------------+----+----+
        */
    [WIN_FN1] = LAYOUT_70_ansi(
        KC_GRV,   KC_BRIU,  KC_BRID,  KC_TASK,  KC_FLXP,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  RGB_SPI,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  RGB_SAI,  RGB_SPD,
        _______,  _______,  _______,                                _______,                      _______,  _______,  _______,  _______,  RGB_HUD,  RGB_SAD,  RGB_HUI
    ),

        /*
        +--------------------------------------------------------------------------+----+----+
        | ESC |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = | BACKSP | INS| RGB|
        +--------------------------------------------------------------------------+----+----+
        |  TAB  |  Q |  W |  E |  R |  T |  Y |  U |  I |  O |  P |  [ |  ] |   \  | END| DEL|
        +--------------------------------------------------------------------------+----+----+
        | CAPSLCK |  A |  S |  D |  F |  G |  H |  J |  K |  L |  ; |  ' |  RETURN | HME|PDUP|
        +--------------------------------------------------------------------------+----+----+
        | LSHIFT   |  Z |  X |  C |  V |  B |  N |  M |  , |  . |  / |   RSHIFT    | UP |PDDN|
        +--------------------------------------------------------------------------+----+----+
        |LCTRL| LALT|  LGUI|            SPACE             |RGUI|LCTL| FN1| FN2| DWN| RGT|LEFT|
        +--------------------------------------------------------------------------+----+----+
        */
    [MAC_BASE] = LAYOUT_70_ansi(
        KC_ESC,    KC_1,      KC_2,      KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,      KC_0,      KC_MINS,      KC_EQL,   KC_BSPC,   KC_INS,    RGB_MOD ,
        KC_TAB,    KC_Q,      KC_W,      KC_E,    KC_R,    KC_T,    KC_Y,     KC_U,    KC_I,    KC_O,      KC_P,      KC_LBRC,      KC_RBRC,  KC_BSLS,   KC_END,    KC_DEL  ,
        KC_CAPS,   KC_A,      KC_S,      KC_D,    KC_F,    KC_G,    KC_H,     KC_J,    KC_K,    KC_L,      KC_SCLN,   KC_QUOT,                KC_ENT,    KC_HOME,   KC_PGUP ,
        KC_LSFT,              KC_Z,      KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M,    KC_COMM,   KC_DOT,    KC_SLSH,                KC_RSFT,   KC_UP,     KC_PGDN ,
        KC_LCTL,   KC_LALT,   KC_LGUI,                              KC_SPC,                     KC_RGUI,   KC_RCTL,   MO(MAC_FN1),  MO(FN2),  KC_LEFT,   KC_DOWN,   KC_RGHT
    ),

        /*
        +--------------------------------------------------------------------------+----+----+
        |GRV   |BRI| BRI| MC |FIND| VAD| VAI|MPRV|MPLY|MNXT|MUTE|VOLD|VOLD|        |    |RTOG|
        +--------------------------------------------------------------------------+----+----+
        |       |    |    |    |    |    |    |    |    |    |    |    |    |      |    |    |
        +--------------------------------------------------------------------------+----+----+
        |         |    |    |    |    |    |    |    |    |    |    |    |         |    |RSPI|
        +--------------------------------------------------------------------------+----+----+
        |          |    |    |    |    |    |    |    |    |    |    |             |RSAI|RSPD|
        +--------------------------------------------------------------------------+----+----+
        |     |     |      |                              |    |    |    |    |RHUD|RSAD|RHUI|
        +--------------------------------------------------------------------------+----+----+
        */
    [MAC_FN1] = LAYOUT_70_ansi(
        KC_GRV,   KC_BRIU,  KC_BRID,  KC_MSSN,  KC_FIND,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  RGB_SPI,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  RGB_SAI,  RGB_SPD,
        _______,  _______,  _______,                                _______,                      _______,  _______,  _______,  _______,  RGB_HUD,  RGB_SAD,  RGB_HUI
    ),

        /*
        +--------------------------------------------------------------------------+----+----+
        |RESET | F1| F2 | F3 | F4 | F5 | F6 | F7 | F8 | F9 | F10| F11| F12|        |    |    |
        +--------------------------------------------------------------------------+----+----+
        |       |    |    |    |    |    |    |    |    |    |    |    |    |      |    |    |
        +--------------------------------------------------------------------------+----+----+
        |         |    |    |    |    |    |    |    |    |    |    |    |         |    |    |
        +--------------------------------------------------------------------------+----+----+
        |          |    |    |    |    |    |    |    |    |    |    |             |    |    |
        +--------------------------------------------------------------------------+----+----+
        |     |     |      |                              |    |    |    |    |    |    |    |
        +--------------------------------------------------------------------------+----+----+
        */
    [FN2] = LAYOUT_70_ansi(
        RESET,      KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,   KC_F12,  _______,  _______,  RGB_TOG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,
        _______,  _______,  _______,                               KC_SCASM,                      _______,  _______,  _______,  _______,  _______,  _______,  _______
    ),

};

bool dip_switch_update_user(uint8_t index, bool active){
  switch(index){
    case 0:
      if(active){ //Mac/iOS mode
        layer_move(MAC_BASE);
      }
      else{ // Win/Android mode
        layer_move(WIN_BASE);
      }
      break;
    case 1:
      if(active){ //BT mode
        // do stuff
      }
      else{ //Cable mode
        // do stuff
      }
      break;
  }
  return true;
}

void keyboard_post_init_user(void) {
    debug_enable = true;
    //rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_startup_swirl_animation);
}

// saRcASm MOde
bool tog_sarcasm = false;
bool uppercase = false;
uint8_t prev_upper = 0;
uint8_t prev_lower = 0;
uint8_t prev_mode = 0;
HSV prev_hsv;

bool process_record_sarcasm(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_ENTER && record->event.pressed) {
        uppercase = false;
        return true;
    }

    if (uppercase == false && record->event.pressed)  { // Dont start with an uppercase letter on new line
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
        case KC_SCASM:
            if (record->event.pressed) {
                tog_sarcasm = !tog_sarcasm;

                if (tog_sarcasm) {
                    dprint("Enabling saRCaSm ModE\n");
                    prev_hsv = rgb_matrix_get_hsv();
                    prev_mode = rgb_matrix_get_mode();
                    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_MULTISPLASH);
                    rgb_matrix_sethsv_noeeprom(HSV_YELLOW);
                }
                else {
                    dprint("Disabling saRCaSm ModE\n");
                    rgb_matrix_mode_noeeprom(prev_mode);
                    rgb_matrix_sethsv_noeeprom(prev_hsv.h, prev_hsv.s, prev_hsv.v);
                }

                uppercase = false;
                prev_upper = 0;
                prev_lower = 0;
            }
            return false;
    }

    if (tog_sarcasm) {
        return process_record_sarcasm(keycode, record);
    }

    return true;
}
