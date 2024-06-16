/**
 * @file queue.cpp
 *
 * @brief Generic queue class implementation
 *
 * @date 06/2024
 */

#include "queue/queue.hpp"

namespace rfidoor::queue {

/**
 * @brief Public variable that correspond to the default value of the wait ticks
 * to be passed to the send and receive RTOS functions
 */
const uint16_t ticks_to_wait{10};

template <typename T> Queue<T>::Queue(const uint32_t length) {
  this->queue_handle = xQueueCreate(length, sizeof(T));
}

template <typename T> void Queue<T>::publish(T message) {
  xQueueSend(this->queue_handle, &message, ticks_to_wait);
}

template <typename T> bool Queue<T>::read(T* buffer) {
  return (xQueueReceive(this->queue_handle, buffer, ticks_to_wait) == pdPASS);
}

template <typename T> bool Queue<T>::peek(T* buffer) {
  return (xQueuePeek(this->queue_handle, buffer, ticks_to_wait) == pdPASS);
}

} // namespace rfidoor::queue
