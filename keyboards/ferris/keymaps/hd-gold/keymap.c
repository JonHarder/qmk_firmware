#include QMK_KEYBOARD_H

#include "oneshot.h"
#include "swapper.h"

/* ====== Keybinding macros ===================*/
// Layer shifts
#define LA_SYM MO(_SYM)
#define LA_NAV MO(_NAV)

// shift focus right screen
#define AM_RIGHT  LSA(KC_L)
// shift focus left screen
#define AM_LEFT   LSA(KC_H)
// shift focus to next window
#define AM_NEXT   LSA(KC_J)
// shift focus to previous window
#define AM_PREV   LSA(KC_K)

// throw window to right window?
#define AM_WRIGHT MEH(KC_E)
// throw window to left window?
#define AM_WLEFT  MEH(KC_W)


// move right one desktop
#define DK_RIGHT C(KC_RIGHT)
// move left one desktop
#define DK_LEFT C(KC_LEFT)

// delete a word (for applications that support this keybinding)
#define BSWORD    C(KC_W)


/* Copy, paste */
#define COPY  G(KC_C)
#define PASTE G(KC_V)


// Screenshot with selection
#define KC_CAPP LGUI(LSFT(KC_4))
/* ============================================ */

/* ========= COMBO ENVETS ===================== */
enum combo_events {
    COMBO_Z,
    COMBO_Q,
    COMBO_ESC,
    // single letter outputs
    COMBO_REPEAT,
    // combo actions (multi-key combos)
    COMBO_TH,
    COMBO_CH,
    COMBO_SH,
    COMBO_WH,
    COMBO_GH,
    COMBO_PH,
    COMBO_CD,
    // word combos
    COMBO_THE,

    // quick access to symbols
    COMBO_COLON,
    COMBO_QUEST,

