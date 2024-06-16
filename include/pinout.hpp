/**
 * @file pinout.hpp
 *
 * @brief Target specific configuration
 *
 * @date 06/2024
 */

#ifndef __PINOUT_HPP__
#define __PINOUT_HPP__

#include <peripheral/button.hpp>
#include <peripheral/keyboard.hpp>
#include <peripheral/lcd.hpp>
#include <peripheral/led.hpp>
#include <peripheral/servo.hpp>

namespace rfidoor::pinout {

// LCD pinout
extern const uint8_t lcd_sda_pin;
extern const uint8_t lcd_scl_pin;

// Internal LED pinout
extern const uint8_t internal_led_pin;

// Keypad pinout
extern uint8_t keypad_row_pins[4];
extern uint8_t keypad_col_pins[4];

// Servo pinout
extern const uint8_t servoPin;

// peripheral initializations
extern rfidoor::peripheral::Led board_led;
extern rfidoor::peripheral::Lcd lcd;
extern rfidoor::peripheral::Keyboard keyboard;
extern rfidoor::peripheral::ServoController servo;

} // namespace rfidoor::pinout

#endif // __PINOUT_HPP__