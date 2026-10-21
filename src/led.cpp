#include <Arduino.h>
#include "led.h"

Led::Led(u8_t pinValue, u32_t blinkingIntervalValue) : pin(pinValue), blinkingInterval(blinkingIntervalValue) {}

void Led::init()
{
    pinMode(pin, OUTPUT);
}

void Led::set(LedState state)
{
    switch (state)
    {
    case LedState::Off:
        isOn = false;
        Off();
        break;
    case LedState::On:
        isOn = true;
        On();
        break;
    case LedState::Blinking:
        if (millis() - lastTimeChanged > blinkingInterval)
        {
            lastTimeChanged = millis();
            isOn = !isOn;
            isOn ? On() : Off();
        }
        break;
    default:
        break;
    }
}

void Led::On()
{
    GPIO.out_w1ts = ledMask;
}

void Led::Off()
{
    GPIO.out_w1tc = ledMask;
}