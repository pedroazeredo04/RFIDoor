/**
 * @file button.cpp
 *
 * @brief Button class source
 *
 * @date 06/2024
 */

#include "peripheral/button.hpp"
#include <Arduino.h>

namespace rfidoor::peripheral {

/**
 * @brief Public variables related to the debouncing and button press time
 */
const uint8_t debounce_delay{20};
const uint32_t long_press_delay{1000};
const uint32_t extra_long_press_delay{5000};

Button::Button(const uint8_t pin) : pin{pin}, debounce_delay{debounce_delay}, long_press_delay{long_press_delay}, extra_long_press_delay{extra_long_press_delay} {
    pinMode(this->pin, INPUT);
}

bool Button::is_pressed() {
    return this->update_state();
}

Button::Status Button::get_status() {
    this->previous_state = this->current_state;
    this->current_state = this->update_state();

    if (this->is_rising_edge()) {
        this->status_timer.reset_ms();
    } else if (this->is_falling_edge()) {
        if (this->status_timer.elapsed_time_ms() > extra_long_press_delay) {
            return EXTRA_LONG_PRESS;
        }

        if (this->status_timer.elapsed_time_ms() > long_press_delay) {
            return LONG_PRESS;
        }

        return SHORT_PRESS;
    }

    return NO_PRESS;
}

bool Button::get_raw_reading() const {
    return this->gpio.read() == static_cast<bool>(this->pull_resistor);
}

bool Button::update_state() {
    bool raw_reading = this->get_raw_reading();

    if ((raw_reading != this->current_state) and not this->is_debouncing) {
        this->is_debouncing = true;
        this->debounce_timer.reset_ms();
    } else if ((this->debounce_timer.elapsed_time_ms() < debounce_delay) and this->is_debouncing) {
        if (this->current_state == raw_reading) {
            this->is_debouncing = false;
        }
    } else {
        return raw_reading;
    }

    return this->current_state;
}

bool Button::is_rising_edge() const {
    return this->current_state and not this->previous_state;
}

bool Button::is_falling_edge() const {
    return not this->current_state and this->previous_state;
}
}  // namespace micras::proxy