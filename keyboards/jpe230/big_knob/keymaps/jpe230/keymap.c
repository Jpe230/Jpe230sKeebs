// Copyright 2023 jpe230 (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "lcd/gfx.h"

enum {
    LY0 = 0,
    LY1,
    LY2,
    LY3,
};

const char *layer_text[] = {
    "Volume +-",
    "Playback",
    "Scrubbing",
    "Brightness Monitor"
};

const HSV layer_colors[] = {
    {RGB_LY0},
    {RGB_LY1},
    {RGB_LY2},
    {RGB_LY3}
};

tap_dance_action_t tap_dance_actions[] = {
    [LY0]  = ACTION_TAP_DANCE_LAYER_MOVE(KC_MUTE, LY1),
    [LY1]  = ACTION_TAP_DANCE_LAYER_MOVE(KC_MPLY, LY2),
    [LY2]  = ACTION_TAP_DANCE_LAYER_MOVE(KC_MPLY, LY3),
    [LY3]  = ACTION_TAP_DANCE_LAYER_MOVE(KC_MUTE, LY0),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LY0] = LAYOUT_ortho_1x1(
        TD(LY0)
    ),
    [LY1] = LAYOUT_ortho_1x1(
        TD(LY1)
    ),
    [LY2] = LAYOUT_ortho_1x1(
        TD(LY2)
    ),
    [LY3] = LAYOUT_ortho_1x1(
        TD(LY3)
    ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LY0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [LY1] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [LY2] = { ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [LY3] = { ENCODER_CCW_CW(KC_F23,  KC_F24)  },
};
#endif

void rgblight_setpackedhsv(HSV hsv){
    uint8_t h = hsv.h;
    uint8_t s = hsv.s;
    uint8_t v = hsv.v;

    rgblight_sethsv_noeeprom(h,s,v);
}

extern painter_device_t lcd;
void keyboard_post_init_user(void) {
    if(qp_lvgl_attach(lcd))
    {
        init_layer();
        layer_state_set_user(0);
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t curr_layer = get_highest_layer(state);
    if(curr_layer > LY3)
    {
        return state;
    }

    rgblight_setpackedhsv(layer_colors[curr_layer]);
    set_layer(layer_text[curr_layer], layer_colors[curr_layer]);
    return state;
}

void lights_suspend_user(void) {
    layer_move(0);
}

static uint16_t key_timer;
bool reset_layer = false;

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    key_timer = timer_read();
    if (!reset_layer) {
        return;
    }
    reset_layer = false;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    key_timer = timer_read();
    if (!reset_layer) {
        return true;
    }
    reset_layer = false;
    return true;
}

void housekeeping_task_user(void) {
    if (!reset_layer && timer_elapsed(key_timer) > LIGHTS_TIMEOUT - 50) {
        reset_layer = true;
        layer_move(0);
    }
}
