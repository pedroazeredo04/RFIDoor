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
 * @brief Public variables that correspond to the default values of the abstract Task class 
 */
const char* default_name = "";
const uint32_t default_stack_size = 1000;  // words
const task_priority_t default_priority = LOW_PRIORITY;


Task::Task(const char* name, uint32_t stack_size, UBaseType_t priority) {
    xTaskCreate(
        entry_function_wrapper,  // Task function
        name,                    // Name of the task (for debugging)
        stack_size,              // Stack size (in words)
        this,                    // Task input parameter
        priority,                // Priority of the task
        &this->task_handle       // Task handle
    );
}

void Task::task_sleep_ms(uint32_t time_to_sleep_ms) {
    vTaskDelay(pdMS_TO_TICKS(time_to_sleep_ms));
}

void Task::entry_function_wrapper(void* params) {
    Task* p = static_cast<Task*>(params);

    auto lambda_entry_function = [p]() {
        p->init();

        while (true) {
            p->spin();
        }
    };

    lambda_entry_function();
}

} // rfidoor::task
