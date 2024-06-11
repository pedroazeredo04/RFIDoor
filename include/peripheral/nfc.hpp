/**
 * @file Nfc.hpp
 *
 * @brief Nfc reader class header
 *
 * @date 06/2024
 */

#ifndef __NFC_HPP__
#define __NFC_HPP__

#include <Adafruit_PN532.h>
#include <SPI.h>
#include <Wire.h>

namespace rfidoor::peripheral {
/**
 * @brief Class for controlling an NfcReader
 */
class Nfc {
public:
  /**
   * @brief Constructor for the Nfc class
   *
   * @param irq_pin IRQ Pin connected to Nfc Module
   * @param rst_pin Reset PIN connected to the Nfc Module
   */
  explicit Nfc(uint8_t irq_pin, uint8_t rst_pin);

  /**
   * @brief Initializes Nfc
   */
  void init();

  /**
   * @brief Read the NFC ID
   *
   * @return true if the NFC ID was read successfully
   */
  bool read_nfcid();

private:
  /**
   * @brief Lib version of the NFC
   */
  Adafruit_PN532 lib_nfc;

  /**
   * @brief Buffer to store the returned UID
   */
  uint8_t uid[7];

  /**
   * @brief Pointer to the lenght of the UID (4 or 7 bytes depending on
   * ISO14443A card type)
   */
  uint8_t *uidLength;
};
} // namespace rfidoor::peripheral

#endif // __NFC_HPP__