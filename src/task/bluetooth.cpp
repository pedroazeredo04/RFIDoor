/**
 * @file bluetooth.cpp
 *
 * @brief Bluetooth class source code
 *
 * @date 06/2024
 */

#include "task/bluetooth.hpp"
#include "blackboard/task_blackboard.hpp"

namespace rfidoor::task {

BluetoothTask::BluetoothTask(BluetoothSerial &bluetooth,
                             const task_config_t &config)
    : Task(config), bluetooth{bluetooth} {}

void BluetoothTask::init() { }

void BluetoothTask::spin() {
  if (this->bluetooth.available()) {
    String command = this->bluetooth.readStringUntil('\n');
    command.trim();

    if (command.startsWith("see_passwords")) {
      // Envia a lista de senhas
      for (password_t &password :
           rfidoor::task::blackboard::password_task.get_valid_passwords()) {
        this->bluetooth.println(password.c_str());
      }
    }
  }
}

} // namespace rfidoor::task