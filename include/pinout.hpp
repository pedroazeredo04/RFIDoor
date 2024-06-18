/**
 * @file pinout.hpp
 *
 * @brief Target specific configuration
 *
 * @date 06/2024
 */

#ifndef __PINOUT_HPP__
#define __PINOUT_HPP__

#include "peripheral/button.hpp"
#include "peripheral/keyboard.hpp"
#include "peripheral/lcd.hpp"
#include "peripheral/led.hpp"
#include "peripheral/nfc.hpp"
#include "peripheral/servo.hpp"

namespace rfidoor::pinout {

/**
 * @brief LCD pinout
 */
extern const uint8_t lcd_sda_pin;
extern const uint8_t lcd_scl_pin;

/**
 * @brief Internal LED Pinout
 */
extern const uint8_t internal_led_pin;

/**
 * @brief Keypad pinout
 */
extern uint8_t keypad_row_pins[4];
extern uint8_t keypad_col_pins[4];

/**
 * @brief Servo pinout
 */
extern const uint8_t servoPin;

/**
 * @brief NFC pinout
 */
extern const uint8_t irq_pin;
extern const uint8_t rst_pin;

/**
 * @brief Inside button pin
 */
extern const uint8_t inside_button_pin;

/**
 * @brief Door button pin
 */
extern const uint8_t door_button_pin;

/**
 * @brief Peripheral Initializations
 */
extern rfidoor::peripheral::Led board_led;
extern rfidoor::peripheral::Lcd lcd;
extern rfidoor::peripheral::Keyboard keyboard;
extern rfidoor::peripheral::ServoController servo;
extern rfidoor::peripheral::Nfc nfc;
extern rfidoor::peripheral::Button inside_button;
extern rfidoor::peripheral::Button door_button;

} // namespace rfidoor::pinout

#endif // __PINOUT_HPP__