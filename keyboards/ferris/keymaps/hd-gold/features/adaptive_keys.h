#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

struct adaptive_key {
    // The first key in the adaptive key series.
    uint16_t prior_key;
    // The second key in the adaptiwe key series.
    uint16_t current_key;
    // If there is no `new_key2`, than this key is simply
    // emitted instead of `current_key`. e.g. 'p m' produces 'p l'.
    uint16_t new_key1;
    // If provided, when the adaptive series is emitted, `prior_key`
    // is deleted (`current_key` was never emitted, only sent to the board)
    // then `new_key1` and `new_key2` are emitted.
    // e.g. 'd b' produces '[bspc] l b' or just 'l b'
    uint16_t new_key2;
};
  
/**
 * Handler for processing any potential adaptive keys.
 *
 * Call this functino from `process_record_user()` to implement
 * "adaptive" keys.
 */
  bool process_adaptive_keys(uint16_t keycode, keyrecord_t* record, uint16_t saved_mods, struct adaptive_key adaptive_key_map[], int map_size);

#ifdef __cplusplus
}
#endif
