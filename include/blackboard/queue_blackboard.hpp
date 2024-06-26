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
#include "task/password.hpp"

namespace rfidoor::queue::blackboard {

/**
 * @brief Queue used to send detected events
 */
extern Queue<rfidoor::task::event_t> event_queue;

/**
 * @brief Queue used to send the current password
 */
extern Queue<char> password_queue;

} // namespace rfidoor::queue::blackboard

#endif // __QUEUE_BLACKBOARD_HPP__