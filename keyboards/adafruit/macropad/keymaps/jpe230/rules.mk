SRC += \
    jpe230.c \
    rgb/indicators.c \
    oled/oled.c \
    oled/bongocat.c \
    oled/lockscreen_oled.c \
    oled/logo.c \
    lib/ds3231/ds3231.c

QUANTUM_LIB_SRC += i2c_master.c

CONSOLE_ENABLE = yes

# ENABLE SECRETS 
ifeq ($(strip $(DEF)), ENABLE_SECRETS)
    OPT_DEFS += -D${DEF}
    SRC += \
        secrets/lockscreen.c \
        secrets/sha1.c \
        secrets/totp.c
endif
        