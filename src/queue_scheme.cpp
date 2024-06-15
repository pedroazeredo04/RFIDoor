/**
 * @file queue_scheme.cpp
 *
 * @brief Define configuration file of all queues variables
 *
 * @date 06/2024
 */

#include "queue_scheme.hpp"

namespace rfidoor::queue {

Queue<rfidoor::task::event_t> events_queue;

} // namespace rfidoor::queue