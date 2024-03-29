#include QMK_KEYBOARD_H
#include "flow.h"

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
#define UI OSM(MOD_LSFT | MOD_LGUI | MOD_LCTL)
#define BUILD C(KC_B)
#define TEST C(S(KC_ENT))

#define OS_SHFT OSM(MOD_LSFT)
#define OS_CTRL OSM(MOD_LCTL)
#define OS_ALT OSM(MOD_LALT)
#define OS_CMD OSM(MOD_LGUI)

enum layers {
    DEF = 0,
    SYM = 1,
    NAV = 2,
    NUM = 3,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    //OS_SHFT,
    //OS_CTRL,
    //OS_ALT,
    //OS_CMD,

    L_SYM,
    L_NAV,

    LOWER,
    RAISE,
    SW_WIN = SAFE_RANGE,  // Switch to next window         (cmd-tab)
    SW_LANG, // Switch to next input language (ctl-spc)
    REPEAT, // https://gist.github.com/NotGate/3e3d8ab81300a86522b2c2549f99b131?permalink_comment_id=4282534#gistcomment-4282534
};

const uint16_t flow_config[FLOW_COUNT][2] = {
  {L_SYM, KC_RALT },
  {L_SYM, KC_RSFT },
  {L_SYM, KC_RCTL },
  {L_SYM, KC_RGUI },
  {L_NAV, KC_LALT },
  {L_NAV, KC_LSFT },
  {L_NAV, KC_LCTL },
  {L_NAV, KC_LGUI },
};

const uint16_t flow_layers_config[FLOW_LAYERS_COUNT][2] = {
  { L_SYM, SYM },
  { L_NAV, NAV }
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_split_3x5_2(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
        KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_QUOT,
                                            L_NAV,  KC_SPC,   UI, L_SYM
    ),

    [SYM] = LAYOUT_split_3x5_2(
        KC_ESC,  KC_LPRN, KC_LT,   KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR,   KC_GT, KC_RPRN,  KC_GRV,
        KC_MINS, KC_ASTR, KC_EQL,  KC_UNDS, KC_DLR,  KC_AT,   KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT,
        KC_PLUS, KC_PIPE, KC_TILD, KC_SLSH, KC_PERC, KC_HASH, KC_BSLS, KC_AMPR, KC_QUES, KC_EXLM,
                                   MO(NUM), _______,  _______, _______
    ),

    [NAV] = LAYOUT_split_3x5_2(
        KC_TAB,  SW_WIN,  TAB_L,   TAB_R,   XXXXXXX,  KC_HOME, KC_PGDN, KC_PGUP,KC_END,  KC_DEL,
        KC_LSFT, KC_LCTL,KC_LALT,KC_LGUI,  XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT, KC_BSPC,
        SPACE_L, SPACE_R, XXXXXXX,XXXXXXX,  QK_BOOT, QK_BOOT, XXXXXXX, XXXXXXX,_______, KC_ENT,
                                   _______, _______, CW_TOGG, MO(NUM)
    ),

    [NUM] = LAYOUT_split_3x5_2(
        KC_7   ,    KC_5,  KC_3,      KC_1,    KC_9,    KC_8,    KC_0,    KC_2,   KC_4,          KC_6,
        KC_F7  ,   KC_F5, KC_F3,    KC_F11,   KC_F1,  KC_F12,  KC_F10,   KC_F2,  KC_F4, LCTL(KC_BSPC),
        XXXXXXX, XXXXXXX,  TEST,     BUILD, XXXXXXX,    BACK, KC_VOLD, KC_VOLU,    FWD,  LALT(KC_ENT),
                                   _______, _______, _______, _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!update_flow(keycode, record->event.pressed, record->event.key)) return false;
    return true;
}
void matrix_scan_user(void) {
    flow_matrix_scan();
}
