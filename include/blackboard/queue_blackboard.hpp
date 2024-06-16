/**
 * @file queue_blackboard.hpp
 *
 * @brief Configuration file of all queues
 *
 * @date 06/2024
 */

#ifndef __QUEUE_BLACKBOARD_HPP__
#define __QUEUE_BLACKBOARD_HPP__

#include "queue/queue.hpp"
#include "task/state_machine_types.hpp"

namespace rfidoor::queue {

/**
 * @brief Queue used to send detected events
 */
extern Queue<rfidoor::task::event_t> event_queue;

/**
 * @brief Queue used to send the current state machine state
 */
extern Queue<rfidoor::task::state_t> state_queue;

} // namespace rfidoor::queue

#endif // __QUEUE_BLACKBOARD_HPP__