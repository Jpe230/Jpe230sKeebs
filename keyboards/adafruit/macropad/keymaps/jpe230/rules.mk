SRC += \
    jpe230.c \
    rgb/indicators.c \
    oled/oled.c \
    oled/bongocat.c \
    oled/lockscreen_oled.c \
    oled/logo.c \
    secrets/lockscreen.c \
    secrets/totp.c \
    secrets/sha1.c

# VIA_ENABLE = yes
# OPENRGB_ENABLE = yes
CONSOLE_ENABLE = yes

OPT_DEFS += -D${KB}