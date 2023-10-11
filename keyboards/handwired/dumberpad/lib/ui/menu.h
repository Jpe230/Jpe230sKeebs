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

typedef enum {
    JP_NEXT_ITEM,
    JP_PREV_ITEM,
    JP_WIDGET
} menu_action;

typedef struct _menu_obj_t {
    char value[15];
    char symbol[15];
    uint8_t action;
    void (*do_action)(void);
    uint8_t position;
    struct _menu_obj_t* parent;
    struct _menu_obj_t* next_sibling;
    struct _menu_obj_t* first_child;
} menu_obj_t;

menu_obj_t root;
void init_menu(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

