#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif
#ifdef CONSOLE_ENABLE
  #include <print.h>
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
  //Following line allows macro to read current RGB settings
  extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number
{
  _QWERTY = 0,
  _EUCALYN,
  _NUML,
  _NUMR,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes
{
  QWERTY = SAFE_RANGE,
  EUCALYN,
  KC_EN,
  KC_JP,
  RGBRST,
  // Brightness
  KC__BRIU,
  KC__BRID,
};

//Macros
#define KC_LOWER MO(_LOWER)
#define KC_NUML  LT(_NUML,KC_SPC)
#define KC_NUMR  LT(_NUMR,KC_SPC)
#define KC_RABS  LT(_RAISE, KC_BSPC)
#define KC_RAEN  LT(_RAISE, KC_ENT)
#define KC_____  _______
#define KC_XXXX  XXXXXXX
#define KC_ADJ   MO(_ADJUST)
#define KC_LSMI  LSFT(KC_MINS)
#define KC_LSEQ  LSFT(KC_EQL)
#define KC_LSRB  LSFT(KC_RBRC)
#define KC_LSLB  LSFT(KC_LBRC)
#define KC_LSGR  LSFT(KC_GRV)
#define KC_LSQT  LSFT(KC_QUOT)
#define ___      _______
#define KC_S0    LSFT(KC_0)
#define KC_S1    LSFT(KC_1)
#define KC_S2    LSFT(KC_2)
#define KC_S3    LSFT(KC_3)
#define KC_S4    LSFT(KC_4)
#define KC_S5    LSFT(KC_5)
#define KC_S6    LSFT(KC_6)
#define KC_S7    LSFT(KC_7)
#define KC_S8    LSFT(KC_8)
#define KC_S9    LSFT(KC_9)
#define KC__VOLU KC__VOLUP
#define KC__VOLD KC__VOLDOWN

#if HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  BS  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  | Ctrl |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   `  |   '  |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Lower | Lower| Caps |  Alt |  GUI | Space|  BS  | Enter| Space| GUI  | Alt  | Menu |Lower |Lower |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT_kc(
    ESC,   1,     2,    3,    4,    5,               6,   7,    8,     9,   0,     BSPC,
    TAB,   Q,     W,    E,    R,    T,               Y,   U,    I,     O,   P,     BSLS,
    LCTL,  A,     S,    D,    F,    G,               H,   J,    K,     L,   SCLN,  RCTL,
    LSFT,  Z,     X,    C,    V,    B,   GRV,  QUOT, N,   M,    COMM,  DOT, SLSH,  RSFT,
    LOWER, LOWER, CAPS, LALT, LGUI, SPC, RABS, RAEN, SPC, RGUI, RALT,  APP, LOWER, LOWER
  ),

  /* Eucalyn (http://eucalyn.hatenadiary.jp/entry/about-eucalyn-layout)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   ,  |   .  |   ;  |             |   M  |   R  |   D  |   Y  |   P  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   O  |   E  |   I  |   U  |             |   G  |   T  |   K  |   S  |   N  | Ctrl |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   F  |   `  |   '  |   B  |   H  |   J  |   L  |   /  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Lower | Lower| Caps |  Alt |  GUI | Space|  BS  | Enter| Space| GUI  | Alt  | Menu |Lower |Lower |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_EUCALYN] = LAYOUT_kc(
    ESC,   1,     2,    3,    4,    5,               6,    7,    8,    9,   0,     BSPC,
    TAB,   Q,     W,    COMM, DOT,  SCLN,            M,    R,    D,    Y,   P,     BSLS,
    LCTL,  A,     O,    E,    I,    U,               G,    T,    K,    S,   N,     RCTL,
    LSFT,  Z,     X,    C,    V,    F,   GRV,  QUOT, B,    H,    J,    L,   SLSH,  RSFT,
    LOWER, LOWER, CAPS, LALT, LGUI, SPC, RABS, RAEN, SPC,  RGUI, RALT, APP, LOWER, LOWER
  ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 | F11  | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |Pause | ScrLk| Ins  |      |             |      | Ins  | ScrLk|Pause |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | PgUp |      | Up   |Delete| Home |             | Home |Delete| Up   |      | PgUp |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      | PgDn | Left | Down | Right| End  |Adjust|Adjust| End  | Left | Down | Right| PgDn |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      | PrtSc|      |      |      |      |      |      |      |      | PrtSc|      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT_kc(
    F1,   F2,   F3,   F4,   F5,   F6,               F7,   F8,   F9,   F10,  F11,  F12,
    XXXX, XXXX, PAUS, SLCK, INS,  XXXX,             XXXX,  INS, SLCK, PAUS, XXXX, ____,
    ____, HOME, XXXX, UP,   DEL,  PGUP,             PGUP,  DEL,   UP, XXXX, HOME, ____,
    ____, END,  LEFT, DOWN, RGHT, PGDN, XXXX, XXXX, PGDN, LEFT, DOWN, RGHT, END,  ____,
    ____, ____, PSCR, ____, ____, ____,  ADJ,  ADJ, ____, ____, ____, PSCR, ____, ____
  ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |  _   |  -   |             |  =   |  +   |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |  {   |  [   |             |  ]   |  }   |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      | EISU | EISU | KANA | KANA | Next | Vol- | Vol+ | Play |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT_kc(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, _VOLUP,  XXXXXXX, LSMI,    MINS,                      EQL,     LSEQ,    XXXXXXX, _VOLUP,   XXXXXXX, XXXXXXX,
    _______, _MUTE,  _VOLDOWN, XXXXXXX, LSLB,    LBRC,                      RBRC,    LSRB,    XXXXXXX, _VOLDOWN, _MUTE,   _______,
    _______, MRWD,    MPLY,    MFFD,    XXXXXXX, EN,      EN,      JP,      JP,    XXXXXXX,   MRWD,    MPLY,     MFFD,    _______,
    ADJ,     ADJ,     XXXXXXX, _______, _______, XXXXXXX, _______, _______, XXXXXXX, _______, _______, XXXXXXX,  ADJ,     ADJ
  ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |Euclyn|Qwerty|             |Qwerty|Euclyn|      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Reset|RGBRST|RGB ON|Aud on| Win  |             | Win  |Aud on|RGB ON|RGBRST|      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | HUE+ | SAT+ | VAL+ |RGB md|Audoff| Mac  |             | Mac  |Audoff|RGB md| VAL+ | SAT+ | HUE+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | HUE- | SAT- | VAL- |      |      |      |      |      |      |      |      | VAL- | SAT- | HUE- |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EUCALYN,  QWERTY,           QWERTY,  EUCALYN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,   RESET,  RGBRST, RGB_TOG,   AU_ON, AG_SWAP,           AG_SWAP, AU_ON,   RGB_TOG, RGBRST,  XXXXXXX, XXXXXXX,
    RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD,  AU_OFF, AG_NORM,           AG_NORM, AU_OFF,  RGB_MOD, RGB_VAI, RGB_SAI, RGB_HUI,
    RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, ___, ___, XXXXXXX, XXXXXXX, XXXXXXX, RGB_VAD, RGB_SAD, RGB_HUD,
    _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ___, ___, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______
  ),
};

#elif HELIX_ROWS == 4

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |   ,  |   .  |   /  |Shift |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * | Lower| Menu | Alt  | Esc  | GUI  | Space|  BS  | Enter| Space| GUI  | Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT_kc(
    TAB,   Q,    W,    E,    R,    T,                Y,    U,    I,    O,    P,    BSLS,
    LCTL,  A,    S,    D,    F,    G,                H,    J,    K,    L,    SCLN, QUOT,
    LSFT,  Z,    X,    C,    V,    B,                N,    M,    COMM, DOT,  SLSH, LSFT,
    LOWER, APP,  LALT, ESC,  LGUI, NUML, RABS, RAEN, NUMR, RGUI, LEFT, DOWN, UP,   RGHT
  ),

  /* Eucalyn
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Tab  |   Q  |   W  |   ,  |   .  |   ;  |             |   M  |   R  |   D  |   Y  |   P  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   O  |   E  |   I  |   U  |             |   G  |   T  |   K  |   S  |   N  |  '   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   F  |             |   B  |   H  |   J  |   L  |   /  | Shift|
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * | Lower| Menu | Alt  | Esc  | GUI  | Space|  BS  | Enter| Space| GUI  | Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_EUCALYN] = LAYOUT_kc(
    TAB,   Q,    W,    COMM, DOT,  SCLN,             M,    R,    D,    Y,    P,    BSLS,
    LCTL,  A,    O,    E,    I,    U,                G,    T,    K,    S,    N,    QUOT,
    LSFT,  Z,    X,    C,    V,    F,                B,    H,    J,    L,    SLSH, RSFT,
    LOWER, APP,  LALT, ESC,  LGUI, NUML, RABS, RAEN, NUMR, RGUI, LEFT, DOWN, UP,   RGHT
  ),

  /* Num
    * ,-----------------------------------------.             ,-----------------------------------------.
    * |      |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |
    * |------+------+------+------+------+------|             |------+------+------+------+------+------|
    * |      |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | F12  |
    * |------+------+------+------+------+------|             |------+------+------+------+------+------|
    * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 | F11  |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
    * `-------------------------------------------------------------------------------------------------'
    */
  [_NUML] = LAYOUT_kc(
    ____,   S1,   S2,   S3,   S4,   S5,               S6,   S7,   S8,   S9,   S0, ____,
    ____,    1,    2,    3,    4,    5,                6,    7,    8,    9,    0,  F12,
    ____,   F1,   F2,   F3,   F4,   F5,               F6,   F7,   F8,   F9,  F10,  F11,
    ____, ____, ____, ____, ____, ____, ____, ____,  SPC, ____, ____, ____, ____, ____
  ),

  [_NUMR] = LAYOUT_kc(
    ____,   S1,   S2,   S3,   S4,   S5,               S6,   S7,   S8,   S9,   S0, ____,
    ____,    1,    2,    3,    4,    5,                6,    7,    8,    9,    0,  F12,
    ____,   F1,   F2,   F3,   F4,   F5,               F6,   F7,   F8,   F9,  F10,  F11,
    ____, ____, ____, ____, ____,  SPC, ____, ____, ____, ____, ____, ____, ____, ____
  ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      | Ins  |  Up  |Pause |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Next | Vol- | Vol+ | Play | Mute |             | Home | Left | Down | Right| PgUp |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      | Bri- | Bri+ |      |      |             | End  |Delete| ScrLk|      | PgDn |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |Adjust|Adjust|      |      |      | PrtSc|      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT_kc(
    XXXX, XXXX, XXXX, XXXX, XXXX, XXXX,             XXXX,  INS, SLCK, PAUS, XXXX, ____,
    ____, MFFD, _VOLD, _VOLU, MPLY, _MUTE,          PGUP,  DEL,   UP, XXXX, HOME, ____,
    ____, XXXX, _BRID, _BRIU, XXXX, XXXX,           PGDN, LEFT, DOWN, RGHT,  END, ____,
    ____, ____, ____, ____, ____, ____,  ADJ,  ADJ, ____, ____, ____, PSCR, ____, ____
  ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |  _   |  -   |             |  =   |  +   |      |      |      |  Del |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |  {   |  [   |             |  ]   |  }   |      |      |      | Mute |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |  ~   |  `   |             |  '   |   "  | Next | Vol- | Vol+ | Play |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |Adjust|      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT_kc(
    ____, XXXX, XXXX, XXXX, LSMI, MINS,              EQL, LSEQ, XXXX, XXXX, XXXX, DEL,
    ____, XXXX, XXXX, XXXX, LSLB, LBRC,             RBRC, LSRB, XXXX, XXXX, XXXX, _MUTE,
    ____, XXXX, XXXX, XXXX, LSGR,  GRV,             QUOT, LSQT, MNXT, _VOLD, _VOLU, MPLY,
    ADJ,  ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____
  ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      | Reset|RGBRST|RGB ON|Aud on| WIN  |             | WIN  |Aud on|RGB ON|RGBRST|      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | HUE+ | SAT+ | VAL+ |RGB md|Audoff| MAC  |             | MAC  |Audoff|RGB md| VAL+ | SAT+ | HUE+ |
   * |------+------+------+------+------+------+             +------+------+------+------+------+------|
   * | HUE- | SAT- | VAL- |      |Euclyn|Qwerty|             |Qwerty|Euclyn|      | VAL- | SAT- | HUE- |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] = LAYOUT(
    XXXXXXX,   RESET,  RGBRST, RGB_TOG,   AU_ON, AG_SWAP,           AG_SWAP, AU_ON,   RGB_TOG, RGBRST,  XXXXXXX, XXXXXXX,
    RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD,  AU_OFF, AG_NORM,           AG_NORM, AU_OFF,  RGB_MOD, RGB_VAI, RGB_SAI, RGB_HUI,
    RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, EUCALYN, QWERTY,            QWERTY,  EUCALYN, XXXXXXX, RGB_VAD, RGB_SAD, RGB_HUD,
    _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ___, ___, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______
  )
};

#else
#error "undefined keymaps"
#endif

#ifdef AUDIO_ENABLE
  float tone_qwerty[][2] = SONG(QWERTY_SOUND);
  float tone_eucalyn[][2] = SONG(DVORAK_SOUND);
  float tone_plover[][2] = SONG(PLOVER_SOUND);
  float tone_plover_gb[][2] = SONG(PLOVER_GOODBYE_SOUND);
  float music_scale[][2] = SONG(MUSIC_SCALE_SOUND);
#endif

static int current_default_layer;

uint32_t default_layer_state_set_kb(uint32_t state)
{
  // 1<<_QWERTY  - 1 == 1 - 1 == _QWERTY (=0)
  // 1<<_EUCALYN - 1 == 2 - 1 == _EUCALYN (=1)
  current_default_layer = state - 1;
  return state;
}

void update_base_layer(int base)
{
  eeconfig_update_default_layer(1UL << base);
  default_layer_set(1UL << base);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode) {
  case QWERTY:
    if (record->event.pressed) {
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_qwerty);
#endif
      update_base_layer(_QWERTY);
    }

    return false;
    break;

  case EUCALYN:
    if (record->event.pressed) {
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_eucalyn);
#endif
      update_base_layer(_EUCALYN);
    }

    return false;
    break;

  case KC_EN:
    if (record->event.pressed) {
      if (keymap_config.swap_lalt_lgui == false) {
        register_code(KC_LANG2);
      } else {
        SEND_STRING(SS_LALT("`"));
      }
    } else {
      unregister_code(KC_LANG2);
    }

    return false;
    break;

  case KC_JP:
    if (record->event.pressed) {
      if (keymap_config.swap_lalt_lgui == false) {
        register_code(KC_LANG1);
      } else {
        SEND_STRING(SS_LALT("`"));
      }
    } else {
      unregister_code(KC_LANG1);
    }

    return false;
    break;

  case RGBRST:
