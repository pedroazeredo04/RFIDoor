#include <pinout.hpp>
#include <queue_scheme.hpp>
#include <task/blinky.hpp>
#include <task/state_machine.hpp>
#include <task_scheme.hpp>

void setup() {
  Serial.begin(9600);

  rfidoor::task::blinky_task.create_task();
  rfidoor::task::state_machine_task.create_task();

  rfidoor::pinout::lcd.init();
  // rfidoor::pinout::lcd.set_cursor(0, 0);
  // rfidoor::pinout::lcd.write("Hello, world!");
  // rfidoor::pinout::lcd.set_cursor(2, 1);
  // rfidoor::pinout::lcd.write("Chupa Tsuzuki");
  // rfidoor::pinout::lcd.write_special_char(
  //     rfidoor::peripheral::SKULL_SPECIAL_CHAR);
  // delay(3000);

  Serial.begin(9600);

  rfidoor::pinout::lcd.clear();
  rfidoor::pinout::lcd.set_cursor(0, 0);
  rfidoor::pinout::lcd.write("Digite a senha ");
  rfidoor::pinout::lcd.write_special_char(
      rfidoor::peripheral::LOCK_SPECIAL_CHAR);
  rfidoor::pinout::lcd.set_cursor(0, 1);

  // Initialize the servo to 0 degrees
  rfidoor::pinout::servo.write_angular_position_degrees(0);
  delay(1000); // Wait for 1 second
}

void loop() {
  char key = rfidoor::pinout::keyboard.getKey();

  if (key) {
    rfidoor::pinout::lcd.write_char_with_increment(key);

    if (key == '*') {
      rfidoor::queue::events_queue.publish(rfidoor::task::SENHA_INVALIDA);
    } else {
      rfidoor::queue::events_queue.publish(rfidoor::task::TECLA);
    }

    // // Move the servo to 90 degrees when a key is pressed
    // rfidoor::pinout::servo.write_angular_position_degrees(90);
    // delay(2000); // Wait for 2 seconds

    // // Move the servo back to 0 degrees
    // rfidoor::pinout::servo.write_angular_position_degrees(0);
    // delay(2000); // Wait for 2 seconds
  }

  rfidoor::task::event_t evento;

  if (rfidoor::queue::events_queue.read(&evento)) {
    Serial.println(evento);
  }
}