/**
 * @file mutex.cpp
 *
 * @brief Mutex Semaphore class implementation
 *
 * @date 06/2024
 */

#include "semaphore/mutex.hpp"

namespace rfidoor::semaphore {

MutexSemaphore::MutexSemaphore(void) {
  this->semaphore_handle = this->create_semaphore();
}

SemaphoreHandle_t MutexSemaphore::create_semaphore() {
  return xSemaphoreCreateMutex();
}

} // namespace rfidoor::semaphore