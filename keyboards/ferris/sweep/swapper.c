#include "swapper.h"
#include <stdint.h>

bool is_swapper_cancel_key(uint16_t keycode) {
  switch(keycode) {
    case KC_UP:
    case KC_DOWN:
    case KC_LEFT:
    case KC_RIGHT:
      return false;
    default:
      return true;
  }
}

void update_swapper(
    bool *active,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
  if (keycode == trigger) {
    if (record->event.pressed) {
      if(!*active) {
        *active = true;
        register_code(cmdish);
      }
      register_code(tabish);
    } else {
      unregister_code(tabish);
    }
  } else if (*active && is_swapper_cancel_key(keycode)) {
    unregister_code(cmdish);
    *active = false;
  }
}
