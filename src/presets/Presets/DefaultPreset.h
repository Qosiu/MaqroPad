#pragma once
#include "../Preset.h"

// HID keycodes (USB HID Usage IDs)
#define HID_KEY_A 0x04
#define HID_KEY_B 0x05
#define HID_KEY_C 0x06
#define HID_KEY_D 0x07
#define HID_KEY_E 0x08
#define HID_KEY_F 0x09
#define HID_KEY_G 0x0A
#define HID_KEY_H 0x0B
#define HID_KEY_I 0x0C
#define HID_KEY_J 0x0D
#define HID_KEY_K 0x0E
#define HID_KEY_L 0x0F
#define HID_KEY_M 0x10
#define HID_KEY_N 0x11
#define HID_KEY_O 0x12
#define HID_KEY_P 0x13

#define HID_KEY_ENTER 0x28
#define HID_KEY_ARROW_UP 0x52
#define HID_KEY_ARROW_DOWN 0x51

#define HID_MOD_NONE 0x00

static Preset DefaultPreset = {

    .name = "Default",

    .keyActions = {

        // 16 klawiszy A–P
        {ACTION_SEND_REPORT, .report = {REPORT_KEYBOARD, HID_KEY_A, HID_MOD_NONE}},
        {ACTION_SEND_REPORT, .report = {REPORT_KEYBOARD, HID_KEY_B, HID_MOD_NONE}},
        {ACTION_SEND_REPORT, .report = {REPORT_KEYBOARD, HID_KEY_C, HID_MOD_NONE}},
        {ACTION_SEND_REPORT, .report = {REPORT_KEYBOARD, HID_KEY_D, HID_MOD_NONE}},

        {ACTION_SEND_REPORT, .report = {REPORT_KEYBOARD, HID_KEY_E, HID_MOD_NONE}},
        {ACTION_SEND_REPORT, .report = {REPORT_KEYBOARD, HID_KEY_F, HID_MOD_NONE}},
        {ACTION_SEND_REPORT, .report = {REPORT_KEYBOARD, HID_KEY_G, HID_MOD_NONE}},
        {ACTION_SEND_REPORT, .report = {REPORT_KEYBOARD, HID_KEY_H, HID_MOD_NONE}},

        {ACTION_SEND_REPORT, .report = {REPORT_KEYBOARD, HID_KEY_I, HID_MOD_NONE}},
        {ACTION_SEND_REPORT, .report = {REPORT_KEYBOARD, HID_KEY_J, HID_MOD_NONE}},
        {ACTION_SEND_REPORT, .report = {REPORT_KEYBOARD, HID_KEY_K, HID_MOD_NONE}},
        {ACTION_SEND_REPORT, .report = {REPORT_KEYBOARD, HID_KEY_L, HID_MOD_NONE}},

        {ACTION_SEND_REPORT, .report = {REPORT_KEYBOARD, HID_KEY_M, HID_MOD_NONE}},
        {ACTION_SEND_REPORT, .report = {REPORT_KEYBOARD, HID_KEY_N, HID_MOD_NONE}},
        {ACTION_SEND_REPORT, .report = {REPORT_KEYBOARD, HID_KEY_O, HID_MOD_NONE}},
        {ACTION_SEND_REPORT, .report = {REPORT_KEYBOARD, HID_KEY_P, HID_MOD_NONE}}},

    // ==============================
    // ENCODER 1
    // ==============================

    .encoder1CW = {
        ACTION_SEND_REPORT, .report = {REPORT_CONSUMER, 0x00E9, 0} // Volume Up (future)
    },

    .encoder1CCW = {
        ACTION_SEND_REPORT, .report = {REPORT_CONSUMER, 0x00EA, 0} // Volume Down (future)
    },

    .encoder1Press = {ACTION_SWITCH_PRESET, .switchPreset = {0}},

    // ==============================
    // ENCODER 2
    // ==============================

    .encoder2CW = {ACTION_SEND_REPORT, .report = {REPORT_KEYBOARD, HID_KEY_ARROW_UP, HID_MOD_NONE}},

    .encoder2CCW = {ACTION_SEND_REPORT, .report = {REPORT_KEYBOARD, HID_KEY_ARROW_DOWN, HID_MOD_NONE}},

    .encoder2Press = {ACTION_SEND_REPORT, .report = {REPORT_KEYBOARD, HID_KEY_ENTER, HID_MOD_NONE}}};