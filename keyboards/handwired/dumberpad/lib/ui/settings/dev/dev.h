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

#include "../../ui_conf.h"

#ifdef USE_WIN32DRV
    #define QK_BOOT 0
    #define DB_TOGG 1
    #define EE_CLR  1
#endif

//////////////////////////////////////////////////////////////
// Actions for the menu knob
void dev_qk_boot(void);
void dev_dbg_toggle(void);
void dev_clr_eeprom(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif
