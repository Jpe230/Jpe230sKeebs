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
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
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
  return true;
}

extern painter_device_t display;

// bool requires_update = false;
// bool first_render = false;

// void render_tft(void) {
//     if(!requires_update) return;

//     static uint8_t number_of_first_renders = 1;

//     if(number_of_first_renders >= 12)
//     {
//         dprint("Printing\n");
//         qp_rect(display, 0, 0, 239, 239, HSV_RED, true);
//         qp_flush(display);

//         // qp_rect(display, 0, 0, 239, 239, HSV_RED, true);
//         // qp_rect(display, 0, 0, 239, 239, HSV_RED, true);
//         // qp_rect(display, 0, 0, 239, 239, HSV_RED, true);
//         //qp_rect(display, 0, 0, 239, 239, HSV_YELLOW, true);
//         //qp_flush(display);
//         first_render = false;
//         number_of_first_renders--;
//     }

// }

// void housekeeping_task_user(void) {
//     static uint32_t reboot = 0;
//     static uint32_t wait = 0;
//     static bool should_wait = true;

//     if (should_wait){
//         if(timer_elapsed32(wait) > 100) should_wait = false;
//         dprint("Waiting...\n");
//         return;
//     }

//     requires_update = true;
//     render_tft();

//     if (timer_elapsed32(reboot) > 4000) {
//         //reset_keyboard();
//     }
// }

void housekeeping_task_user(void) {
  static uint32_t last_draw = 0;
  static uint32_t i = 0;

  if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
    last_draw = timer_read32();

    // writePin(LCD_RST_PIN, i);
    // writePin(LCD_DC_PIN, i);
    // writePin(LCD_CS_PIN, !i);
    // i = !i;

    qp_rect(display, 100, 100, 130, 130, i, 255, 255, true);
    i++;
    if (i >= 254)
      i = 0;
    // for (int i = 0; i < 50; ++i) {
    //     qp_line(display, 40, i, 50, i, i, 255, 255);
    // }
    qp_flush(display);
  }
}