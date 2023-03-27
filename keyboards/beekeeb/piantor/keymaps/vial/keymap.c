// Copyright 2022 Diego Palacios (@diepala)
// SPDX-License-Identifier: GPL-2.0

#include QMK_KEYBOARD_H

enum custom_keycodes {
  C_GESC = USER00,
  ALT_TAB,
  GUI_TAB,
  GUI_GRV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │Tab│ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │Bsp│
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Ctl│ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ ; │ ' │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Sft│ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ / │Sft│
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                   ┌───┐
      *               │GUI├───┐           ┌───┤Alt│
      *               └───┤   ├───┐   ┌───┤   ├───┘
      *                   └───┤Bsp│   │Ent├───┘
      *                       └───┘   └───┘
      */
    [0] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                            KC_LGUI, KC_SPC, KC_BSPC,          KC_ENT, KC_SPC, KC_RALT
    ),

    [1] = LAYOUT_split_3x6_3(
        KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                               KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                               KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                               KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [2] = LAYOUT_split_3x6_3(
        KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                               KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                               KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                               KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [3] = LAYOUT_split_3x6_3(
        KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                               KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                               KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                               KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
    )
};

bool is_alt_tab_active = false;

layer_state_t layer_state_set_user(layer_state_t state) {
    if (is_alt_tab_active) {
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
        is_alt_tab_active = false;
    }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  static uint16_t lctl_timer;

  switch (keycode) {
    case C_GESC:
        if(record->event.pressed) {
            lctl_timer = timer_read();
            register_code(KC_LCTL); // Change the key to be held here
        }
        else {
            unregister_code(KC_LCTL); // Change the key that was held here, too!
            if (timer_elapsed(lctl_timer) < TAPPING_TERM) {
                if (get_mods() & MOD_BIT(KC_LGUI)) {
                    tap_code(KC_GRAVE);
                } else {
                    tap_code(KC_ESC);
                }
            }
        }
        return false; // We handled this keypress

    case ALT_TAB: // super alt tab macro
    case GUI_TAB:
        if (record->event.pressed) {
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(keycode == ALT_TAB ? KC_LALT : KC_LGUI);
            }
            register_code(KC_TAB);
        } else {
            unregister_code(KC_TAB);
        }
        break;

    case GUI_GRV:
        if (record->event.pressed) {
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(keycode == ALT_TAB ? KC_LALT : KC_LGUI);
            }
            register_code(KC_GRV);
        } else {
            unregister_code(KC_GRV);
        }
        break;
  }
  return true;
}

bool get_tapping_force_hold_user(uint16_t keycode, keyrecord_t *record, bool _default) {
  switch (keycode) {
    case LT(4, KC_SPC):
    case LT(3, KC_BSPC):
      return true;
    default:
      return _default;
  }
}

uint16_t get_tapping_term_user(uint16_t keycode, keyrecord_t *record, uint16_t _default) {
  switch (keycode) {
    // keys used in fast combos, works fine with default TAPPING_TERM of 150
    case C_GESC:
    case LCTL_T(KC_QUOTE):
    case LT(3, KC_BSPC):
      return _default - 50;
    default:
      return _default;
  }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (layer_state_is(4)) {
    // clockwise ? tap_code(KC_BRIU) : tap_code(KC_BRID);
    clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD);
  }
  else if (layer_state_is(2)) {
    clockwise ? tap_code(KC_RIGHT) : tap_code(KC_LEFT);

    /* undo/redo
    if (get_mods() & MOD_BIT(KC_LSHIFT)) {  // use shift-z for redo
        if (clockwise) {
            tap_code16(LCTL(KC_Z));         // shift is already pressed
        } else {
            // WITHOUT_MODS({
            //     tap_code16(LCTL(KC_Z));
            // });
        }
    }
    else {                                  // use ctrl-y for redo
      clockwise ? tap_code16(LCTL(KC_Y)) : tap_code16(LCTL(KC_Z));
    }
    */
  }
  else if (layer_state_is(3)) {
      // nothing
  }
  else {  // default layer
    // change desktop ctrl-alt-up/down (also move window with shift)
    if ((get_mods() & MOD_BIT(KC_LCTL)) && (get_mods() & MOD_BIT(KC_LALT))) {
      clockwise ? tap_code(KC_DOWN) : tap_code(KC_UP);
    }
    // alt-tab for windows, ctrl-tab for browser tabs (XOR/(!a != !b), only ONE of alt/ctrl pressed)
    else if (get_mods() & (MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI))) {
        clockwise ? tap_code(KC_TAB) : tap_code16(LSFT(KC_TAB));
    }
    else if (get_mods() & MOD_BIT(KC_LCTL)) {
        // clockwise ? tap_code(KC_TAB) : tap_code16(LSFT(KC_TAB));
        clockwise ? tap_code16(LCTL(KC_PGDN)) : tap_code16(LCTL(KC_PGUP));
    }
    else {
        clockwise ? tap_code(KC_WH_D) : tap_code(KC_WH_U);
    }
  }

  return false;
}
