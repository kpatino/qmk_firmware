// Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
// Copyright 2023 Kevin Patino
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Tap Dance declarations
enum {
    TD_ESC_CAPS,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        TD(TD_ESC_CAPS),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_PSCR,           _______,
        _______, RGB_TOG, RGB_M_P, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______,
        _______, RGB_HUI, RGB_VAI, RGB_SAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,           _______,
        KC_CAPS, RGB_HUD, RGB_VAD, RGB_SAD, _______, _______, _______, _______, _______, _______, _______, _______,          EE_CLR,            _______,
        _______,          _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RGB_MOD,  _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),
};
// clang-format on

// Make side lights white when capslock is on
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_UNDERGLOW) {
                // led 82 to 97
                rgb_matrix_set_color(i, 255, 255, 255);
            }
        }
    }
    return false;
}
