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

namespace rfidoor::task {

/**
 * @brief Class for the blinky Task, that blinks the board LED continuously
 */
class RFIDTask : public Task {
public:
  /**
   * @brief Constructor for the blinky Task
   *
   * @param nfc NFC object to be controlled
   * @param config Configuration type for Task class
   */
  RFIDTask(rfidoor::peripheral::Nfc &nfc,
           const task_config_t &config = default_config);

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
   * @brief NFC peripheral to be controlled
   */
  rfidoor::peripheral::Nfc nfc;

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
