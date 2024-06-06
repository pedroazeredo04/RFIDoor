/**
 * @file keyboard.hpp
 *
 * @brief keyboard class header
 *
 * @date 06/2024
 */

#ifndef __KEYBOARD_HPP__
#define __KEYBOARD_HPP__

#include <Arduino.h>
#include <Keypad.h>

namespace rfidoor::peripheral {

extern const unsigned char keypad_rowls;
extern const unsigned char keypad_cols;

extern const char keyboard_keys[4][4];

enum keyboard_chars_t {
  A = 10,
  B,
  C,
  D,
};

/**
 * @brief Class for controlling a Keyboard
 */
class Keyboard {
public:
  /**
   * @brief Constructor for the Keypad class
   *
   * @param config
   */
  explicit Keyboard(unsigned char *row_pins, unsigned char *col_pins);

  /**
   * @brief Reads keypad current pressed key
   *
   * @return Char that keypad has read
   */
  char getKey();

private:
  /**
   * @brief Keypad row pins
   */
  const uint8_t *row_pins;

  /**
   * @brief Keypad column pins
   */
  const uint8_t *col_pins;

  /**
   * @brief Keypad pins
   */
  Keypad lib_keypad;
};

} // namespace rfidoor::peripheral

#endif // __KEYBOARD_HPP__