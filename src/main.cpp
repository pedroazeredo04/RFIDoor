#include <task/blinky.hpp>
#include <pinout.hpp>

namespace rfidoor::pinout {

const uint32_t blinky_frequency_ms{500};

// Tasks initializations
 rfidoor::task::BlinkyTask blinky_task(board_led, blinky_frequency_ms, "blinkyTask");

}  // rfidoor::pinout

void setup() {
  rfidoor::pinout::lcd.init();
  rfidoor::pinout::lcd.setCursor(0,0);
	rfidoor::pinout::lcd.print("Hello, world!");
	rfidoor::pinout::lcd.setCursor(2,1);
	rfidoor::pinout::lcd.print("Chupa Tsuzuki");
  rfidoor::pinout::lcd.write_special_char(rfidoor::peripheral::SKULL_SPECIAL_CHAR);
}

void loop() {
  rfidoor::pinout::board_led.toggle();
  delay(500);
}