    // macros
    COMBO_CAPS_WORD,
    // no touchey
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

struct adaptive_key {
  uint16_t prior_key;
  uint16_t current_key;
  uint16_t new_key1;
  uint16_t new_key2;
};


// single lstter outputs
const uint16_t PROGMEM combo_z[]         = {KC_J, KC_G, COMBO_END};
const uint16_t PROGMEM combo_q[]         = {KC_G, KC_P, COMBO_END};
// const uint16_t PROGMEM combo_repeat[] = {KC_C, KC_S, COMBO_END};
// Common H digraphs
const uint16_t PROGMEM combo_th[]        = {KC_D, KC_N, COMBO_END};
const uint16_t PROGMEM combo_ch[]        = {KC_C, KC_L, COMBO_END};
const uint16_t PROGMEM combo_sh[]        = {KC_S, KC_N, COMBO_END};
const uint16_t PROGMEM combo_wh[]        = {KC_W, KC_C, COMBO_END};
const uint16_t PROGMEM combo_ph[]        = {KC_P, KC_M, COMBO_END};
const uint16_t PROGMEM combo_gh[]        = {KC_G, KC_M, COMBO_END};

const uint16_t PROGMEM combo_cd[]        = {KC_C, KC_N, COMBO_END};
// word combos
const uint16_t PROGMEM combo_the[]       = {KC_S, KC_N, KC_D, COMBO_END};
// quick access to symbols
const uint16_t PROGMEM combo_colon[]     = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM combo_quest[]     = {KC_DOT, KC_DQUO, COMBO_END};
// macros
const uint16_t PROGMEM combo_caps_word[] = {KC_D, KC_A, COMBO_END};
const uint16_t PROGMEM combo_esc[]       = {KC_R, KC_S, COMBO_END};

combo_t key_combos[] = {
    [COMBO_Z] = COMBO(combo_z, KC_Z),
    [COMBO_Q] = COMBO(combo_q, KC_Q),
    [COMBO_CAPS_WORD] = COMBO(combo_caps_word, CW_TOGG),
    [COMBO_ESC] = COMBO(combo_esc, KC_ESC),
    // combo actions
    [COMBO_TH] = COMBO_ACTION(combo_th),
    [COMBO_CH] = COMBO_ACTION(combo_ch),
    [COMBO_SH] = COMBO_ACTION(combo_sh),
    [COMBO_WH] = COMBO_ACTION(combo_wh),
    [COMBO_PH] = COMBO_ACTION(combo_ph),
    [COMBO_GH] = COMBO_ACTION(combo_gh),
    [COMBO_CD] = COMBO_ACTION(combo_cd),
    // whole word combos
    [COMBO_THE] = COMBO_ACTION(combo_the),
    // quick access to symbols
    [COMBO_COLON] = COMBO(combo_colon, KC_COLON),
    [COMBO_QUEST] = COMBO(combo_quest, KC_QUES)
};

/* ========= END COMBO EVENTS ================= */



/* ======== Custom keycodes =================== */
enum custom_keycodes {
  VRSN = SAFE_RANGE,
  M_THIS,
  REPEAT,
  OS_SHFT,
  OS_CTRL,
  OS_OPT,
  OS_CMD,
  ILL,
  IVE,
  SW_WIN,
  SW_LANG
};
/* ============================================ */


/* ====== LAYERS ============================*/
enum ferris_layers { _BSE, _NAV, _SYM, _NUM, _OSH };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [_BSE] = LAYOUT_split_3x5_2( /* Base layer */
		KC_J,      KC_G,      KC_M,    KC_P,    KC_V,       KC_SCLN,  KC_DOT,  KC_SLSH,  KC_DQUO,   KC_QUOT,
		KC_R,      KC_S,      KC_N,    KC_D,    KC_B,       KC_COMM,  KC_A,    KC_E,     KC_I,      KC_H,
		KC_X,      KC_F,      KC_L,    KC_C,    KC_W,       KC_UNDS,  KC_U,    KC_O,     KC_Y,      KC_K,
		                               LA_NAV,  KC_T,       KC_SPC,   LA_SYM
	),
	[_NAV] = LAYOUT_split_3x5_2( /* Navigation */
		SW_WIN,    C(KC_SPC), KC_MPRV, KC_MNXT, KC_VOLU,    AM_WLEFT, DK_LEFT, DK_RIGHT, AM_WRIGHT, BSWORD,
		OS_CTRL,   OS_OPT,    OS_CMD,  OS_SHFT, KC_VOLD,    KC_LEFT,  KC_DOWN, KC_UP,    KC_RGHT,   KC_BSPC,
		OSL(_OSH), COPY,      PASTE,   C(KC_C), KC_MPLY,    AM_LEFT,  AM_NEXT, AM_PREV,  AM_RIGHT,  KC_ENT,
		                               _______, _______,    KC_TAB,   _______
		/*                             LA_NAV                                                          */
	),
	[_SYM] = LAYOUT_split_3x5_2( /* Symbols */
                KC_CIRC,   KC_LBRC,   KC_LCBR, KC_LPRN, KC_TILD,    KC_AMPR,  KC_RPRN, KC_RCBR,  KC_RBRC, KC_GRV,
		KC_ASTR,   KC_MINS,   KC_EQL,  KC_GT,   KC_DLR,     KC_COLN,  OS_SHFT, OS_CMD,   OS_OPT,  OS_CTRL,
		KC_AT,     KC_PIPE,   KC_HASH, KC_LT,   KC_PERC,    KC_PLUS,  KC_HOME, KC_END,   KC_CAPP, KC_BSLS,
		                               _______, KC_SPC,     _______, _______
		/*                                                           LA_SYM                             */
        ),
	[_NUM] = LAYOUT_split_3x5_2(
                KC_TRNS,  KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,   KC_P7, KC_P8, KC_P9, KC_EQL,
                OS_CTRL,  OS_OPT,     OS_CMD,  OS_SHFT, KC_TRNS,     KC_TRNS,   KC_P4, KC_P5, KC_P6, KC_BSPC,
                QK_BOOT,  KC_PDOT,    KC_MINS, KC_COLN, KC_TRNS,     KC_TRNS,   KC_P1, KC_P2, KC_P3, KC_P0,
                                               _______, _______,     _______, _______
        ),               /*                             LA_NAV                         LA_SYM                            */
        [_OSH] = LAYOUT( /* [> One Shot Layer <] */
          KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,           KC_NO, KC_F7, KC_F8, KC_F9, KC_F12,
          OS_CTRL, OS_OPT,  OS_CMD, OS_SHFT, KC_NO,           KC_NO, KC_F4, KC_F5, KC_F6, KC_F11,
          KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,           KC_NO, KC_F1, KC_F2, KC_F3, KC_F10,
                                      _______, _______,          _______, _______
        )
};

