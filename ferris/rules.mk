MOUSEKEY_ENABLE  = yes    # Mouse keys
RGBLIGHT_ENABLE  = no    # Enable WS2812 RGB underlight.
OLED_ENABLE      = no
OLED_DRIVER      = SSD1306
LTO_ENABLE       = yes
TAP_DANCE_ENABLE = yes
LEADER_ENABLE    = yes
COMBO_ENABLE     = yes

VPATH  +=  keyboards/gboards/

SRC += features/select_word.c
SRC += features/layermodes.c
SRC += features/case_mods.c

# this enables the keyboard-driven reset functionality
BOOTLOADER = atmel-dfu
