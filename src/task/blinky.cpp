#include "task/blinky.hpp"
#include <Arduino.h>
#include <freertos/FreeRTOS.h>

namespace rfidoor::task {

BlinkyTask::BlinkyTask(const rfidoor::peripherical::Led& led, uint32_t blinky_frequency_ms, const char* name, uint32_t stack_size, UBaseType_t priority) : 
                       Task(name, stack_size, priority), 
                       led{led}, 
                       blinky_frequency_ms{blinky_frequency_ms} {  }

void BlinkyTask::init() {
    //
}

void BlinkyTask::spin() {
    this->led.toggle();
    this->task_sleep_ms(this->blinky_frequency_ms);
}

} // rfidoor::task
