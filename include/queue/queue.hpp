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
const uint32_t default_queue_length{10};

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
  Queue(const uint32_t length = default_queue_length);

  /**
   * @brief Publish function
   *
   * @param message Message to be published
   */
  void publish(T message);

  /**
   * @brief Function to read queue
   *
   * @param buffer Pointer to the buffer where the message will be stored
   *
   * @return true if the message was successfully read, false otherwise
   */
  bool read(T *buffer);

  /**
   * @brief Function to peek at queue
   *
   * @param buffer Pointer to the buffer where the message will be stored
   *
   * @return true if the message was successfully peeked, false otherwise
   */
  bool peek(T *buffer);

private:
  /**
   * @brief Handle for the queue, required by xQueueSend RTOS function
   */
  QueueHandle_t queue_handle;
};

} // namespace rfidoor::queue

#include "queue/queue.tpp"

#endif // __QUEUE_HPP__
