#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
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
#define _QWERTY 0
#define _ASTARTE 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  ASTARTE,
  LOWER,
  RAISE,
  ADJUST,

  GUIEI, // GUI when hold, EISU/MHEN when tapped.
  ALTKN, // ALT when hold, KANA/HENK when tapped.
  SFTSP, // Shift when hold, Space when tapped.
  SSSPC, // Shift when hold, Shift + Space when tapped.
  LWRTB, // Lower when hold, Tab when tapped.
  LWGTB, // Lower when hold, GUI+Tab when tapped.
  RSBSP, // Raise when hold, BS when tapped.
  RSDEL, // Raise when hold, BS when tapped.

  BACKLIT,
  RGBRST,

  F1x,
  F2x,
  F3x,
  F4x,
  F5x,
  F6x,
  F7x,
  F8x,
  F9x,
  F10x
};

#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

// enum macro_keycodes {
//   KC_SAMPLEMACRO,
// };

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_QWERTY QWERTY
#define KC_ASTARTE ASTARTE
#define KC_LOWER LOWER
#define KC_RAISE RAISE

#define KC_GUIEI GUIEI
#define KC_ALTKN ALTKN
#define KC_SFTSP SFTSP
#define KC_SSSPC SSSPC
#define KC_LWRTB LWRTB
#define KC_LWGTB LWGTB
#define KC_RSBSP RSBSP
#define KC_RSDEL RSDEL

#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD

#define KC_CTLEC CTL_T(KC_ESC)

#define KC_EIKN   LALT(KC_GRV)
#define KC_ALENT  LALT(KC_ENT)

