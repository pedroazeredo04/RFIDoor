/**
 * @file state_machine_types.hpp
 *
 * @brief Useful types for the state machine and other tasks
 *
 * @date 06/2024
 */

#ifndef __STATE_MACHINE_TYPES_HPP__
#define __STATE_MACHINE_TYPES_HPP__

#include <Arduino.h>

namespace rfidoor::task {

#define NUM_STATES 7
#define NUM_EVENTS 12

/**
 * @brief Enum corresponding to the possible states of the state machine
 */
enum state_t : int8_t {
  TRANCADA_IDLE,
  DIGITANDO_SENHA,
  DESTRANCADA_FECHADA,
  ABERTA,
  REGISTRO
};

/**
 * @brief Enum corresponding to the possible events of the state machine
 */
enum event_t : int8_t {
  NENHUM_EVENTO = -1,
  SINAL_INVALIDO,
  SINAL_VALIDO,
  SINAL_CADASTRADO,
  BOTAO,
  TIMEOUT,
  SENHA_INVALIDA,
  SENHA_VALIDA,
  SENHA_CADASTRADA,
  TECLA,
  FECHAR,
  ABRIR,
  SEGURAR_ASTERISCO
};

/**
 * @brief Enum corresponding to the possible actions of the state machine
 */
enum action_t : int8_t {
  NENHUMA_ACAO = -1,
  A01,
  A02,
  A03,
  A04,
  A05,
  A06,
  A07,
  A08,
  A09,
  A10,
  A11,
  A12,
  A13,
  A14
};

/**
 * @brief Enum corresponding to the possible states of the keyboard and rfid
 * sensor
 *
 * @note rfid and keyboard can read password or id, and register password or id
 */
enum input_device_state_t : int8_t { READING, REGISTERING };

}; // namespace rfidoor::task

#endif // __STATE_MACHINE_TYPES_HPP__