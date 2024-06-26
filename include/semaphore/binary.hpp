/**
 * @file binary.hpp
 *
 * @brief Binary Semaphore class header
 *
 * @date 06/2024
 */

#ifndef __BINARY_HPP__
#define __BINARY_HPP__

#include "semaphore/semaphore.hpp"

namespace rfidoor::semaphore {

/**
 * @brief Class for the Binary Semaphore
 */
class BinarySemaphore : public Semaphore {
public:
  /**
   * @brief Constructor for the BinarySemaphore class
   */
  explicit BinarySemaphore(void);

  /**
   * @brief Override of the mother class Semaphore create_semaphore function
   *
   * @return SemaphoreHandle_t Handle for the semaphore
   */
  virtual SemaphoreHandle_t create_semaphore() override;
};
} // namespace rfidoor::semaphore

#endif // __BINARY_HPP__