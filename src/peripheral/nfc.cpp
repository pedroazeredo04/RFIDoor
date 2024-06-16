/**
 * @file nfc.cpp
 *
 * @brief nfc reader class implementation
 *
 * @date 06/2024
 */

#include "peripheral/nfc.hpp"

namespace rfidoor::peripheral {

Nfc::Nfc(uint8_t irq_pin, uint8_t rst_pin)
    : lib_nfc(irq_pin, rst_pin), uid{0, 0, 0, 0, 0, 0, 0}, uidLength(0) {}

void Nfc::init() {
  lib_nfc.begin();
  uint32_t versiondata = lib_nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1)
      ; // halt
  }
}

bool Nfc::read() {
  return lib_nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, this->uid.bytes,
                                     this->uidLength);
}

ID_t Nfc::get_last_read_value() { return this->uid; }

} // namespace rfidoor::peripheral
