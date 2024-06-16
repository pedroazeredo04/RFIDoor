/**
 * @file state_machine.hpp
 *
 * @brief StateMachine class header, that implements the state machine
 *
 * @date 06/2024
 */

#ifndef __STATE_MACHINE_HPP__
#define __STATE_MACHINE_HPP__

#include "pinout.hpp"
#include "task/task.hpp"

namespace rfidoor::task {

#define NUM_STATES 7
#define NUM_EVENTS 12

/**
 * @brief Enum corresponding to the possible states of the state machine
 */
enum state_t {
  TRANCADA_IDLE,
  DIGITANDO_SENHA,
  DESTRANCADA_FECHADA,
  ABERTA,
  REGISTRO
};

/**
 * @brief Enum corresponding to the possible events of the state machine
 */
enum event_t {
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
enum action_t {
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
 * @brief Class for the state machine Task, that implements the state machine
 */
class StateMachineTask : public Task {
public:
  /**
   * @brief Constructor for the state machine Task
   */
  StateMachineTask(const task_config_t &config = default_config);

  /**
   * @brief Override of the mother class Task init function
   */
  virtual void init() override;

  /**
   * @brief Override of the mother class Task spin function
   */
  virtual void spin() override;

  /**
   * @brief Function to get the current state of the state machine
   */
  state_t get_state();

private:
  /**
   * @brief Function to get the next state of the state machine from the table
   */
  state_t get_next_state();

  /**
   * @brief Function to get the action of the state machine from the table
   */
  action_t get_action();

  /**
   * @brief Function to execute the action of the state machine
   */
  void execute_action();

  /**
   * @brief Table of actions of the state machine [state][event]
   */
  action_t action_state_machine_table[NUM_STATES][NUM_EVENTS];

  /**
   * @brief Table of next states of the state machine [state][event]
   */
  state_t next_state_state_machine_table[NUM_STATES][NUM_EVENTS];

  /**
   * @brief Current state of the state machine
   */
  state_t state;

  /**
   * @brief Current event of the state machine
   */
  event_t event;

  /**
   * @brief Action of the state machine
   */
  action_t action;
};

} // namespace rfidoor::task
#endif // __STATE_MACHINE_HPP__