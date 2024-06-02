#include <peripherical/lcd.hpp>
#include <task/blinky.hpp>

const uint8_t internal_led_pin{2};
const uint32_t blinky_frequency_ms{500};

const uint8_t lcd_sda_pin{2};
const uint8_t lcd_scl_pin{3};

// Periphericals initializations
rfidoor::peripherical::Led board_led(internal_led_pin);
rfidoor::peripherical::Lcd lcd(lcd_sda_pin, lcd_scl_pin);

// Tasks initializations
rfidoor::task::BlinkyTask blinky_task(board_led, blinky_frequency_ms, "blinkyTask");

void setup() {
  Serial.begin(115200);

  // No need to initialize RTOS scheduler; ESP32 does it automatically
}

void loop() {
  // Loop empty, using RTOS;
}
