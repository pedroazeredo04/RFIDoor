/**
 * @file servo.hpp
 *
 * @brief Servo class header
 *
 * @date 06/2024
 */

#ifndef __SERVO_HPP__
#define __SERVO_HPP__

#include <Arduino.h>
#include <ESP32Servo.h> 

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
  explicit ServoController(const uint8_t pin);

  /**
   * @brief Writes a value to the servo, limited from 0 to 1000
   *
   * @param value
   */
  void write(uint16_t value);

private:
  /**
   * @brief Servo pin
   */
  const uint8_t pin;

  /**
   * @brief Servo object
   */
  Servo lib_servo;
};

} // namespace rfidoor::peripheral

#endif // __SERVO_HPP__
