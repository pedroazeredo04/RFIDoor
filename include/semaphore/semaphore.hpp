/**
 * @file semaphore.hpp
 *
 * @brief Generic semaphore class header
 *
 * @date 06/2024
 */

#ifndef __SEMAPHORE_HPP__
#define __SEMAPHORE_HPP__

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

namespace rfidoor::semaphore {

class Semaphore {
public:
  /**
   * @brief Constructor for the generic Semaphore class
   */
  Semaphore(void);

  /**
   * @brief Create semaphore function to be overriden by the derived class
   *
   * @return SemaphoreHandle_t Handle for the semaphore
   */
  virtual SemaphoreHandle_t create_semaphore() { return NULL; };

  /**
   * @brief Function that calls xSemaphoreGive from FreeRTOS
   */
  const void give();

  /**
   * @brief Function that calls xSemaphoreTake from FreeRTOS
   */
  const void take();

protected:
  /**
   * @brief Handle for the semaphore, required by xSemaphoreCreateBinary RTOS
   * function
   */
  SemaphoreHandle_t semaphore_handle;
};

} // namespace rfidoor::semaphore

#endif // __SEMAPHORE_HPP__