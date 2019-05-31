#include QMK_KEYBOARD_H

// These are all aliases for the  function layers.
#define _BASE	0
#define _PROG	1
#define _GAME	2
#define _FN		7
#define _FN1	8
#define _NUM	9


/* Tap Dance  */
typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

//Tap dance enums
enum {
  S_PROG = 0,
};

int cur_dance (qk_tap_dance_state_t *state);
//for the x tap dance. Put it here so it can be used in any keymap
void x_finished (qk_tap_dance_state_t *state, void *user_data);
void x_reset (qk_tap_dance_state_t *state, void *user_data);


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
  KC_LCTL,		KC_LGUI,	KC_LALT,	TD(S_PROG),	KC_SPC,					KC_SPC,					MO(_FN),	KC_RALT,	KC_APP,					KC_RCTRL),	\


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
  _______,		_______,	_______,	_______,	_______,	_______,	KC_7,		KC_8,		KC_9,		_______,	_______,	_______,	_______,	\
  _______,		_______,	_______,	_______,	_______,	_______,	KC_4,		KC_5,		KC_6,		_______,	_______,				_______,	\
  _______,		_______,	_______,	_______,	_______,	KC_1,		KC_2,		KC_3,		KC_DOT,		_______,	_______,				_______,	\
  _______,		_______,	_______,	_______,	_______,				KC_0,					_______,	_______,	DEBUG,					RESET),	\
};


// NUMLOCK always on:
void led_set_keymap(uint8_t usb_led) {
  if (!(usb_led & (1<<USB_LED_NUM_LOCK))) {
    register_code(KC_NUMLOCK);
    unregister_code(KC_NUMLOCK);
  }
}

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void x_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: layer_on(_PROG); break;
    case SINGLE_HOLD: layer_on(_NUM); break;
    //case DOUBLE_TAP: register_code(KC_ESC); break;
    //case DOUBLE_HOLD: register_code(KC_LALT); break;
    //case DOUBLE_SINGLE_TAP: register_code(KC_X); unregister_code(KC_X); register_code(KC_X);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void x_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    //case SINGLE_TAP: unregister_code(KC_X); break;
    case SINGLE_HOLD: layer_off(_NUM); break;
    //case DOUBLE_TAP: unregister_code(KC_ESC); break;
    //case DOUBLE_HOLD: unregister_code(KC_LALT);
    //case DOUBLE_SINGLE_TAP: unregister_code(KC_X);
  }
  xtap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [S_PROG]		= ACTION_TAP_DANCE_FN_ADVANCED(NULL,x_finished, x_reset)
};
