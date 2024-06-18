/**
 * @file display.cpp
 * 
 * @brief DisplayTask class source code
 * 
 * @date 06/2024
 */

#include "blackboard/semaphore_blackboard.hpp"
#include "blackboard/task_blackboard.hpp"
#include "blackboard/queue_blackboard.hpp"

namespace rfidoor::task {

DisplayTask::DisplayTask(const task_config_t &config)
    : Task(config) {}

void DisplayTask::init() {
}

void DisplayTask::spin() {
    rfidoor::semaphore::blackboard::display_semaphore.take();
    this->default_display(blackboard::state_machine_task.get_state());
}

void DisplayTask::default_display(state_t state) {
  switch (state) {
    case state_t::TRANCADA_IDLE:
        rfidoor::pinout::lcd.clear();
        rfidoor::pinout::lcd.set_cursor(0, 0);
        rfidoor::pinout::lcd.write("Digite a senha ");
        rfidoor::pinout::lcd.write_special_char(
            rfidoor::peripheral::LOCK_SPECIAL_CHAR);

        Serial.println("PADRAO TRANCADA_IDLE");
        break;
    case state_t::DIGITANDO_SENHA:
        if (not rfidoor::queue::blackboard::password_queue.read(&(this->password_ch))){
            this->default_display(state_t::TRANCADA_IDLE);
        }
        rfidoor::pinout::lcd.set_cursor(1, 1);
        this->current_password = blackboard::password_task.get_current_password().c_str();
        rfidoor::pinout::lcd.write(this->current_password);

        Serial.println("PADRAO DIGITANDO_SENHA");
        break;
    case state_t::DESTRANCADA_FECHADA:
        rfidoor::pinout::lcd.clear();
        rfidoor::pinout::lcd.set_cursor(0, 0);
        rfidoor::pinout::lcd.write("     Porta     ");
        rfidoor::pinout::lcd.set_cursor(1, 1);
        rfidoor::pinout::lcd.write("  destrancada  ");

        Serial.println("PADRAO DESTRANCADA_FECHADA");
        break;
    case state_t::ABERTA:
        rfidoor::pinout::lcd.clear();
        rfidoor::pinout::lcd.set_cursor(0, 0);
        rfidoor::pinout::lcd.write("Segure o botão");
        rfidoor::pinout::lcd.set_cursor(1, 1);
        rfidoor::pinout::lcd.write("para registrar!");

        Serial.println("PADRAO ABERTA");
        break;
    case state_t::REGISTRO:
        this->default_display(state_t::DIGITANDO_SENHA);

        Serial.println("PADRAO REGISTRO");
        break;
  }
}

void DisplayTask::temporary_display(std::string message) {
    rfidoor::pinout::lcd.clear();
    rfidoor::pinout::lcd.set_cursor(0, 0);
    rfidoor::pinout::lcd.write(message.c_str());
    delay(2000);
}

}; // namespace rfidoor::task
