#pragma once
#include <Arduino.h>

#include "../drivers/MatrixScanner.h"
#include "../drivers/Encoder.h"
#include "../core/EventBus.h"
#include "../config/Config.h"
#include "../config/Pins.h"

class InputManager
{
public:
    InputManager(MatrixScanner &matrix,
                 Encoder &enc1,
                 Encoder &enc2);

    void begin();
    void update(); // wywoływane w każdej pętli

private:
    MatrixScanner &_matrix;
    Encoder &_enc1;
    Encoder &_enc2;

    // ====== Matrix state ======
    uint16_t _lastRawState;
    uint16_t _stableState;
    uint32_t _lastDebounceTime[MATRIX_KEY_COUNT];

    // ====== Encoder button debounce ======
    bool _enc1LastButtonState;
    bool _enc2LastButtonState;
    uint32_t _enc1LastDebounce;
    uint32_t _enc2LastDebounce;

    void processMatrix();
    void processEncoder(Encoder &encoder,
                        EncoderId id,
                        bool &lastButtonState,
                        uint32_t &lastDebounceTime);
};