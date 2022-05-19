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
#include <stdio.h>
#include <string.h>

#ifdef VIA_ENABLE
    #define USER_START USER00
#else
    #define USER_START SAFE_RANGE
#endif

/* -----------------------
 * Custom Keycodes Region
 * -----------------------
 */
enum JP_KEYCODES {
    /* Teams */
    TM_AVC = USER_START, // Accept Video Call
    TM_AAC,              // Accept Audio Call
    TM_DC,               // Decline Call
    TM_EC,               // End Call
    TM_MUT,              // Mute
    TM_VID,              // Toggle Video
    /* EDGE  */
    ED_ZOP,              // Zoom positive
    ED_ZON,              // Zoom Negative
    ED_NEWT,             // New Tab
    ED_NTAB,             // Previous Tab
    ED_PTAB,             // Next Tab
    ED_CTAB,             // Close Tab
    ED_RTAB,             // Restore Tabs
    /* VScode  */
    VS_SB,               // Side Bar
    VS_COM,              // Comment
    VS_UCOM,             // Uncomment
    VS_NCUR,             // Next Cursor
    VS_BCUR,             // Prev Cursor
    /* Visual Studio */
    VS_ZOP,              // Zoom Positive
    VS_ZON,              // Zoom Negative
    /* Discord */
    DC_NUCM,             // Next Unread Channel Message
    DC_PUCM,             // Prev Unread Channel Message
    DC_AC,               // Accept Call
    /* Conf */
    MC_OLED,             // Toggle OLED
    MC_INDI,             // Show Indicators
    MC_MSKI,             // Mask Indicators
    MC_SHWA,             // Show Anim
    MC_ODEF,             // Select Default OLED
    MC_OBNC,             // Select Bongo Cat OLED
    MC_OLOG,             // Select Logo OLED
};

#define __xxx__ KC_NO

/* -----------------------
 * Custom Layers Region
 * -----------------------
 */
enum JP_LAYERS{
    MEDIA = 0,
    TEAMS,
    EDGE,
    VSCODE,
    VS,
    DISCORD,
    CONFS,
    EMPTLAYER
};


/* -----------------------
 * Custom Layers Prototypes
 * -----------------------
 */
void handle_layer_move(uint8_t layer);

/* -----------------------
 * Layers Defines
 * -----------------------
 */
#define ___ns____ ""

/* -----------------------
 * Custom OLED Region
 * -----------------------
 */
enum OLED_STATES{
    DEFAULT_OLED = 0,
    BONGO_CAT,
    LOGO
};

/* -----------------------
 * OLED Function Prototypes
 * -----------------------
 */
uint8_t get_current_wpm(void);
void fake_wpm_increment(void);
void fake_wpm_decay(void);
void render_short_array_pos(const uint16_t* frame, uint8_t x, uint8_t y, uint8_t width);
void render_short_array(const uint16_t* frame);
void render_anim(void);
void render_wpm(void);
void render_logo(void);
void render_bongo_cat(void);

extern uint8_t oled_state;
extern bool indicator_oled_state[MATRIX_ROWS][MATRIX_COLS];

/* -----------------------
 * OLED Defines
 * -----------------------
 */
#define CHARS_PER_LINE 21
#define CHARS_PER_KEY 7
#define decay_every_x 250
#define increment_amount 15

/* -----------------------
 * Custom Indicators Region
 * -----------------------
 */
enum INDICATOR_STATES{
    DEFAULT_INDI = 0,
    MASK_ANIM,
    SHOW_ANIM
};

/* -----------------------
 * Indicators Stuff.
 * -----------------------
 */
typedef union Color
{
    unsigned int hex;
    struct { unsigned char b, g, r; };
} HexColor;

extern bool rgb_matrix_idling;
extern uint8_t indicator_state;

#define _x______ 0

/* -----------------------
 * Custom Configuration
 * -----------------------
 */
#define SHOW_DEFAULT 1500 // in ms
#define RGB_IDLE_TIMEOUT 300000
