/**
 * @file special_chars.hpp
 *
 * @brief Some special chars to be included in LCD implementation
 *
 * @note Taken from: https://lastminuteengineers.com/esp32-i2c-lcd-tutorial/
 *
 * @date 06/2024
 */

#ifndef __SPECIAL_CHARS_HPP__
#define __SPECIAL_CHARS_HPP__

namespace rfidoor::peripheral {

/**
 * @brief Enum containing the possible special chars
 */
enum special_char_t {
  HEART_SPECIAL_CHAR = 0,
  BELL_SPECIAL_CHAR,
  ALIEN_SPECIAL_CHAR,
  CHECK_SPECIAL_CHAR,
  X_SPECIAL_CHAR,
  SOUND_SPECIAL_CHAR,
  SKULL_SPECIAL_CHAR,
  LOCK_SPECIAL_CHAR,
  MAX_SPECIAL_CHAR_NUM
};

extern const char heart_bytemap[8];

extern const char bell_bytemap[8];

extern const char alien_bytemap[8];

extern const char check_bytemap[8];

extern const char x_bytemap[8];

extern const char sound_bytemap[8];

extern const char skull_bytemap[8];

extern const char lock_bytemap[8];

extern const char *special_char_list[8];

} // namespace rfidoor::peripheral

#endif //__SPECIAL_CHARS_HPP__