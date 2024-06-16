/**
 * @file state_machine.cpp
 *
 * @brief RFID class source code
 *
 * @date 06/2024
 */

#include "task/rfid.hpp"
#include "queue_scheme.hpp"

namespace rfidoor::task {

RFIDTask::RFIDTask(rfidoor::peripheral::Nfc &nfc, const task_config_t &config) : Task(config), nfc{nfc} { }

void RFIDTask::init() {
  //
}

void RFIDTask::spin() {
  if (this->nfc.read()) {
    for(rfidoor::peripheral::ID_t& id : this->valid_ids) {
      if (id.bytes == this->nfc.get_last_read_value().bytes) {
        rfidoor::queue::events_queue.publish(rfidoor::task::event_t::SINAL_VALIDO);
      }
    }
    rfidoor::queue::events_queue.publish(rfidoor::task::event_t::SINAL_INVALIDO);
  }
}

} // namespace rfidoor::task
