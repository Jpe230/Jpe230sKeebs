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

#ifdef VIA_ENABLE
  #define USER_START USER00
#else
  #define USER_START SAFE_RANGE
#endif
