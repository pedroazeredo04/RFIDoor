/**
 * @file button.hpp
 *
 * @brief Button class header, that reads the button value
 *
 * @date 06/2024
 */

#ifndef _BUTTON_TASK_HPP_
#define _BUTTON_TASK_HPP_

#include "peripheral/button.hpp"
#include "task/task.hpp"

namespace rfidoor::task {

/**
 * @brief Class for the Button Task, that reads the button value
 */
class ButtonTask : public Task {
public:
  /**
   * @brief Constructor for the button Task
   *
   * @param button Button object to be monitored
   * @param config Configuration type for Task class
   */
  ButtonTask(const rfidoor::peripheral::Button &button,
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
   * @brief Button object to be monitored
   */
  rfidoor::peripheral::Button button;

  /**
   * @brief Current button status
   */
  rfidoor::peripheral::Button::Status button_status;
};

} // namespace rfidoor::task
#endif // _BUTTON_TASK_HPP_