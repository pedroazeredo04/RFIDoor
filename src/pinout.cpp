/**
 * @file pinout.cpp
 *
 * @brief Define target specific configuration variables
 *
 * @date 06/2024
 */

#include <pinout.hpp>

namespace rfidoor::pinout {

/**
 * @brief LCD Pinout
 */
const uint8_t lcd_sda_pin{21};
const uint8_t lcd_scl_pin{22};

/**
 * @brief Internal LED pinout
 */
const uint8_t internal_led_pin{2};

/**
 * @brief Keyboard pinout
 */
// Old config
uint8_t keypad_row_pins[4]{14, 13, 12, 15};
uint8_t keypad_col_pins[4]{19, 23, 25, 26};

// New try
// uint8_t keypad_row_pins[4]{35, 32, 33, 25};
// uint8_t keypad_col_pins[4]{26, 27, 14, 12};

/**
 * @brief Servo pinout
 */
const uint8_t servoPin{18};

/**
 * @brief NFC Pinout
 */
const uint8_t irq_pin{4};
const uint8_t rst_pin{5};

/**
 * @brief Inside button pin
 */
extern const uint8_t inside_button_pin{34};

/**
 * @brief Door button pin
 */
extern const uint8_t door_button_pin{5};

/**
 * @brief Peripheral initializations
 */
rfidoor::peripheral::Led board_led(internal_led_pin);
rfidoor::peripheral::Lcd lcd(lcd_sda_pin, lcd_scl_pin);
rfidoor::peripheral::Keyboard keyboard(keypad_row_pins, keypad_col_pins);
rfidoor::peripheral::ServoController servo(servoPin);
rfidoor::peripheral::Nfc nfc(irq_pin, rst_pin);
rfidoor::peripheral::Button inside_button(inside_button_pin);
rfidoor::peripheral::Button door_button(door_button_pin);

BluetoothSerial SerialBT;

} // namespace rfidoor::pinout