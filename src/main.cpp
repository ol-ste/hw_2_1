#include <Arduino.h>

#include "led.h"
#include "config.h"

volatile bool BtnEvent = false;
volatile u32_t LastPress = 0;

LedState currentState = LedState::Off;
Led led(Config::LED_PIN, Config::LED_BLINKING_INTERVAL);

void IRAM_ATTR onButton()
{
  u32_t now = millis();
  if (now - LastPress > Config::DEBOUNCE_MS)
  {
    LastPress = now;
    BtnEvent = true;
  }
}

void io_init()
{
  led.init();
  pinMode(Config::BTN_PIN, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(Config::BTN_PIN), onButton, RISING);
}

void setup()
{
  Serial.begin(115200);
  io_init();
  Serial.println("Setup completed...");
}

void loop()
{
  u32_t loopStartTime = millis();
  bool pressed = BtnEvent;
  if (pressed)
  {
    BtnEvent = false;
  }

  switch (currentState)
  {
  case LedState::Off:
    led.set(LedState::Off);
    if (pressed)
    {
      currentState = LedState::Blinking;
      Serial.println("Changing state to Blinking...");
    }
    break;
  case LedState::Blinking:
    led.set(LedState::Blinking);
    if (pressed)
    {
      currentState = LedState::On;
      Serial.println("Changing state to On...");
    }
    break;
  case LedState::On:
    led.set(LedState::On);
    if (pressed)
    {
      currentState = LedState::Off;
      Serial.println("Changing state to Off...");
    }
    break;
  }
}