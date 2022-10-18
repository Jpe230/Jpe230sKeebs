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
                    KC_7,      KC_8,     KC_9,     KC_PMNS,
                    KC_4,      KC_5,     KC_6,     KC_PPLS,
                    KC_1,      KC_2,     KC_3,     KC_A,
        KC_MUTE,    TT(1),     KC_0,     KC_N,     KC_Z
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
        ENA_LVGL,   _______,    RGB_SPD,     RGB_SPI,      KC_NO
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

extern LED_TYPE rgb_matrix_ws2812_array[DRIVER_LED_TOTAL];

#define TRACKBALL_LED_IDX 15

void trackball_set_rgb(uint8_t r,uint8_t g,uint8_t b, bool adjust_brightness) {


    /* Board uses 127 as max value, multiply the values otherwise
     * the trackball will be dim
     */
    if(adjust_brightness){
        r <<= 1;
        g <<= 1;
        b <<= 1;
    }

    /* Determine lowest value in all three colors, put that into
     * the white channel and then shift all colors by that amount
     */
    uint8_t w = MIN(r, MIN(g, b));
    r -= w;
    g -= w;
    b -= w;

    pimoroni_trackball_set_rgbw(r, g, b, w);
}

void rgb_matrix_indicators_user(void) {
    /* Obtain LED values and multiply it by 2 */
    uint8_t r =  rgb_matrix_ws2812_array[TRACKBALL_LED_IDX].r;
    uint8_t g =  rgb_matrix_ws2812_array[TRACKBALL_LED_IDX].g;
    uint8_t b =  rgb_matrix_ws2812_array[TRACKBALL_LED_IDX].b;

    /* Send to trackball */
    trackball_set_rgb(r, g, b, true);
}