// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H

/* ---------------------------
 * Custom OLED Fncs Prototypes
 * ---------------------------
 */
void render_slave_oled(void);
void render_master_oled(void);
void oled_timer_reset(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);

enum custom_keycodes
{
    KC_SCR1 = SAFE_RANGE,
    KC_SCR2,
    KC_SCR3,
    KC_SCR4,
    KC_SCR5
};