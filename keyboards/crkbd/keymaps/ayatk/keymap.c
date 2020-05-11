#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
#    include "lufa.h"
#    include "split_util.h"
#endif
#ifdef SSD1306OLED
#    include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

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
#define KC_CTLA CTL_T(KC_A)      // Ctrl/A
#define KC_CTLSC CTL_T(KC_SCLN)  // Ctrl/;
#define KC_CTLS CTL_T(KC_S)      // Ctrl/S
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
    [_QWERTY] = LAYOUT_kc( \
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

    [_EUCALYN] = LAYOUT_kc( \
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

    /* Lower
     * ,-----------------------------------------.             ,-----------------------------------------.
     * | ESC  |  1   |  2   |  3   |  4   |  5   |             |  6   |  7   |  8   |  9   |  0   |  BS  |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * | Tab  | HOME | END  |PgDwon| PgUp |SCREENSHOT|         |  ←  |  ↓  |  ↑  |  →  |      |      |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * | Shift|  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 |      |
     * `---------------------------+------+------+------+------+------+------+---------------------------'
     *                             | GUI |Lower/en|Space|Enter |ADJUST| Alt  |
     *                             `-----------------------------------------'
     */
    [_LOWER] = LAYOUT_kc( \
    //,-----------------------------------------.                ,-----------------------------------------.
            ,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,      ,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
            ,  HOME,   END,  PGDN,  PGUP, SCREENSHOT,              LEFT,  DOWN,    UP,  RGHT, XXXXX, XXXXX,
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
            ,    F1,    F2,    F3,    F4,    F5,                     F6,    F7,    F8,    F9,   F10,      ,
    //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                        ,      ,      ,         ,ADJUST,       \
                                //`--------------------'  `--------------------'
    ),

    /* Raise
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
    [_RAISE] = LAYOUT_kc( \
    //,-----------------------------------------.                ,-----------------------------------------.
            ,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN,      ,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
            , LCTRL,  TILD,  UNDS,  MINS,  PIPE,                   BSLS,   EQL,  PLUS,   GRV, RCTRL, XXXXX,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
            , XXXXX, XXXXX,  LCBR,  LBRC,  LPRN,                   RPRN,  RBRC,  RCBR, XXXXX, XXXXX,      ,\
    //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                        ,ADJUST,      ,         ,      ,       \
                                //`--------------------'  `--------------------'
    ),

    [_ADJUST] = LAYOUT_kc( \
    //,-----------------------------------------.                ,-----------------------------------------.
            ,  LRST, XXXXX, XXXXX,   RST, XXXXX,                  XXXXX,   RST, XXXXX, XXXXX, XXXXX, XXXXX,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
            ,  LHUI,  LSAI,  LVAI, XXXXX, XXXXX,                  XXXXX,QWERTY,EUCALYN,XXXXX, XXXXX, XXXXX,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
            ,  LHUD,  LSAD,  LVAD, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
    //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                        ,      ,      ,         ,      ,       \
                                //`--------------------'  `--------------------'
    )
    // clang-format on
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
#endif
// SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
    iota_gfx_init(!has_usb());  // turns on the display
#endif
}

// SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

static void render_logo(struct CharacterMatrix *matrix) {
    static char logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
        0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9,
        0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0
    };
    matrix_write(matrix, logo);
#    if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_ANIMATIONS)
    char buf[30];

    if (rgblight_config.enable) {
        snprintf(buf, sizeof(buf), " LED %2d: %d,%d,%d ",
            rgblight_config.mode,
            rgblight_config.hue / RGBLIGHT_HUE_STEP,
            rgblight_config.sat / RGBLIGHT_SAT_STEP,
            rgblight_config.val / RGBLIGHT_VAL_STEP
        );
        matrix_write(matrix, buf);
    }

#    endif
    // matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}

// Render to OLED
int row_num    = 0;
int row_func   = 0;
int row_adjust = 0;
int row_shift  = 0;

void matrix_scan_user(void) { iota_gfx_task(); }

void render_status(struct CharacterMatrix *matrix) {
    // froggy logo
    static char logo[4][1][17] = {{{0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0}}, {{0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0}}, {{0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0}}, {{0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0}}};

    static char indctr[8][2][4] = {
        // white icon
        {{0x60, 0x61, 0x62, 0}, {0x63, 0x64, 0}},  // numbers
        {{0x80, 0x81, 0x82, 0}, {0x83, 0x84, 0}},  // shift
        {{0xa0, 0xa1, 0xa2, 0}, {0xa3, 0xa4, 0}},  // function
        {{0xc0, 0xc1, 0xc2, 0}, {0xc3, 0xc4, 0}},  // adjust
        // Black icon
        {{0x75, 0x76, 0x77, 0}, {0x78, 0x79, 0}},  // numbers
        {{0x95, 0x96, 0x97, 0}, {0x98, 0x99, 0}},  // shift
        {{0xb5, 0xb6, 0xb7, 0}, {0xb8, 0xb9, 0}},  // function
        {{0xd5, 0xd6, 0xd7, 0}, {0xd8, 0xd9, 0}},  // adjust
    };

    row_num    = (layer_state_is(_LOWER) && !layer_state_is(_ADJUST)) ? 4 : 0;
    row_shift  = (layer_state_is(_EUCALYN)) ? 4 : 0;
    row_func   = (layer_state_is(_RAISE) && !layer_state_is(_ADJUST)) ? 4 : 0;
    row_adjust = (layer_state_is(_ADJUST)) ? 4 : 0;

    matrix_write(matrix, indctr[row_num][0]);
    matrix_write(matrix, indctr[row_func][1]);
    matrix_write(matrix, logo[0][0]);
    matrix_write(matrix, indctr[row_num + 1][0]);
    matrix_write(matrix, indctr[row_func + 1][1]);
    matrix_write(matrix, logo[1][0]);
    matrix_write(matrix, indctr[row_adjust + 2][0]);
    matrix_write(matrix, indctr[row_shift + 2][1]);
    matrix_write(matrix, logo[2][0]);
    matrix_write(matrix, indctr[row_adjust + 3][0]);
    matrix_write(matrix, indctr[row_shift + 3][1]);
    matrix_write(matrix, logo[3][0]);
}

void matrix_render_user(struct CharacterMatrix *matrix) {
    if (is_master) {
        render_status(matrix);
    } else {
        render_logo(matrix);
    }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
    if (memcmp(dest->display, source->display, sizeof(dest->display))) {
        memcpy(dest->display, source->display, sizeof(dest->display));
        dest->dirty = true;
    }
}

void iota_gfx_task_user(void) {
    struct CharacterMatrix matrix;
    matrix_clear(&matrix);
    matrix_render_user(&matrix);
    matrix_update(&display, &matrix);
}
#endif  // SSD1306OLED

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
        case RGB_MOD:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGB_current_mode);
                rgblight_step();
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
        case RGBRST:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            break;
    }
    return true;
}
