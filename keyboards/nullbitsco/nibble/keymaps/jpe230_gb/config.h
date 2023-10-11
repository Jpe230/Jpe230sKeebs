// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later#undef RGB_DI_PIN

/* Allow for more space for Flash (for GB ROM) + EEPROM to save our data*/
#undef  PICO_FLASH_SIZE_BYTES
#define PICO_FLASH_SIZE_BYTES (8 * 1024 * 1024) 
#define WEAR_LEVELING_BACKING_SIZE (128 * 1024) 
#define WEAR_LEVELING_LOGICAL_SIZE (64 * 1024)

/* Boot maigic */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 1

/* RGB LIGHT Stuff*/
#define RGBLIGHT_DEFAULT_HUE 137
#define RGBLIGHT_DEFAULT_SAT 255
#define RGB_DISABLE_TIMEOUT 600000
#define RGBLIGHT_DI_PIN E6

/* Custom features */
#define ENABLE_COMPILE_KEYCODE
#define FORCE_NKRO
// #define DEBUG_MATRIX_SCAN_RATE

/* SPI pins */
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN 2U
#define SPI_MOSI_PIN 3U
#define SPI_MISO_PIN 0U

/* LCD Configuration */
#define LCD_RST_PIN 6U
#define LCD_DC_PIN 0U
#define LCD_CS_PIN 1U
#define LCD_BLK_PIN 5U

/* Include ChibiOS configs */
#include "config/halconf.h"
#include "config/mcuconf.h"

/* Game settings */
#define QP_SCR1_X 320
#define QP_SCR1_Y 170
