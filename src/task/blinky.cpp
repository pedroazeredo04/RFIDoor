#include "task/blinky.hpp"

namespace rfidoor::task {

BlinkyTask::BlinkyTask(const rfidoor::peripheral::Led& led, uint32_t blinky_frequency_ms, const char* name, uint32_t stack_size, task_priority_t priority) : 
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
