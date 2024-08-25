/* Copyright 2022 DOIO
 * Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
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

// OLED animation
#include "./lib/layer_status/layer_status.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
    _BASE = 0,
    _MUSIC = 1,
    _NUMPAD = 2,
    _ADMIN = 3
};

// Map some buttons!
enum custom_keycodes {
    SPOTIFY = SAFE_RANGE, // SAFE_RANGE prevents it from using a clashing keycode
    OBS,
    A_S_TAB,
    A_TAB,
    _D20,
    PHOTO,
    VIDEO
};

// Super alt tab variables
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

// ALT TAB && ALT SHIFT TAB Timer
void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      unregister_code(KC_LSFT);
      is_alt_tab_active = false;
    }
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*=============================================*\
       ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
       │   │   │   │D20│   │CUS│ │TO1│
       ├───┼───┼───┼───┤   └───┘ └───┘
       │f13│f14│f15│f16│
       ├───┼───┼───┼───┤
       │f17│f18│f19│f20│      ┌───┐
       ├───┼───┼───┼───┤      │CUS│
       │f21│f22│f23│f24│      └───┘
       └───┴───┴───┴───┘
\*=============================================*/
    /*  Row:    0         1        2        3         4      */
    [_BASE] = LAYOUT(
                _______,  _______, _______, _D20,      C(KC_0), // Reset view size
                KC_F13,   KC_F14,  KC_F15,  KC_F16,    TO(_MUSIC),
                KC_F17,   KC_F18,  KC_F19,  KC_F20,    C(KC_W), // Close browser tab
                KC_F21,   KC_F22,  KC_F23,  KC_F24
            ),

/*=========MUSIC AND PROGRAM LAUNCHER==========*\
       ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
       │RUN│RUN│   │TO0│   │RUN│ │TO2│
       ├───┼───┼───┼───┤   └───┘ └───┘
       │   │RUN│   │   │
       ├───┼───┼───┼───┤
       │   │   │   │   │      ┌───┐
       ├───┼───┼───┼───┤      │PLY│
       │   │   │AST│AT │      └───┘
       └───┴───┴───┴───┘
\*=============================================*/
    /*  Row:    0        1        2        3          4       */
    [_MUSIC] = LAYOUT(
                OBS,     VIDEO,   _______, TO(_BASE), SPOTIFY,
                _______, PHOTO,   _______, _______,   TO(_NUMPAD),
                _______, _______, _______, _______,   KC_MPLY,
                _______, _______, A_S_TAB, A_TAB
            ),

/*=============================================*\
       ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
       │   │   │   │   │   │   │ │TO3│
       ├───┼───┼───┼───┤   └───┘ └───┘
       │   │   │   │   │
       ├───┼───┼───┼───┤
       │   │   │   │   │      ┌───┐
       ├───┼───┼───┼───┤      │   │
       │   │   │   │   │      └───┘
       └───┴───┴───┴───┘
\*=============================================*/
    /*  Row:    0        1        2        3        4       */
    [_NUMPAD] = LAYOUT(
                KC_KP_7, KC_KP_8, KC_KP_9, KC_PAST, _______,
                KC_KP_4, KC_KP_5, KC_KP_6, KC_PMNS, TO(_ADMIN),
                KC_KP_1, KC_KP_2, KC_KP_3, KC_PPLS, _______,
                KC_KP_0, KC_PSLS, KC_PDOT, KC_PENT
            ),

/*=====================RGB=====================*\
       ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
       │Sai│Vai│Hui│Res│   │   │ │TO0│
       ├───┼───┼───┼───┤   └───┘ └───┘
       │Sad│Vad│Hud│MOD│
       ├───┼───┼───┼───┤
       │Spi│Mod│Tog│MOD│      ┌───┐
       ├───┼───┼───┼───┤      │   │
       │Spd│Mod│   │   │      └───┘
       └───┴───┴───┴───┘
\*=============================================*/
    /*  Row:    0        1        2        3        4        */
    [_ADMIN] = LAYOUT(
                RGB_SAI, RGB_VAI,  RGB_HUI, QK_BOOT, _______,
                RGB_SAD, RGB_VAD,  RGB_HUD, _______,  TO(_BASE),
                RGB_SPI, RGB_MOD,  RGB_TOG, _______, _______,
                RGB_SPD, RGB_RMOD, _______, _______
            ),
};

// Tomfoolery time
// Function for opening program from start menu
void open_prog(char* str) {
    SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(250) "app:");
    SEND_STRING(str);
    SEND_STRING(SS_DELAY(500) SS_TAP(X_ENT));
}

