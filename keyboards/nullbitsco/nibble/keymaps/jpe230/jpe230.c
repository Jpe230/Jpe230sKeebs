// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef RGBLIGHT_ENABLE
#undef RGB_DI_PIN
#define RGB_DI_PIN RGBLIGHT_DI_PIN

#define ws2812_setleds ws2812_rgb_setleds
#define ws2812_init ws2812_rgb_init

#include "ws2812_vendor.c"

void rgblight_call_driver(LED_TYPE *start_led, uint8_t num_leds) {
  ws2812_setleds(start_led, num_leds);
}
#endif

#if defined(RGB_MATRIX_ENABLE)
led_config_t g_led_config = {{{0}}, {{1, 1}}, {4}};
#endif

void set_bitc_LED(uint8_t mode) {};