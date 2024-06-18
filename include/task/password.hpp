/**
 * @file password.hpp
 *
 * @brief Password class header, that reads and validates a password card
 *
 * @date 06/2024
 */

#ifndef __PASSWORD_HPP__
#define __PASSWORD_HPP__

#include "peripheral/keyboard.hpp"
#include "task/state_machine_types.hpp"
#include "task/task.hpp"
#include <string>
#include <vector>

namespace rfidoor::task {

/**
 * @brief Length of the password
 */
const uint8_t password_max_length{15};

/**
 * @brief Password type definition
 */
typedef std::string password_t;

/**
 * @brief Class for the password Task, that reads and validates a password
 */
class PasswordTask : public Task {
public:
  /**
   * @brief Constructor for the Password Task
   *
   * @param keyboard keyboard object to be controlled
   * @param config Configuration type for Task class
   */
  PasswordTask(rfidoor::peripheral::Keyboard &keyboard,
               const task_config_t &config = default_config);

  /**
   * @brief Override of the mother class Task init function
   */
  virtual void init() override;

  /**
   * @brief Override of the mother class Task spin function
   */
  virtual void spin() override;

  /**
  * @brief Override of the mother class Task spin function
  */
  password_t get_current_password();

  /**
   * @brief Get the valid passwords
   *
   * @return std::vector<password_t> Vector containing the valid passwords
   */
  std::vector<password_t> get_valid_passwords() const;

private:
  /**
   * @brief Read an id from the keyboard peripheral
   */
  void read_password();

  /**
   * @brief Register a new id in the valid_ids vector
   */
  void register_password();

  /**
   * @brief keyboard peripheral to be controlled
   */
  rfidoor::peripheral::Keyboard keyboard;

  /**
   * @brief Vector containing valid passwords
   */
  std::vector<password_t> valid_passwords;

  /**
   * @brief State of the keyboard task
   */
  state_t current_state_machine_state{TRANCADA_IDLE};

  /**
   * @brief is entering password
   */
  bool is_entering_password{false};

  /**
   * @brief Current password to be built
   */
  password_t current_password;
};

} // namespace rfidoor::task
#endif // __PASSWORD_HPP__
