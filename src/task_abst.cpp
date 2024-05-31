// #include "task_abst.hpp"

// Task::Task(const char* name, uint32_t stackSize, UBaseType_t priority) {
//     xTaskCreate(
//         Task::taskFunction,  // Task function
//         name,                // Name of the task (for debugging)
//         stackSize,           // Stack size (in words)
//         this,                // Task input parameter
//         priority,            // Priority of the task
//         &taskHandle          // Task handle
//     );
// }

// void Task::taskFunction(void* pvParameters) {
//     // Cast the parameter to a Task object
//     Task* task = static_cast<Task*>(pvParameters);
//     // Call the loop method
//     task->loop();
// }
