#include <task/blinky.hpp>
#include <pinout.hpp>

const uint32_t blinky_frequency_ms{500};

// Tasks initializations
rfidoor::task::BlinkyTask blinky_task(rfidoor::pinout::board_led, blinky_frequency_ms, "blinkyTask"); 

void setup() {
  rfidoor::pinout::lcd.init();
  rfidoor::pinout::lcd.set_cursor(0,0);
	rfidoor::pinout::lcd.write("Hello, world!");
	rfidoor::pinout::lcd.set_cursor(2,1);
	rfidoor::pinout::lcd.write("Chupa Tsuzuki");
  rfidoor::pinout::lcd.write_special_char(rfidoor::peripheral::SKULL_SPECIAL_CHAR);

  delay(1000);
  rfidoor::pinout::lcd.clear();
  rfidoor::pinout::lcd.set_cursor(0, 0);
  rfidoor::pinout::lcd.write("Digite a senha ");
  rfidoor::pinout::lcd.write_special_char(rfidoor::peripheral::LOCK_SPECIAL_CHAR);
  rfidoor::pinout::lcd.set_cursor(0, 1);
}

void loop() {
  char key = rfidoor::pinout::keyboard.getKey();

  if (key){
    rfidoor::pinout::lcd.write_char_with_increment(key);
  }
}
