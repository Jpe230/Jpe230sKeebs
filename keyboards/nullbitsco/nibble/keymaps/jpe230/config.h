// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later#undef RGB_DI_PIN

#define RGBLIGHT_DI_PIN E6

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 1

#undef RGB_DI_PIN
#define RGB_DI_PIN 17U
#define RGB_MATRIX_LED_COUNT 1
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 20
#define RGB_MATRIX_DISABLE_KEYCODES

#define RGB_MATRIX_STARTUP_HUE 137
#define RGB_MATRIX_STARTUP_SAT 255
#define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS

#define RGBLIGHT_DEFAULT_HUE 137
#define RGBLIGHT_DEFAULT_SAT 255

#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_DISABLE_TIMEOUT 600000

#define ENABLE_COMPILE_KEYCODE
#define DEBUG_MATRIX_SCAN_RATE

