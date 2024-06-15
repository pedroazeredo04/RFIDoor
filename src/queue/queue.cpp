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

Queue::Queue(const uint32_t length) : length{length} {
  this->queue_handle = xQueueCreate(this->length, sizeof(uint8_t));
}

void Queue::publish(uint8_t message) {
  xQueueSend(this->queue_handle, &message, ticks_to_wait);
}

uint8_t Queue::read() {
  uint8_t buffer;
  xQueueReceive(this->queue_handle, &buffer, ticks_to_wait);
  return buffer;
}

} // namespace rfidoor::queue
