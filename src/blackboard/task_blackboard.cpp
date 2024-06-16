/**
 * @file task_blackboard.cpp
 *
 * @brief Configuration file of all tasks
 *
 * @date 06/2024
 */

#include "blackboard/task_blackboard.hpp"

namespace rfidoor::task {

const task_config_t blinky_config = {
    .name = "blinkyTask", .stack_size = 1000, .priority = LOW_PRIORITY};

const task_config_t state_machine_config = {
    .name = "stateMachineTask", .stack_size = 5000, .priority = LOW_PRIORITY};

const task_config_t rfid_config = {
    .name = "RFIDTAsk", .stack_size = 1000, .priority = LOW_PRIORITY};

/**
 * @brief Frequency of the blinky task in miliseconds
 */
const uint32_t blinky_frequency_ms{500};

/**
 * @brief Instanciate the blinky task
 */
BlinkyTask blinky_task(rfidoor::pinout::board_led, blinky_frequency_ms,
                       blinky_config);

/**
 * @brief Instanciate the state machine task
 */
StateMachineTask state_machine_task(state_machine_config);

/**
 * @brief Instanciate the state machine task
 */
RFIDTask RFID_task(rfidoor::pinout::nfc, rfid_config);

}; // namespace rfidoor::task