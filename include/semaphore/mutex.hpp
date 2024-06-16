/**
 * @file mutex.hpp
 * 
 * @brief Mutex Semaphore class header
 * 
 * @date 06/2024
 */

#ifndef __MUTEX_HPP__
#define __MUTEX_HPP__

#include "semaphore/semaphore.hpp"

namespace rfidoor::semaphore {

/**
 * @brief Class for the Mutex Semaphore
 */
class MutexSemaphore : public Semaphore {
public:
    /**
     * @brief Override of the mother class Semaphore create_semaphore function
     * 
     * @return SemaphoreHandle_t Handle for the semaphore
     */
    virtual SemaphoreHandle_t create_semaphore() override;
};
}

#endif // __MUTEX_HPP__