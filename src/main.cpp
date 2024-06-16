#include <pinout.hpp>
#include <task/blinky.hpp>
#include <task/state_machine.hpp>
#include <task_scheme.hpp>
const uint32_t blinky_frequency_ms{500};

// Tasks initializations
rfidoor::task::BlinkyTask blinky_task(rfidoor::pinout::board_led,
                                      blinky_frequency_ms,
                                      rfidoor::task::blinky_config);
rfidoor::task::StateMachineTask
    state_machine_task(rfidoor::task::state_machine_config);

void setup() {
  // blinky_task.create_task();
  // state_machine_task.create_task();

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

  if (rfidoor::pinout::button.get_status() ==
      rfidoor::peripheral::Button::Status::EXTRA_LONG_PRESS) {
    rfidoor::pinout::board_led.toggle();
    Serial.println("Button pressed");
  }

  if (key) {
    rfidoor::pinout::lcd.write_char_with_increment(key);
  }
}