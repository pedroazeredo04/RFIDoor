#include <task/blinky.hpp>
#include <pinout.hpp>
#include <task_scheme.hpp>
const uint32_t blinky_frequency_ms{500};

// Tasks initializations
 rfidoor::task::BlinkyTask blinky_task(rfidoor::pinout::board_led, blinky_frequency_ms, rfidoor::task::blinky_config);

void setup() {
  blinky_task.create_task();

  rfidoor::pinout::lcd.init();
  rfidoor::pinout::lcd.set_cursor(0,0);
	rfidoor::pinout::lcd.write("Hello, world!");
	rfidoor::pinout::lcd.set_cursor(2,1);
	rfidoor::pinout::lcd.write("Chupa Tsuzuki");
  rfidoor::pinout::lcd.write_special_char(rfidoor::peripheral::SKULL_SPECIAL_CHAR);

  delay(5000);
  rfidoor::pinout::lcd.clear();
  rfidoor::pinout::lcd.set_cursor(0, 0);
  rfidoor::pinout::lcd.write("Digite a senha ");
  rfidoor::pinout::lcd.write_special_char(rfidoor::peripheral::LOCK_SPECIAL_CHAR);
  rfidoor::pinout::lcd.set_cursor(0, 1);

  // Initialize the servo to 0 degrees
  rfidoor::pinout::servo.write(0);
  delay(1000); // Wait for 1 second
}

void loop() {
  char key = rfidoor::pinout::keyboard.getKey();

  if (key){
    rfidoor::pinout::lcd.write_char_with_increment(key);

    // Move the servo to 90 degrees when a key is pressed
    rfidoor::pinout::servo.write(90);
    delay(2000); // Wait for 2 seconds

    // Move the servo back to 0 degrees
    rfidoor::pinout::servo.write(0);
    delay(2000); // Wait for 2 seconds
  }
}