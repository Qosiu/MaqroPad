#pragma once
#include <Arduino.h>

// =====================================================
// ================= I2C ================================
// =====================================================

// Wspólna magistrala dla OLED + PCF8574

constexpr uint8_t PIN_I2C_SDA = 6;
constexpr uint8_t PIN_I2C_SCL = 7;

constexpr uint8_t I2C_ADDR_PCF8574 = 0x20;
// SSD1306 zwykle 0x3C — ustawimy w DisplayManager

// =====================================================
// ================= ENCODER 1 ==========================
// =====================================================

constexpr uint8_t PIN_ENC1_DT = 8;
constexpr uint8_t PIN_ENC1_CLK = 9;
constexpr uint8_t PIN_ENC1_SW = 10;

// =====================================================
// ================= ENCODER 2 ==========================
// =====================================================

constexpr uint8_t PIN_ENC2_DT = 4;
constexpr uint8_t PIN_ENC2_CLK = 5;
constexpr uint8_t PIN_ENC2_SW = 3;

// =====================================================
// ================= MATRIX (PCF8574) ===================
// =====================================================

// PCF8574:
// P0 → R0
// P1 → R1
// P2 → R2
// P3 → R3
// P4 → C0
// P5 → C1
// P6 → C2
// P7 → C3

constexpr uint8_t MATRIX_ROWS = 4;
constexpr uint8_t MATRIX_COLS = 4;
constexpr uint8_t MATRIX_KEY_COUNT = 16;