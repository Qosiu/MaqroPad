#pragma once
#include <Arduino.h>
#include "../core/Types.h"

class Encoder
{
public:
    Encoder(uint8_t pinDT, uint8_t pinCLK, uint8_t pinSW);

    void begin();

    // Wywoływać w każdej pętli
    void update();

    // Zwraca kierunek od ostatniego wywołania (DIR_NONE jeśli brak)
    EncoderDirection getDirection();

    // Surowy stan przycisku (LOW = wciśnięty)
    bool isButtonPressed() const;

private:
    uint8_t _pinDT;
    uint8_t _pinCLK;
    uint8_t _pinSW;

    uint8_t _lastState;
    EncoderDirection _direction;
};