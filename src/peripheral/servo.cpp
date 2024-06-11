/**
 * @file servo.cpp
 *
 * @brief Servo class implementation
 *
 * @date 06/2024
 */

#include <peripheral/servo.hpp>

namespace rfidoor::peripheral {

ServoController::ServoController(uint8_t pin) : pin(pin) {
  servo.attach(pin);
}

void ServoController::write(uint8_t value) {
  servo.write(value);
}

} // namespace rfidoor::peripheral