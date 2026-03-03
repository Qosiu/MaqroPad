#pragma once
#include <Arduino.h>

#include "Preset.h"
#include "../core/EventBus.h"
#include "../config/Config.h"

class PresetManager
{
public:
    PresetManager();

    void begin();

    void setPresets(Preset *presets, uint8_t count);
    uint8_t getCurrentPresetIndex() const;
    const Preset &getCurrentPreset() const;

    void switchPreset(uint8_t index);

private:
    static void handleEvent(const Event &event);

    void processInputEvent(const InputEvent &input);

    static PresetManager *_instance;

    Preset *_presets;
    uint8_t _presetCount;
    uint8_t _currentPreset;
};