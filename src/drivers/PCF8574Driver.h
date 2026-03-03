#pragma once
#include <Arduino.h>
#include <Wire.h>

class PCF8574Driver
{
public:
    PCF8574Driver(uint8_t address);

    void begin(uint8_t sda, uint8_t scl, uint32_t frequency);

    // Ustaw cały port (8 bitów)
    void write(uint8_t value);

    // Odczytaj cały port
    uint8_t read();

    // Operacje na pojedynczym pinie
    void setPin(uint8_t pin, bool level);
    bool readPin(uint8_t pin);

private:
    uint8_t _address;
    uint8_t _state; // ostatni zapisany stan portu
};