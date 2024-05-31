#include <peripherical/led.hpp>
#include <task/blinky.hpp>

const uint8_t internal_led_pin{2};
const uint32_t blinky_frequency_ms{500};

void setup() {
  rfidoor::peripherical::Led led(internal_led_pin);
  rfidoor::task::BlinkyTask blinky_task("Blinky", led, blinky_frequency_ms);
}

void loop() {
  // Empty loop since we are using FreeRTOS tasks
}
