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

private:
  /**
   * @brief Function to display the message on the display
   */
  void default_display(rfidoor::task::state_t state);
};

}; // namespace rfidoor::task

#endif
