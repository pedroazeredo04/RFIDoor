/**
 * @file special_chars.hpp
 *
 * @brief Some special chars to be included in LCD implementation
 *
 * @note Taken from: https://lastminuteengineers.com/esp32-i2c-lcd-tutorial/
 *
 * @date 06/2024
 */

#include <peripheral/special_chars.hpp>

namespace rfidoor::peripheral {

const char heart_bytemap[8] = {0b00000, 0b01010, 0b11111, 0b11111,
                               0b01110, 0b00100, 0b00000, 0b00000};

const char bell_bytemap[8] = {0b00100, 0b01110, 0b01110, 0b01110,
                              0b11111, 0b00000, 0b00100, 0b00000};

const char alien_bytemap[8] = {0b11111, 0b10101, 0b11111, 0b11111,
                               0b01110, 0b01010, 0b11011, 0b00000};

const char check_bytemap[8] = {0b00000, 0b00001, 0b00011, 0b10110,
                               0b11100, 0b01000, 0b00000, 0b00000};

const char x_bytemap[8] = {0b10001, 0b11011, 0b01110, 0b00100,
                           0b01110, 0b11011, 0b10001, 0b00000};

const char sound_bytemap[8] = {0b00001, 0b00011, 0b00101, 0b01001,
                               0b01001, 0b01011, 0b11011, 0b11000};

const char skull_bytemap[8] = {0b00000, 0b01110, 0b10101, 0b11011,
                               0b01110, 0b01110, 0b00000, 0b00000};

const char lock_bytemap[8] = {0b01110, 0b10001, 0b10001, 0b11111,
                              0b11011, 0b11011, 0b11111, 0b00000};

const char *special_char_list[8] = {heart_bytemap, bell_bytemap, alien_bytemap,
                                    check_bytemap, x_bytemap,    sound_bytemap,
                                    skull_bytemap, lock_bytemap};

} // namespace rfidoor::peripheral
