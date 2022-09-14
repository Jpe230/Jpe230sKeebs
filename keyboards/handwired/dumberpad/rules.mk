# MCU name
MCU = RP2040
# Bootloader selection
BOOTLOADER = rp2040
# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
# AUDIO_DRIVER = pwm_software
ENCODER_ENABLE = yes
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
WS2812_DRIVER = vendor

QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_LVGL_INTEGRATION = yes
QUANTUM_PAINTER_DRIVERS = gc9a01_spi

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pimoroni_trackball

LTO_ENABLE = yes # For whatever reason the compiler doesnt like compiling LVGL without optimizations

# Project specific files
SRC += lib/ui/ui.c

# Note: Not needed QP already add this for us
# QUANTUM_LIB_SRC += spi_master.c
