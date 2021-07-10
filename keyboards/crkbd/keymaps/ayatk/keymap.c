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

#define KC_ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWEI LT(_LOWER, KC_LANG2)
#define KC_RAIKN LT(_RAISE, KC_LANG1)
#define KC_ADJUST MO(_ADJUST)
#define KC_LSLB LSFT(KC_LBRC)    // [
#define KC_LSRB LSFT(KC_RBRC)    // ]
#define KC_CTLA CTL_T(KC_A)      // Ctrl or A
#define KC_CTLSC CTL_T(KC_SCLN)  // Ctrl or ;
#define KC_CTLS CTL_T(KC_S)      // Ctrl or S
#define KC_SCREENSHOT LSFT(LGUI(KC_4))
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
    [_QWERTY] = LAYOUT_split_3x6_3( \
    //,-----------------------------------------.                ,-----------------------------------------.
         ESC,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
         TAB,  CTLA,     S,     D,     F,     G,                      H,     J,     K,     L, CTLSC,  QUOT,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
         LSFT,    Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  RSFT,\
    //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                    LGUI, LOWEI,   SPC,     ENT,  RAIKN,  LALT \
                                //`--------------------'  `--------------------'
    ),

    [_EUCALYN] = LAYOUT_split_3x6_3( \
    //,-----------------------------------------.                ,-----------------------------------------.
         ESC,  SCLN,  COMM,   DOT,     P,     Q,                      Y,     G,     D,     M,     F,  BSPC,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
         TAB,  CTLA,     O,     E,     I,     U,                      B,     N,     T,     R,  CTLS,  QUOT,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
         LSFT,    Z,     X,     C,     V,     W,                      H,     J,     K,     L,  SLSH,  RSFT,\
    //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                        ,      ,      ,         ,      ,       \
                                //`--------------------'  `--------------------'
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
    [_RAISE] = LAYOUT_split_3x6_3( \
    //,-----------------------------------------.                ,-----------------------------------------.
            ,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,      ,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
            ,  HOME,   END,  PGDN,  PGUP, SCREENSHOT,              LEFT,  DOWN,    UP,  RGHT, XXXXX, XXXXX,
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
            ,    F1,    F2,    F3,    F4,    F5,                     F6,    F7,    F8,    F9,   F10,      ,
    //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                         ,ADJUST,      ,         ,      ,      \
                                //`--------------------'  `--------------------'
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
    [_LOWER] = LAYOUT_split_3x6_3( \
    //,-----------------------------------------.                ,-----------------------------------------.
            ,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN,      ,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
            , LCTRL,  TILD,  UNDS,  MINS,  PIPE,                   BSLS,   EQL,  PLUS,   GRV, RCTRL, XXXXX,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
            , XXXXX, XXXXX,  LCBR,  LBRC,  LPRN,                   RPRN,  RBRC,  RCBR, XXXXX, XXXXX,      ,\
    //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                         ,      ,      ,         ,ADJUST,      \
                                //`--------------------'  `--------------------'
    ),

    [_ADJUST] = LAYOUT_split_3x6_3( \
    //,-----------------------------------------.                ,-----------------------------------------.
            ,  LRST, XXXXX, XXXXX,   RST, XXXXX,                  XXXXX,   RST, XXXXX, XXXXX, QWERTY, EUCALYN,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
            ,  LHUI,  LSAI,  LVAI, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
            ,  LHUD,  LSAD,  LVAD, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
    //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                        ,      ,      ,         ,      ,       \
                                //`--------------------'  `--------------------'
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
