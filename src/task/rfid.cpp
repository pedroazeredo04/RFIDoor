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

RFIDTask::RFIDTask(const task_config_t &config)
    : Task(config), current_state_machine_state{TRANCADA_IDLE} {}

void RFIDTask::init() {
  uint32_t versiondata = rfidoor::pinout::nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX);
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC);
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);

  Serial.println("Waiting for an ISO14443A Card ...");
}

void RFIDTask::spin() {
    Serial.print("SPINO RFID");

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
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  uint8_t read_success = rfidoor::pinout::nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  Serial.println("ESTADO DI LER");

  if (read_success) {
    Serial.println("LEU RFID");
    for (const auto &id : this->valid_ids) {
      if (id.bytes == uid) {
        rfidoor::queue::blackboard::event_queue.publish(SINAL_VALIDO);
      }
    }
    rfidoor::queue::blackboard::event_queue.publish(SINAL_INVALIDO);
  }
}

void RFIDTask::register_id() {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  uint8_t register_sucesss = rfidoor::pinout::nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  rfidoor::peripheral::ID_t id_to_be_registered;

  if (register_sucesss) {
    Serial.println("REGISTRO RFID");
    rfidoor::semaphore::blackboard::registering_semaphore.take();

    std::copy(uid, uid + uidLength, id_to_be_registered.bytes);

    this->valid_ids.push_back(id_to_be_registered);
    rfidoor::queue::blackboard::event_queue.publish(SINAL_CADASTRADO);

    rfidoor::semaphore::blackboard::registering_semaphore.give();
  }
}

} // namespace rfidoor::task