#ifdef RGBLIGHT_ENABLE
    if (record->event.pressed) {
      eeconfig_update_rgblight_default();
      rgblight_enable();
    }

#endif
    break;

  case KC__BRIU:
    if (record->event.pressed) {
      register_code(keymap_config.swap_lalt_lgui ? KC_BRIGHTNESS_UP : KC_BRMU);
    } else {
      unregister_code(keymap_config.swap_lalt_lgui ? KC_BRIGHTNESS_UP : KC_BRMU);
    }

    return false;
    break;

  case KC__BRID:
    if (record->event.pressed) {
      register_code(keymap_config.swap_lalt_lgui ? KC_BRIGHTNESS_DOWN : KC_BRMD);
    } else {
      unregister_code(keymap_config.swap_lalt_lgui ? KC_BRIGHTNESS_DOWN : KC_BRMD);
    }

    return false;
    break;
  }

  return true;
}

void matrix_init_user(void)
{
#ifdef AUDIO_ENABLE
  startup_user();
#endif
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
  iota_gfx_init(!has_usb()); // turns on the display
#endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
  _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
  _delay_ms(150);
  stop_all_notes();
}

void music_on_user(void)
{
  music_scale_user();
}

void music_scale_user(void)
{
  PLAY_SONG(music_scale);
}

