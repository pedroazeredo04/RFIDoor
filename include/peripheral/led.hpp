/**
 * @file led.hpp
 *
 * @brief Led class header
 *
 * @date 06/2024
 */

#ifndef __LED_HPP__
#define __LED_HPP__

#include <Arduino.h>

namespace rfidoor::peripheral {
/**
 * @brief Class for controlling an LED
 */
class Led {
public:
    /**
     * @brief Constructor for the Led class
     *
     * @param pin Pin of the referred LED
     */
    explicit Led(const uint8_t pin);

    /**
     * @brief Turn the LED on
     */
    void turn_on();

    /**
     * @brief Turn the LED off
     */
    void turn_off();

    /**
     * @brief Toggle the LED
     */
    void toggle();

private:
    /**
     * @brief Gpio pin for the LED
     */
    const uint8_t pin;

    /**
     * @brief Current LED output value (HIGH or LOW) 
     */
    bool value = LOW;
};
}  // rfidoor::peripheral

#endif  // __LED_HPP__