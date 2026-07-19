#include QMK_KEYBOARD_H

#include "swapper.h"
#include "features/sentence_case.h"
#include "features/adaptive_keys.h"

/* ====== Keybinding macros ===================*/
// Layer shifts
#define LA_SYM MO(_SYM)
#define LA_NAV MO(_NAV)

// delete a word (for applications that support this keybinding)
#define BSWORD A(KC_BSPC)

/* Copy, paste */
#define COPY G(KC_C)
#define PASTE G(KC_V)

// Screenshot with selection
#define KC_CAPP LGUI(LSFT(KC_4))
/* ============================================ */

/* ========= HOME ROW MODS ALIASES ============*/
// Left hand home row mods
#define HOME_R LCTL_T(KC_R)
#define HOME_S LALT_T(KC_S)
#define HOME_N LGUI_T(KC_N)
#define HOME_D LSFT_T(KC_D)

// right hand home row mods
#define HOME_A RSFT_T(KC_A)
#define HOME_E RGUI_T(KC_E)
#define HOME_I RALT_T(KC_I)
#define HOME_H RCTL_T(KC_H)

/* ============================================*/

/* ========= COMBO ENVETS ===================== */
enum combo_events {
    COMBO_Z,
    COMBO_Q,
    COMBO_QU,
    COMBO_ESC,
    COMBO_DEL,
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
    COMBO_AND,
    COMBO_SCH,
    COMBO_SQU,
    COMBO_DCOM, // sends .com
    COMBO_TF,   // sends "terraform"
    COMBO_IVE,
    COMBO_I,
    // quick access to symbols
    COMBO_COLON,
	COMBO_UNDS,
    COMBO_QUEST,
    COMBO_ASTR,
    COMBO_EXLM,
    COMBO_AMPR,
    COMBO_FZF,

