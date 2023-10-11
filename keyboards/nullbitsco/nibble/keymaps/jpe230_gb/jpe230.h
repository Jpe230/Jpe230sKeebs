// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#pragma once

void gb_main(void);
void game_loop(void);

extern bool game_keys[16];
extern painter_device_t display;

enum custom_keycodes {
  JIGGLER = SAFE_RANGE,
  SCR_ON,
  SCR_OFF,
  KC_SCR1,
  KC_SCR2,
  KC_SCR3,
  KC_SCR4,
  KC_SCR5,
  GKEY_U,
  GKEY_R,
  GKEY_D,
  GKEY_L,
  GKEY_A,
  GKEY_B,
  GKEY_ST,
  GKEY_SL,
  GKEY_SP
};


enum layers { BASE, FN1, FN2, FN3 };