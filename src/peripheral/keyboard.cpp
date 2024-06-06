/**
 * @file keyboard.cpp
 *
 * @brief Keyboard class implementation
 *
 * @date 06/2024
 */

#include <peripheral/keyboard.hpp>

namespace rfidoor::peripheral {

const unsigned char keyboard_rowls{4};
const unsigned char keyboard_cols{4};

const char keyboard_keys[keyboard_rowls][keyboard_cols]{{'1', '2', '3', 'A'},
                                                        {'4', '5', '6', 'B'},
                                                        {'7', '8', '9', 'C'},
                                                        {'*', '0', '#', 'D'}};

Keyboard::Keyboard(unsigned char *row_pins, unsigned char *col_pins)
    : row_pins{row_pins}, col_pins{col_pins},
      lib_keypad{Keypad(makeKeymap(keyboard_keys), row_pins, col_pins,
                        keyboard_rowls, keyboard_cols)} {}

char Keyboard::getKey() { return this->lib_keypad.getKey(); }

} // namespace rfidoor::peripheral
