#pragma once
#include <Arduino.h>
#include "../core/Event.h"
#include "../config/Pins.h"

struct Preset
{

    const char *name;

    // ==============================
    // 16 klawiszy macierzy
    // ==============================
    ActionEvent keyActions[MATRIX_KEY_COUNT];

    // ==============================
    // ENCODER 1
    // ==============================
    ActionEvent encoder1CW;
    ActionEvent encoder1CCW;
    ActionEvent encoder1Press;

    // ==============================
    // ENCODER 2
    // ==============================
    ActionEvent encoder2CW;
    ActionEvent encoder2CCW;
    ActionEvent encoder2Press;
};