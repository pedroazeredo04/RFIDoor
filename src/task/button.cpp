/**
 * @file button.cpp
 *
 * @brief ButtonTask class source code
 *
 * @date 06/2024
 */

#include "task/button.hpp"
#include "blackboard/queue_blackboard.hpp"

namespace rfidoor::task {

ButtonTask::ButtonTask(const rfidoor::peripheral::Button &button,
                       const task_config_t &config)
    : Task(config), button{button},
      button_status{rfidoor::peripheral::Button::Status::NO_PRESS} {}

void ButtonTask::init() {}

void ButtonTask::spin() {
  this->button_status = this->button.get_status();
  if (this->button_status == rfidoor::peripheral::Button::Status::SHORT_PRESS) {
    rfidoor::queue::blackboard::event_queue.publish(
        rfidoor::task::event_t::BOTAO);
  }
}

} // namespace rfidoor::task
