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
    BlinkyTask(const rfidoor::peripherical::Led& led,
               uint32_t blinky_frequency_ms, 
               const char* name = default_name,
               uint32_t stack_size = default_stack_size,
               UBaseType_t priority = default_priority);

    /**
     * @brief Override of the mother class Task init function  
     */
    virtual void init() override;

    /**
     * @brief Override of the mother class Task spin function  
     */
    virtual void spin() override;

private:
    /**
     * @brief LED peripherical to be blinked  
     */
    rfidoor::peripherical::Led led;

    /**
     * @brief Time in miliseconds to blink LED  
     */
    const uint32_t blinky_frequency_ms;
};

}
#endif // __BLINKY_HPP__
