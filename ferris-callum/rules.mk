RGBLIGHT_ENABLE = no
CAPS_WORD_ENABLE = yes
AUTO_SHIFT_ENABLE = yes
TRI_LAYER_ENABLE = yes

POINTING_DEVICE_ENABLE = yes	# Enable Pimoroni Trackball on master (+2304)
POINTING_DEVICE_DRIVER = pimoroni_trackball

QUANTUM_LIB_SRC += i2c_master.c

SRC += oneshot.c
SRC += swapper.c
SRC += drivers/sensors/pimoroni_trackball.c

# Bootloader selection
BOOTLOADER = atmel-dfu
