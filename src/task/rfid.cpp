/**
 * @file state_machine.cpp
 *
 * @brief RFID class source code
 *
 * @date 06/2024
 */

#include "task/rfid.hpp"
#include "scheme/queue_scheme.hpp"
#include "scheme/semaphore_scheme.hpp"

namespace rfidoor::task {

RFIDTask::RFIDTask(rfidoor::peripheral::Nfc &nfc, const task_config_t &config)
    : Task(config), nfc{nfc}, state{READING} {}

void RFIDTask::init() {
  //
}

void RFIDTask::spin() {
  input_device_state_t queue_state;

  if (rfidoor::queue::input_device_state_queue.peek(&queue_state)) {
    this->state = queue_state;
  }

  switch (this->state) {
  case READING: {
    this->read_id();
    break;
  }

  case REGISTERING: {
    this->register_id();
    break;
  }

  default: {
    break;
  }
  }
}

void RFIDTask::read_id() {
  if (this->nfc.read()) {
    for (auto id : this->valid_ids) {
      if (id.bytes == this->nfc.get_last_read_value().bytes) {
        rfidoor::queue::event_queue.publish(SINAL_VALIDO);
      }
    }
    rfidoor::queue::event_queue.publish(SINAL_INVALIDO);
  }
}

void RFIDTask::register_id() {
  if (this->nfc.read()) {
    rfidoor::semaphore::registering_semaphore.take();

    this->valid_ids.push_back(this->nfc.get_last_read_value());
    rfidoor::queue::event_queue.publish(SINAL_CADASTRADO);

    rfidoor::semaphore::registering_semaphore.give();
  }
}

} // namespace rfidoor::task
