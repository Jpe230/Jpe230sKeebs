// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifndef VIA_ENABLE
#    ifndef RGB_MATRIX_TOGGLE
#        define RGB_MATRIX_TOGGLE KC_F15
#    endif
#    ifndef RGB_MATRIX_MODE_INC
#        define RGB_MATRIX_MODE_INC KC_F16
#    endif
#    ifndef RGB_MATRIX_MODE_DEC
#        define RGB_MATRIX_MODE_DEC KC_F17
#    endif
#    ifndef RGB_MATRIX_HUE_INC
#        define RGB_MATRIX_HUE_INC KC_F18
#    endif
#    ifndef RGB_MATRIX_HUE_DEC
#        define RGB_MATRIX_HUE_DEC KC_F19
#    endif
#    ifndef RGB_MATRIX_SAT_INC
#        define RGB_MATRIX_SAT_INC KC_F20
#    endif
#    ifndef RGB_MATRIX_SAT_DEC
#        define RGB_MATRIX_SAT_DEC KC_F21
#    endif
#    ifndef RGB_MATRIX_VAL_INC
#        define RGB_MATRIX_VAL_INC KC_F22
#    endif
#    ifndef RGB_MATRIX_VAL_DEC
#        define RGB_MATRIX_VAL_DEC KC_F23
#    endif
#else
#    ifndef RGB_MATRIX_TOGGLE
#        define RGB_MATRIX_TOGGLE USER00
#    endif
#    ifndef RGB_MATRIX_MODE_INC
#        define RGB_MATRIX_MODE_INC USER01
#    endif
#    ifndef RGB_MATRIX_MODE_DEC
#        define RGB_MATRIX_MODE_DEC USER02
#    endif
#    ifndef RGB_MATRIX_HUE_INC
#        define RGB_MATRIX_HUE_INC USER03
#    endif
#    ifndef RGB_MATRIX_HUE_DEC
#        define RGB_MATRIX_HUE_DEC USER04
#    endif
#    ifndef RGB_MATRIX_SAT_INC
#        define RGB_MATRIX_SAT_INC USER05
#    endif
#    ifndef RGB_MATRIX_SAT_DEC
#        define RGB_MATRIX_SAT_DEC USER06
#    endif
#    ifndef RGB_MATRIX_VAL_INC
#        define RGB_MATRIX_VAL_INC USER07
#    endif
#    ifndef RGB_MATRIX_VAL_DEC
#        define RGB_MATRIX_VAL_DEC USER08
#    endif
#endif

#define R_M_TOG RGB_MATRIX_TOGGLE
#define R_M_MOD RGB_MATRIX_MODE_INC
#define R_M_RMOD RGB_MATRIX_MODE_DEC
#define R_M_HUI RGB_MATRIX_HUE_INC
#define R_M_HUD RGB_MATRIX_HUE_DEC
#define R_M_SAI RGB_MATRIX_SAT_INC
#define R_M_SAD RGB_MATRIX_SAT_DEC
#define R_M_VAI RGB_MATRIX_VAL_INC
#define R_M_VAD RGB_MATRIX_VAL_DEC
