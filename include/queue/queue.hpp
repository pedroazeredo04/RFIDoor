/**
 * @file queue.hpp
 *
 * @brief Generic queue class header
 *
 * @date 06/2024
 */

#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

namespace rfidoor::queue {

/**
 * @brief Public variable that correspond to the default value of the length of
 * a generic queue
 */
const uint32_t default_length{5};

/**
 * @brief Class for a generic Queue
 *
 * @note Each queue has a specific type attached to it. Thus, they are written,
 * in code, as a template
 */
class Queue {
public:
  /**
   * @brief Constructor for the generic Queue class
   *
   * @param length The maximum number of items the queue can hold at any one
   * time
   */
  Queue(const uint32_t length = default_length);

  /**
   * @brief Publish function
   */
  void publish(uint8_t message);

  /**
   * @brief Function to read queue
   */
  uint8_t read(uint8_t* buffer_pointer);

private:
  /**
   * @brief Length of the queue
   */
  const uint32_t length;

  /**
   * @brief Handle for the queue, required by xQueueSend RTOS function
   */
  QueueHandle_t queue_handle;
};

} // namespace rfidoor::queue

#endif // __QUEUE_HPP__
