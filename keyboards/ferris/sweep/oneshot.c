#include "oneshot.h"

void update_oneshot(
    oneshot_state *state, // the state of the oneshot struct for the mod
    uint16_t mod,         // the KC mod in question (KC_LSFT, KC_LCTRL, etc)
    uint16_t trigger,     // the key that triggers the oneshot. OS_SHFT, OS_CTRL, etc
    uint16_t keycode,     // the key that was actually pressed by the user.
    keyrecord_t *record   // information about the key
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == os_up_unqueued) {
                register_code(mod);
            }
            *state = os_down_unused;
        } else {
            // Trigger keyup
            switch (*state) {
            case os_down_unused:
                // If we didn't use the mod while trigger was held, queue it.
                *state = os_up_queued;
                break;
            case os_down_used:
                // If we did use the mod while trigger was held, unregister it.
                *state = os_up_unqueued;
                unregister_code(mod);
                break;
            default:
                break;
            }
        }
    } else { // keycode != trigger
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode) && *state != os_up_unqueued) {
                // Cancel oneshot on designated cancel keydown.
                *state = os_up_unqueued;
                unregister_code(mod);
            }
            if (!is_oneshot_ignored_key(keycode)) {
                switch(*state) {
                case os_up_queued:
                    *state = os_up_queued_used;
                    break;
                case os_up_queued_used:
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    break;
                default:
                    break;
                }
            }
        } else { // not pressed
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                case os_down_unused:
                    *state = os_down_used;
                    break;
                case os_up_queued:
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    break;
                case os_up_queued_used:
                    *state = os_up_unqueued;
                    unregister_code(mod);
                default:
                    break;
                }
            }
        }
    }
}
