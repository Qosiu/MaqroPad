#pragma once
#include <Arduino.h>
#include "Event.h"

// =====================================================
// Prosty, statyczny EventBus
// =====================================================

namespace EventBus
{

    // Maksymalna liczba subskrybentów na typ zdarzenia
    constexpr uint8_t MAX_SUBSCRIBERS = 8;

    using EventCallback = void (*)(const Event &);

    struct Subscriber
    {
        EventType type;
        EventCallback callback;
    };

    // Statyczna lista subskrybentów
    static Subscriber subscribers[MAX_SUBSCRIBERS];
    static uint8_t subscriberCount = 0;

    // ==============================
    // SUBSCRIBE
    // ==============================
    inline void subscribe(EventType type, EventCallback callback)
    {

        if (subscriberCount >= MAX_SUBSCRIBERS)
            return; // brak miejsca

        subscribers[subscriberCount++] = {type, callback};
    }

    // ==============================
    // PUBLISH
    // ==============================
    inline void publish(const Event &event)
    {

        for (uint8_t i = 0; i < subscriberCount; i++)
        {

            if (subscribers[i].type == event.type)
            {
                subscribers[i].callback(event);
            }
        }
    }

}