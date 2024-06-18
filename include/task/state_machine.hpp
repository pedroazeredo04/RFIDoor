/**
 * @file state_machine.hpp
 *
 * @brief StateMachine class header, that implements the state machine
 *
 * @date 06/2024
 */

#ifndef __STATE_MACHINE_HPP__
#define __STATE_MACHINE_HPP__

#include "pinout.hpp"
#include "task/state_machine_types.hpp"
#include "task/task.hpp"

namespace rfidoor::task {

enum lock_state_t : uint8_t {
  LOCKED, 
  UNLOCKED
};

/**
 * @brief Class for the state machine Task, that implements the state machine
 */
class StateMachineTask : public Task {
public:
  /**
   * @brief Constructor for the state machine Task
   *
   * @param config Configuration type for Task class
   */
  StateMachineTask(rfidoor::peripheral::ServoController& servo, const task_config_t &config = default_config);

  /**
   * @brief Override of the mother class Task init function
   */
  virtual void init() override;

  /**
   * @brief Override of the mother class Task spin function
   */
  virtual void spin() override;

  /**
   * @brief Function to get the current state of the state machine
   * 
   * @return state_t Current state of the state machine
   */
  state_t get_state();

private:
  /**
   * @brief Function to get the next state of the state machine from the table
   * 
   * @return state_t Next state of the state machine
   */
  state_t get_next_state();

  /**
   * @brief Function to get the action of the state machine from the table
   * 
   * @return action_t Action of the state machine
   */
  action_t get_action();

  /**
   * @brief Function to execute the action of the state machine
   */
  void execute_action();

  /**
   * @brief Function to set the current lock state
   *
   * @param lock_state locked or unlocked
   */
  void set_lock_state(lock_state_t lock_state);

  /**
   * @brief Table of actions of the state machine [state][event]
   */
  action_t action_state_machine_table[NUM_STATES][NUM_EVENTS];

  /**
   * @brief Table of next states of the state machine [state][event]
   */
  state_t next_state_state_machine_table[NUM_STATES][NUM_EVENTS];

  /**
   * @brief Current state of the state machine
   */
  state_t state;

  /**
   * @brief Current event of the state machine
   */
  event_t event;

  /**
   * @brief Action of the state machine
   */
  action_t action;

  /**
   * @brief Servo object to be controlled
   */
  rfidoor::peripheral::ServoController servo;

  /**
  * @brief Timer for timeout
  */
  uint32_t timeout_timer_start_ms;

  /**
  * @brief True if timeout timer must be considered, false otherwise
  */
  bool is_timeout_timer_running{false};
};

} // namespace rfidoor::task
#endif // __STATE_MACHINE_HPP__