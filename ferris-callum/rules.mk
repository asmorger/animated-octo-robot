RGBLIGHT_ENABLE = no
CAPS_WORD_ENABLE = yes
AUTO_SHIFT_ENABLE = yes

SRC += oneshot.c
SRC += swapper.c

# Bootloader selection
BOOTLOADER = atmel-dfu