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
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes
{
  QWERTY = SAFE_RANGE,
  EUCALYN,
  EISU,
  KANA,
  ONEPASS,
  RGBRST
};

enum macro_keycodes
{
  KC_SAMPLEMACRO,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

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
   * |Lower | Lower| Caps | GUI  | Alt  | Space|  BS  | Enter| Space| Alt  | GUI  | Menu |Lower |Lower |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_RCTL, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_GRV, KC_QUOT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
      MO(_LOWER),MO(_LOWER),  KC_CAPS, KC_LALT, KC_LGUI, KC_SPC, LT(_RAISE,KC_BSPC), \
                                                         LT(_RAISE,KC_ENT), KC_SPC,  KC_RGUI, KC_RALT, KC_APP,MO(_LOWER),MO(_LOWER) \
      ),
  /* Eucalyn
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  BS  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   ,  |   .  |   ;  |             |   M  |   R  |   D  |   Y  |   P  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   O  |   E  |   I  |   U  |             |   G  |   T  |   K  |   S  |   N  | Ctrl |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   F  |   `  |   '  |   B  |   H  |   J  |   L  |   /  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Lower | Lower| Caps | GUI  | Alt  | Space|  BS  | Enter| Space| Alt  | GUI  | Menu |Lower |Lower |
   * `-------------------------------------------------------------------------------------------------'
   */
    [_EUCALYN] = LAYOUT(
        KC_ESC,     KC_1,       KC_2,    KC_3,    KC_4,   KC_5,                  KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        KC_TAB,     KC_Q,       KC_W,    KC_COMM, KC_DOT, KC_SCLN,               KC_M, KC_R, KC_D, KC_Y, KC_P, KC_BSLS,
        KC_LCTL,    KC_A,       KC_O,    KC_E,    KC_I,   KC_U,                  KC_G, KC_T, KC_K, KC_S, KC_N, KC_RCTL,
        KC_LSFT,    KC_Z,       KC_X,    KC_C,    KC_V,   KC_F, KC_GRV, KC_QUOT, KC_B, KC_H, KC_J, KC_L, KC_SLSH, KC_RSFT,
        MO(_LOWER), MO(_LOWER), KC_CAPS, KC_LALT, KC_LGUI, KC_SPC, LT(_RAISE, KC_BSPC),
                                            LT(_RAISE, KC_ENT), KC_SPC, KC_RGUI, KC_RALT, KC_APP, MO(_LOWER), MO(_LOWER)),

    /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 | F11  | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |Pause | ScrLk| Ins  |      |             |      | Ins  | ScrLk|Pause |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | PgUp |1PASS | Up   |Delete| Home |             | Home |Delete| Up   |1PASS | PgUp |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      | PgDn | Left | Down | Right| End  |      |      | End  | Left | Down | Right| PgDn |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      | PrtSc|      |      |      |Adjust|Adjust|      |      |      | PrtSc|      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
      XXXXXXX, XXXXXXX, KC_PAUS, KC_SLCK, KC_INS,  XXXXXXX,                   XXXXXXX, KC_INS,  KC_SLCK, KC_PAUS, XXXXXXX, XXXXXXX, \
      _______, KC_HOME, ONEPASS, KC_UP,   KC_DEL,  KC_PGUP,                   KC_PGUP, KC_DEL,  KC_UP,   ONEPASS, KC_HOME, _______, \
      _______, KC_END,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,  XXXXXXX, XXXXXXX,KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  _______, \
        _______, _______, KC_PSCR, _______, _______, _______, MO(_ADJUST),
                                                                 MO(_ADJUST), _______, _______, _______, KC_PSCR, _______, _______ \
      ),

    /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      | Vol+ |      |  _   |  -   |             |  =   |  +   |      | Vol+ |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Mute | Vol- |      |  {   |  [   |             |  ]   |  }   |      | Vol- | Mute |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      | Prev | Play | Next |      | EISU | EISU | KANA | KANA |      | Prev | Play | Next |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, XXXXXXX, KC__VOLUP, XXXXXXX, LSFT(KC_MINS), KC_MINS,                   KC_EQL,  LSFT(KC_EQL), XXXXXXX, KC__VOLUP, XXXXXXX, XXXXXXX, \
      _______, KC__MUTE, KC__VOLDOWN, XXXXXXX, LSFT(KC_LBRC), KC_LBRC,                   KC_RBRC, LSFT(KC_RBRC), XXXXXXX, KC__VOLDOWN, KC__MUTE, _______, \
      _______, KC_MRWD, KC_MPLY, KC_MFFD, XXXXXXX,       EISU,    EISU,    KANA,    KANA,    XXXXXXX, KC_MRWD, KC_MPLY, KC_MFFD, _______, \
      MO(_ADJUST),MO(_ADJUST),XXXXXXX, _______, _______, XXXXXXX, _______,
                                                                _______, XXXXXXX, _______, _______, XXXXXXX,MO(_ADJUST),MO(_ADJUST) \
      ),

    /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Reset|RGBRST|RGB ON|Aud on| Win  |             | Win  |Aud on|RGB ON|RGBRST|      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | HUE+ | SAT+ | VAL+ |RGB md|Audoff| Mac  |             | Mac  |Audoff|RGB md| VAL+ | SAT+ | HUE+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | HUE- | SAT- | VAL- |     |EUCALYN|QWERTY|      |      |QWERTY|EUCALYN|     | VAL- | SAT- | HUE- |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, RESET,   RGBRST,  RGB_TOG,   AU_ON, AG_SWAP,                   AG_SWAP,   AU_ON, RGB_TOG,  RGBRST, XXXXXXX, XXXXXXX, \
      RGB_HUI, RGB_SAI, RGB_VAI,RGB_SMOD,  AU_OFF, AG_NORM,                   AG_NORM,  AU_OFF,RGB_SMOD, RGB_VAI, RGB_SAI, RGB_HUI, \
      RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, EUCALYN,  QWERTY, _______, _______,  QWERTY, EUCALYN, XXXXXXX, RGB_VAD, RGB_SAD, RGB_HUD, \
      _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______ \
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
   * |Lower |Lower | Esc  | Alt  |  GUI | Space|  BS  | Enter| Space| GUI  |  Alt | Menu |Raise |Raise |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT, \
      MO(_LOWER), MO(_LOWER), KC_ESC, KC_LALT, KC_LGUI, KC_SPC, LT(_RAISE,KC_BSPC), \
                                                         LT(_LOWER,KC_ENT), KC_SPC,  KC_RGUI, KC_RALT, KC_APP,MO(_RAISE),MO(_RAISE) \
  ),

  /* Eucalyn
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Tab  |   Q  |   W  |   ,  |   .  |   ;  |             |   M  |   R  |   D  |   Y  |   P  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   O  |   E  |   I  |   U  |             |   G  |   T  |   K  |   S  |   N  | Ctrl |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   F  |             |   B  |   H  |   J  |   L  |   /  | Shift|
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |Lower | Lower| Esc  | GUI  | Alt  | Space|  BS  | Enter| Space| Alt  | GUI  | Menu |Lower |Lower |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_EUCALYN] = LAYOUT(
      KC_TAB,     KC_Q,       KC_W,   KC_COMM, KC_DOT, KC_SCLN,               KC_M, KC_R, KC_D, KC_Y, KC_P, KC_BSLS,
      KC_LCTL,    KC_A,       KC_O,   KC_E,    KC_I,   KC_U,                  KC_G, KC_T, KC_K, KC_S, KC_N, KC_RCTL,
      KC_LSFT,    KC_Z,       KC_X,   KC_C,    KC_V,   KC_F,                  KC_B, KC_H, KC_J, KC_L, KC_SLSH, KC_RSFT,
     MO(_LOWER), MO(_LOWER),  KC_ESC, KC_LALT, KC_LGUI, KC_SPC, LT(_RAISE, KC_BSPC),
                                          LT(_RAISE, KC_ENT), KC_SPC, KC_RGUI, KC_RALT, KC_APP, MO(_LOWER), MO(_LOWER)
  ),


  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   _  |   +  |   {  |   }  |  |   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  F7  |  F8  |  F9  |  F10 |  F11 |             |  F12 |      |      | Home | End  |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
      _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,                    KC_F12,  _______, _______, KC_HOME, KC_END,  _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   -  |   =  |   [  |   ]  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  F7  |  F8  |  F9  |  F10 |  F11 |             |  F12 |      |      |PageDn|PageUp|      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
      _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,                    KC_F12,  _______, _______, KC_PGDN, KC_PGUP, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
      ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      | Reset|      |      |      |      |             |      |      |      |      |      |  Del |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |Aud on|Audoff| Mac  |             | Win  |Qwerty|      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | MODE | HUE- | SAT- | VAL- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
      _______, RESET,   _______, _______, _______, _______,                   _______, _______, _______, _______, _______, KC_DEL, \
      _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM,                   AG_SWAP, QWERTY,  _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______,                   _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD \
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
  // 1<<_COLEMAK - 1 == 2 - 1 == _COLEMAK (=1)
  current_default_layer = state - 1;
  return state;
}

void update_base_layer(uint16_t default_layer)
{
  eeconfig_update_default_layer(1UL << default_layer);
  default_layer_set(1UL << default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode)
  {
  case QWERTY:
    if (record->event.pressed)
    {
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_qwerty);
#endif
      update_base_layer(_QWERTY);
    }
    return false;
    break;
  case EUCALYN:
    if (record->event.pressed)
    {
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_eucalyn);
#endif
      update_base_layer(_EUCALYN);
    }
    return false;
    break;
  case EISU:
    if (record->event.pressed)
    {
      if (keymap_config.swap_lalt_lgui == false)
      {
        register_code(KC_LANG2);
      }
      else
      {
        SEND_STRING(SS_LALT("`"));
      }
    }
    else
    {
      unregister_code(KC_LANG2);
    }
    return false;
    break;
  case KANA:
    if (record->event.pressed)
    {
      if (keymap_config.swap_lalt_lgui == false)
      {
        register_code(KC_LANG1);
      }
      else
      {
        SEND_STRING(SS_LALT("`"));
      }
    }
    else
    {
      unregister_code(KC_LANG1);
    }
    return false;
    break;
  case RGBRST:
#ifdef RGBLIGHT_ENABLE
    if (record->event.pressed)
    {
      eeconfig_update_rgblight_default();
      rgblight_enable();
    }
#endif
    break;
  case ONEPASS:
    if (record->event.pressed)
    {
      SEND_STRING(SS_LGUI("\\"));
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
  if (memcmp(dest->display, source->display, sizeof(dest->display)))
  {
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
      0};
  matrix_write(matrix, logo);
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_ANIMATIONS)
  char buf[30];
  if (rgblight_config.enable)
  {
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

static const char Qwerty_name[] PROGMEM = " Qwerty";
static const char Eucalyn_name[] PROGMEM = " Eucalyn ";

static const char Lower_name[] PROGMEM = ":Func";
static const char Raise_name[] PROGMEM = ":Extra";
static const char Adjust_name[] PROGMEM = ":Adjust";

static const char *layer_names[] = {
    [_QWERTY] = Qwerty_name,
    [_EUCALYN] = Eucalyn_name,
    [_LOWER] = Lower_name,
    [_RAISE] = Raise_name,
    [_ADJUST] = Adjust_name};

void render_status(struct CharacterMatrix *matrix)
{

  // Render to mode icon
  static char logo[][2][3] = {{{0x95, 0x96, 0}, {0xb5, 0xb6, 0}}, {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}}};
  if (keymap_config.swap_lalt_lgui == false)
  {
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }
  else
  {
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  int name_num;
  uint32_t lstate;
  matrix_write_P(matrix, layer_names[current_default_layer]);
  matrix_write_P(matrix, PSTR("\n"));
  for (lstate = layer_state, name_num = 0;
       lstate && name_num < sizeof(layer_names) / sizeof(char *);
       lstate >>= 1, name_num++)
  {
    if ((lstate & 1) != 0)
    {
      if (layer_names[name_num])
      {
        matrix_write_P(matrix, layer_names[name_num]);
      }
    }
  }

  // Host Keyboard LED Status
  char led[40];
  snprintf(led, sizeof(led), "\n%s  %s  %s",
           (host_keyboard_leds() & (1 << USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
           (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
           (host_keyboard_leds() & (1 << USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}

void iota_gfx_task_user(void)
{
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable)
  {
    return;
  }
#endif

  matrix_clear(&matrix);
  if (is_master)
  {
    render_status(&matrix);
  }
  else
  {
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
