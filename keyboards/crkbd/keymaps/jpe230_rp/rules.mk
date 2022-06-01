MCU = RP2040
BOOTLOADER = rp2040

RGB_MATRIX_ENABLE = yes
WS2812_DRIVER     = vendor
OLED_ENABLE       = yes
OLED_DRIVER       = SSD1306
SERIAL_DRIVER     = vendor
VIA_ENABLE        = yes
EEPROM_DRIVER     = transient

ALLOW_WARNINGS    = yes
PICO_INTRINSICS_ENABLED = no # ATM Unsupported by ChibiOS!
