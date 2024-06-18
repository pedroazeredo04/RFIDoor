#include <blackboard/queue_blackboard.hpp>
#include <blackboard/task_blackboard.hpp>
#include <pinout.hpp>
#include <task/blinky.hpp>
#include <task/state_machine.hpp>

void setup() {
  Serial.begin(9600);

  rfidoor::task::blackboard::blinky_task.create_task();
  rfidoor::task::blackboard::password_task.create_task();

  rfidoor::pinout::lcd.init();
  // rfidoor::pinout::lcd.set_cursor(0, 0);
  // rfidoor::pinout::lcd.write("Hello, world!");
  // rfidoor::pinout::lcd.set_cursor(2, 1);
  // rfidoor::pinout::lcd.write("Chupa Tsuzuki");
  // rfidoor::pinout::lcd.write_special_char(
  //     rfidoor::peripheral::SKULL_SPECIAL_CHAR);
  // delay(3000);

  rfidoor::pinout::lcd.clear();
  rfidoor::pinout::lcd.set_cursor(0, 0);
  rfidoor::pinout::lcd.write("Digite a senha ");
  rfidoor::pinout::lcd.write_special_char(
      rfidoor::peripheral::LOCK_SPECIAL_CHAR);
  rfidoor::pinout::lcd.set_cursor(0, 1);

  // Initialize the servo to 0 degrees
  rfidoor::pinout::servo.write_angular_position_degrees(0);

  rfidoor::queue::blackboard::state_queue.publish(
      rfidoor::task::state_t::TRANCADA_IDLE);

  delay(1000); // Wait for 1 second
}

void loop() {
  static bool is_registro{false};

  // Pega o estado do botão
  // rfidoor::peripheral::Button::Status button_status =
  //     rfidoor::pinout::inside_button.get_status();

  bool button_read = rfidoor::pinout::inside_button.is_pressed();

  if (button_read) {
    Serial.println("Botao pressionado");
  }

  // if (button_status == rfidoor::peripheral::Button::Status::SHORT_PRESS) {
  //   is_registro = not is_registro;
  //   Serial.println("flipou o registro");
  //   if (not is_registro) {
  //     rfidoor::queue::blackboard::state_queue.publish(
  //         rfidoor::task::state_t::TRANCADA_IDLE);
  //     Serial.println("Ta registrando n");
  //   } else {
  //     rfidoor::queue::blackboard::state_queue.publish(
  //         rfidoor::task::state_t::REGISTRO);
  //     Serial.println("Ta registrando");
  //   }
  // }

  // rfidoor::task::event_t evento = rfidoor::task::event_t::NENHUM_EVENTO;

  // if (rfidoor::queue::blackboard::event_queue.read(&evento)) {
  //   Serial.println(evento);
  // }
}