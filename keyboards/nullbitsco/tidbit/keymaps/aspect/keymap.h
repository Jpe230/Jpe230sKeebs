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

#include QMK_KEYBOARD_H

#ifdef VIA_ENABLE
    #define USER_START USER00
#else
    #define USER_START SAFE_RANGE
#endif

enum MACROPAD_KEYCODES {
    /* Common */
    AP_NEW = USER_START,
    AP_OPEN,
    AP_CLOSE,
    AP_SAVE,
    AP_SAVEAS,
    AP_PRINT,
    AP_QUIT,
    AP_COPY,
    AP_CUT,
    AP_UNDO,
    AP_REDO,
    AP_PASTE,
    AP_SELALL,
    AP_DUPL,
    AP_DESEL,
    AP_SELINV,
    AP_SELLAY,
    AP_ZOOMP,
    AP_ZOOMN,
    AP_FITSCRN,
    AP_ACTUAL,
    AP_GRID,
    AP_GUIDES,
    /* Illustrator */
    AP_GROUP,
    AP_UNGROUP,
    AP_PASTEF,
    AP_PASTEB,
    AP_PASTEUB,
    /* Photoshop */
    AP_LEVELS,
    AP_CURVES,
    AP_COLBAL,
    AP_HUESAT,
    AP_NEWLAY,
    AP_LAYCPY,
    AP_LAYCUT,
    AP_CLIPMSK,
    AP_BRINGF,
    AP_SENDF,
    AP_BRINGB,
    AP_SENDB,
    AP_MERGE,
    AP_UNMERGE,
    /* After Effect */
    AP_TEXT,
    AP_TOOL,
    AP_PINC,
    AP_PIN,
    AP_AE_DIV,
    AP_AE_VOL,
    AP_AE_ME,
    AP_AE_LAYER
};