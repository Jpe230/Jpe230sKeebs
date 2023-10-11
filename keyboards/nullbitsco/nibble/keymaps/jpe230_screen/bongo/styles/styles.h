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
#include "../ui_conf.h"

    #ifdef USE_WIN32DRV

        #define LV_STYLE_INIT(var_name, prop_array)                             \
            lv_style_t var_name = {                                             \
                .v_p = { .const_props = prop_array },                           \
                .has_group = 0xFF,                                              \
                .prop1 = LV_STYLE_PROP_ANY,                                     \
                .prop_cnt = (sizeof(prop_array) / sizeof((prop_array)[0])),     \
            }
    #else
        #define LV_STYLE_INIT(var_name, prop_array) lv_style_t var_name = { .v_p = { .const_props = prop_array }, .has_group = 0xFF, .is_const = 1 }
    #endif

    #define C_LV_STYLE_PROP_INV { .prop = LV_STYLE_PROP_INV, .value = {0} },

    //////////////////////////////////////////////////////////////
    // Main Screen Styles
    lv_style_t style_main_screen;

#ifdef __cplusplus
} /*extern "C"*/
#endif
