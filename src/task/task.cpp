/**
 * @file task.cpp
 *
 * @brief Generic task class implementation
 *
 * @date 06/2024
 */

#include "task/task.hpp"

namespace rfidoor::task {

/**
 * @brief Public variable that correspond to the default values of the abstract
 * Task class
 */
const task_config_t default_config = {
    .name = "", .stack_size = 1000, .priority = LOW_PRIORITY};

Task::Task(const task_config_t &config) : configuration{config} {}

const void Task::create_task() {
  xTaskCreate(this->entry_function_wrapper,   // Task function
              this->configuration.name, // Name of the task (for debugging)
              this->configuration.stack_size, // Stack size (in words)
              this,                           // Task input parameter
              this->configuration.priority,   // Priority of the task
              &this->task_handle              // Task handle
  );
}

const void Task::task_sleep_ms(const uint32_t &time_to_sleep_ms) {
  vTaskDelay(pdMS_TO_TICKS(time_to_sleep_ms));
}

void Task::entry_function_wrapper(void *params) {
  Task *p = static_cast<Task *>(params);

  p->init();

  while (true) {
    p->spin();
  }
}

} // namespace rfidoor::task
