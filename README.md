# MaqroPad

# ESP32-C3 SuperMini Macropad

Custom 4x4 macropad built on **ESP32-C3 SuperMini** with:

- 16 MX-style mechanical switches (4x4 matrix with diodes)
- PCF8574 I2C GPIO expander
- 2x EC11 rotary encoders (with hardware pull-ups)
- SSD1306 128x64 OLED (I2C)
- USB HID (TinyUSB)
- Modular, event-driven software architecture

This project is designed to be **clean, scalable, and extensible** — ready for multiple presets, overlays, and future BLE support.

---

# ✨ Features (MVP)

- 16-key matrix with per-key debounce
- 2 rotary encoders (rotation + push)
- USB HID keyboard output
- Event-driven architecture
- Preset-based action mapping
- Clean separation of:
  - Hardware drivers
  - Input logic
  - Preset logic
  - HID layer

---

# 🧠 Architecture Overview

The firmware follows a layered architecture:

```
Hardware Drivers
    ↓
InputManager (debounce + edge detection)
    ↓
PresetManager (maps input → action)
    ↓
HIDService (Action → USB HID)
```

All communication between layers is handled via a lightweight static `EventBus`.

---

# 📁 Project Structure

```
/src
│
├── main.ino
├── App.h / App.cpp
│
├── config/
│   ├── Pins.h
│   ├── Config.h
│
├── core/
│   ├── Types.h
│   ├── Event.h
│   ├── EventBus.h
│
├── drivers/
│   ├── PCF8574Driver
│   ├── MatrixScanner
│   ├── Encoder
│
├── input/
│   ├── InputManager
│
├── presets/
│   ├── Preset
│   ├── PresetManager
│   └── Presets/
│       └── DefaultPreset
│
├── hid/
│   ├── HIDService
│
└── utils/ (future extensions)
```

---

# 🔌 Hardware Configuration

## I2C Bus

- SDA → GPIO6
- SCL → GPIO7
- PCF8574 address → 0x20
- OLED (SSD1306) → typically 0x3C

## Matrix via PCF8574

| PCF Pin | Function |
| ------- | -------- |
| P0–P3   | Rows     |
| P4–P7   | Columns  |

Matrix topology:

```
ROW → switch → diode → COL
```

Diodes prevent ghosting.

## Encoders

Encoder 1:

- DT → GPIO8
- CLK → GPIO9
- SW → GPIO10

Encoder 2:

- DT → GPIO4
- CLK → GPIO5
- SW → GPIO3

Modules include 10k pull-ups, so inputs use `INPUT`.

---

# ⚙️ Arduino IDE Settings

Board: **ESP32-C3**

Recommended options:

- USB Mode → `USB-OTG (TinyUSB)`
- USB CDC On Boot → `Enabled`
- Upload Speed → default

---

# 🚀 Default Preset (MVP)

### 4x4 Keys

Keys send letters **A–P**.

### Encoder 1

- Rotate → (prepared for volume control)
- Press → preset switch

### Encoder 2

- CW → Arrow Up
- CCW → Arrow Down
- Press → Enter

---

# 🧩 Design Principles

- No dynamic memory allocation
- No STL
- No `String`
- Union-based event structures (RAM efficient)
- Header-only EventBus
- Clear separation of responsibilities

Drivers never:

- Publish events
- Know about presets
- Know about HID

---

# 🛠 Roadmap

Planned next steps:

- SSD1306 OLED UI (U8g2)
- Overlay system (volume / zoom indicators)
- Consumer Control HID support
- Multiple presets
- BLE mode
- Flash-stored configuration
- Per-app preset switching

---

# 📜 License

MIT

---

# 🧪 Status

MVP: Functional USB macropad
Architecture: Stable and extensible
Ready for UI layer integration
