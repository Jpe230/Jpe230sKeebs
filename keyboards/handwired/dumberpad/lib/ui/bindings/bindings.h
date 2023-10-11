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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#if __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif //__has_include("lvgl.h")
 #include "quantum.h"
    uint8_t qmk_lv_get_bpm(void);
    
    lv_color_hsv_t qmk_lv_rgb_matrix_get_hsv(void);
    void qmk_lv_rgb_matrix_sethsv(uint16_t hue, uint8_t sat, uint8_t val, bool eeprom);

    uint8_t qmk_lv_rgb_matrix_get_speed(void);
    void qmk_lv_rgb_matrix_set_speed(uint8_t speed, bool eeprom);

    uint8_t qmk_lv_rgb_matrix_get_mode(void);
    void qmk_lv_rgb_matrix_mode(uint8_t mode, bool eeprom);

    void qmk_lv_tap_keycode(int keycode);

    void qmk_lv_set_layer(uint8_t layer);
    uint8_t qmk_lv_geT_layer(void);
#ifdef __cplusplus
} /*extern "C"*/
#endif

