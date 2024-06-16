/**
 * @file queue_scheme.cpp
 *
 * @brief Define configuration file of all queues variables
 *
 * @date 06/2024
 */

#include "scheme/queue_scheme.hpp"

namespace rfidoor::queue {

Queue<rfidoor::task::event_t> event_queue;

Queue<rfidoor::task::input_device_state_t> input_device_state_queue(1);

} // namespace rfidoor::queue