#define KC_F1x F1x
#define KC_F2x F2x
#define KC_F3x F3x
#define KC_F4x F4x
#define KC_F5x F5x
#define KC_F6x F6x
#define KC_F7x F7x
#define KC_F8x F8x
#define KC_F9x F9x
#define KC_F10x F10x

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        GRV,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  MINS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLEC,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  GUIEI, LWRTB, SFTSP,     ENT, RSBSP, ALTKN \
                              //`--------------------'  `--------------------'
  ),

    [_ASTARTE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        GRV,     Q,     P,     U,     Y,  COMM,                      J,     D,     H,     G,     W,  MINS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLEC,     I,     O,     E,     A,   DOT,                      K,     T,     N,     S,     R,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     F,                      M,     L,     B,  SCLN,  SLSH,  RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  GUIEI, LWRTB, SFTSP,     ENT, RSBSP, ALTKN \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       EIKN,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,  PSLS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLEC,   F1x,   F2x,   F3x,   F4x,   F5x,                   PDOT,     4,     5,     6,  PMNS,  PAST,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,   F6x,   F7x,   F8x,   F9x,  F10x,                    TAB,     1,     2,     3,  PPLS,  PENT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    ALENT, RSDEL, LALT \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      XXXXX,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLEC, XXXXX,  LCBR,  RCBR,  LBRC,  RBRC,                   LEFT,  DOWN,    UP, RIGHT,   APP,  PSCR,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT, XXXXX, XXXXX, XXXXX,  PIPE,  BSLS,                   UNDS,   EQL,  PLUS,  MINS, XXXXX, PAUSE,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LGUI,LWGTB,  SSSPC,    _____, _____, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  LRST, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX,QWERTY,ASTARTE,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI, XXXXX, XXXXX,                   HOME,  PGDN,  PGUP,   END, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____, _____ \
                              //`--------------------'  `--------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
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
#endif//SSD1306OLED

static bool gui_pressed = false;
static bool alt_pressed = false;
static bool shift_pressed = false;
static bool lower_pressed = false;
static bool raise_pressed = false;

static uint16_t gui_pressed_time = 0;
static uint16_t alt_pressed_time = 0;
static uint16_t shift_pressed_time = 0;
static uint16_t lower_pressed_time = 0;
static uint16_t raise_pressed_time = 0;

void reset_hold(void) {
  lower_pressed = false;
  raise_pressed = false;
  gui_pressed = false;
  alt_pressed = false;
  shift_pressed = false;
}

static bool f_key_mods = false;
static const uint16_t f_key_codes[20] = {
  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
  KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        reset_hold();
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case ASTARTE:
      if (record->event.pressed) {
        reset_hold();
        persistent_default_layer_set(1UL<<_ASTARTE);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        reset_hold();
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        reset_hold();
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          reset_hold();
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;

    case GUIEI:
      if (record->event.pressed) {
        reset_hold();
        gui_pressed = true;
        gui_pressed_time = record->event.time;

        register_code(KC_LGUI);
      } else {
        unregister_code(KC_LGUI);

        if (gui_pressed && (TIMER_DIFF_16(record->event.time, gui_pressed_time) < TAPPING_TERM)) {
          register_code(KC_LANG2); // macOS
          register_code(KC_MHEN); // win
          unregister_code(KC_MHEN);
          unregister_code(KC_LANG2);
        }
        gui_pressed = false;
      }
      return false;
      break;
    case ALTKN:
      if (record->event.pressed) {
        reset_hold();
        alt_pressed = true;
        alt_pressed_time = record->event.time;

        register_code(KC_LALT);
      } else {
        unregister_code(KC_LALT);

        if (alt_pressed && (TIMER_DIFF_16(record->event.time, alt_pressed_time) < TAPPING_TERM)) {
          register_code(KC_LANG1); // macOS
          register_code(KC_HENK); // win
          unregister_code(KC_HENK);
          unregister_code(KC_LANG1);
        }
        alt_pressed = false;
      }
      return false;
      break;
    case SFTSP:
      if (record->event.pressed) {
        reset_hold();
        shift_pressed = true;
        shift_pressed_time = record->event.time;

        register_code(KC_LSFT);
      } else {
        unregister_code(KC_LSFT);

        if (shift_pressed && (TIMER_DIFF_16(record->event.time, shift_pressed_time) < TAPPING_TERM)) {
          register_code(KC_SPC);
          unregister_code(KC_SPC);
        }
        shift_pressed = false;
      }
      return false;
      break;

    case SSSPC:
      if (record->event.pressed) {
        reset_hold();
        shift_pressed = true;
        shift_pressed_time = record->event.time;

        register_code(KC_LSFT);
      } else {

        if (shift_pressed && (TIMER_DIFF_16(record->event.time, shift_pressed_time) < TAPPING_TERM)) {
          register_code(KC_SPC);
          unregister_code(KC_SPC);
        }
        unregister_code(KC_LSFT);

        shift_pressed = false;
      }
      return false;
      break;

    case LWRTB:
      if (record->event.pressed) {
        reset_hold();
        lower_pressed = true;
        lower_pressed_time = record->event.time;

        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        if (lower_pressed && (TIMER_DIFF_16(record->event.time, lower_pressed_time) < TAPPING_TERM)) {
          register_code(KC_TAB);
          unregister_code(KC_TAB);
        }
        lower_pressed = false;
      }
      return false;
      break;
    case LWGTB:
      if (record->event.pressed) {
        reset_hold();
        lower_pressed = true;
        lower_pressed_time = record->event.time;

        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        if (lower_pressed && (TIMER_DIFF_16(record->event.time, lower_pressed_time) < TAPPING_TERM)) {
          register_code(KC_LGUI);
          register_code(KC_TAB);
          unregister_code(KC_TAB);
          unregister_code(KC_LGUI);
        }
        lower_pressed = false;
      }
      return false;
      break;
    case RSBSP:
      if (record->event.pressed) {
        reset_hold();
        raise_pressed = true;
        raise_pressed_time = record->event.time;

        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        if (raise_pressed && (TIMER_DIFF_16(record->event.time, raise_pressed_time) < TAPPING_TERM)) {
          register_code(KC_BSPC);
          unregister_code(KC_BSPC);
        }
        raise_pressed = false;
      }
      return false;
      break;
    case RSDEL:
      if (record->event.pressed) {
        reset_hold();
        raise_pressed = true;
        raise_pressed_time = record->event.time;

        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        if (raise_pressed && (TIMER_DIFF_16(record->event.time, raise_pressed_time) < TAPPING_TERM)) {
          register_code(KC_DEL);
          unregister_code(KC_DEL);
        }
        raise_pressed = false;
      }
      return false;
      break;

    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          reset_hold();
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          reset_hold();
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case F1x:
    case F2x:
    case F3x:
    case F4x:
    case F5x:
    case F6x:
    case F7x:
    case F8x:
    case F9x:
    case F10x:
      {
        uint8_t kc = f_key_codes[keycode - F1x];
        if (record->event.pressed) {
          reset_hold();
          if (keyboard_report->mods & MODS_SHIFT_MASK) {
            kc = f_key_codes[keycode - F1x + 10];
          }
          register_code(kc);
          f_key_mods = keyboard_report->mods;
        }
        else {
          if (f_key_mods) {
            kc = f_key_codes[keycode - F1x + 10];
          }
          unregister_code (kc);
        }
      }
      return false;
      break;
    default:
      if (record->event.pressed) {
        reset_hold();
      }
      break;
  }
  return true;
}
