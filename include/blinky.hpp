#ifndef __BLINK_TASK_HPP__
#define __BLINK_TASK_HPP__

#include "task_abst.hpp"

class BlinkTask : public Task {
public:
    BlinkTask();

    void loop() override;

private:
    const uint8_t led_pin = 2;
    const uint32_t blinky_frequency_ms = 1000;
};

#endif // __BLINK_TASK_HPP__
