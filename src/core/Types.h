#pragma once
#include <Arduino.h>

// --- ID klawiszy 0–15 ---
using KeyId = uint8_t; // 0–15

// --- ID enkoderów ---
enum EncoderId : uint8_t
{
    ENCODER_1 = 0,
    ENCODER_2 = 1
};

// --- Kierunek enkodera ---
enum EncoderDirection : int8_t
{
    DIR_NONE = 0,
    DIR_CW = 1,
    DIR_CCW = -1
};