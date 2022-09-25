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

#include "dumberpad.h"
#include "lib/ui/ui.h"
#include "lib/ui/settings/screensaver/screensaver.h"
#include "qp_lvgl.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {{// Key Matrix to LED Index
                              {NO_LED, 0, 1, 2, 3},
                              {NO_LED, 7, 6, 5, 4},
                              {NO_LED, 8, 9, 10, 11},
                              {NO_LED, 15, 14, 13, 12}},
                             {// LED Index to Physical Position
                              {0, 0},
                              {75, 0},
                              {149, 0},
                              {224, 0},

                              {224, 21},
                              {149, 21},
                              {75, 21},
                              {0, 21},

                              {0, 43},
                              {75, 43},
                              {149, 43},
                              {224, 43},

                              {224, 64},
                              {149, 64},
                              {75, 64},
                              {0, 64}},
                             {// LED Index to Flag
                              4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}};
#endif

static int8_t rotations = 0;
painter_device_t display;
static lv_group_t *g;
bool pressed_encoder = false;
bool lvgl_control = false;

bool encoder_update_kb(uint8_t index, bool clockwise) {
    dprintf("lvgl_control = %d, Rotations = %d\n", lvgl_control, rotations);

    if (lvgl_control && index == 0) {
        if (clockwise) {
            rotations++;
        } else {
            rotations--;
        }
        dprintf("Rotations: %d\n", rotations);
        return false;
    }

    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }

    return true;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    
    if(lvgl_control){
        if(record->event.key.col == 0 && record->event.key.row == 3) {
            if (record->event.pressed) {
                pressed_encoder = true;
            } else {
                pressed_encoder = false;
            }

            return false;
        }
    }
    
    switch (keycode) {
        case ENA_LVGL:
            if (record->event.pressed && !lvgl_control) {
                lvgl_control = true;
                hide_screensaver();
            }
            return false;
    }

  return true;
}

void encoder_read_2(lv_indev_drv_t *drv, lv_indev_data_t *data) {
    data->enc_diff = rotations;
    rotations = 0;

    if (pressed_encoder)
        data->state = LV_INDEV_STATE_PRESSED;
    else
        data->state = LV_INDEV_STATE_RELEASED;
}

void keyboard_post_init_kb(void) {
    debug_enable = true;

    display = qp_gc9a01_make_spi_device(
        QUANTUM_PAINTER_LVGL_DISPLAY_WIDTH, QUANTUM_PAINTER_LVGL_DISPLAY_HEIGHT,
        LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 2, 0);
    qp_init(display, QP_ROTATION_180);

    // Turn on the LCD and clear the display
    qp_power(display, true);
    qp_rect(display, 0, 0, QUANTUM_PAINTER_LVGL_DISPLAY_WIDTH - 1,
            QUANTUM_PAINTER_LVGL_DISPLAY_HEIGHT - 1, HSV_BLACK, true);
    qp_flush(display);

    // Start LVGL
    qp_lvgl_start(display);

    // Register Encoder and create default group
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_ENCODER;
    indev_drv.read_cb = encoder_read_2;
    lv_indev_drv_register(&indev_drv);

    g = lv_group_create();
    lv_group_set_default(g);
    lv_indev_t *cur_drv = NULL;
    for (;;) {
        cur_drv = lv_indev_get_next(cur_drv);
        if (!cur_drv) {
            break;
        }

        if (cur_drv->driver->type == LV_INDEV_TYPE_KEYPAD) {
            lv_indev_set_group(cur_drv, g);
        }

        if (cur_drv->driver->type == LV_INDEV_TYPE_ENCODER) {
            lv_indev_set_group(cur_drv, g);
        }
    }

    // Run user defined LVGL specific code:
    main_screen_init();

    // Allow for user post-init
    keyboard_post_init_user();

    show_screensaver();
}

void disable_lvgl() {
    lvgl_control = false;
}