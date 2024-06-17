/**
 * @file state_machine.cpp
 *
 * @brief RFID class source code
 *
 * @date 06/2024
 */

#include "task/rfid.hpp"
#include "blackboard/queue_blackboard.hpp"
#include "blackboard/semaphore_blackboard.hpp"
#include "blackboard/task_blackboard.hpp"

namespace rfidoor::task {

RFIDTask::RFIDTask(rfidoor::peripheral::Nfc &nfc, const task_config_t &config)
    : Task(config), nfc{nfc}, current_state_machine_state{TRANCADA_IDLE} {}

void RFIDTask::init() {
  //
}

void RFIDTask::spin() {
  this->current_state_machine_state =
      blackboard::state_machine_task.get_state();

  switch (this->current_state_machine_state) {
  case REGISTRO: {
    this->register_id();
    break;
  }

  default: {
    this->read_id();
    break;
  }
  }
}

void RFIDTask::read_id() {
  if (this->nfc.read()) {
    for (const auto &id : this->valid_ids) {
      if (id.bytes == this->nfc.get_last_read_value().bytes) {
        rfidoor::queue::blackboard::event_queue.publish(SINAL_VALIDO);
      }
    }
    rfidoor::queue::blackboard::event_queue.publish(SINAL_INVALIDO);
  }
}

void RFIDTask::register_id() {
  if (this->nfc.read()) {
    rfidoor::semaphore::blackboard::registering_semaphore.take();

    this->valid_ids.push_back(this->nfc.get_last_read_value());
    rfidoor::queue::blackboard::event_queue.publish(SINAL_CADASTRADO);

    rfidoor::semaphore::blackboard::registering_semaphore.give();
  }
}

} // namespace rfidoor::task
