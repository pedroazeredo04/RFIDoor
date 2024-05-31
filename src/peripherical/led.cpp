/**
 * @file led.cpp
 *
 * @brief Led class implementation
 *
 * @date 06/2024
 */

#include <peripherical/led.hpp>

namespace rfidoor::peripherical {

Led::Led(const uint8_t pin) : pin{pin} {
    pinMode(this->pin, OUTPUT);
 }

void Led::turn_on() {
    this->value = HIGH;
    digitalWrite(this->pin, this->value);
}

void Led::turn_off() {
    this->value = LOW;
    digitalWrite(this->pin, this->value);
}

void Led::toggle() {
    this->value = !(this->value);
    digitalWrite(this->pin, this->value);
}

}