/* MOD STATE TRACKING */
uint16_t saved_mods;
uint16_t prior_keycode = KC_NO; // for process_adaptive_key and process_caps_word
uint16_t prior_keydown = 0;     // time since finished processing prior_keycode

uint16_t linger_key = 0;
uint32_t linger_timer = 0;


#define register_linger_key(kc) {register_code16(kc); linger_key = kc; linger_timer = timer_read();}
#define unregister_linger_key() {unregister_code16(linger_key); linger_key = 0;}

/* END MOD STATE TRACKING */

/* ONESHOT SETUP */
oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_opt_state  = os_up_unqueued;
oneshot_state os_cmd_state  = os_up_unqueued;

bool sw_win_active = false;
bool sw_lang_active = false;

bool is_oneshot_cancel_key(uint16_t keycode) {
  switch(keycode) {
  case LA_SYM:
  case LA_NAV:
    return true;
  default:
    return false;
  }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case LA_SYM:
        case LA_NAV:
        case KC_LSFT:
        case OS_SHFT:
        case OS_CTRL:
        case OS_OPT:
        case OS_CMD:
            return true;
        default:
            return false;
    }
}

/* END ONSHOT SETUP */

/* Process combo events */
// DONE: caps words doesn't capitalize combos
// DONE: Seems like shifted combos are acting kinda funny now
// TODO: Still seems like there's some bugs to work out.
// ex. hit caps word, hit a combo, space, than any series of letters:
// THIS IS The message that
void process_combo_event(uint16_t combo_index, bool pressed) {
  saved_mods = get_mods();
  bool caps_on = is_caps_word_on();
  if (pressed) {
    switch (combo_index) {
    case COMBO_THE:
      tap_code(KC_T);
      if (saved_mods & MOD_MASK_SHIFT && !caps_on) {
	unregister_mods(MOD_MASK_SHIFT);
      }
      send_string("he");
      break;
    case COMBO_TH:
      tap_code(KC_T);
      if (saved_mods & MOD_MASK_SHIFT && !caps_on) {
	unregister_mods(MOD_MASK_SHIFT);
      }
      tap_code(KC_H);
      break;
    case COMBO_CH:
      tap_code(KC_C);
      if (saved_mods & MOD_MASK_SHIFT && !caps_on) {
	unregister_mods(MOD_MASK_SHIFT);
      }
      tap_code(KC_H);
      break;
    case COMBO_SH:
      tap_code(KC_S);
      if (saved_mods & MOD_MASK_SHIFT && !caps_on) {
	unregister_mods(MOD_MASK_SHIFT);
      }
      tap_code(KC_H);
      break;
    case COMBO_WH:
      tap_code(KC_W);
      if (saved_mods & MOD_MASK_SHIFT && !caps_on) {
	unregister_mods(MOD_MASK_SHIFT);
      }
      tap_code(KC_H);
      break;
    case COMBO_PH:
      tap_code(KC_P);
      if (saved_mods & MOD_MASK_SHIFT && !caps_on) {
	unregister_mods(MOD_MASK_SHIFT);
      }
      tap_code(KC_H);
      break;
    case COMBO_GH:
      tap_code(KC_G);
      if (saved_mods & MOD_MASK_SHIFT && !caps_on) {
	unregister_mods(MOD_MASK_SHIFT);
      }
      tap_code(KC_H);
      break;
    case COMBO_CD:
      tap_code(KC_C);
      if (saved_mods & MOD_MASK_SHIFT && !caps_on) {
	unregister_mods(MOD_MASK_SHIFT);
      }
      tap_code(KC_D);
    }
  }
}



