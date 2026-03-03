#include "Encoder.h"

Encoder::Encoder(uint8_t pinDT, uint8_t pinCLK, uint8_t pinSW)
    : _pinDT(pinDT),
      _pinCLK(pinCLK),
      _pinSW(pinSW),
      _lastState(0),
      _direction(DIR_NONE)
{
}

void Encoder::begin()
{
    pinMode(_pinDT, INPUT);
    pinMode(_pinCLK, INPUT);
    pinMode(_pinSW, INPUT);

    // zapamiętaj początkowy stan CLK
    _lastState = digitalRead(_pinCLK);
}

void Encoder::update()
{

    uint8_t currentState = digitalRead(_pinCLK);

    // reagujemy tylko na zbocze opadające
    if (_lastState == HIGH && currentState == LOW)
    {

        if (digitalRead(_pinDT) == HIGH)
        {
            _direction = DIR_CW;
        }
        else
        {
            _direction = DIR_CCW;
        }
    }

    _lastState = currentState;
}

EncoderDirection Encoder::getDirection()
{
    EncoderDirection dir = _direction;
    _direction = DIR_NONE; // reset po odczycie
    return dir;
}

bool Encoder::isButtonPressed() const
{
    return digitalRead(_pinSW) == LOW; // aktywne LOW
}