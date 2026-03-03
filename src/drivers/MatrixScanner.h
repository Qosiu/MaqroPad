#pragma once
#include <Arduino.h>
#include "PCF8574Driver.h"
#include "../config/Pins.h"

class MatrixScanner
{
public:
    MatrixScanner(PCF8574Driver &pcf);

    void begin();

    // Wykonuje jeden pełny scan 4x4
    void scan();

    // Zwraca surowy stan (bitmask 16 bitów)
    uint16_t getRawState() const;

private:
    PCF8574Driver &_pcf;

    uint16_t _rawState;

    void driveRow(uint8_t row);
};