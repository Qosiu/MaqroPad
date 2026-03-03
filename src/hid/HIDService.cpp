#include "HIDService.h"

#include "USB.h"
#include "USBHIDKeyboard.h"

HIDService *HIDService::_instance = nullptr;

// TinyUSB keyboard
static USBHIDKeyboard Keyboard;

HIDService::HIDService()
{
    _instance = this;
}

void HIDService::begin()
{

    // Start USB stack
    USB.begin();
    Keyboard.begin();

    EventBus::subscribe(EVENT_ACTION, handleEvent);
}

// =====================================================
// ================= EVENT HANDLER ======================
// =====================================================

void HIDService::handleEvent(const Event &event)
{

    if (!_instance)
        return;

    if (event.type != EVENT_ACTION)
        return;

    _instance->processActionEvent(event.action);
}

// =====================================================
// ================= ACTION PROCESSING ==================
// =====================================================

void HIDService::processActionEvent(const ActionEvent &action)
{

    if (action.type != ACTION_SEND_REPORT)
        return;

    switch (action.report.reportType)
    {

    case REPORT_KEYBOARD:
        sendKeyboardReport(action.report.keycode,
                           action.report.modifiers);
        break;

    case REPORT_CONSUMER:
        sendConsumerReport(action.report.keycode);
        break;

    case REPORT_SYSTEM:
        sendSystemReport(action.report.keycode);
        break;

    case REPORT_MOUSE:
        sendMouseReport(action.report.keycode);
        break;

    default:
        break;
    }
}

// =====================================================
// ================= REPORT SENDERS =====================
// =====================================================

void HIDService::sendKeyboardReport(uint16_t keycode,
                                    uint8_t modifiers)
{
    Keyboard.pressRaw(keycode, modifiers);
    delay(5); // krótki impuls
    Keyboard.releaseAll();
}

void HIDService::sendConsumerReport(uint16_t keycode)
{
    // TODO: implementacja w przyszłości
}

void HIDService::sendSystemReport(uint16_t keycode)
{
    // TODO: implementacja w przyszłości
}

void HIDService::sendMouseReport(uint16_t keycode)
{
    // TODO: implementacja w przyszłości
}