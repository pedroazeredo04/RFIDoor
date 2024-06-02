/**
 * @file pinout.hpp
 *
 * @brief Target specific configuration
 *
 * @date 06/2024
 */

#ifndef __PINOUT_HPP__
#define __PINOUT_HPP__

#include <peripherical/led.hpp>
#include <peripherical/lcd.hpp>

namespace rfidoor::main {

// LCD pinout
const uint8_t lcd_sda_pin{21};
const uint8_t lcd_scl_pin{22};

// Internal LED pinout
const uint8_t internal_led_pin{2};

// Periphericals initializations
rfidoor::peripherical::Led board_led(internal_led_pin);
rfidoor::peripherical::Lcd lcd(lcd_sda_pin, lcd_scl_pin);

}  // rfidoor::main

#endif // __PINOUT_HPP__