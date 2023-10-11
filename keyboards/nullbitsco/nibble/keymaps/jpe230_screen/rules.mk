VIA_ENABLE = yes

SRC = matrix.c logic/process_keys.c painter/painter.c bongo/main_screen.c bongo/styles/styles.c bongo/assets/cat.c bongo/assets/paw_l_down.c bongo/assets/paw_r_down.c bongo/assets/paw_l_up.c bongo/assets/paw_r_up.c bongo/assets/table.c
QUANTUM_LIB_SRC =

CONSOLE_ENABLE = yes
BOOTMAGIC_ENABLE = yes
RGBLIGHT_ENABLE = yes
EXTRAKEY_ENABLE = yes
WPM_ENABLE = yes
NKRO_ENABLE = yes
MOUSEKEY_ENABLE = yes

DEFERRED_EXEC_ENABLE = yes
LTO_ENABLE = yes

QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += st7789_spi
QUANTUM_PAINTER_LVGL_INTEGRATION = yes

S_LOCATION = ${SLOCATION}

ifneq ("$(wildcard $(S_LOCATION)/supersecrets.c)","")
    SRC +=  $(S_LOCATION)/supersecrets.c
endif

