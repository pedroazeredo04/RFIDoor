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
const uint16_t debounce_delay_ms_constant{50};
const uint16_t long_press_delay_ms_constant{1000};
const uint16_t extra_long_press_delay_ms_constant{3000};

/**
 * @brief Default value for the pull resistor
 */
const PullResistor default_pull_resistor{PullResistor::PULL_DOWN};

/**
 * @brief Conversion constant from microseconds to milliseconds
 */
const float microseconds_to_miliseconds{1e-3};

/**
 * @brief Function to get the current time in milliseconds
 */
float get_time_ms() {
  return esp_timer_get_time() * microseconds_to_miliseconds;
}

Button::Button(const uint8_t pin, const PullResistor pull_resistor)
    : pin{pin}, pull_resistor{pull_resistor},
      debounce_delay_ms{debounce_delay_ms_constant},
      long_press_delay_ms{long_press_delay_ms_constant},
      extra_long_press_delay_ms{extra_long_press_delay_ms_constant} {
  pinMode(this->pin, INPUT);
  this->status_timer_start_ms = get_time_ms();
  this->debounce_timer_start_ms = get_time_ms();
  this->pull_resistor = PullResistor::PULL_DOWN;
}

Button::Status Button::get_status() {
  this->previous_state = this->current_state;
  this->current_state = this->get_raw_reading();

  if (this->is_rising_edge(this->current_state, this->previous_state)) {
    this->status_timer_start_ms = get_time_ms();
  } else if (this->is_falling_edge(this->current_state, this->previous_state)) {
    float elapsed = get_time_ms() - this->status_timer_start_ms;

    if (elapsed < this->debounce_delay_ms) {
      return NO_PRESS;
    }

    if (elapsed > this->extra_long_press_delay_ms) {
      return EXTRA_LONG_PRESS;
    }

    if (elapsed > this->long_press_delay_ms) {
      return LONG_PRESS;
    }

    return SHORT_PRESS;
  }

  return NO_PRESS;
}

bool Button::is_pressed() {
  this->previous_read = this->current_read;
  this->current_read = this->get_raw_reading();

  // If the reading has changed, reset the debounce timer
  if (this->current_read != this->previous_read) {
    this->debounce_timer_start_ms = get_time_ms();
  }

  // If the reading is stable for longer than the debounce delay, take it as valid
  if ((get_time_ms() - this->debounce_timer_start_ms) > this->debounce_delay_ms) {
    return this->current_read;
  }

  return false;
}

bool Button::get_raw_reading() const {
  switch (this->pull_resistor) {
  case PullResistor::PULL_UP: {
    return not digitalRead(this->pin);
    break;
  }
  case PullResistor::PULL_DOWN: {
    return digitalRead(this->pin);
    break;
  }
  default: {
    return false;
  }
  }
}

bool Button::is_rising_edge(bool current_state, bool previous_state) const {
  return (current_state and (not previous_state));
}

bool Button::is_falling_edge(bool current_state, bool previous_state) const {
  return ((not current_state) and previous_state);
}
} // namespace rfidoor::peripheral
