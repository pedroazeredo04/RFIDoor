/**
 * @file binary.cpp
 * 
 * @brief Binary Semaphore class implementation
 * 
 * @date 06/2024
 */

#include "semaphore/binary.hpp"

namespace rfidoor::semaphore {

BinarySemaphore::BinarySemaphore(void) {
    this->semaphore_handle = this->create_semaphore();
}

SemaphoreHandle_t BinarySemaphore::create_semaphore() {
    return xSemaphoreCreateBinary();
}

} // namespace rfidoor::semaphore