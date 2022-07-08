#VIA_ENABLE = yes

# Project specific files
SRC += \
    utils.c \
    rgb/rgb_handler.c \
    oled/oled_handler.c \
    oled/renderers/bongocat.c \
    oled/renderers/logo.c
        
QUANTUM_LIB_SRC += i2c_master.c