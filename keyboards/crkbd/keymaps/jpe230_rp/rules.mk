SRC += oled/master/number_graphics.c custom_oled.c

MCU = RP2040
BOOTLOADER = rp2040

RGB_MATRIX_ENABLE = yes
WS2812_DRIVER     = vendor
OLED_ENABLE       = yes
OLED_DRIVER       = SSD1306
SERIAL_DRIVER     = vendor
VIA_ENABLE        = yes
EEPROM_DRIVER     = transient
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pimoroni_trackball

DEBUG_MATRIX_SCAN_RATE_ENABLE = yes
ALLOW_WARNINGS    = yes
PICO_INTRINSICS_ENABLED = no # ATM Unsupported by ChibiOS!
