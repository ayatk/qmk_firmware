#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _EUCALYN 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 4

enum custom_keycodes { QWERTY = SAFE_RANGE, EUCALYN, RGBRST };

#define KC_LOWEI LT(_LOWER, KC_LANG2)
#define KC_RAIKN LT(_RAISE, KC_LANG1)
#define KC_ADST MO(_ADJUST)
#define KC_LSLB LSFT(KC_LBRC)    // [
#define KC_LSRB LSFT(KC_RBRC)    // ]
#define KC_CTLA CTL_T(KC_A)      // Ctrl or A
#define KC_CTLSC CTL_T(KC_SCLN)  // Ctrl or ;
#define KC_CTLS CTL_T(KC_S)      // Ctrl or S
#define KC_SS LSFT(LGUI(KC_4))
#define KC_QWERTY QWERTY
#define KC_EUCALYN EUCALYN

// system
#define KC_RST RESET

// RGB
#define KC_LRST RGBRST
#define KC_LTOG RGB_TOG
#define KC_LHUI RGB_HUI
#define KC_LHUD RGB_HUD
#define KC_LSAI RGB_SAI
#define KC_LSAD RGB_SAD
#define KC_LVAI RGB_VAI
#define KC_LVAD RGB_VAD
#define KC_LMOD RGB_MOD

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [_QWERTY] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL, KC_CTLA,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,KC_CTLSC, KC_QUOT,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LGUI,KC_LOWEI,  KC_SPC,     KC_ENT,KC_RAIKN, KC_LALT 
                                        //`--------------------------'  `--------------------------'
    ),

    /* Raise
     * ,-----------------------------------------.             ,-----------------------------------------.
     * | ESC  |  1   |  2   |  3   |  4   |  5   |             |  6   |  7   |  8   |  9   |  0   |  BS  |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * | Tab  | HOME | END  |PgDwon| PgUp |SCREENSHOT|         |  ←  |  ↓  |  ↑  |  →  |      |      |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * | Shift|  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 | Shift|
     * `---------------------------+------+------+------+------+------+------+---------------------------'
     *                             | GUI |Lower/en|Space|Enter |ADJUST| Alt  |
     *                             `-----------------------------------------'
     */

    [_RAISE] = LAYOUT_split_3x6_3( 
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TRNS,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_TRNS,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_TRNS, KC_HOME,  KC_END, KC_PGDN, KC_PGUP,   KC_SS,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_TRNS,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_TRNS,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_TRNS, KC_ADST, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS 
                                        //`--------------------------'  `--------------------------'
    ),

    /* Lower
     * ,-----------------------------------------.             ,-----------------------------------------.
     * | ESC  |  !   |  @   |  #   |  $   |  %   |             |  ^   |  &   |  *   |  (   |  )   |  BS  |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * | Tab  | Ctrl |  ~   |  _   |  -   |  |   |             |  \   |  =   |  +   |  `   | Ctrl |      |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * | Shift|      |      |  {   |  [   |  (   |             |  )   |  ]   |  }   |      |      |      |
     * `---------------------------+------+------+------+------+------+------+---------------------------'
     *                             | GUI |ADJUST|Space|Enter|Raise/ja|Alt  |
     *                             `-----------------------------------------'
     */
    [_LOWER] = LAYOUT_split_3x6_3( 
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TRNS, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_TRNS,KC_LCTRL, KC_TILD, KC_UNDS, KC_MINS, KC_PIPE,                      KC_BSLS,  KC_EQL, KC_PLUS,  KC_GRV,KC_RCTRL, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_TRNS, XXXXXXX, XXXXXXX, KC_LCBR, KC_LBRC, KC_LPRN,                      KC_RPRN, KC_RBRC, KC_RCBR, XXXXXXX, XXXXXXX, KC_TRNS,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_ADST, KC_TRNS
                                        //`--------------------------'  `--------------------------'
    ),

    [_ADJUST] = LAYOUT_split_3x6_3( 
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TRNS, KC_LRST, XXXXXXX, XXXXXXX,  KC_RST, XXXXXXX,                      XXXXXXX,  KC_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_TRNS, KC_LHUI, KC_LSAI, KC_LVAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_TRNS, KC_LHUD, KC_LSAD, KC_LVAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS  
                                        //`--------------------------'  `--------------------------'
    )
    // clang-format on
};

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                persistent_default_layer_set(1UL << _QWERTY);
            }
            return false;
        case EUCALYN:
            if (record->event.pressed) {
                persistent_default_layer_set(1UL << _EUCALYN);
            }
            return false;
    }
    return true;
}
