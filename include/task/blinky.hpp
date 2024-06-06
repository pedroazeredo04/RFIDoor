/**
 * @file blinky.hpp
 *
 * @brief Blinky class header, that blinks a LED each fixed amount of time
 *
 * @date 06/2024
 */

#ifndef __BLINKY_HPP__
#define __BLINKY_HPP__

#include "peripheral/led.hpp"
#include "task/task.hpp"

namespace rfidoor::task {

/**
 * @brief Class for the blinky Task, that blinks the board LED continuously
 */
class BlinkyTask : public Task {
public:
  /**
   * @brief Constructor for the blinky Task
   *
   * @param led LED object to be blinked
   * @param blinky_frequency_ms Frequency to blink the LED in miliseconds
   */
  BlinkyTask(const rfidoor::peripheral::Led &led, uint32_t blinky_frequency_ms,
             const task_config_t &config = default_config);

  /**
   * @brief Override of the mother class Task init function
   */
  virtual void init() override;

  /**
   * @brief Override of the mother class Task spin function
   */
  virtual void spin() override;

private:
  /**
   * @brief LED peripheral to be blinked
   */
  rfidoor::peripheral::Led led;

  /**
   * @brief Time in miliseconds to blink LED
   */
  const uint32_t blinky_frequency_ms;
};

} // namespace rfidoor::task
#endif // __BLINKY_HPP__
