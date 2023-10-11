// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifndef VIA_ENABLE
#    ifndef RGB_MATRIX_TOGGLE
#        define RGB_MATRIX_TOGGLE KC_F15
#    endif
#else
#    ifndef RGB_MATRIX_TOGGLE
#        define RGB_MATRIX_TOGGLE USER10
#    endif
#endif

#define R_M_TOG RGB_MATRIX_TOGGLE

enum custom_keycodes {
  JIGGLER = SAFE_RANGE,
  SCR_ON,
  SCR_OFF,
  KC_SCR1,
  KC_SCR2,
  KC_SCR3,
  KC_SCR4,
  KC_SCR5
};