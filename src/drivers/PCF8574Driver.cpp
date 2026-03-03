#include "PCF8574Driver.h"

PCF8574Driver::PCF8574Driver(uint8_t address)
    : _address(address), _state(0xFF) // domyślnie wszystko HIGH (input)
{
}

void PCF8574Driver::begin(uint8_t sda, uint8_t scl, uint32_t frequency)
{
    Wire.begin(sda, scl);
    Wire.setClock(frequency);

    // Ustaw wszystko jako HIGH (czyli wejścia z pull-up)
    write(_state);
}

void PCF8574Driver::write(uint8_t value)
{
    _state = value;

    Wire.beginTransmission(_address);
    Wire.write(_state);
    Wire.endTransmission();
}

uint8_t PCF8574Driver::read()
{
    Wire.requestFrom(_address, (uint8_t)1);

    if (Wire.available())
    {
        _state = Wire.read();
    }

    return _state;
}

void PCF8574Driver::setPin(uint8_t pin, bool level)
{
    if (level)
        _state |= (1 << pin);
    else
        _state &= ~(1 << pin);

    write(_state);
}

bool PCF8574Driver::readPin(uint8_t pin)
{
    uint8_t value = read();
    return value & (1 << pin);
}