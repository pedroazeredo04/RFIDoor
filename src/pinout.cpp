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
uint8_t keypad_row_pins[4]{12, 14, 27, 26};
uint8_t keypad_col_pins[4]{25, 33, 32, 15};

/**
 * @brief Servo pinout
 */
const uint8_t servoPin{13};

/**
 * @brief NFC Pinout
 */
const uint8_t irq_pin{2};
const uint8_t rst_pin{4};

/**
 * @brief Inside button pin
 */
extern const uint8_t inside_button_pin{18};

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
Adafruit_PN532 nfc(irq_pin, rst_pin);
rfidoor::peripheral::Button inside_button(inside_button_pin);
rfidoor::peripheral::Button door_button(door_button_pin);

BluetoothSerial SerialBT;

} // namespace rfidoor::pinout