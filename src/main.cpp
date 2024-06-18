#include <blackboard/queue_blackboard.hpp>
#include <blackboard/task_blackboard.hpp>
#include <pinout.hpp>

void setup() {
  Serial.begin(9600);
  rfidoor::pinout::lcd.init();

  rfidoor::task::blackboard::display_task.create_task();
  rfidoor::task::blackboard::blinky_task.create_task();
  rfidoor::task::blackboard::password_task.create_task();
  rfidoor::task::blackboard::state_machine_task.create_task();
  rfidoor::task::blackboard::button_task.create_task();



}

void loop() {}