struct adaptive_key adaptive_keys[] = {
  {KC_G, KC_M, KC_L},       // GM -> GL
  {KC_P, KC_M, KC_L},       // PM -> PL
  {KC_P, KC_V, KC_L, KC_V}, // PV -> LV
  {KC_B, KC_D, KC_L},       // BD -> BL
  {KC_D, KC_B, KC_L, KC_B}, // DB -> LB
  {KC_A, KC_COMM, KC_U},    // A, -> AU
  {KC_E, KC_H, KC_O},       // EH -> EO
  {KC_U, KC_H, KC_A},       // UH -> UA
  {KC_J, KC_G, KC_G, KC_S}, // JG -> GS
  {KC_O, KC_H, KC_E},       // OH -> OE
  {KC_W, KC_C, KC_N}        // WC -> WN
};

// Runs constantly in the background, in a loop
void matrix_scan_user(void) {
  if (linger_key && timer_elapsed(linger_timer) > LINGER_TIME) {
    saved_mods = get_mods();
    clear_mods();
    unregister_mods(MOD_MASK_SHIFT);
    switch(linger_key) {
    case KC_Q:
      tap_code(KC_U);
      break;
    case KC_LT:
      tap_code16(KC_GT);
      tap_code(KC_LEFT);
      break;
    case KC_LBRC:
      tap_code(KC_RBRC);
      tap_code(KC_LEFT);
      break;
    case KC_LCBR:
      tap_code16(KC_RCBR);
      tap_code(KC_LEFT);
      break;
    case KC_LPRN:
      tap_code16(KC_RPRN);
      tap_code(KC_LEFT);
      break;
    case KC_QUOT:
      tap_code(KC_QUOT);
      tap_code(KC_LEFT);
      break;
    case KC_DQUO:
      tap_code16(KC_DQUO);
      tap_code(KC_LEFT);
    default:
      break;
    }
    linger_timer = linger_key = 0; // done lingering
    set_mods(saved_mods);
  }
}

