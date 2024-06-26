/**
 * @file task_blackboard.cpp
 *
 * @brief Configuration file of all tasks
 *
 * @date 06/2024
 */

#include "blackboard/task_blackboard.hpp"

namespace rfidoor::task::blackboard {

/**
 * @brief Frequency of the blinky task in miliseconds
 */
const uint32_t blinky_frequency_ms{500};

const task_config_t blinky_config = {.name = "blinkyTask",
                                     .stack_size = 1000,
                                     .priority = HIGH_PRIORITY,
                                     .delay_ms = blinky_frequency_ms};

const task_config_t state_machine_config = {.name = "stateMachineTask",
                                            .stack_size = 5000,
                                            .priority = LOW_PRIORITY,
                                            .delay_ms = 10};

const task_config_t rfid_config = {.name = "RFIDTask",
                                   .stack_size = 5000,
                                   .priority = LOW_PRIORITY,
                                   .delay_ms = 10};

const task_config_t button_config = {.name = "ButtonTask",
                                     .stack_size = 1000,
                                     .priority = LOW_PRIORITY,
                                     .delay_ms = 10};

const task_config_t password_config = {.name = "passwordTask",
                                       .stack_size = 5000,
                                       .priority = LOW_PRIORITY,
                                       .delay_ms = 10};

const task_config_t display_config = {
    .name = "displayTask", .stack_size = 5000, .priority = LOW_PRIORITY};

const task_config_t bluetooth_config = {
    .name = "bluetoothTask", .stack_size = 5000, .priority = LOW_PRIORITY, .delay_ms = 10};

/**
 * @brief Instanciate the blinky task
 */
BlinkyTask blinky_task(rfidoor::pinout::board_led, blinky_frequency_ms,
                       blinky_config);

/**
 * @brief Instanciate the state machine task
 */
StateMachineTask state_machine_task(rfidoor::pinout::servo, state_machine_config);

/**
 * @brief Instanciate the RFID task
 */
RFIDTask RFID_task(rfid_config);

/**
 * @brief Instanciate the password task
 */
PasswordTask password_task(rfidoor::pinout::keyboard, password_config);

/**
 * @brief Instanciate the button task
 */
ButtonTask button_task(rfidoor::pinout::inside_button, rfidoor::pinout::door_button, button_config);

/**
 * @brief Instanciate the display task
 */
DisplayTask display_task(display_config);

/**
 * @brief Instanciate the bluetooth task
 */
BluetoothTask bluetooth_task(rfidoor::pinout::SerialBT, bluetooth_config);

}; // namespace rfidoor::task::blackboard