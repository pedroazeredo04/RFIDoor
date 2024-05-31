#ifndef __TASK_ABST_HPP__
#define __TASK_ABST_HPP__

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

class Task {
public:
    // Constructor
    Task(const char* name, uint32_t stackSize, UBaseType_t priority);

    // Pure virtual function for task loop
    virtual void loop() = 0;

    // Static wrapper for the task function
    static void taskFunction(void* pvParameters);

private:
    TaskHandle_t taskHandle;  // Handle for the task
};

#endif // __TASK_ABST_HPP__