/* ADAPTIVE KEYS */
bool process_adaptive_keys(uint16_t keycode, keyrecord_t *record) {
    // e.g. does the key still need processing?
    bool continue_processing = true; // assume we didn't handle the key here.

    if (record->event.pressed) {
        if ((timer_elapsed(prior_keydown) < ADAPTIVE_TERM)) {
            saved_mods = get_mods(); //
            clear_mods();
            keycode = keycode & 0xFF; // taps&mods handled earlier.
            if (is_caps_word_on()) {
                add_weak_mods(MOD_BIT(KC_LSFT));
            }

	    // loop through all available adaptive key configuration
	    for (int i=0; i<sizeof(adaptive_keys)/sizeof(struct adaptive_key); i++) {
	      // if the previous key and current key match this adaptive key set:
	      if (prior_keycode == adaptive_keys[i].prior_key && keycode == adaptive_keys[i].current_key) {
		// some adaptive keys just send a different code for the given `keycode`. These adaptive
		// keys will have their `new_key2` set to 0.
		// This means we simply send an altered key instead of the one pressed (new_key1)
		if (adaptive_keys[i].new_key2 == 0) {
		  tap_code(adaptive_keys[i].new_key1);
		} else {
		  // Other adaptive keys replace the previous key AND the current key.
		  // We know this by having an adaptive key record with a non-zero `new_key2`
		  // In these instances, we delete the previous key and send both new keys
		  // i.e. `new_key1` and `new_key2`.
		  tap_code(KC_BSPC);
		  tap_code(adaptive_keys[i].new_key1);
		  tap_code(adaptive_keys[i].new_key2);
		}
		// in either case, we have processed this key and so we indicate to the caller
		// that no further processing is needed.
		continue_processing = false;
		break;
	      }
	    }
            set_mods(saved_mods); // Restore mods
        }
        prior_keycode = keycode;      // this keycode is stripped of mods+taps
        prior_keydown = timer_read(); // (re)start prior_key timing
    }
    return continue_processing;
}
/* END ADAPTIVE KEYS */


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  update_swapper(
      &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
      keycode, record
  );
  update_swapper(
      &sw_lang_active, KC_LCTL, KC_SPC, SW_LANG,
      keycode, record
  );

  update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
  update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record);
  update_oneshot(&os_opt_state,  KC_LOPT, OS_OPT,  keycode, record);
  update_oneshot(&os_cmd_state,  KC_LCMD, OS_CMD,  keycode, record);

  saved_mods =        get_mods();
  bool return_state = true;

  if (!process_adaptive_keys(keycode, record)) {
    // This means we already took care of the key
    // and do not need to process it further
    return false;
  }

  if (record->event.pressed) {
    if (is_caps_word_on()) add_weak_mods(MOD_BIT(KC_LSFT));
    switch(keycode) {
    case KC_Q:
      register_linger_key(keycode);
      return_state = false;
      break;
    case KC_LBRC:
    case KC_LCBR:
    case KC_LPRN:
      register_linger_key(keycode);
      return_state = false;
      break;
    case KC_LT:
      register_linger_key(keycode);
      return_state = false;
      break;
    case KC_HASH:
      if (saved_mods & MOD_MASK_SHIFT) {
	set_mods(saved_mods & ~MOD_MASK_SHIFT); // turn off shift
	tap_code16(KC_UNDS);
	set_mods(saved_mods);
	return_state = false;
      }
      break;
    case KC_EQL:
      if (saved_mods & MOD_MASK_SHIFT) {
	set_mods(saved_mods & ~MOD_MASK_SHIFT);
	tap_code16(KC_QUES);
	set_mods(saved_mods);
	return_state = false;
      }
      break;
    case KC_DOT:
      if (saved_mods & MOD_MASK_SHIFT) {
        set_mods(saved_mods & ~MOD_MASK_SHIFT);
        tap_code16(KC_COLN);
        set_mods(saved_mods);
        return_state = false;
      }
      break;
    case KC_SLSH:
      if (saved_mods & MOD_MASK_SHIFT) {
        set_mods(saved_mods & ~MOD_MASK_SHIFT);
        tap_code16(KC_ASTR);
        set_mods(saved_mods);
        return_state = false;
      }
      break;
    case KC_QUOT:
      if (saved_mods & MOD_MASK_SHIFT) {
        set_mods(saved_mods & ~MOD_MASK_SHIFT);
        tap_code16(KC_EXLM);
        set_mods(saved_mods);
        return_state = false;
      } else {
	// just a regular quote
	register_linger_key(keycode);
	return_state = false;
      }
      break;
    case KC_DQUO:
      if (saved_mods & MOD_MASK_SHIFT) {
        set_mods(saved_mods & ~MOD_MASK_SHIFT);
        tap_code16(KC_QUES);
        set_mods(saved_mods);
        return_state = false;
      } else {
	// just a regular double quote
	register_linger_key(keycode);
	return_state = false;
      }
      break;
    case KC_MINS:
      if (saved_mods & MOD_MASK_SHIFT) {
        set_mods(saved_mods & ~MOD_MASK_SHIFT);
        tap_code16(KC_PLUS);
        set_mods(saved_mods);
        return_state = false;
      }
      break;
    case KC_COMM:
      if (saved_mods & MOD_MASK_SHIFT) {
        set_mods(saved_mods & ~MOD_MASK_SHIFT);
        tap_code16(KC_EQL);
        set_mods(saved_mods);
        return_state = false;
      }
      break;
    case KC_SCLN:
      if (saved_mods & MOD_MASK_SHIFT) {
        set_mods(saved_mods & ~MOD_MASK_SHIFT);
        tap_code16(KC_PIPE);
        set_mods(saved_mods);
        return_state = false;
      }
      break;
    case KC_UNDS:
      if (saved_mods & MOD_MASK_SHIFT) {
        set_mods(saved_mods & ~MOD_MASK_SHIFT);
        tap_code16(KC_MINS);
        set_mods(saved_mods);
        return_state = false;
      }
      break;
    } // end switch (keycode)
    prior_keycode = keycode;
    prior_keydown = timer_read();
  } else { // else branch of if (record->event.pressed)
    switch(keycode) {
    case KC_Q:
      unregister_code16(keycode);
      linger_key = 0;
      return_state = false;
      break;
    case KC_LT:
      unregister_linger_key();
      return_state = false;
      break;
    case KC_LBRC:
    case KC_LCBR:
    case KC_LPRN:
      unregister_linger_key();
      return_state = false;
      break;
    case KC_QUOT:
    case KC_DQUO:
      unregister_linger_key();
      return_state = false;
      break;
    }
  } 
  return return_state;
}


layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _SYM, _NAV, _NUM);
}

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)





