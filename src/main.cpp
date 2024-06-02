#include <peripheral/lcd.hpp>
#include <task/blinky.hpp>
#include <pinout.hpp>

namespace rfidoor::main {

const uint32_t blinky_frequency_ms{500};

// Tasks initializations
rfidoor::task::BlinkyTask blinky_task(board_led, blinky_frequency_ms, "blinkyTask");

}  // rfidoor::main

void setup() {
  Serial.begin(115200);

  // No need to initialize RTOS scheduler; ESP32 does it automatically
}

void loop() {
  // Loop empty, using RTOS;
}