/**
 * @file semaphore_blackboard.cpp
 *
 * @brief Define configuration file of all semaphores variables
 *
 * @date 06/2024
 */

#include "blackboard/semaphore_blackboard.hpp"

namespace rfidoor::semaphore::blackboard {

BinarySemaphore display_semaphore;

MutexSemaphore registering_semaphore;

} // namespace rfidoor::semaphore::blackboard