

#pragma once

#include QMK_KEYBOARD_H

// Call this function from `process_record_user()` to implement Layer Return.
bool process_single_layer_return(uint16_t keycode, keyrecord_t* record, uint16_t t_enum, uint16_t t_keypress);