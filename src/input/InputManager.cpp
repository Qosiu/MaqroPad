#include "InputManager.h"

InputManager::InputManager(MatrixScanner &matrix,
                           Encoder &enc1,
                           Encoder &enc2)
    : _matrix(matrix),
      _enc1(enc1),
      _enc2(enc2),
      _lastRawState(0),
      _stableState(0),
      _enc1LastButtonState(false),
      _enc2LastButtonState(false),
      _enc1LastDebounce(0),
      _enc2LastDebounce(0)
{
    for (uint8_t i = 0; i < MATRIX_KEY_COUNT; i++)
    {
        _lastDebounceTime[i] = 0;
    }
}

void InputManager::begin()
{
    _matrix.begin();
    _enc1.begin();
    _enc2.begin();
}

void InputManager::update()
{

    processMatrix();

    _enc1.update();
    _enc2.update();

    processEncoder(_enc1, ENCODER_1,
                   _enc1LastButtonState,
                   _enc1LastDebounce);

    processEncoder(_enc2, ENCODER_2,
                   _enc2LastButtonState,
                   _enc2LastDebounce);
}

// =====================================================
// ================= MATRIX =============================
// =====================================================

void InputManager::processMatrix()
{

    _matrix.scan();
    uint16_t raw = _matrix.getRawState();

    uint32_t now = millis();

    for (uint8_t i = 0; i < MATRIX_KEY_COUNT; i++)
    {

        bool rawPressed = raw & (1 << i);
        bool stablePressed = _stableState & (1 << i);

        if (rawPressed != stablePressed)
        {

            if (now - _lastDebounceTime[i] > KEY_DEBOUNCE_MS)
            {

                _lastDebounceTime[i] = now;

                if (rawPressed)
                {
                    _stableState |= (1 << i);

                    Event e;
                    e.type = EVENT_INPUT;
                    e.input.type = INPUT_KEY_DOWN;
                    e.input.key = i;
                    EventBus::publish(e);
                }
                else
                {
                    _stableState &= ~(1 << i);

                    Event e;
                    e.type = EVENT_INPUT;
                    e.input.type = INPUT_KEY_UP;
                    e.input.key = i;
                    EventBus::publish(e);
                }
            }
        }
    }

    _lastRawState = raw;
}

// =====================================================
// ================= ENCODER ============================
// =====================================================

void InputManager::processEncoder(Encoder &encoder,
                                  EncoderId id,
                                  bool &lastButtonState,
                                  uint32_t &lastDebounceTime)
{
    uint32_t now = millis();

    // ---- ROTATION ----
    EncoderDirection dir = encoder.getDirection();

    if (dir != DIR_NONE)
    {

        Event e;
        e.type = EVENT_INPUT;
        e.input.type = INPUT_ENCODER_ROTATE;
        e.input.encoderRotate.id = id;
        e.input.encoderRotate.direction = dir;

        EventBus::publish(e);
    }

    // ---- BUTTON ----
    bool pressed = encoder.isButtonPressed();

    if (pressed != lastButtonState)
    {

        if (now - lastDebounceTime > ENCODER_BUTTON_DEBOUNCE_MS)
        {

            lastDebounceTime = now;
            lastButtonState = pressed;

            Event e;
            e.type = EVENT_INPUT;

            if (pressed)
            {
                e.input.type = INPUT_ENCODER_PRESS;
            }
            else
            {
                e.input.type = INPUT_ENCODER_RELEASE;
            }

            e.input.encoderButton = id;

            EventBus::publish(e);
        }
    }
}