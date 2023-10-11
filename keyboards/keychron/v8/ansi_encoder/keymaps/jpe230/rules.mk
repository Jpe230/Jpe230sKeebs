VIA_ENABLE = yes
MOUSEKEY_ENABLE = yes
CONSOLE_ENABLE = yes
ENCODER_MAP_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes

S_LOCATION = ${SLOCATION}

ifneq ("$(wildcard $(S_LOCATION)/supersecrets.c)","")
    SRC +=  $(S_LOCATION)/supersecrets.c
endif
