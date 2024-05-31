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

const uint32_t default_stack_size{1000};  // words
const task_priority_t default_priority{MEDIUM_PRIORITY};

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
    Task(const char* name, uint32_t stack_size = default_stack_size, task_priority_t priority = default_priority);

protected:
    /**
     * @brief Loop function to be overrided by inheriting classes
     */
    virtual void loop() = 0;

private:
    /**
     * @brief Wrapper function that calls the loop function
     * 
     * @param pvParameters RTOS required parameters
     */
    static void task_wrapper(void* pvParameters);

    TaskHandle_t task_handle;  // Handle for the task
};


/**
 * @brief RTOS wrapper to task sleep
 *
 * @param time_to_sleep_ms Time to task sleep in miliseconds
 */
void task_sleep_ms(uint32_t time_to_sleep_ms);


}  // rfidoor::task

#endif // __TASK_HPP__
