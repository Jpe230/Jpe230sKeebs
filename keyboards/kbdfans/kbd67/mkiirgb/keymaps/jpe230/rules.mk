VIA_ENABLE = yes
LTO_ENABLE = yes

S_LOCATION = ${SLOCATION}

ifneq ("$(wildcard $(S_LOCATION)/supersecrets.c)","")
    SRC +=  $(S_LOCATION)/supersecrets.c
endif