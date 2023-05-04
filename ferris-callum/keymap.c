#include QMK_KEYBOARD_H

#include "oneshot.h"
#include "swapper.h"

#define HOME G(KC_LEFT)
#define END G(KC_RGHT)
#define FWD G(KC_RBRC)
#define BACK G(KC_LBRC)
#define TAB_L G(S(KC_LBRC))
#define TAB_R G(S(KC_RBRC))
#define SPACE_L A(G(KC_LEFT))
#define SPACE_R A(G(KC_RGHT))
#define LA_SYM MO(SYM)
#define LA_NAV MO(NAV)
#define UI OSM(MOD_LSFT | MOD_LGUI)
#define BUILD C(KC_B)
#define TEST C(S(KC_ENT))

enum layers {
    DEF,
    SYM,
    NAV,
    NUM,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    SW_WIN,  // Switch to next window         (cmd-tab)
    SW_LANG, // Switch to next input language (ctl-spc)
    REPEAT, // https://gist.github.com/NotGate/3e3d8ab81300a86522b2c2549f99b131?permalink_comment_id=4282534#gistcomment-4282534
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_split_3x5_2(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
        KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_QUOT,
                                   LA_NAV,  KC_SPC,  UI,      LA_SYM
    ),

    [SYM] = LAYOUT_split_3x5_2(
        KC_ESC,  KC_LPRN, KC_LT,   KC_LBRC, KC_LCBR, KC_RCBR, KC_RBRC,   KC_GT, KC_RPRN,  KC_GRV,
        KC_MINS, KC_ASTR, KC_EQL,  KC_UNDS, KC_DLR,  KC_AT,    OS_CMD,  OS_ALT, OS_CTRL, OS_SHFT,
        KC_PLUS, KC_PIPE, KC_TILD, KC_SLSH, KC_PERC, KC_HASH, KC_BSLS, KC_AMPR, KC_QUES, KC_EXLM,
                                   _______, REPEAT,  _______, _______
    ),

    [NAV] = LAYOUT_split_3x5_2(
        KC_TAB,  SW_WIN,  TAB_L,   TAB_R,  QK_BOOT,  KC_HOME, KC_PGDN, KC_PGUP,KC_END,  KC_DEL,
        OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT, KC_BSPC,
        SPACE_L, SPACE_R, XXXXXXX,XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,_______, KC_ENT,
                                   _______, _______, _______, _______
    ),

    [NUM] = LAYOUT_split_3x5_2(
        KC_7   ,    KC_5,  KC_3,      KC_1,    KC_9,    KC_8,    KC_0,    KC_2,   KC_4,          KC_6,
        KC_F7  ,   KC_F5, KC_F3,    KC_F11,   KC_F1,  KC_F12,  KC_F10,   KC_F2,  KC_F4, LCTL(KC_BSPC),
        XXXXXXX, XXXXXXX,  TEST,     BUILD, XXXXXXX,    BACK, KC_VOLD, KC_VOLU,    FWD,  LALT(KC_ENT),
                                   _______, _______, _______, _______
    ),
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
        return true;
    default:
        return false;
    }
}
bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

bool sw_win_active = false;
bool sw_lang_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

// Used to extract the basic tapping keycode from a dual-role key.
// Example: GET_TAP_KC(MT(MOD_RSFT, KC_E)) == KC_E
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF
uint16_t last_keycode = KC_NO;
uint8_t last_modifier = 0;
uint16_t pressed_keycode = KC_NO;

void process_repeat_key(uint16_t keycode, const keyrecord_t *record) {
  if (keycode != REPEAT) {
    // Early return when holding down a pure layer key
    // to retain modifiers
    switch (keycode) {
      case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
      case QK_MOMENTARY ... QK_MOMENTARY_MAX:
      case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
      case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
      case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
      case QK_TO ... QK_TO_MAX:
      case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
      case QK_MODS ... QK_MODS_MAX:
        return;
    }
    if (record->event.pressed) {
      last_modifier = get_mods() | get_oneshot_mods();
      switch (keycode) {
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
          last_keycode = GET_TAP_KC(keycode);
          break;
        default:
          last_keycode = keycode;
          break;
        }
    }
  } else { // keycode == REPEAT
    if (record->event.pressed) {
      pressed_keycode = last_keycode;
      register_mods(last_modifier);
      register_code16(pressed_keycode);
      unregister_mods(last_modifier);
    } else {
      unregister_code16(pressed_keycode);
    }
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_repeat_key(keycode, record);
    
    update_swapper(
        &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
        keycode, record
    );
    update_swapper(
        &sw_lang_active, KC_LCTL, KC_SPC, SW_LANG,
        keycode, record
    );

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}
