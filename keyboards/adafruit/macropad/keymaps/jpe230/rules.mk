VIA_ENABLE = yes

# Project specific files
SRC += \
    utils.c \
    rgb/rgb_handler.c \
    oled/oled_handler.c \
    oled/renderers/bongocat.c \
    oled/renderers/logo.c \
    oled/renderers/otp.c \
    oled/renderers/lockscreen.c \
    otp/otp.c \
    otp/password_validator.c \
    lib/ds3231/ds3231.c \
    lib/security/sha1/sha1.c \
        
QUANTUM_LIB_SRC += i2c_master.c