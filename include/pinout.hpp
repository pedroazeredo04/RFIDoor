/**
 * @file pinout.hpp
 *
 * @brief Target specific configuration
 *
 * @date 06/2024
 */

#ifndef __PINOUT_HPP__
#define __PINOUT_HPP__

#include <peripheral/keyboard.hpp>
#include <peripheral/lcd.hpp>
#include <peripheral/led.hpp>
#include <peripheral/servo.hpp>
#include <peripheral/button.hpp>

namespace rfidoor::pinout {

/**
 * @brief LCD Pinout
 */
const uint8_t lcd_sda_pin{21};
const uint8_t lcd_scl_pin{22};

/**
 * @brief Internal LED Pinout
 */
const uint8_t internal_led_pin{2};

/**
 * @brief Keypad Pinout
 */
uint8_t keypad_row_pins[4] = {14, 13, 12, 15};
uint8_t keypad_col_pins[4] = {19, 23, 25, 26};

/**
 * @brief Servo Pinout
 */
const uint8_t servo_pin = 18;

/**
 * @brief Button Pinout
 */
const uint8_t button_pin = 5;

/**
 * @brief Peripheral initializations
 */
rfidoor::peripheral::Led board_led(internal_led_pin);
rfidoor::peripheral::Lcd lcd(lcd_sda_pin, lcd_scl_pin);
rfidoor::peripheral::Keyboard keyboard(keypad_row_pins, keypad_col_pins);
rfidoor::peripheral::ServoController servo(servo_pin);
rfidoor::peripheral::Button button(button_pin);

} // namespace rfidoor::pinout

#endif // __PINOUT_HPP__