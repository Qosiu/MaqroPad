#pragma once
#include <Arduino.h>
#include "Types.h"

// =====================================================
// GŁÓWNY TYP ZDARZENIA (dla EventBus)
// =====================================================

enum EventType : uint8_t
{
    EVENT_INPUT,
    EVENT_ACTION
};

// =====================================================
// ================= INPUT EVENT ========================
// =====================================================

enum InputEventType : uint8_t
{
    INPUT_KEY_DOWN,
    INPUT_KEY_UP,

    INPUT_ENCODER_ROTATE,
    INPUT_ENCODER_PRESS,
    INPUT_ENCODER_RELEASE
};

struct InputEvent
{
    InputEventType type;

    union
    {

        // dla KEY_DOWN / KEY_UP
        KeyId key;

        // dla ROTATE
        struct
        {
            EncoderId id;
            EncoderDirection direction;
        } encoderRotate;

        // dla PRESS / RELEASE
        EncoderId encoderButton;
    };
};

// =====================================================
// ================= ACTION EVENT =======================
// =====================================================

enum ReportType : uint8_t
{
    REPORT_KEYBOARD,
    REPORT_CONSUMER,
    REPORT_SYSTEM,
    REPORT_MOUSE
};

enum ActionType : uint8_t
{
    ACTION_NONE,
    ACTION_SEND_REPORT,
    ACTION_SWITCH_PRESET,
    ACTION_MACRO
};

struct ActionEvent
{
    ActionType type;

    union
    {

        // Wysyłanie raportu HID
        struct
        {
            ReportType reportType;
            uint16_t keycode;
            uint8_t modifiers;
        } report;

        // Przełącz preset
        struct
        {
            uint8_t presetIndex;
        } switchPreset;

        // Makro (ID makra)
        struct
        {
            uint8_t macroId;
        } macro;
    };
};

// =====================================================
// ================= WRAPPER EVENT ======================
// =====================================================

struct Event
{
    EventType type;

    union
    {
        InputEvent input;
        ActionEvent action;
    };
};