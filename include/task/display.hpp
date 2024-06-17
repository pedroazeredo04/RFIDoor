/**
 * @file display.hpp
 * 
 * @brief DisplayTask class header
 * 
 * @date 06/2024
 */

#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#include "pinout.hpp"
#include "blackboard/task_blackboard.hpp"

namespace rfidoor::task {

class DisplayTask : public Task {
public:
  /**
   * @brief Constructor for the display Task
   *
   * @param config Configuration type for Task class
   */
  DisplayTask(const task_config_t &config = default_config);

  /**
   * @brief Override of the mother class Task init function
   */
  virtual void init() override;

  /**
   * @brief Override of the mother class Task spin function
   */
  virtual void spin() override;

  /**
   * @brief Function to display a temporary message on the display
   * 
   * @param message Message to be displayed
   */
  static void temporary_display(std::string message);

private:
  /**
   * @brief Function to display the message on the display
   */
  void default_display(rfidoor::task::state_t state);

  const char* current_password{"oi"};
};

}; // namespace rfidoor::task

#endif
