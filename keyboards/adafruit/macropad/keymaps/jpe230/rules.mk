QUANTUM_LIB_SRC += i2c_master.c
CONSOLE_ENABLE = yes

# Project specific files
SRC += \
    jpe230.c \
    rgb/indicators.c \
    oled/oled.c \
    oled/bongocat.c \
    oled/lockscreen_oled.c \
    oled/logo.c \
    lib/ds3231/ds3231.c

# Enable secrets (by design the public version doesnt include those files)
ifeq ($(strip $(DEF)), ENABLE_SECRETS)
    OPT_DEFS += -D${DEF}
    SRC += \
        secrets/lockscreen.c \
        secrets/sha1.c \
        secrets/totp.c
endif
        