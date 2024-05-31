/**
 * @file task.cpp
 *
 * @brief Generic task class implementation 
 *
 * @date 06/2024
 */

#include "task/task.hpp"

namespace rfidoor::task {

Task::Task(const char* name, uint32_t stack_size, task_priority_t priority) {
    xTaskCreate(
        this->task_wrapper,   // Task function
        name,                 // Name of the task (for debugging)
        stack_size,           // Stack size (in words)
        this,                 // Task input parameter
        priority,             // Priority of the task
        &(this->task_handle)  // Task handle
    );
}

void Task::task_wrapper(void* pvParameters) {
    Task* task = static_cast<Task*>(pvParameters);
    while (true) {
        task->loop();
    }
}

void task_sleep_ms(uint32_t time_to_sleep_ms) {
    vTaskDelay(pdMS_TO_TICKS(time_to_sleep_ms));
}

} // rfidoor::task