    // macros
    COMBO_CAPS_WORD,
    // no touchey
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;


// single letter outputs
const uint16_t PROGMEM combo_z[]  = {KC_J, KC_G, COMBO_END};
const uint16_t PROGMEM combo_q[]  = {KC_J, KC_P, COMBO_END};
const uint16_t PROGMEM combo_qu[] = {KC_G, KC_P, COMBO_END};
// const uint16_t PROGMEM combo_repeat[] = {KC_C, KC_S, COMBO_END};
// Common H digraphs
const uint16_t PROGMEM combo_th[] = {HOME_D, HOME_N, COMBO_END};
const uint16_t PROGMEM combo_ch[] = {HOME_S, HOME_D, COMBO_END};
const uint16_t PROGMEM combo_sh[] = {HOME_S, HOME_N, COMBO_END};
const uint16_t PROGMEM combo_wh[] = {KC_L, KC_C, COMBO_END};
const uint16_t PROGMEM combo_ph[] = {KC_P, KC_M, COMBO_END};
const uint16_t PROGMEM combo_gh[] = {KC_G, KC_M, COMBO_END};

const uint16_t PROGMEM combo_cd[] = {KC_C, HOME_N, COMBO_END};
// word combos
const uint16_t PROGMEM combo_the[]    = {HOME_S, HOME_N, HOME_D, COMBO_END};
const uint16_t PROGMEM combo_and[]    = {HOME_A, HOME_E, HOME_I, COMBO_END};
const uint16_t PROGMEM combo_sch[]    = {KC_F, KC_L, KC_C, COMBO_END};
const uint16_t PROGMEM combo_squ[]    = {KC_G, KC_M, KC_P, COMBO_END};
const uint16_t PROGMEM combo_dotcom[] = {KC_DOT, KC_SLSH, KC_EQL, COMBO_END};
const uint16_t PROGMEM combo_tf[]     = {KC_T, KC_F, COMBO_END};
const uint16_t PROGMEM combo_i[]      = {HOME_E, HOME_I, COMBO_END};
// quick access to symbols
const uint16_t PROGMEM combo_colon[] = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM combo_quest[] = {KC_DOT, KC_EQL, COMBO_END};
const uint16_t PROGMEM combo_astr[]  = {KC_SLSH, KC_EQL, COMBO_END};
const uint16_t PROGMEM combo_exlm[]  = {KC_QUOT, KC_EQL, COMBO_END};
const uint16_t PROGMEM combo_ampr[]  = {KC_DOT, KC_QUOT, COMBO_END};
const uint16_t PROGMEM combo_unds[]  = {HOME_A, HOME_E, COMBO_END};

// macros
const uint16_t PROGMEM combo_caps_word[] = {HOME_D, HOME_A, COMBO_END};
const uint16_t PROGMEM combo_esc[]       = {HOME_R, HOME_S, COMBO_END};
const uint16_t PROGMEM combo_fzf[]   = {KC_X, KC_F, COMBO_END};

combo_t key_combos[] = {
    [COMBO_Z]         = COMBO(combo_z, KC_Z),
    [COMBO_Q]         = COMBO(combo_q, KC_Q),
    [COMBO_QU]        = COMBO_ACTION(combo_qu),
    [COMBO_CAPS_WORD] = COMBO(combo_caps_word, CW_TOGG),
    [COMBO_ESC]       = COMBO(combo_esc, KC_ESC),
    // combo actions
    [COMBO_TH] = COMBO_ACTION(combo_th),
    [COMBO_CH] = COMBO_ACTION(combo_ch),
    [COMBO_SH] = COMBO_ACTION(combo_sh),
    [COMBO_WH] = COMBO_ACTION(combo_wh),
    [COMBO_PH] = COMBO_ACTION(combo_ph),
    [COMBO_GH] = COMBO_ACTION(combo_gh),
    [COMBO_CD] = COMBO_ACTION(combo_cd),
    // whole word combos
    [COMBO_THE]  = COMBO_ACTION(combo_the),
    [COMBO_AND]  = COMBO_ACTION(combo_and),
    [COMBO_SCH]  = COMBO_ACTION(combo_sch),
    [COMBO_SQU]  = COMBO_ACTION(combo_squ),
    [COMBO_DCOM] = COMBO_ACTION(combo_dotcom),
    [COMBO_TF]   = COMBO_ACTION(combo_tf),
    [COMBO_I]    = COMBO(combo_i, S(KC_I)),
    [COMBO_FZF]  = COMBO_ACTION(combo_fzf),

    // quick access to symbols
    [COMBO_COLON] = COMBO(combo_colon, KC_COLON),
    [COMBO_QUEST] = COMBO(combo_quest, KC_QUES),
    [COMBO_ASTR]  = COMBO(combo_astr, KC_ASTR),
    [COMBO_EXLM]  = COMBO(combo_exlm, KC_EXLM),
    [COMBO_AMPR]  = COMBO(combo_ampr, KC_AMPR),
	[COMBO_UNDS]  = COMBO(combo_unds, KC_UNDS),
};

/* ========= END COMBO EVENTS ================= */

/* ======== Custom keycodes =================== */
// TODO: refactor uses of COMBO_ACTION to just use custom
// keycodes instead and process in `process_record_user`
enum custom_keycodes { VRSN = SAFE_RANGE, M_THIS, REPEAT, ILL, IVE, SW_WIN, SW_LANG };
/* ============================================ */

/* ====== LAYERS ============================*/
enum ferris_layers { _BSE, _NAV, _SYM, _NUM, _OSH };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BSE] = LAYOUT_split_3x5_2(/* Base layer */
        KC_J,     KC_G,      KC_M,    KC_P,    KC_V,      KC_SCLN,  KC_DOT,  KC_SLSH,  KC_EQL,    KC_QUOT,
        HOME_R,   HOME_S,    HOME_N,  HOME_D,  KC_B,      KC_MINS,  HOME_A,  HOME_E,   HOME_I,    HOME_H, 
        KC_X,     KC_F,      KC_L,    KC_C,    KC_W,      KC_COMM,  KC_U,    KC_O,     KC_Y,      KC_K,
                                      LA_NAV,  KC_T,      KC_SPC,   LA_SYM
   ),
   [_NAV] = LAYOUT_split_3x5_2(/* Navigation */
       SW_WIN,    C(KC_SPC), KC_MPRV, KC_MNXT, KC_VOLU,   KC_NO,    KC_NO,   KC_NO,    KC_NO,   KC_NO, 
       KC_LCTL,   KC_LALT,   KC_LGUI, KC_LSFT, KC_VOLD,   KC_LEFT,  KC_DOWN, KC_UP,    KC_RGHT, KC_BSPC,
       OSL(_OSH), COPY,      PASTE,   C(KC_C), KC_MPLY,   KC_UNDS,  KC_NO,   KC_NO,    KC_NO,   BSWORD,
                                      _______, _______,   KC_TAB,   _______
   ), /*                              LA_NAV                                                          */
   [_SYM] = LAYOUT_split_3x5_2(/* Symbols */
       KC_CIRC,   KC_PERC,  KC_LCBR,  KC_RCBR,  KC_TILD,   KC_NO,    LCMD(KC_MINS), LCMD(KC_EQL),  KC_PLUS,   KC_DQUO,
       KC_LT,     KC_GT,    KC_LPRN,  KC_RPRN,  KC_DLR,    KC_NO,    KC_RSFT,       KC_RGUI,       KC_RALT,   KC_RCTL,
       KC_AT,     KC_HASH,  KC_LBRC,  KC_RBRC,  KC_GRV,    KC_NO,    KC_HOME,       KC_END,        KC_CAPP,   KC_ENTER,
                                      _______,  KC_PIPE,   _______,  _______
   ), /*                                                             LA_SYM                            */
   [_NUM] = LAYOUT_split_3x5_2(/* numpad */
       KC_TRNS,   KC_PERC, KC_EQL,    KC_TRNS, KC_TRNS,   KC_TRNS,  KC_7,   KC_8,    KC_9,     KC_EQL,
       KC_LCTL,   KC_LALT, KC_LGUI,   KC_LSFT, KC_TRNS,   KC_TRNS,  KC_4,   KC_5,    KC_6,     KC_BSPC,
       QK_BOOT,   KC_PDOT, KC_MINS,   KC_COLN, KC_TRNS,   KC_TRNS,  KC_1,   KC_2,    KC_3,     KC_0,
                                      _______, _______,   _______,  _______
   ), /*                              LA_NAV                        LA_SYM                            */
   [_OSH] = LAYOUT(/* [> One Shot Layer <] */
       KC_NO,     KC_NO,   KC_NO,     KC_NO,   KC_NO,     KC_NO,    KC_F7,   KC_F8,    KC_F9,     KC_F12,
       KC_NO,     KC_NO,   KC_NO,     KC_NO,   KC_NO,     KC_NO,    KC_F4,   KC_F5,    KC_F6,     KC_F11,
       KC_NO,     KC_NO,   KC_NO,     KC_NO,   KC_NO,     KC_NO,    KC_F1,   KC_F2,    KC_F3,     KC_F10,
                                      _______, _______,   _______,  _______
)};

