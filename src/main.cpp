#include <task/blinky.hpp>

const uint8_t internal_led_pin{2};
const uint32_t blinky_frequency_ms{500};

// Periphericals initializations
rfidoor::peripherical::Led led(internal_led_pin);

// Tasks initializations
rfidoor::task::BlinkyTask blinky_task(led, blinky_frequency_ms, "blinkyTask");

void setup() {
  Serial.begin(115200);

  // No need to initialize RTOS scheduler; ESP32 does it automatically
}

void loop() {
  // Loop empty, using RTOS;
}
