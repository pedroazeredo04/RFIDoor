/**
 * @file queue_blackboard.cpp
 *
 * @brief Define configuration file of all queues variables
 *
 * @date 06/2024
 */

#include "blackboard/queue_blackboard.hpp"

namespace rfidoor::queue::blackboard {

Queue<rfidoor::task::event_t> event_queue;

Queue<char> password_queue;

} // namespace rfidoor::queue::blackboard