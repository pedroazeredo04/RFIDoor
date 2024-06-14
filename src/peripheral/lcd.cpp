/**
 * @file lcd.cpp
 *
 * @brief LCD display class header
 *
 * @note This class is responsible to automate some configurations of the
 * pre-made LiquidCrystal_I2C lib
 *
 * @date 06/2024
 */

#include <peripheral/lcd.hpp>

namespace rfidoor::peripheral {

/**
 * @brief set the LCD address to 0x27 for a 16 chars and 2 line display
 */
const uint8_t lcd_addr{0x27};
const uint8_t lcd_cols{16};
const uint8_t lcd_rows{2};

Lcd::Lcd(const uint8_t sda_pin, const uint8_t scl_pin, const uint8_t address,
         const uint8_t columns, const uint8_t rows)
    : lib_lcd(address, columns, rows), sda_pin{sda_pin}, scl_pin{scl_pin},
      cursor_position{0, 0} {}

void Lcd::init() {
  this->lib_lcd.init(this->sda_pin, this->scl_pin);
  this->lib_lcd.clear();
  this->lib_lcd.backlight();
  this->set_cursor(0, 0);

  for (int i = 0; i < MAX_SPECIAL_CHAR_NUM; i++) {
    this->lib_lcd.createChar(i, special_char_list[i]);
  }
}

void Lcd::clear() { this->lib_lcd.clear(); }

void Lcd::write(const char *str) { this->lib_lcd.print(str); }

void Lcd::write(char character) { this->lib_lcd.print(character); }

void Lcd::write_char_with_increment(char character) {
  this->cursor_increment_position();
  this->lib_lcd.print(character);
}

void Lcd::write_special_char(special_char_t special_char) {
  this->lib_lcd.write(special_char);
}

void Lcd::cursor_increment_position() {
  this->cursor_position.column++;

  if (this->cursor_position.column >= lcd_cols) {
    this->cursor_position.column = 0;
    this->cursor_position.row++;
  }

  if (this->cursor_position.row >= lcd_rows) {
    this->cursor_position.row = 0;
  }

  this->set_cursor(this->cursor_position.column, this->cursor_position.row);
}

void Lcd::set_cursor(const uint8_t col, const uint8_t row) {
  this->lib_lcd.setCursor(
      col - 1, row); // -1 because lib_lcd count starts at -1 for some reason
  this->cursor_position = {col, row};
}

} // namespace rfidoor::peripheral
