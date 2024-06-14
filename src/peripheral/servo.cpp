/**
 * @file servo.cpp
 *
 * @brief Servo class implementation
 *
 * @date 06/2024
 */

#include <peripheral/servo.hpp>

namespace rfidoor::peripheral {

const uint16_t max_command{180};
const uint16_t min_command{0};

ServoController::ServoController(const uint8_t pin) : pin(pin) {}

void ServoController::write_angular_position_degrees(uint8_t command) {
  command = command > max_command   ? max_command
            : command < min_command ? min_command
                                    : command;

  this->lib_servo.write(this->pin, command);
}

} // namespace rfidoor::peripheral
