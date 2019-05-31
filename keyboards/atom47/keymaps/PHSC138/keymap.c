#include QMK_KEYBOARD_H

// These are all aliases for the  function layers.
#define _BASE	0
#define _PROG	1
#define _GAME	2
#define _FN		7
#define _FN1	8
#define _NUM	9

//Tap Dance Declarations
enum {
  TD_ESC_CAPS = 0
};
//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS)
// Other declarations would go here, separated by commas, if you have them
};
//In Layer declaration, add tap dance item in place of a key code
//TD(TD_ESC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// TREE: 'pn' to enter custom layers:
	// _BASE
		// _FN
		// _FN1
		// TODO: _NUM
		// _PROG
	// _PROG
		// _FN
		// _FN1
		// TODO: _NUM
		// _GAME
	// _GAME
		// _BASE

// TODO tap pn for toggle to _PROG, hold for numpad
[_BASE] = LAYOUT(
  KC_ESC,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,		KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_DEL,		KC_BSPC,	\
  KC_TAB,		KC_A,		KC_S,		KC_D,		KC_F,		KC_G,		KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,				KC_ENT,		\
  KC_LSFT,		KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,		KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_RSFT,				MO(_FN1),	\
  KC_LCTL,		KC_LGUI,	KC_LALT,	TO(_PROG),	KC_SPC,					KC_SPC,					MO(_FN),	KC_RALT,	KC_APP,					KC_RCTRL),	\


// LEFT AND RIGHT SHIFT: '(' and ')' when tapped, shift when held
[_PROG] = LAYOUT(
  KC_ESC,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,		KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_DEL,		KC_BSPC,	\
  KC_TAB,		KC_A,		KC_S,		KC_D,		KC_F,		KC_G,		KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,				KC_ENT,		\
  KC_LSPO,		KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,		KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_RSPC,				MO(_FN1),	\
  KC_LCTL,		KC_LGUI,	KC_LALT,	TO(_GAME),	KC_SPC,					KC_SPC,					MO(_FN),	KC_RALT,	KC_APP,					KC_RCTRL),	\


//MT(mod, kc) - is mod (modifier key - MOD_LCTL, MOD_LSFT) when held, and kc when tapped.

// Macro for 'pn' is to return to base layer
// Macro for right space is bhop
// Maco for 'fn' is move forward
// Macro for 'fn1' is spin constantly
[_GAME] = LAYOUT(
  KC_ESC,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,		KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_DEL,		KC_BSPC,	\
  KC_TAB,		KC_A,		KC_S,		KC_D,		KC_F,		KC_G,		KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,				KC_ENT,		\
  KC_LSFT,		KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,		KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_RSFT,				XXXXXXX,	\
  KC_LCTL,		KC_LGUI,	KC_LALT,	TO(_BASE),	KC_SPC,					XXXXXXX,				XXXXXXX,	KC_RALT,	XXXXXXX,				KC_RCTRL),	\


[_FN] = LAYOUT(
  _______,		KC_VOLD,	KC_VOLU,	KC_MUTE,	RESET,		_______,	KC_CALC,	KC_PGUP,	_______,	KC_PGDN,	KC_PSCR,	KC_SLCK,	KC_PAUS,	\
  KC_CAPS,		KC_MPRV,	KC_MPLY,	KC_MNXT,	_______,	_______,	KC_LEFT,	KC_DOWN,	KC_UP,		KC_RIGHT,	KC_INS,					_______,	\
  _______,		_______,	_______,	_______,	_______,	KC_HOME,	KC_END,		BL_TOGG,	BL_DEC,		BL_INC,		_______,				_______,	\
  _______,		_______,	_______,	_______,	_______,				_______,				_______,	_______,	_______,				_______),	\


[_FN1] = LAYOUT(
  KC_GRV,		KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,		KC_F12,		\
  KC_1,			KC_2,		KC_3,		KC_4,		KC_5,		KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,				KC_EQL,		\
  _______,		_______,	_______,	_______,	_______,	KC_QUOT,	KC_SLSH,	KC_LBRC,	KC_RBRC,	KC_BSLS,	KC_RSFT,				_______,	\
  _______,		_______,	_______,	_______,	_______,				_______,				_______,	_______,	_______,				_______),	\


[_NUM] = LAYOUT(
  _______,		_______,	_______,	_______,	_______,	_______,	KC_P7,		KC_P8,		KC_P9,		_______,	_______,	_______,	_______,	\
  _______,		_______,	_______,	_______,	_______,	_______,	KC_P4,		KC_P5,		KC_P6,		_______,	_______,				_______,	\
  _______,		_______,	_______,	_______,	_______,	KC_P1,		KC_P2,		KC_P3,		KC_PDOT,	_______,	_______,				_______,	\
  _______,		_______,	_______,	_______,	_______,				KC_P0,					_______,	_______,	DEBUG,					RESET),	\
};
