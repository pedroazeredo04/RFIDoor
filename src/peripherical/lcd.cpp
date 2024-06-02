/**
 * @file lcd.cpp
 *
 * @brief LCD display class header
 * 
 * @note This class is responsible to automate some configurations of the pre-made LiquidCrystal_I2C lib
 *
 * @date 06/2024
 */


#include <peripherical/lcd.hpp>

namespace rfidoor::peripherical {

/**
 * @brief set the LCD address to 0x27 for a 16 chars and 2 line display 
 */
static const uint8_t lcd_addr{0x27};
static const uint8_t lcd_cols{16};
static const uint8_t lcd_rows{2};

Lcd::Lcd(const uint8_t sda_pin, const uint8_t scl_pin) : sda_pin{sda_pin}, 
                                                         scl_pin{scl_pin}, 
                                                         lib_lcd(lcd_addr, lcd_cols, lcd_rows) { 
    this->lib_lcd.init(this->sda_pin, this->scl_pin);
    this->lib_lcd.clear();
    this->lib_lcd.backlight();

    for (int i = 0; i < MAX_SPECIAL_CHAR_NUM; i++) {
        this->lib_lcd.createChar(i, special_char_list[i]);
    }
}

void Lcd::clear() {
    this->lib_lcd.clear();
}

void Lcd::print(const char* str) {
    this->lib_lcd.print(str);
}

void Lcd::set_cursor(const uint8_t col, const uint8_t row) {
    this->lib_lcd.setCursor(col, row);
}

void Lcd::write_special_char(special_char_t special_char) {
    this->lib_lcd.write(special_char);
}

} // rfidoor::peripherical