/* MOD STATE TRACKING */
uint16_t saved_mods;
uint16_t prior_keycode = KC_NO; // for process_adaptive_key and process_caps_word
uint16_t prior_keydown = 0;     // time since finished processing prior_keycode

uint16_t linger_key   = 0;
uint32_t linger_timer = 0;

#define register_linger_key(kc)      \
    {                                \
        register_code16(kc);         \
        linger_key   = kc;           \
        linger_timer = timer_read(); \
    }
#define unregister_linger_key()        \
    {                                  \
        unregister_code16(linger_key); \
        linger_key = 0;                \
    }

/* END MOD STATE TRACKING */

bool sw_win_active  = false;
bool sw_lang_active = false;


/* END ONSHOT SETUP */
bool semantic_shift = false;
void sentence_case_primed(bool primed) {
    semantic_shift = primed;
}

/* Process combo events */
void process_combo_event(uint16_t combo_index, bool pressed) {
    saved_mods   = get_mods() | get_weak_mods() | get_oneshot_mods();
    bool caps_on = is_caps_word_on();
    if (caps_on) {
        register_mods(MOD_MASK_SHIFT);
    }
    bool shifted = saved_mods & MOD_MASK_SHIFT;
    if (semantic_shift) {
        shifted = true;
        register_mods(MOD_MASK_SHIFT);
        sentence_case_clear();
    }
    if (pressed) {
        switch (combo_index) {
            case COMBO_DCOM:
                unregister_mods(MOD_MASK_SHIFT);
                send_string(".com");
                break;
            case COMBO_QU:
                tap_code(KC_Q);
                if (shifted && !caps_on) {
                    unregister_mods(MOD_MASK_SHIFT);
                }
                tap_code(KC_U);
                break;
            case COMBO_TF:
                tap_code(KC_T);
                if (shifted && !caps_on) {
                    unregister_mods(MOD_MASK_SHIFT);
                }
                send_string("erraform");
                break;
            case COMBO_THE:
                tap_code(KC_T);
                if (shifted && !caps_on) {
                    unregister_mods(MOD_MASK_SHIFT);
                }
                send_string("he ");
                break;
            case COMBO_AND:
                tap_code(KC_A);
                if (shifted && !caps_on) {
                    unregister_mods(MOD_MASK_SHIFT);
                }
                send_string("nd ");
                break;
            case COMBO_SCH:
                tap_code(KC_S);
                if (shifted && !caps_on) {
                    unregister_mods(MOD_MASK_SHIFT);
                }
                send_string("ch");
                break;
            case COMBO_SQU:
                tap_code(KC_S);
                tap_code(KC_Q);
                tap_code(KC_U);
                break;
            case COMBO_TH:
                tap_code(KC_T);
                if (shifted && !caps_on) {
                    unregister_mods(MOD_MASK_SHIFT);
                }
                tap_code(KC_H);
                break;
            case COMBO_CH:
                tap_code(KC_C);
                if (shifted && !caps_on) {
                    unregister_mods(MOD_MASK_SHIFT);
                }
                tap_code(KC_H);
                break;
            case COMBO_SH:
                tap_code(KC_S);
                if (shifted && !caps_on) {
                    unregister_mods(MOD_MASK_SHIFT);
                }
                tap_code(KC_H);
                break;
            case COMBO_WH:
                tap_code(KC_W);
                if (shifted && !caps_on) {
                    unregister_mods(MOD_MASK_SHIFT);
                }
                tap_code(KC_H);
                break;
            case COMBO_PH:
                tap_code(KC_P);
                if (shifted && !caps_on) {
                    unregister_mods(MOD_MASK_SHIFT);
                }
                tap_code(KC_H);
                break;
            case COMBO_GH:
                tap_code(KC_G);
                if (shifted && !caps_on) {
                    unregister_mods(MOD_MASK_SHIFT);
                }
                tap_code(KC_H);
                break;
            case COMBO_CD:
                tap_code(KC_C);
                if (shifted && !caps_on) {
                    unregister_mods(MOD_MASK_SHIFT);
                }
                tap_code(KC_D);
                break;
            case COMBO_FZF:
                send_string("fzf");
                break;
        }
    }
    if (caps_on) {
        unregister_mods(MOD_MASK_SHIFT);
    }
}

