MCU = RP2040
BOOTLOADER = rp2040

RGB_MATRIX_ENABLE = yes
WS2812_DRIVER = vendor
OLED_ENABLE = yes
OLED_DRIVER  = SSD1306
SERIAL_DRIVER  = vendor
DEBUG_MATRIX_SCAN_RATE_ENABLE = yes
WPM_ENABLE = yes
CONSOLE_ENABLE = yes
VIA_ENABLE = yes

# Project specific files
SRC += \
    process_record.c \
	oled/oled_handler.c \
	oled/master/oled_master_handler.c \
	oled/master/indicators_up.c \
	oled/master/indicators_down.c \
	oled/slave/oled_slave_handler.c \
	oled/slave/ocean_dream.c