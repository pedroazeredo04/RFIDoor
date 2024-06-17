/**
 * @file display.cpp
 * 
 * @brief DisplayTask class source code
 * 
 * @date 06/2024
 */

#include "blackboard/semaphore_blackboard.hpp"
#include "blackboard/task_blackboard.hpp"

namespace rfidoor::task {

DisplayTask::DisplayTask(const task_config_t &config)
    : Task(config) {}

void DisplayTask::init() {
}

void DisplayTask::spin() {
}

void DisplayTask::default_display(rfidoor::task::state_t state) {
  
  rfidoor::pinout::lcd.clear();
  rfidoor::pinout::lcd.set_cursor(0, 0);
  switch (state) {
    case rfidoor::task::state_t::TRANCADA_IDLE:
      rfidoor::pinout::lcd.write("Digite a senha ");
      rfidoor::pinout::lcd.write_special_char(
          rfidoor::peripheral::LOCK_SPECIAL_CHAR);
      break;
    case rfidoor::task::state_t::DIGITANDO_SENHA:
      const char* current_password = rfidoor::task::blackboard::password_task.get_current_password().c_str();
      default_display(rfidoor::task::state_t::TRANCADA_IDLE);
      rfidoor::pinout::lcd.set_cursor(0, 1);
      rfidoor::pinout::lcd.write(current_password);
      break;
    

  }
}

}; // namespace rfidoor::task
