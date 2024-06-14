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

extern const uint32_t default_length;

/**
 * @brief Class for a generic Queue
 *
 * @note Each queue has a specific type attached to it. Thus, they are written,
 * in code, as a template
 */
template <typename T> class Queue {
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
  void publish(T message);

  /**
   * @brief Function to read queue
   */
  T read();

private:
  /**
   * @brief Configuration type for class configuring
   */
  const uint32_t type_size;

  /**
   * @brief Handle for the queue, required by xQueueSend RTOS function
   */
  QueueHandle_t queue_handle;
};

} // namespace rfidoor::queue

#endif // __QUEUE_HPP__