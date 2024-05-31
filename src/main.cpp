#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define INTERNAL_LED 2
#define BLINK_FREQUENCY_MS 1000

void blinkyTask(void *pvParameters) {
  pinMode(INTERNAL_LED, OUTPUT);

  while (1) {
    digitalWrite(INTERNAL_LED, HIGH);
    vTaskDelay(pdMS_TO_TICKS(BLINK_FREQUENCY_MS));
    digitalWrite(INTERNAL_LED, LOW);
    vTaskDelay(pdMS_TO_TICKS(BLINK_FREQUENCY_MS));
  }
}

void setup() {
  xTaskCreate(
    blinkyTask,           // Task function
    "blinkyTask",         // Name of the task (for debugging)
    1000,               // Stack size (in words)
    NULL,               // Task input parameter
    1,                  // Priority of the task
    NULL                // Task handle
  );

  // No need to start the scheduler explicitly as it's already running in the ESP32 Arduino core
}

void loop() {
  // Empty loop since we are using FreeRTOS tasks
}
