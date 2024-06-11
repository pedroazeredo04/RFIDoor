/**
 * @file lcd.hpp
 *
 * @brief LCD display class header
 *
 * @note This class is responsible to automate some configurations from
 * https://registry.platformio.org/libraries/iakop/LiquidCrystal_I2C_ESP32 lib
 *
 * @date 06/2024
 */

#ifndef __LCD_HPP__
#define __LCD_HPP__

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <peripheral/special_chars.hpp>

namespace rfidoor::peripheral {

extern const uint8_t lcd_addr;
extern const uint8_t lcd_cols;
extern const uint8_t lcd_rows;

typedef struct lcd_position_t {
  uint8_t column;
  uint8_t row;
} lcd_position_t;

/**
 * @brief Class for controlling a Liquid Crystal Display
 */
class Lcd {
public:
  /**
   * @brief Constructor for the Lcd class
   *
   * @param sda_pin SDA pin for i2c communication
   * @param scl_pin SCL pin for i2c communication
   * @param address Address of LCD for i2c communication
   * @param columns Number of column of LCD 
   * @param rows Number of row of LCD 
   */
  explicit Lcd(const uint8_t sda_pin, const uint8_t scl_pin, const uint8_t address = lcd_addr, const uint8_t columns = lcd_cols, const uint8_t rows = lcd_rows);

  /**
   * @brief Initializes LCD
   */
  void init();

  /**
   * @brief Clear LCD screen
   */
  void clear();

  /**
   * @brief Print a string at the current cursor position in the screen
   *
   * @param str String to be printed in screen
   */
  void write(const char *str);

  /**
   * @brief Print a char at the current cursor position in the screen
   *
   * @param character Char to be printed in screen
   */
  void write(char character);

  /**
   * @brief Print a char at the current cursor position in the screen, and
   * increment cursor
   *
   * @param character Char to be printed in screen
   */
  void write_char_with_increment(char character);

  /**
   * @brief Write a special defined by user at the current cursor position in
   * the screen
   *
   * @param special_char Char to be written (needs to be added to special_char_t
   * ENUM)
   */
  void write_special_char(special_char_t special_char);

  /**
   * @brief Increment the position of the cursor
   */
  void cursor_increment_position();

  /**
   * @brief Set the LCD cursos at specified coordinates
   *
   * @param col Column to be setted by cursor
   * @param row Row to be setted by cursor
   */
  void set_cursor(const uint8_t col, const uint8_t row);

private:
  /**
   * @brief SDA pin for i2c communication
   */
  const uint8_t sda_pin;

  /**
   * @brief SCL pin for i2c communication
   */
  const uint8_t scl_pin;

  /**
   * @brief LCD object from prebuilt lib
   */
  LiquidCrystal_I2C lib_lcd;

  /**
   * @brief LCD object from prebuilt lib
   */
  lcd_position_t cursor_position;
};
} // namespace rfidoor::peripheral

#endif // __LCD_HPP__