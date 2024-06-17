#include <blackboard/queue_blackboard.hpp>
#include <blackboard/task_blackboard.hpp>
#include <pinout.hpp>
#include <task/blinky.hpp>
#include <task/state_machine.hpp>

void setup() {
  Serial.begin(9600);

  rfidoor::task::blackboard::blinky_task.create_task();
  rfidoor::task::blackboard::password_task.create_task();
  rfidoor::task::blackboard::state_machine_task.create_task();
  rfidoor::task::blackboard::button_task.create_task();

  rfidoor::pinout::lcd.init();

  
}

void loop() {
  static bool is_registro{false};

  // Pega o estado do botão
  rfidoor::peripheral::Button::Status button_status =
      rfidoor::pinout::button.get_status();

  if (button_status == rfidoor::peripheral::Button::Status::SHORT_PRESS) {
    is_registro = not is_registro;
    Serial.println("flipou o registro");
    if (not is_registro) {
      rfidoor::queue::blackboard::state_queue.publish(
          rfidoor::task::state_t::TRANCADA_IDLE);
      Serial.println("Ta registrando n");
    } else {
      rfidoor::queue::blackboard::state_queue.publish(
          rfidoor::task::state_t::REGISTRO);
      Serial.println("Ta registrando");
    }
  }

  rfidoor::task::event_t evento = rfidoor::task::event_t::NENHUM_EVENTO;

  if (rfidoor::queue::blackboard::event_queue.read(&evento)) {
    Serial.println(evento);
  }
}