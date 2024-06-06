/**
 * @file task.hpp
 *
 * @brief Generic task class header
 *
 * @date 06/2024
 */

#ifndef __TASK_HPP__
#define __TASK_HPP__

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

namespace rfidoor::task {

/**
 * @brief Enum corresponding to the possible task priorities
 */
enum task_priority_t {
  LOW_PRIORITY = 1,
  MEDIUM_LOW_PRIORITY,
  MEDIUM_PRIORITY,
  MEDIUM_HIGH_PRIORITY,
  HIGH_PRIORITY,
  REAL_TIME_PRIORITY
};

/**
 * @brief Struct to be passed to Task constructor
 */
typedef struct task_config_t {
  const char *name;
  uint32_t stack_size;
  task_priority_t priority;
} task_config_t;

/**
 * @brief Public variable that correspond to the default values of the abstract
 * Task class
 */
extern const task_config_t default_config;

/**
 * @brief Class for a generic Task
 */
class Task {
public:
  /**
   * @brief Constructor for the generic Task class
   *
   * @param task_config_t Configuration of the task
   */
  Task(const task_config_t &config = default_config);

  /**
   * @brief Function that calls xTaskCreate from FreeRTOS
   */
  const void create_task();

  /**
   * @brief Init function to be overrided by inheriting classes
   */
  virtual void init() = 0;

  /**
   * @brief Spin function to be overrided by inheriting classes
   */
  virtual void spin() = 0;

  /**
   * @brief RTOS wrapper to task sleep
   *
   * @param time_to_sleep_ms Time to task sleep in miliseconds
   */
  static const void task_sleep_ms(const uint32_t &time_to_sleep_ms);

protected:
  /**
   * @brief Wrapper function to be passed to xTaskCreate
   *
   * @param params RTOS required parameters
   */
  static void entry_function_wrapper(void *params);

private:
  /**
   * @brief Configuration type for class configuring
   */
  const task_config_t configuration;

  /**
   * @brief Handle for the task, required by xTaskCreate RTOS function
   */
  TaskHandle_t task_handle;
};

} // namespace rfidoor::task

#endif // __TASK_HPP__
