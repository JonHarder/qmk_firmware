#pragma once

#include QMK_KEYBOARD_H

// Represents the four states a oneshot key can be in
typedef enum {
  os_up_unqueued, // default resting state for a oneshot. Not used, not queued.
  os_up_queued, // trigger has been pressed and released. It will be saved until the next non-trigger keycode
  os_up_queued_used, // we queued it, then used it. It's spent
  os_down_unused, // 
  os_down_used, // the trigger and a keycode was used, meaning we don't want this mod queued anymore, it's been used/spent.
} oneshot_state;

// Custom oneshot mod implementation that doesn't rely on timers. If a mod is
// used while it is held it will be unregistered on keyup as normal, otherwise
// it will be queued and only released after the next non-mod keyup.
void update_oneshot(
    oneshot_state *state,
    uint16_t mod,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
);

// To be implemented by the consumer. Defines keys to cancel oneshot mods.
bool is_oneshot_cancel_key(uint16_t keycode);

// To be implemented by the consumer. Defines keys to ignore when determining
// whether a oneshot mod has been used. Setting this to modifiers and layer
// change keys allows stacking multiple oneshot modifiers, and carrying them
// between layers.
bool is_oneshot_ignored_key(uint16_t keycode);
