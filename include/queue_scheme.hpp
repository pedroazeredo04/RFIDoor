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

rfidoor::queue::Queue<int> intQueue(5);

#endif // __QUEUE_SCHEME_HPP__