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
QUANTUM_PAINTER_LVGL_USE_CUSTOM_CONF = yes
QUANTUM_PAINTER_DRIVERS = gc9a01_spi

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pimoroni_trackball
WPM_ENABLE = yes

LTO_ENABLE = yes # For whatever reason the compiler doesnt like compiling LVGL without optimizations

OPT_DEFS += -DTESTING

# Project specific files

SRC += lib/ui/custom-widgets/lv_custom_colorwheel.c lib/ui/widgets/bpm.c lib/ui/layers/layers.c lib/ui/styles/styles.c lib/ui/assets/sama.c lib/ui/assets/badge-dark.c lib/ui/settings/screensaver/screensaver.c lib/ui/settings/appr/layer/layer.c lib/ui/settings/appr/img/img.c lib/ui/settings/appr/appr.c lib/ui/settings/rgb/rgb_mode/rgb_mode.c lib/ui/settings/rgb/rgb_speed/rgb_speed.c lib/ui/settings/rgb/rgb_hsv/rgb_hsv.c lib/ui/settings/dev/dev.c lib/ui/ui.c lib/ui/manu.c lib/ui/bindings/bindings.c lib/ui/fonts/impact_45.c lib/ui/fonts/impact_22.c lib/ui/fonts/extra_icons.c lib/ui/dial_menu/dial_menu.c
# Note: Not needed QP already add this for us
# QUANTUM_LIB_SRC += spi_master.c