#endif

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void)
{
  iota_gfx_task(); // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                   const struct CharacterMatrix *source)
{
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

static void render_logo(struct CharacterMatrix *matrix)
{

  static char logo[] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
    0
  };
  matrix_write(matrix, logo);
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_ANIMATIONS)
  char buf[30];

  if (rgblight_config.enable) {
    snprintf(buf, sizeof(buf), " LED %2d: %d,%d,%d ",
             rgblight_config.mode,
             rgblight_config.hue / RGBLIGHT_HUE_STEP,
             rgblight_config.sat / RGBLIGHT_SAT_STEP,
             rgblight_config.val / RGBLIGHT_VAL_STEP);
    matrix_write(matrix, buf);
  }

#endif
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}

int rown = 0;
int rowf = 0;
int rowa = 0;
int rows = 0;

void render_status(struct CharacterMatrix *matrix)
{

  // froggy logo
  static char logo[4][1][17] = {
    {
      {0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0}
    },
    {
      {0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0}
    },
    {
      {0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0}
    },
    {
      {0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0}
    }
  };

  static char indctr[8][2][4] = {
    // white icon
    {
      {0x60, 0x61, 0x62, 0},
      {0x63, 0x64, 0}
    },
    {
      {0x80, 0x81, 0x82, 0},
      {0x83, 0x84, 0}
    },
    {
      {0xa0, 0xa1, 0xa2, 0},
      {0xa3, 0xa4, 0}
    },
    {
      {0xc0, 0xc1, 0xc2, 0},
      {0xc3, 0xc4, 0}
    },
    // Black icon
    {
      {0x75, 0x76, 0x77, 0},
      {0x78, 0x79, 0}
    },
    {
      {0x95, 0x96, 0x97, 0},
      {0x98, 0x99, 0}
    },
    {
      {0xb5, 0xb6, 0xb7, 0},
      {0xb8, 0xb9, 0}
    },
    {
      {0xd5, 0xd6, 0xd7, 0},
      {0xd8, 0xd9, 0}
    },
  };

  rown = (layer_state_is(_NUML) || layer_state_is(_NUMR) ) ? 4 : 0;
  rows = (layer_state_is(_LOWER)  ) ? 4 : 0;
  rowf = (layer_state_is(_RAISE) ) ? 4 : 0;
  rowa = (layer_state_is(_ADJUST) ) ? 4 : 0;

  matrix_write(matrix, indctr[rown]  [0]);
  matrix_write(matrix, indctr[rowf]  [1]);
  matrix_write(matrix, logo  [0]     [0]);
  matrix_write(matrix, indctr[rown + 1][0]);
  matrix_write(matrix, indctr[rowf + 1][1]);
  matrix_write(matrix, logo  [1]     [0]);
  matrix_write(matrix, indctr[rowa + 2][0]);
  matrix_write(matrix, indctr[rows + 2][1]);
  matrix_write(matrix, logo  [2]     [0]);
  matrix_write(matrix, indctr[rowa + 3][0]);
  matrix_write(matrix, indctr[rows + 3][1]);
  matrix_write(matrix, logo  [3]     [0]);
}

void iota_gfx_task_user(void)
{
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN

  if (debug_enable) {
    return;
  }

#endif

  matrix_clear(&matrix);

  if (is_master) {
    render_status(&matrix);
  } else {
    render_logo(&matrix);
  }

  matrix_update(&display, &matrix);
}

#endif
