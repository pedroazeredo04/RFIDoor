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

Semaphore::Semaphore(void) {
  this->semaphore_handle = this->create_semaphore();
}

const void Semaphore::give() { xSemaphoreGive(this->semaphore_handle); }

const void Semaphore::take() {
  xSemaphoreTake(this->semaphore_handle, semaphore_delay);
}

} // namespace rfidoor::semaphore