struct adaptive_key adaptive_keys[] = {
    {KC_G,    KC_M,    KC_L},       // GM -> GL
    {KC_P,    KC_M,    KC_L},       // PM -> PL
    {KC_P,    KC_V,    KC_L, KC_V}, // PV -> LV
    {KC_B,    KC_D,    KC_L},       // BD -> BL
    {KC_D,    KC_B,    KC_L, KC_B}, // DB -> LB
    {KC_A,    KC_MINS, KC_U},       // A, -> AU
    {KC_E,    KC_H,    KC_O},       // EH -> EO
    {KC_U,    KC_H,    KC_A},       // UH -> UA
    {KC_J,    KC_G,    KC_G, KC_S}, // JG -> GS
    {KC_O,    KC_H,    KC_E},       // OH -> OE
    {KC_W,    KC_C,    KC_N},       // WC -> WN
    {KC_G,    KC_J,    KC_S},       // GJ -> GS. Saves same finger jump for words like things. Note that 'g' and 's' both use the left ring finger
};

// Runs constantly in the background, in a loop
// primarily used to handle linger keys.
void matrix_scan_user(void) {
  if (linger_key && timer_elapsed(linger_timer) > LINGER_TIME) {
	saved_mods = get_mods();
	clear_mods();
	/* unregister_mods(MOD_MASK_SHIFT); */
	switch (linger_key) {
	  /* case KC_Q: */
	  /*   tap_code(KC_U); */
	  /*   break; */
	case KC_GT:
	  tap_code16(KC_BSPC);
	  send_string("->");
	  break;
	case KC_LT:
	  tap_code16(KC_GT);
	  tap_code(KC_LEFT);
	  break;
	case KC_GRV:
	  tap_code(KC_GRV);
	  tap_code(KC_GRV);
	  tap_code(KC_ENTER);
	  tap_code(KC_ENTER);
	  tap_code(KC_GRV);
	  tap_code(KC_GRV);
	  tap_code(KC_GRV);
	  tap_code(KC_UP);
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(&sw_win_active, KC_LGUI, KC_TAB, SW_WIN, keycode, record);
    update_swapper(&sw_lang_active, KC_LCTL, KC_SPC, SW_LANG, keycode, record);

    saved_mods        = get_mods() | get_weak_mods();
    bool shifted      = saved_mods & MOD_MASK_SHIFT;
    bool return_state = true;

    if (!process_sentence_case(keycode, record)) {
        return false;
    }

    if (!process_adaptive_keys(keycode, record, saved_mods, adaptive_keys, ARRAY_SIZE(adaptive_keys))) {
        // This means we already took care of the key
        // and do not need to process it further
        return false;
    }

    if (record->event.pressed) {
	  if (is_caps_word_on()) add_weak_mods(MOD_BIT(KC_LSFT));
	  switch (keycode) {
	  case KC_GT:
		register_linger_key(KC_GT);
		return_state = false;
		break;
	  case KC_GRV:
		register_linger_key(KC_GRV);
		return_state = false;
		break;
		// ( by itself is still (
	  case KC_LT:
		register_linger_key(keycode);
		return_state = false;
		break;
	  case KC_SLSH:
		if (shifted) {
		  set_mods(saved_mods & ~MOD_MASK_SHIFT);
		  tap_code16(KC_BSLS);
		  set_mods(saved_mods);
		  return_state = false;
		}
		break;
	  case KC_UNDS:
		if (shifted) {
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
	  switch (keycode) {
	  case KC_GT:
		unregister_linger_key();
		return_state = false;
		break;
	  case KC_LT:
		unregister_linger_key();
		return_state = false;
		break;
	  case KC_GRV:
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
