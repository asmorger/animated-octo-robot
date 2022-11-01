#include "layer_return.h"

bool process_single_layer_return(uint16_t keycode, keyrecord_t* record, uint16_t t_enum, char t_keypress) {

    switch (keycode)
    {
        case t_enum:
            if (record->event.pressed) {
                layer_off(1);
                layer_off(2);
                layer_off(3);
                layer_on(0); 

                SEND_STRING(t_keypress);
                return false;
            }
            break;
        
        default:
            return break;
    }
    
    
    return true;
}