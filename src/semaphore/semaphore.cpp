/**
 * @file semaphore.cpp
 *
 * @brief Generic semaphore class implementation
 *
 * @date 06/2024
 */

#include "semaphore/semaphore.hpp"

namespace rfidoor::semaphore {

const uint32_t semaphore_delay{portMAX_DELAY};

Semaphore::Semaphore(void) {}

const void Semaphore::give() { xSemaphoreGive(this->semaphore_handle); }

const void Semaphore::take() {
  if (this->semaphore_handle != NULL) {
    xSemaphoreTake(this->semaphore_handle, semaphore_delay);
    return;
  }
}

} // namespace rfidoor::semaphore