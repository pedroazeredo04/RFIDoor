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
typedef enum task_priority_t {
    LOW_PRIORITY = 1,
    MEDIUM_LOW_PRIORITY,
    MEDIUM_PRIORITY,
    MEDIUM_HIGH_PRIORITY,
    HIGH_PRIORITY,
    REAL_TIME_PRIORITY
} task_priority_t;

/**
 * @brief Public variables that correspond to the default values of the abstract Task class 
 */
extern const char* default_name;
extern const uint32_t default_stack_size;  // words
extern const task_priority_t default_priority;

/**
 * @brief Class for a generic Task
 */
class Task {
public:
    /**
     * @brief Constructor for the generic Task class
     *
     * @param name String that represents the name of the refered task
     * @param stack_size Size of the stack reserved for task in words
     * @param priority The priority of the task that will be runned
     */
    Task(const char* name = default_name, uint32_t stack_size = default_stack_size, task_priority_t priority = default_priority);

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
    static void task_sleep_ms(uint32_t time_to_sleep_ms);

protected:
    /**
     * @brief Wrapper function to be passed to xTaskCreate
     * 
     * @param params RTOS required parameters
     */
    static void entry_function_wrapper(void* params);

    /**
     * @brief Handle for the task, required by xTaskCreate RTOS function
     */
    TaskHandle_t task_handle;
};


}  // rfidoor::task

#endif // __TASK_HPP__
