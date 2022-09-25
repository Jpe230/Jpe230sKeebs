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


/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 5

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { GP29, GP28, GP27, GP26 }
#define MATRIX_COL_PINS { GP5, GP6, GP7, GP8, GP9 }
#define DIODE_DIRECTION COL2ROW


/* Encoders */
#define ENCODERS_PAD_A { GP4 }
#define ENCODERS_PAD_B { GP19 }
#define ENCODER_RESOLUTION 4

/* Bootmagic lite */
/* (Phold down rotary encoder pushbutton while plugging in to enter bootloader) */
#define BOOTMAGIC_LITE_ROW 3
#define BOOTMAGIC_LITE_COLUMN 0

/* Double tap the side button to enter bootloader */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
// #define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP13
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

/* I2C pins */
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP12
#define I2C1_SCL_PIN GP13

/* SPI pins */
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP18
#define SPI_MOSI_PIN GP3
#define SPI_MISO_PIN GP20

/* LCD Configuration */
#define LCD_RST_PIN GP0
#define LCD_DC_PIN GP20
#define LCD_CS_PIN GP10

#ifndef QUANTUM_PAINTER_LVGL_DISPLAY_WIDTH
#define QUANTUM_PAINTER_LVGL_DISPLAY_WIDTH 240
#endif

#ifndef QUANTUM_PAINTER_LVGL_DISPLAY_HEIGHT
#define QUANTUM_PAINTER_LVGL_DISPLAY_HEIGHT 240
#endif

#define QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE 128

#define WPM_UNFILTERED
#define WPM_SAMPLE_SECONDS 1
#define WPM_SAMPLE_PERIODS 15
#define WPM_ESTIMATED_WORD_SIZE 4

#ifdef RGB_MATRIX_ENABLE

     /* RGB Defines */
#    define RGB_DI_PIN GP2
#    define DRIVER_LED_TOTAL 16
#    define RGBLED_NUM 16
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#    define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS

     /* Enable Framebuffer and keypress effects */
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_MATRIX_KEYPRESSES

#    define ENABLE_RGB_MATRIX_ALPHAS_MODS
#    define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_BREATHING
#    define ENABLE_RGB_MATRIX_BAND_SAT
#    define ENABLE_RGB_MATRIX_BAND_VAL
#    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#    define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#    define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#    define ENABLE_RGB_MATRIX_CYCLE_ALL
#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#    define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#    define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#    define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#    define ENABLE_RGB_MATRIX_DUAL_BEACON
#    define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#    define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#    define ENABLE_RGB_MATRIX_RAINDROPS
#    define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#    define ENABLE_RGB_MATRIX_HUE_BREATHING
#    define ENABLE_RGB_MATRIX_HUE_PENDULUM
#    define ENABLE_RGB_MATRIX_HUE_WAVE
#    define ENABLE_RGB_MATRIX_PIXEL_RAIN
#    define ENABLE_RGB_MATRIX_PIXEL_FLOW
#    define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#    define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#    define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#    define ENABLE_RGB_MATRIX_SPLASH
#    define ENABLE_RGB_MATRIX_MULTISPLASH
#    define ENABLE_RGB_MATRIX_SOLID_SPLASH
#    define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif
