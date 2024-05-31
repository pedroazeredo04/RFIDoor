/**
 * @file blinky.hpp
 *
 * @brief Blinky class header, that blinks a LED each fixed amount of time
 *
 * @date 06/2024
 */

#ifndef __BLINKY_HPP__
#define __BLINKY_HPP__

#include "task/task.hpp"
#include "peripherical/led.hpp"

namespace rfidoor::task {

/**
 * @brief Class for the blinky Task, that blinks the board LED continuously
 */
class BlinkyTask : public Task {
public:
    /**
     * @brief Constructor for the blinky Task
     *
     * @param led LED object to be blinked
     * @param blinky_frequency_ms Frequency to blink the LED in miliseconds
     */
    BlinkyTask(const char* task_name, rfidoor::peripherical::Led led, uint32_t blinky_frequency_ms);

protected: 
    void loop() override;

private:
    rfidoor::peripherical::Led led;
    const uint32_t blinky_frequency_ms = 1000;
};

}
#endif // __BLINKY_HPP__
