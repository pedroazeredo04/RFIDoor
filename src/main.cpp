#include <blackboard/queue_blackboard.hpp>
#include <blackboard/task_blackboard.hpp>
#include <pinout.hpp>

void setup() {
  Serial.begin(9600);
  rfidoor::pinout::lcd.init();
  rfidoor::pinout::SerialBT.begin("RFIDoor");

  rfidoor::task::blackboard::display_task.create_task();
  // rfidoor::task::blackboard::blinky_task.create_task();
  // rfidoor::task::blackboard::bluetooth_task.create_task();
  rfidoor::task::blackboard::password_task.create_task();
  rfidoor::task::blackboard::state_machine_task.create_task();
  rfidoor::task::blackboard::button_task.create_task();
  // rfidoor::task::blackboard::RFID_task.create_task();
}

void loop() {}