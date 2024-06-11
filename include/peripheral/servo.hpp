/**
 * @file servo.hpp
 *
 * @brief Servo class header
 *
 * @date 06/2024
 */

#ifndef _SERVO_HPP_
#define _SERVO_HPP_

#include <Arduino.h>
#include <Servo.h> // Include the Servo library

namespace rfidoor::peripheral {

/**
 * @brief Class for controlling a servo
 */
class ServoController {
public:
  /**
   * @brief Constructor for the Servo class
   *
   * @param pin
   */
  explicit ServoController(uint8_t pin);

  /**
   * @brief Writes a value to the servo
   *
   * @param value
   */
  void write(uint8_t value);

private:
  /**
   * @brief Servo pin
   */
  const uint8_t pin;

  /**
   * @brief Servo object
   */
  Servo servo;
};

} // namespace rfidoor::peripheral

#endif // _SERVO_HPP_