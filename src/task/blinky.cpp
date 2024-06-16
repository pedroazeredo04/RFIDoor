/**
 * @file state_machine.cpp
 *
 * @brief Blinky class source code
 *
 * @date 06/2024
 */

#include "task/blinky.hpp"

namespace rfidoor::task {

BlinkyTask::BlinkyTask(const rfidoor::peripheral::Led &led,
                       uint32_t blinky_frequency_ms,
                       const task_config_t &config)
    : Task(config), led{led}, blinky_frequency_ms{blinky_frequency_ms} {}

void BlinkyTask::init() {
  //
}

void BlinkyTask::spin() {
  this->led.toggle();
  this->task_sleep_ms(this->blinky_frequency_ms);
}

} // namespace rfidoor::task
