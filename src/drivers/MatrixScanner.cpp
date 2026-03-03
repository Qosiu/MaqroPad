#include "MatrixScanner.h"

MatrixScanner::MatrixScanner(PCF8574Driver &pcf)
    : _pcf(pcf), _rawState(0)
{
}

void MatrixScanner::begin()
{
    // Ustaw wszystko HIGH (czyli wejścia)
    _pcf.write(0xFF);
}

void MatrixScanner::driveRow(uint8_t row)
{

    // Wszystkie piny HIGH (input)
    uint8_t value = 0xFF;

    // P0–P3 to ROW
    // Ustaw wybraną linię ROW na LOW
    value &= ~(1 << row);

    _pcf.write(value);
}

void MatrixScanner::scan()
{

    uint16_t newState = 0;

    for (uint8_t row = 0; row < MATRIX_ROWS; row++)
    {

        driveRow(row);

        // krótka stabilizacja sygnału
        delayMicroseconds(30);

        uint8_t portState = _pcf.read();

        for (uint8_t col = 0; col < MATRIX_COLS; col++)
        {

            // P4–P7 to kolumny
            bool pressed = !(portState & (1 << (col + 4)));

            if (pressed)
            {
                uint8_t index = row * MATRIX_COLS + col;
                newState |= (1 << index);
            }
        }
    }

    _rawState = newState;
}

uint16_t MatrixScanner::getRawState() const
{
    return _rawState;
}