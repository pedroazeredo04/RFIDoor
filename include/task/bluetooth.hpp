/**
 * @file blueooth.hpp
 *
 * @brief Bluetooth class header, that controls the bluetooth action
 *
 * @date 06/2024
 */

#ifndef __BLUETOOTH_HPP__
#define __BLUETOOTH_HPP__

#include "task/task.hpp"
#include <BluetoothSerial.h>

namespace rfidoor::task {

/**
 * @brief Class for the blueooth Task
 */
class BluetoothTask : public Task {
public:
  /**
   * @brief Constructor for the blueooth Task
   *
   * @param bluetooth bluetooth object to be read
   * @param config Configuration type for Task class
   */
  BluetoothTask(BluetoothSerial &bluetooth,
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
   * @brief Bluetooth peripheral to be blinked
   */
  BluetoothSerial bluetooth;
};

} // namespace rfidoor::task
#endif // __BLUETOOTH_HPP__
