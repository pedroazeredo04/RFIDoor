#include "blinky.hpp"
#include <Arduino.h>

BlinkTask::BlinkTask() : Task("BlinkTask", 1000, 1) {
    pinMode(led_pin, OUTPUT);
}

void BlinkTask::loop() {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(pdMS_TO_TICKS(blinky_frequency_ms));
    digitalWrite(led_pin, LOW);
    vTaskDelay(pdMS_TO_TICKS(blinky_frequency_ms));
}
