/**
 * @file button.hpp
 *
 * @brief Button class header
 *
 * @date 06/2024
 */

#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include <cstdint>

namespace rfidoor::peripheral {
/**
 * @brief Class for acquiring a button data
 */
class Button {
public:
    /**
     * @brief Enum for button status
     */
    enum Status : uint8_t {
        NO_PRESS,
        SHORT_PRESS,
        LONG_PRESS,
        EXTRA_LONG_PRESS
    };

    /**
     * @brief Enum for button pull resistor
     */
    enum PullResistor : uint8_t {
        PULL_UP,
        PULL_DOWN,
    };

    /**
     * @brief Constructor for Button class
     *
     * @param config Button configuration
     */
    explicit Button(const uint8_t pin);

    /**
     * @brief Check if button is pressed
     *
     * @return bool True if button is pressed, false otherwise
     */
    bool is_pressed();

    /**
     * @brief Get button status
     *
     * @return Status Button status
     */
    Status get_status();

private:
    /**
     * @brief Get raw button reading
     *
     * @return bool Button reading without debounce
     */
    bool get_raw_reading() const;

    /**
     * @brief Update button state
     *
     * @return Current state of the button
     */
    bool update_state();

    /**
     * @brief Check if button was just pressed
     *
     * @return True if button was just pressed, false otherwise
     */
    bool is_rising_edge() const;

    /**
     * @brief Check if button was just released
     *
     * @return True if button was just released, false otherwise
     */
    bool is_falling_edge() const;

    /**
     * @brief Button pressing delays in ms
     */
    const uint16_t debounce_delay;
    const uint16_t long_press_delay;
    const uint16_t extra_long_press_delay;


    /**
     * @brief Pull resistor configuration
     */
    PullResistor pull_resistor;

    /**
     * @brief Timer to check if button is debouncing
     */
    hal::Timer debounce_timer;

    /**
     * @brief Timer to determine type of button press
     */
    hal::Timer status_timer;

    /**
     * @brief Flag to know when button is debouncing
     */
    bool is_debouncing{false};

    /**
     * @brief Flag to know if button was being pressed
     */
    bool previous_state{false};

    /**
     * @brief Flag to know if button is being pressed
     */
    bool current_state{false};
};
}  // namespace micras::proxy

#endif  // __BUTTON_HPP__