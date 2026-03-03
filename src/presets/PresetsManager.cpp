#include "PresetManager.h"

PresetManager *PresetManager::_instance = nullptr;

PresetManager::PresetManager()
    : _presets(nullptr),
      _presetCount(0),
      _currentPreset(0)
{
    _instance = this;
}

void PresetManager::begin()
{
    EventBus::subscribe(EVENT_INPUT, handleEvent);
}

void PresetManager::setPresets(Preset *presets, uint8_t count)
{
    _presets = presets;
    _presetCount = count;
    _currentPreset = 0;
}

uint8_t PresetManager::getCurrentPresetIndex() const
{
    return _currentPreset;
}

const Preset &PresetManager::getCurrentPreset() const
{
    return _presets[_currentPreset];
}

void PresetManager::switchPreset(uint8_t index)
{

    if (index >= _presetCount)
        return;

    _currentPreset = index;

    // Możemy w przyszłości opublikować EVENT_ACTION lub EVENT_SYSTEM
    // żeby UI odświeżył ekran
}

// =====================================================
// ================= EVENT HANDLER ======================
// =====================================================

void PresetManager::handleEvent(const Event &event)
{

    if (!_instance)
        return;

    if (event.type != EVENT_INPUT)
        return;

    _instance->processInputEvent(event.input);
}

// =====================================================
// ================= LOGIKA MAPOWANIA ===================
// =====================================================

void PresetManager::processInputEvent(const InputEvent &input)
{

    if (!_presets)
        return;

    const Preset &preset = _presets[_currentPreset];

    Event actionEvent;
    actionEvent.type = EVENT_ACTION;

    switch (input.type)
    {

    case INPUT_KEY_DOWN:
        actionEvent.action = preset.keyActions[input.key];
        break;

    case INPUT_ENCODER_ROTATE:

        if (input.encoderRotate.id == ENCODER_1)
        {

            if (input.encoderRotate.direction == DIR_CW)
                actionEvent.action = preset.encoder1CW;
            else
                actionEvent.action = preset.encoder1CCW;
        }
        else
        {

            if (input.encoderRotate.direction == DIR_CW)
                actionEvent.action = preset.encoder2CW;
            else
                actionEvent.action = preset.encoder2CCW;
        }

        break;

    case INPUT_ENCODER_PRESS:

        if (input.encoderButton == ENCODER_1)
            actionEvent.action = preset.encoder1Press;
        else
            actionEvent.action = preset.encoder2Press;

        break;

    default:
        return; // ignorujemy KEY_UP i RELEASE na razie
    }

    // Jeśli akcja to przełącz preset
    if (actionEvent.action.type == ACTION_SWITCH_PRESET)
    {
        switchPreset(actionEvent.action.switchPreset.presetIndex);
        return;
    }

    // Ignoruj puste akcje
    if (actionEvent.action.type == ACTION_NONE)
        return;

    EventBus::publish(actionEvent);
}