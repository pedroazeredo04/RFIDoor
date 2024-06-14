/**
 * @file task_scheme.hpp
 *
 * @brief Configuration file of all tasks
 *
 * @date 06/2024
 */

#include "task/task.hpp"

namespace rfidoor::task {

task_config_t blinky_config = {
    .name = "blinkyTask", .stack_size = 1000, .priority = LOW_PRIORITY};

task_config_t state_machine_config = {
    .name = "stateMachineTask", .stack_size = 1000, .priority = LOW_PRIORITY};

}; // namespace rfidoor::task
