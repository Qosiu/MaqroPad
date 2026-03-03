#pragma once
#include <Arduino.h>

#include "../core/EventBus.h"
#include "../core/Event.h"

class HIDService
{
public:
    HIDService();

    void begin();

private:
    static void handleEvent(const Event &event);

    void processActionEvent(const ActionEvent &action);

    void sendKeyboardReport(uint16_t keycode, uint8_t modifiers);
    void sendConsumerReport(uint16_t keycode);
    void sendSystemReport(uint16_t keycode);
    void sendMouseReport(uint16_t keycode);

    static HIDService *_instance;
};