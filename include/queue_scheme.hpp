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

namespace rfidoor::queue {

/**
 * @brief Instanciate the events queue
 */
Queue events_queue(default_length);

} // namespace rfidoor::queue

#endif // __QUEUE_SCHEME_HPP__