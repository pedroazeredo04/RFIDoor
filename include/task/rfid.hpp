/**
 * @file rfid.hpp
 *
 * @brief RFID class header, that reads and validates a RFID card
 *
 * @date 06/2024
 */

#ifndef __RFID_HPP__
#define __RFID_HPP__

#include "peripheral/nfc.hpp"
#include "task/state_machine_types.hpp"
#include "task/task.hpp"
#include <vector>
#include <Adafruit_PN532.h>

namespace rfidoor::task {

/**
 * @brief Class for the RFID Task, that reads and validates a RFID card
 */
class RFIDTask : public Task {
public:
  /**
   * @brief Constructor for the RFID Task
   *
   * @param nfc NFC object to be controlled
   * @param config Configuration type for Task class
   */
  RFIDTask(const task_config_t &config = default_config);

  /**
   * @brief Override of the mother class Task init function
   */
  virtual void init() override;

  /**
   * @brief Override of the mother class Task spin function
   */
  virtual void spin() override;

private:
  /**
   * @brief Read an id from the NFC peripheral
   */
  void read_id();

  /**
   * @brief Register a new id in the valid_ids vector
   */
  void register_id();

  /**
   * @brief Vector containing valid IDs
   */
  std::vector<rfidoor::peripheral::ID_t> valid_ids;

  /**
   * @brief State of the RFID task
   */
  state_t current_state_machine_state;
};

} // namespace rfidoor::task
#endif // __RFID_HPP__
