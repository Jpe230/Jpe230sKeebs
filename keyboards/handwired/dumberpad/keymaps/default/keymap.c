#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
            BASE LAYER - Num Pad
    /-----------------------------------------------------`
    |             |    7    |    8    |    9    |    -    |
    |             |---------|---------|---------|---------|
    |             |    4    |    5    |    6    |    +    |
    |             |---------|---------|---------|---------|
    |             |    1    |    2    |    3    |    *    |
    |-------------|---------|---------|---------|---------|
    |    Mute     |  TT(1)  |    0    |         |  Enter  |
    \-----------------------------------------------------'
    */
    [0] = LAYOUT(
                    KC_P7,      KC_P8,    KC_P9,             KC_PMNS,
                    KC_P4,      KC_P5,    KC_P6,             KC_PPLS,
                    KC_P1,      KC_P2,    KC_P3,             KC_PAST,
        KC_MUTE,    TT(1),      KC_P0,    _______,           KC_ENTER
    ),
    /*
            SUB LAYER  - RGB controls, Modes on encoder
    /-----------------------------------------------------`
    |             | On/Off  | Bright- | Bright+ |  Reset  |
    |             |---------|---------|---------|---------|
    |             |         | Hue-    | Hue+    |         |
    |             |---------|---------|---------|---------|
    |             |         | Sat-    | Sat+    |         |
    |-------------|---------|---------|---------|---------|
    |             |  TT(1)  | Effect- | Effect+ |         |
    \-----------------------------------------------------'
    */
    [1] = LAYOUT(
                    RGB_TOG,    RGB_VAD,     RGB_VAI,      QK_BOOT,
                    KC_NO,      RGB_HUD,     RGB_HUI,      KC_NO,
                    KC_NO,      RGB_SAD,     RGB_SAI,      KC_NO,
        KC_NO,      _______,    RGB_SPD,     RGB_SPI,      KC_NO
    ),
};
// clang-format on

bool encoder_update_user(uint8_t index, bool clockwise) {
  switch (get_highest_layer(layer_state)) {
  case 0:
    // main layer, volume
    if (clockwise) {
      tap_code_delay(KC_VOLU, 10);
    } else {
      tap_code_delay(KC_VOLD, 10);
    }
    break;
  default:
    // rgb control layer, effects
    if (clockwise) {
      rgblight_step();
    } else {
      rgblight_step_reverse();
    }
    break;
  }
  return false;
}
