VIA_ENABLE = yes
CONSOLE_ENABLE = yes

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
    lib/security/sha256/sha256.c \
    lib/security/aes128/aes128.c \
        
QUANTUM_LIB_SRC += i2c_master.c