// Boolean, has d20 been seeded
char d20_has_seed = 0;

// Handle custom keycodes here
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SPOTIFY:
            if (record->event.pressed) {
                open_prog("spotify");
            } else {
                // when keycode is released
            }
            break;
        case OBS:
            if (record->event.pressed) {
                open_prog("obs");
            }
            break;
        case PHOTO:
            if (record->event.pressed) {
                open_prog("on1 photo raw 2022");
            }
            break;
        case VIDEO:
            if (record->event.pressed) {
                open_prog("davinci resolve");
            }
            break;
        case _D20:
            if (record->event.pressed) {
                if (d20_has_seed == 0) {
                    // Seed the random :)
                    srand((unsigned int)timer_read());
                    d20_has_seed = 1;
                }

                unsigned char roll = rand() % 20 + 1;
                char res[3];
                res[0] = (char)((char)(roll / 10) + '0');
                res[1] = (char)(roll % 10 + '0');

                send_string(res);
            }
            break;
        case A_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case A_S_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_RSFT);
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
                unregister_code(KC_RSFT);
            }
            break;
    }
    return true;
}

#ifdef OLED_ENABLE
    bool oled_task_user(void) {
        render_layer_status();

        return true;
    }
#endif

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] = {
      // Mouse scroll down and up
      ENCODER_CCW_CW(KC_WH_D, KC_WH_U),
      // Zoom in and out
      ENCODER_CCW_CW(C(KC_MINS), C(KC_PLUS)),
      // Next previous tab
      ENCODER_CCW_CW(S(C(KC_TAB)), C(KC_TAB))
    },
    [_MUSIC] = {
      ENCODER_CCW_CW(KC_TRNS, KC_TRNS),
      // Previous and next track
      ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
      // Volume down and up
      ENCODER_CCW_CW(KC_VOLD, KC_VOLU)
    },
    [_NUMPAD] = {
      ENCODER_CCW_CW(KC_TRNS, KC_TRNS),
      ENCODER_CCW_CW(KC_TRNS, KC_TRNS),
      ENCODER_CCW_CW(KC_TRNS, KC_TRNS)
    },
    [_ADMIN] = {
      ENCODER_CCW_CW(KC_TRNS, KC_TRNS),
      ENCODER_CCW_CW(KC_TRNS, KC_TRNS),
      ENCODER_CCW_CW(KC_TRNS, KC_TRNS)
    },
};
#endif

#ifndef ENCODER_MAP_ENABLE
// Without map TODO: remove?
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (get_highest_layer(layer_state|default_layer_state) == _BASE) {
        switch(index) {
            case 0:
                if (clockwise) tap_code(KC_WH_U);
                else tap_code(KC_WH_D);
                break;
            case 1:
                if (clockwise) tap_code16(C(KC_PLUS));
                else tap_code16(C(KC_MINS));
                break;
            case 2:
                if (clockwise) tap_code16(C(KC_TAB));
                else tap_code16(S(C(KC_TAB)));
                break;
        }
    } else if (get_highest_layer(layer_state|default_layer_state) == _MUSIC) {
        switch(index) {
            case 0:
                if (clockwise) tap_code(KC_WH_D);
                else tap_code(KC_WH_U);
                break;
            case 1:
                if (clockwise) tap_code(KC_MNXT);
                else tap_code(KC_MPRV);
                break;
            case 2:
                if (clockwise) tap_code(KC_VOLU);
                else tap_code(KC_VOLD);
                break;
        }
    } else if (get_highest_layer(layer_state|default_layer_state) == _NUMPAD) {
        switch(index) {
            case 0:
                if (clockwise) tap_code(KC_WH_U);
                else tap_code(KC_WH_D);
                break;
            case 1:
                if (clockwise) tap_code16(C(KC_MINS));
                else tap_code16(C(KC_PLUS));
                break;
            case 2:
                if (clockwise) tap_code16(S(C(KC_TAB)));
                else tap_code16(C(KC_TAB));
                break;
        }
    } else if (get_highest_layer(layer_state|default_layer_state) == _ADMIN) {
        switch(index) {
            case 0:
                if (clockwise) tap_code(KC_WH_U);
                else tap_code(KC_WH_D);
                break;
            case 1:
                if (clockwise) tap_code16(C(KC_MINS));
                else tap_code16(C(KC_PLUS));
                break;
            case 2:
                if (clockwise) tap_code16(S(C(KC_TAB)));
                else tap_code16(C(KC_TAB));
                break;
        }
    }

    return false;
};
#endif
