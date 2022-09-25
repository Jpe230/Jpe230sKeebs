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

#include "bindings.h"
#include "../ui_conf.h"

uint8_t qmk_lv_get_bpm(void) {
    uint8_t wpm = 0;

#ifdef USE_WIN32DRV
    wpm = lv_rand(0, 200);
#else
    wpm = get_current_wpm();
#endif
    dprintf("WPM: %d\n", wpm);
    return wpm;
}

lv_color_hsv_t qmk_lv_rgb_matrix_get_hsv(void) {
    lv_color_hsv_t col_hsv = {0, 0, 0};
    
#ifdef USE_WIN32DRV
    col_hsv.h = lv_rand(0, 255);
    col_hsv.s = lv_rand(0, 255);
    col_hsv.v = lv_rand(0, 255);
#else
    col_hsv.h = rgb_matrix_get_hue();
    col_hsv.s = rgb_matrix_get_sat();
    col_hsv.v = (uint8_t)(((float)(rgb_matrix_get_val() / 150.0)) * 255.0); // Scale up brightness
#endif

    return col_hsv;
}

void qmk_lv_rgb_matrix_sethsv(uint16_t hue, uint8_t sat, uint8_t val, bool eeprom) {
#ifdef USE_WIN32DRV
    printf("rgb matrix set hsv [%s]: %u,%u,%u\n", (eeprom) ? "EEPROM" : "NOEEPROM", hue, sat, val);
#else
    val = (uint8_t)(((float)(val / 255.0)) * 150.0); // Scale down brightness
    if (eeprom)
        rgb_matrix_sethsv(hue, sat, val);
    else
        rgb_matrix_sethsv_noeeprom(hue, sat, val);
#endif 
}

uint8_t qmk_lv_rgb_matrix_get_speed(void) {
    uint8_t speed = 0;
    
#ifdef USE_WIN32DRV
    speed = lv_rand(0, 255);
#else
    speed = rgb_matrix_get_speed();
#endif

    return speed;
}
void qmk_lv_rgb_matrix_set_speed(uint8_t speed, bool eeprom) {
#ifdef USE_WIN32DRV
    printf("rgb matrix set speed [%s]: %u\n", (eeprom) ? "EEPROM" : "NOEEPROM", speed);
#else
    if (eeprom)
        rgb_matrix_set_speed(speed);
    else
        rgb_matrix_set_speed_noeeprom(speed);
#endif
}

uint8_t qmk_lv_rgb_matrix_get_mode(void) {
    uint8_t mode = 0;
    
#ifdef USE_WIN32DRV
    mode = lv_rand(0, 42);
#else
    mode = rgb_matrix_get_mode();
#endif
    
    return mode;
}

void qmk_lv_rgb_matrix_mode(uint8_t mode, bool eeprom) {
#ifdef USE_WIN32DRV
    printf("rgb matrix mode [%s]: %u\n", (eeprom) ? "EEPROM" : "NOEEPROM", mode);
#else
    if (eeprom)
        rgb_matrix_mode(mode);
    else
        rgb_matrix_mode_noeeprom(mode);
#endif
}

void qmk_lv_tap_keycode(int keycode) {
#ifdef USE_WIN32DRV
    printf("tap keycode: %u\n", keycode);
#else
    switch(keycode){
        case QK_BOOT:
            reset_keyboard();
            break;
        case DB_TOGG:
            debug_enable ^= 1;
            break;
        case EE_CLR:
            eeconfig_disable();
            soft_reset_keyboard();
            break;
    }
#endif
}

void qmk_lv_set_layer(uint8_t layer) {
#ifdef USE_WIN32DRV
    printf("set layer: %u\n", layer);
#else
    layer_move(layer);
#endif
}

uint8_t qmk_lv_geT_layer() {
    uint8_t layer = 0;
#ifdef USE_WIN32DRV
    layer = lv_rand(0, 3);
#else
    layer = get_highest_layer(layer_state | default_layer_state);
#endif
    return layer;
}
