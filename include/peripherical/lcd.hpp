/**
 * @file lcd.hpp
 *
 * @brief LCD display class header
 * 
 * @note This class is responsible to automate some configurations of the pre-made LiquidCrystal_I2C lib
 *
 * @date 06/2024
 */

#ifndef __LCD_HPP__
#define __LCD_HPP__

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

namespace rfidoor::peripherical {
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
     */
    explicit Lcd(const uint8_t sda_pin, const uint8_t scl_pin);

    /**
     * @brief Clear LCD screen
     */
    void clear();

    /**
     * @brief Print a string at the current cursor position in the screen
     * 
     * @param str String to be printed in screen
     */
    void print(const char* str);

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

};
}  // rfidoor::peripherical

#endif  // __LCD_HPP__