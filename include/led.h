#pragma once

#include "led_state.h"

class Led
{
private:
    u8_t pin;
    u32_t blinkingInterval;

    bool isOn;
    u32_t ledMask = 1u << pin;
    u32_t lastTimeChanged = 0;

    void On();
    void Off();

public:
    Led(u8_t pinValue, u32_t blinkingIntervalValue);

    void init();
    void set(LedState state);
};
