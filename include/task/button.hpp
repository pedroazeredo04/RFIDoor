/**
 * @file button.hpp
 *
 * @brief Button class header, that reads the button value
 *
 * @date 06/2024
 */

#ifndef __BUTTON_TASK_HPP__
#define __BUTTON_TASK_HPP__

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
   * @param inside_button Button object to be monitored from the inside
   * @param door_button Button object to be monitored from the door
   * @param config Configuration type for Task class
   */
  ButtonTask(const rfidoor::peripheral::Button &inside_button,
             const rfidoor::peripheral::Button &door_button,
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
   * @brief Button object to be monitored for the inside
   */
  rfidoor::peripheral::Button inside_button;

  /**
   * @brief Button object to be monitored for the door
   */
  rfidoor::peripheral::Button door_button;

  /**
   * @brief Current button status
   */
  rfidoor::peripheral::Button::Status inside_button_status;

  /**
   * @brief Current button status
   */
  rfidoor::peripheral::Button::Status door_button_status;
};

} // namespace rfidoor::task
#endif // __BUTTON_TASK_HPP__