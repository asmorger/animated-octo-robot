/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keymap_steno.h"
#include <stdio.h>

enum layers {
    _COLEMAK = 0,
    _SYM,
    _DIR,
    _NUM,
    _NAV,
    _STENO
};

#define G_A LGUI_T(KC_A)
#define S_R LALT_T(KC_R)
#define A_S RSFT_T(KC_S)
#define C_T LCTL_T(KC_T)

#define C_N RCTL_T(KC_N)
#define A_E RALT_T(KC_E)
#define S_I RSFT_T(KC_I)
#define G_O RGUI_T(KC_O)
#define S_C_A LSFT(LCTL(KC_LALT))

#define DIR_T LT(_DIR, KC_D)
#define NUM_H LT(_NUM, KC_H)

#define NAV_SPC LT(_NAV, KC_SPC)
#define OSM_S OSM(MOD_LSFT)
#define OSM_OS OSM(MOD_LSFT | MOD_LGUI)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,     G_A,     S_R,     A_S,     C_T,    KC_G,                         KC_M,     C_N,     A_E,     S_I,     G_O, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_Z,    KC_X,    KC_C,   DIR_T,    KC_V,                         KC_K,   NUM_H, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX,  NAV_SPC, OSM_S,     OSM_OS,OSL(_SYM), XXXXXXX
                                      //`--------------------------'  `--------------------------'

  ),

  [_SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_HASH,KC_COLON,   KC_LT,   KC_GT, KC_EXLM,                      XXXXXXX, KC_UNDS, KC_PIPE, KC_QUOT,  KC_ESC, KC_TAB,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_QUES,                      KC_EQL, KC_TILD, KC_SLASH, KC_DQUO,  KC_ENT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_F22, KC_TILD, KC_LBRC, KC_RBRC, KC_AMPR,                      KC_MINS, KC_MINS, KC_BSLS,  KC_GRV,  KC_F21, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                     XXXXXXX, KC_BSPC, LCTL(KC_BSPC),     KC_TAB, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [_DIR] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_HOME, KC_PGDN, KC_PGUP, KC_END, XXXXXXX, XXXXXXX, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, S_C_A, KC_LCTL,    LALT(KC_LALT), KC_F5, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_BSLS,    KC_7,    KC_8,    KC_9, KC_PLUS,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_0,    KC_1,    KC_2,    KC_3,  KC_EQL,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_ASTR,    KC_4,    KC_5,    KC_6, KC_MINS,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_VOLD, KC_VOLU, KC_MUTE, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),
    [_STENO] = LAYOUT_split_3x6_3(
		XXXXXXX,  STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,  STN_ST3,  STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
		XXXXXXX,  STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2,  STN_ST4,  STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
              TG(_STENO),  STN_A,   STN_O,   STN_E,   STN_U,  STN_N2)
};

