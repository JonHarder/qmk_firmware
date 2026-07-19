#include "adaptive_keys.h"

#ifndef ADAPTIVE_TERM
#define ADAPTIVE_TERM TAPPING_TERM * 0.80
#endif

uint16_t adaptive_prior_keycode = KC_NO; // 
uint16_t adaptive_prior_keydown = 0;

bool process_adaptive_keys(uint16_t keycode, keyrecord_t *record, uint16_t saved_mods, struct adaptive_key adaptive_key_map[], int map_size) {
    // e.g. does the key still need processing?
    bool continue_processing = true; // assume we didn't handle the key here.
	

    if (record->event.pressed) {
        if ((timer_elapsed(adaptive_prior_keydown) < ADAPTIVE_TERM)) {
            saved_mods = get_mods(); //
            clear_mods();
            keycode = keycode & 0xFF; // taps&mods handled earlier.
            if (is_caps_word_on()) {
                add_weak_mods(MOD_BIT(KC_LSFT));
            }

            // loop through all available adaptive key configuration
            for (int i = 0; i < map_size; i++) {
                // if the previous key and current key match this adaptive key set:
                if (adaptive_prior_keycode == adaptive_key_map[i].prior_key && keycode == adaptive_key_map[i].current_key) {
                    // some adaptive keys just send a different code for the given `keycode`. These adaptive
                    // keys will have their `new_key2` set to 0.
                    // This means we simply send an altered key instead of the one pressed (new_key1)
                    if (adaptive_key_map[i].new_key2 == 0) {
                        tap_code(adaptive_key_map[i].new_key1);
                    } else {
                        // Other adaptive keys replace the previous key AND the current key.
                        // We know this by having an adaptive key record with a non-zero `new_key2`
                        // In these instances, we delete the previous key and send both new keys
                        // i.e. `new_key1` and `new_key2`.
                        tap_code(KC_BSPC);
                        tap_code(adaptive_key_map[i].new_key1);
                        tap_code(adaptive_key_map[i].new_key2);
                    }
                    // in either case, we have processed this key and so we indicate to the caller
                    // that no further processing is needed.
                    continue_processing = false;
					break;
                }
            }
            set_mods(saved_mods); // Restore mods
        }
        adaptive_prior_keycode = keycode;      // this keycode is stripped of mods+taps
		adaptive_prior_keydown = timer_read(); // (re)start adaptive_prior_keydown timing
    }
    return continue_processing;
}
