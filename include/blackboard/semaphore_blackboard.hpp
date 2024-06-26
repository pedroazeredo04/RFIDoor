/**
 * @file semaphore_blackboard.hpp
 *
 * @brief Configuration file of all semaphores
 *
 * @date 06/2024
 */

#ifndef __SEMAPHORE_BLACKBOARD_HPP__
#define __SEMAPHORE_BLACKBOARD_HPP__

#include "semaphore/binary.hpp"
#include "semaphore/mutex.hpp"
#include "semaphore/semaphore.hpp"

namespace rfidoor::semaphore::blackboard {

/**
 * @brief Binary semaphore for the display
 */
extern BinarySemaphore display_semaphore;

/**
 * @brief Mutex semaphore for the registering state
 */
extern MutexSemaphore registering_semaphore;

}; // namespace rfidoor::semaphore::blackboard

#endif // __SEMAPHORE_BLACKBOARD_HPP__