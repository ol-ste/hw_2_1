#pragma once

struct Config
{
    static constexpr u8_t LED_PIN = 18;
    static constexpr u32_t LED_BLINKING_INTERVAL = 500;

    static constexpr u8_t BTN_PIN = 17;
    static constexpr u16_t DEBOUNCE_MS = 100;
};