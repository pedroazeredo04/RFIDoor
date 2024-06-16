/**
 * @file queue_scheme.hpp
 *
 * @brief Configuration file of all queues
 *
 * @date 06/2024
 */

#ifndef __QUEUE_SCHEME_HPP__
#define __QUEUE_SCHEME_HPP__

#include "queue/queue.hpp"
#include "task/state_machine_types.hpp"

namespace rfidoor::queue {

/**
 * @brief Queue used to send detected events
 */
extern Queue<rfidoor::task::event_t> event_queue;

extern Queue<rfidoor::task::input_device_state_t> input_device_state_queue;

} // namespace rfidoor::queue

#endif // __QUEUE_SCHEME_HPP__