/**
 * @file button.cpp
 *
 * @brief Button class source
 *
 * @date 06/2024
 */

#include "peripheral/button.hpp"
#include <Arduino.h>
#include <esp_timer.h>

namespace rfidoor::peripheral {

/**
 * @brief Public variables related to the debouncing and button press time
 */
const int8_t debounce_delay_ms{20};
const long long_press_delay_ms{999999999};
const long extra_long_press_delay_ms{999999999};

/**
 * @brief Conversion constant from microseconds to milliseconds
 */
const float microseconds_to_miliseconds{10e-3};

/**
 * @brief Function to get the current time in milliseconds
 */
float get_time_ms() {
    return esp_timer_get_time() * microseconds_to_miliseconds;
}

Button::Button(const uint8_t pin) : pin{pin}, debounce_delay_ms{debounce_delay_ms}, long_press_delay_ms{long_press_delay_ms}, extra_long_press_delay_ms{extra_long_press_delay_ms} {
    pinMode(this->pin, INPUT);
    this->status_timer_start_ms = get_time_ms();
    this->debounce_timer_start_ms = get_time_ms();
}

bool Button::is_pressed() {
    return this->update_state();
}

Button::Status Button::get_status() {
    this->previous_state = this->current_state;
    this->current_state = this->get_raw_reading();

    if (this->is_rising_edge()) {
        this->status_timer_start_ms = get_time_ms();
    } else if (this->is_falling_edge()) {
        float elapsed = get_time_ms() - this->status_timer_start_ms;
        Serial.println(elapsed);

        if (elapsed > extra_long_press_delay_ms) {
            return EXTRA_LONG_PRESS;
        }

        if (elapsed > long_press_delay_ms) {
            return LONG_PRESS;
        }

        return SHORT_PRESS;
    }

    return NO_PRESS;
}

bool Button::get_raw_reading() const {
    return digitalRead(this->pin);
}

bool Button::update_state() {
    bool raw_reading = this->get_raw_reading();

    if ((raw_reading != this->current_state) and not this->is_debouncing) {
        this->is_debouncing = true;
        this->debounce_timer_start_ms = get_time_ms();
    } else if ((get_time_ms() - this->debounce_timer_start_ms < debounce_delay_ms) and this->is_debouncing) {
        if (this->current_state == raw_reading) {
            this->is_debouncing = false;
        }
    } else {
        return raw_reading;
    }

    return this->current_state;
}

bool Button::is_rising_edge() const {
    return (this->current_state and (not this->previous_state));
}

bool Button::is_falling_edge() const {
    return ((not this->current_state) and this->previous_state);
}
}  // namespace rfidoor::peripheral
