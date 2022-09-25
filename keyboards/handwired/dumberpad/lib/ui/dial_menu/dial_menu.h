﻿/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

    #include "../menu.h"

    //////////////////////////////////////////////////////////////
    // Initialization
    void init_dial_menu(lv_obj_t* screen);
    void create_dial_menu(lv_obj_t* screen, menu_obj_t* menu_root);


    //////////////////////////////////////////////////////////////
    // API
    void dial_menu_set_label_text(const char* value);
    void dial_menu_set_label_text_fml(const char* format, uint16_t value);
    //void dial_menu_reset_label_text(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

