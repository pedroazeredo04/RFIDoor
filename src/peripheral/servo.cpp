/**
 * @file servo.cpp
 *
 * @brief Servo class implementation
 *
 * @date 06/2024
 */

#include <peripheral/servo.hpp>

namespace rfidoor::peripheral {

const uint16_t max_angle{2400};
const uint16_t min_angle{500};

const uint16_t max_command{180};
const uint16_t min_command{0};

const uint8_t servo_frequency{50};  // Standard 50hz servo

ServoController::ServoController(const uint8_t pin) : pin(pin) {
  this->lib_servo.setPeriodHertz(servo_frequency);
  this->lib_servo.attach(pin, min_angle, max_angle);
}

void ServoController::write(uint16_t value) {
  value = value > max_command ? max_command : value < min_command ? min_command : value;

  //value = map(value, min_command, max_command, min_angle, max_angle);

  this->lib_servo.write(value);
}

} // namespace rfidoor::peripheral
