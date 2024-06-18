/**
 * @file password.cpp
 *
 * @brief Password class source code
 *
 * @date 06/2024
 */

#include "task/password.hpp"
#include "blackboard/queue_blackboard.hpp"
#include "blackboard/semaphore_blackboard.hpp"
#include "blackboard/task_blackboard.hpp"

namespace rfidoor::task {

PasswordTask::PasswordTask(rfidoor::peripheral::Keyboard &keyboard,
                           const task_config_t &config)
    : Task(config), keyboard{keyboard} {}

void PasswordTask::init() {
  this->valid_passwords.push_back({"1234"});
  this->valid_passwords.push_back({"000000"});
}

void PasswordTask::spin() {
  this->current_state_machine_state =
      blackboard::state_machine_task.get_state();

  switch (this->current_state_machine_state) {
  case REGISTRO: {
    this->register_password();
    break;
  }

  default: {
    this->read_password();
    break;
  }
  }
}

std::vector<PasswordTask::password_t>
PasswordTask::get_valid_passwords() const {
  return this->valid_passwords;
}

void PasswordTask::read_password() {
  char key = this->keyboard.getKey();

  if (key) {
    if (not this->is_entering_password) {
      if (not(key >= '0' and key <= '9'))
        return; // First letter must be a number

      this->is_entering_password = true;
      this->current_password.password.clear();
      rfidoor::queue::blackboard::event_queue.publish(event_t::TECLA);
    }

    if (key >= '0' and key <= '9') {
      this->current_password.password += key;
    }

    if ((this->current_password.password.length() >= password_max_length) or
        key == '#') {
      this->is_entering_password = false;

      for (const auto &password : this->valid_passwords) {
        if (password.password == this->current_password.password) {
          rfidoor::queue::blackboard::event_queue.publish(
              event_t::SENHA_VALIDA);
          return;
        }
      }
      rfidoor::queue::blackboard::event_queue.publish(event_t::SENHA_INVALIDA);
    }
  }
}

void PasswordTask::register_password() {
  char key = this->keyboard.getKey();

  if (key) {
    if (not this->is_entering_password) {
      if (not(key >= '0' and key <= '9'))
        return; // First letter must be a number

      rfidoor::semaphore::blackboard::registering_semaphore.take();
      this->is_entering_password = true;
      this->current_password.password.clear();
    }

    if (key >= '0' and key <= '9') {
      this->current_password.password += key;
    }

    if ((this->current_password.password.length() >= password_max_length) or
        key == '#') {
      this->is_entering_password = false;
      this->valid_passwords.push_back(this->current_password);
      rfidoor::queue::blackboard::event_queue.publish(
          event_t::SENHA_CADASTRADA);
      rfidoor::semaphore::blackboard::registering_semaphore.give();
    }
  }
}

} // namespace rfidoor::task
