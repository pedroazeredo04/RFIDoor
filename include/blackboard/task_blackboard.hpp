/**
 * @file task_blackboard.hpp
 *
 * @brief Configuration file of all tasks
 *
 * @date 06/2024
 */

#ifndef __TASK_BLACKBOARD_HPP__
#define __TASK_BLACKBOARD_HPP__

#include "pinout.hpp"
#include "task/blinky.hpp"
#include "task/rfid.hpp"
#include "task/state_machine.hpp"
#include "task/task.hpp"
#include "task/password.hpp"

namespace rfidoor::task::blackboard {
/**
 * @brief Frequency of the blinky task in miliseconds
 */
extern const uint32_t blinky_frequency_ms;

/**
 * @brief Instanciate the blinky task
 */
extern BlinkyTask blinky_task;

/**
 * @brief Instanciate the state machine task
 */
extern StateMachineTask state_machine_task;

/**
 * @brief Instanciate the state machine task
 */
extern RFIDTask RFID_task;

/**
 * @brief Password task
 */
extern PasswordTask password_task;

}; // namespace rfidoor::task

#endif // __TASK_BLACKBOARD_HPP__