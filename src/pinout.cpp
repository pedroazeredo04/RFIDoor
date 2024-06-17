/**
 * @file pinout.cpp
 *
 * @brief Define target specific configuration variables
 *
 * @date 06/2024
 */

#include <pinout.hpp>

namespace rfidoor::pinout {

// LCD pinout
const uint8_t lcd_sda_pin{21};
const uint8_t lcd_scl_pin{22};

// Internal LED pinout
const uint8_t internal_led_pin{2};

// Keypad pinout
uint8_t keypad_row_pins[4]{14, 13, 12, 15};
uint8_t keypad_col_pins[4]{19, 23, 25, 26};

// Servo pinout
const uint8_t servoPin{18};

// NFC pinout
const uint8_t irq_pin{4};
const uint8_t rst_pin{5};

// Button pinout
const uint8_t button_pin{5};

// peripheral initializations
rfidoor::peripheral::Led board_led(internal_led_pin);
rfidoor::peripheral::Lcd lcd(lcd_sda_pin, lcd_scl_pin);
rfidoor::peripheral::Keyboard keyboard(keypad_row_pins, keypad_col_pins);
rfidoor::peripheral::ServoController servo(servoPin);
rfidoor::peripheral::Nfc nfc(irq_pin, rst_pin);
rfidoor::peripheral::Button button(button_pin);

} // namespace rfidoor::pinout