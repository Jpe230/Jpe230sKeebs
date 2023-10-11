// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later#undef RGB_DI_PIN
#define RGBLIGHT_DI_PIN E6

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 1

#define RGBLIGHT_DEFAULT_HUE 137
#define RGBLIGHT_DEFAULT_SAT 255
#define RGB_DISABLE_TIMEOUT 600000

#define ENABLE_COMPILE_KEYCODE

#define FORCE_NKRO

/* SPI pins */
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN 2U
#define SPI_MOSI_PIN 3U
#define SPI_MISO_PIN 0U

// /* LCD Configuration */
#define LCD_RST_PIN 6U
#define LCD_DC_PIN 0U
#define LCD_CS_PIN 1U
#define LCD_BLK_PIN 5U

#include "config/halconf.h"
#include "config/mcuconf.h"