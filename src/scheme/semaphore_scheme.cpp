/**
 * @file semaphore_scheme.cpp
 *
 * @brief Define configuration file of all semaphores variables
 *
 * @date 06/2024
 */

#include "scheme/semaphore_scheme.hpp"

namespace rfidoor::semaphore {

BinarySemaphore binary_semaphore_example;

MutexSemaphore registering_semaphore;

} // namespace rfidoor::semaphore