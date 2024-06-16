/**
 * @file semaphore_scheme.hpp
 *
 * @brief Configuration file of all semaphores
 *
 * @date 06/2024
 */

#ifndef __SEMAPHORE_SCHEME_HPP__
#define __SEMAPHORE_SCHEME_HPP__

#include "semaphore/binary.hpp"
#include "semaphore/semaphore.hpp"

namespace rfidoor::semaphore {

/**
 * @brief Binary semaphore example
 */
extern BinarySemaphore binary_semaphore_example;

}; // namespace rfidoor::semaphore

#endif // __SEMAPHORE_SCHEME_HPP__