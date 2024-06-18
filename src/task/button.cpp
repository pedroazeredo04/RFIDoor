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

ButtonTask::ButtonTask(const rfidoor::peripheral::Button &inside_button,
                       const rfidoor::peripheral::Button &door_button,
                       const task_config_t &config)
    : Task(config), inside_button{inside_button}, door_button{door_button},
      inside_button_status{rfidoor::peripheral::Button::Status::NO_PRESS},
      door_button_status{rfidoor::peripheral::Button::Status::NO_PRESS} {}

void ButtonTask::init() {}

void ButtonTask::spin() {
  this->inside_button_status = this->inside_button.get_status();
  this->door_button_status = this->door_button.get_status();

  if (this->inside_button_status ==
      rfidoor::peripheral::Button::Status::SHORT_PRESS) {
    rfidoor::queue::blackboard::event_queue.publish(
        rfidoor::task::event_t::BOTAO);
  }

  if (this->door_button.is_pressed()) {
    rfidoor::queue::blackboard::event_queue.publish(
        rfidoor::task::event_t::FECHAR);
  }
}

} // namespace rfidoor::task
