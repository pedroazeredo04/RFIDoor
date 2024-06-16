/**
 * @file queue_blackboard.cpp
 *
 * @brief Define configuration file of all queues variables
 *
 * @date 06/2024
 */

#include "blackboard/queue_blackboard.hpp"

namespace rfidoor::queue {

Queue<rfidoor::task::event_t> event_queue;

Queue<rfidoor::task::state_t> state_queue(1);

} // namespace rfidoor::queue