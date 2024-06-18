/**
 * @file button.cpp
 *
 * @brief ButtonTask class source code
 *
 * @date 06/2024
 */

#include "blackboard/task_blackboard.hpp"
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
    if (blackboard::state_machine_task.get_state() == state_t::ABERTA) {
        rfidoor::queue::blackboard::event_queue.publish(
            rfidoor::task::event_t::FECHAR);
      Serial.println("oi vou fechar");
    }
    Serial.println("Botao da porta pressionado");
  }
  else if (blackboard::state_machine_task.get_state() == state_t::DESTRANCADA_FECHADA) {
    rfidoor::queue::blackboard::event_queue.publish(
        rfidoor::task::event_t::ABRIR);
        Serial.println("Botao da porta despressionado");
  }
}

} // namespace rfidoor::task
