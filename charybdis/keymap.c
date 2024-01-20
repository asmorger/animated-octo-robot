/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_TRI,
    LAYER_POINT
};

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define TRI MO(LAYER_TRI)
#define POINT OSL(LAYER_POINT)

#define OS_SHFT OSM(MOD_LSFT)
#define OS_CTRL OSM(MOD_LCTL)
#define OS_ALT OSM(MOD_LALT)
#define OS_CMD OSM(MOD_LGUI)

#define UI OSM(MOD_LSFT | MOD_LGUI | MOD_LCTL)
#define BUILD C(KC_B)
#define TEST C(S(KC_ENT))

#define CTL_BSP CTL_T(KC_BSPC)
#define SFT_SPC SFT_T(KC_SPC)
#define GUI_ENT GUI_T(KC_ENT)


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
          KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,       KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          KC_A,    KC_R,    KC_S,    KC_T,    KC_G,       KC_M,    KC_N,    KC_E,    KC_I, KC_O,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,       KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         POINT,   RAISE, SFT_SPC,     UI, LOWER
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮

        KC_ESC,  KC_LPRN, KC_LT,   KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR,   KC_GT, KC_RPRN,  KC_GRV,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        
        KC_MINS, KC_ASTR, KC_EQL,  KC_UNDS, KC_DLR,    KC_AT,  OS_CMD, OS_CTRL,  OS_ALT, OS_SHFT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        KC_PLUS, KC_PIPE, KC_TILD, KC_SLSH, KC_PERC, KC_HASH, KC_BSLS, KC_AMPR, KC_QUES, KC_EXLM,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                          XXXXXXX,     TRI, _______,  XXXXXXX, _______
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        KC_TAB, XXXXXXX,XXXXXXX, XXXXXXX,   XXXXXXX,  KC_HOME, KC_PGDN, KC_PGUP,KC_END,  KC_DEL,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        OS_SHFT, OS_ALT,OS_CTRL,OS_CMD,  XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT, KC_BSPC,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        XXXXXXX,XXXXXXX, XXXXXXX,XXXXXXX,  QK_BOOT, QK_BOOT, XXXXXXX, XXXXXXX,_______, KC_ENT,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         _______, _______, XXXXXXX,    _______,    TRI
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),
  
  [LAYER_TRI] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        KC_7   ,    KC_5,  KC_3,      KC_1,    KC_9,    KC_8,    KC_0,    KC_2,   KC_4,          KC_6,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        KC_F7  ,   KC_F5, KC_F3,    KC_F11,   KC_F1,  KC_F12,  KC_F10,   KC_F2,  KC_F4, LCTL(KC_BSPC),
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        XXXXXXX, XXXXXXX,  TEST,     BUILD, XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, XXXXXXX,  LALT(KC_ENT),
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         _______, _______, XXXXXXX,    _______, XXXXXXX
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINT] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        KC_7   ,    KC_5,  KC_3,      KC_1,    KC_9,    KC_8,    KC_0,    KC_2,   KC_4,          KC_6,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        KC_F7  ,   KC_F5, KC_F3,    KC_F11,   KC_F1,  KC_F12,  KC_F10,   KC_F2,  KC_F4, LCTL(KC_BSPC),
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        XXXXXXX, XXXXXXX,  TEST,     BUILD, XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, XXXXXXX,  LALT(KC_ENT),
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         KC_BTN1,   KC_BTN2, KC_BTN3, KC_BTN2, KC_BTN1
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on
