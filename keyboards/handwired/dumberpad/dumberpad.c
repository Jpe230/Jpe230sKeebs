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
#include "qp_lvgl.h"
#include "lib/ui/ui.h"

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

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    switch (get_highest_layer(layer_state)) {
        case 0:
            // main layer, volume
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
    }
    return true;
}
#endif

painter_device_t display;

void keyboard_post_init_kb(void) {
    debug_enable = true;

    display = qp_gc9a01_make_spi_device(QUANTUM_PAINTER_LVGL_DISPLaY_WIDTH, QUANTUM_PAINTER_LVGL_DISPLaY_HEIGHT, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 4, 0);
    qp_init(display, QP_ROTATION_180);
    
    // Turn on the LCD and clear the display
    qp_power(display, true);
    qp_rect(display, 0, 0, QUANTUM_PAINTER_LVGL_DISPLaY_WIDTH - 1, QUANTUM_PAINTER_LVGL_DISPLaY_HEIGHT - 1, HSV_BLACK, true);
    qp_flush(display);

    // Start LVGL
    qp_lvgl_start(display);
    
    // Run user defined LVGL specific code:
    ui_init();

    // Allow for user post-init
    keyboard_post_init_user();
}