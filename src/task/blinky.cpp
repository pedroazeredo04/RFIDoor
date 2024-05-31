#include "task/blinky.hpp"
#include <Arduino.h>
#include <freertos/FreeRTOS.h>

namespace rfidoor::task {

BlinkyTask::BlinkyTask(const char* task_name, rfidoor::peripherical::Led led, uint32_t blinky_frequency_ms) : Task(task_name), led{led}, blinky_frequency_ms{blinky_frequency_ms} {  }

void BlinkyTask::loop() {
    this->led.toggle();
    vTaskDelay(pdMS_TO_TICKS(this->blinky_frequency_ms));
}

} // rfidoor::task
