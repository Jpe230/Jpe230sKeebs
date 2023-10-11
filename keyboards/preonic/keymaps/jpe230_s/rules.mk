# Disable unused features inherited from the kb rules.mk
ENCODER_ENABLE    = no
DIP_SWITCH_ENABLE = no
CONSOLE_ENABLE    = no
COMMAND_ENABLE    = no
OLED_ENABLE       = yes

# Enable VIA
VIA_ENABLE = yes

S_LOCATION = ${SLOCATION}

ifneq ("$(wildcard $(S_LOCATION)/supersecrets.c)","")
    SRC +=  $(S_LOCATION)/supersecrets.c
endif