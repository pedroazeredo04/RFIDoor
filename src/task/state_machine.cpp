/**
 * @file state_machine.cpp
 *
 * @brief StateMachine class source code, that implements the state machine
 *
 * @date 06/2024
 */

#include "blackboard/task_blackboard.hpp"
#include "blackboard/queue_blackboard.hpp"
#include "blackboard/semaphore_blackboard.hpp"
#include <esp_timer.h>

namespace rfidoor::task {

/**
 * @brief Conversion constant from microseconds to milliseconds
 */
const float microseconds_to_miliseconds{1e-3};

/**
 * @brief Function to get the current time in milliseconds
 */
float get_time_ms() {
  return esp_timer_get_time() * microseconds_to_miliseconds;
}

/**
 * @brief Timeout to be given to the state machine
 */
const uint32_t timeout_ms{5000};

/**
 * @brief Open and closed servo motor position
 */
const uint8_t open_position{90};
const uint8_t close_position{0};

StateMachineTask::StateMachineTask(rfidoor::peripheral::ServoController& servo, const task_config_t &config)
    : servo{servo}, Task(config) {}

void StateMachineTask::init() {
  for (int state = 0; state < NUM_STATES; state++) {
    for (int event = 0; event < NUM_EVENTS; event++) {
      this->action_state_machine_table[state][event] = NENHUMA_ACAO;
      this->next_state_state_machine_table[state][event] = (state_t)state;
    }
  }

  // Set the actions and next states for each event for TRANCADA_IDLE
  this->next_state_state_machine_table[TRANCADA_IDLE][SINAL_INVALIDO] =
      TRANCADA_IDLE;
  this->action_state_machine_table[TRANCADA_IDLE][SINAL_INVALIDO] = A03;
  this->next_state_state_machine_table[TRANCADA_IDLE][SINAL_VALIDO] =
      DESTRANCADA_FECHADA;
  this->action_state_machine_table[TRANCADA_IDLE][SINAL_VALIDO] = A04;
  this->next_state_state_machine_table[TRANCADA_IDLE][BOTAO] =
      DESTRANCADA_FECHADA;
  this->action_state_machine_table[TRANCADA_IDLE][BOTAO] = A01;
  this->next_state_state_machine_table[TRANCADA_IDLE][TECLA] = DIGITANDO_SENHA;
  this->action_state_machine_table[TRANCADA_IDLE][TECLA] = A02;

  // Set the actions and next states for each event for DIGITANDO_SENHA
  this->next_state_state_machine_table[DIGITANDO_SENHA][SINAL_INVALIDO] =
      DIGITANDO_SENHA;
  this->action_state_machine_table[DIGITANDO_SENHA][SINAL_INVALIDO] = A03;
  this->next_state_state_machine_table[DIGITANDO_SENHA][SINAL_VALIDO] =
      DESTRANCADA_FECHADA;
  this->action_state_machine_table[DIGITANDO_SENHA][SINAL_VALIDO] = A04;
  this->next_state_state_machine_table[DIGITANDO_SENHA][BOTAO] =
      DESTRANCADA_FECHADA;
  this->action_state_machine_table[DIGITANDO_SENHA][BOTAO] = A01;
  this->next_state_state_machine_table[DIGITANDO_SENHA][TIMEOUT] =
      TRANCADA_IDLE;
  this->action_state_machine_table[DIGITANDO_SENHA][TIMEOUT] = A05;
  this->next_state_state_machine_table[DIGITANDO_SENHA][SENHA_INVALIDA] =
      TRANCADA_IDLE;
  this->action_state_machine_table[DIGITANDO_SENHA][SENHA_INVALIDA] = A06;
  this->next_state_state_machine_table[DIGITANDO_SENHA][SENHA_VALIDA] =
      DESTRANCADA_FECHADA;
  this->action_state_machine_table[DIGITANDO_SENHA][SENHA_VALIDA] = A07;
  this->next_state_state_machine_table[DIGITANDO_SENHA][TECLA] = DIGITANDO_SENHA;
  this->action_state_machine_table[DIGITANDO_SENHA][TECLA] = A02;

  // Set the actions and next states for each event for DESTRANCADA_FECHADA
  this->next_state_state_machine_table[DESTRANCADA_FECHADA][TIMEOUT] =
      TRANCADA_IDLE;
  this->action_state_machine_table[DESTRANCADA_FECHADA][TIMEOUT] = A08;
  this->next_state_state_machine_table[DESTRANCADA_FECHADA][ABRIR] = ABERTA;
  this->action_state_machine_table[DESTRANCADA_FECHADA][ABRIR] = A09;

  // Set the actions and next states for each event for ABERTA
  this->next_state_state_machine_table[ABERTA][FECHAR] = DESTRANCADA_FECHADA;
  this->action_state_machine_table[ABERTA][FECHAR] = A10;
  this->next_state_state_machine_table[ABERTA][SEGURAR_ASTERISCO] = REGISTRO;
  this->action_state_machine_table[ABERTA][SEGURAR_ASTERISCO] = A11;

  // Set the actions and next states for each event for REGISTRO
  this->next_state_state_machine_table[REGISTRO][SINAL_CADASTRADO] = ABERTA;
  this->action_state_machine_table[REGISTRO][SINAL_CADASTRADO] = A12;
  this->next_state_state_machine_table[REGISTRO][SENHA_CADASTRADA] = ABERTA;
  this->action_state_machine_table[REGISTRO][SENHA_CADASTRADA] = A13;
  this->next_state_state_machine_table[REGISTRO][SEGURAR_ASTERISCO] = ABERTA;
  this->action_state_machine_table[REGISTRO][SEGURAR_ASTERISCO] = A14;

  this->state = TRANCADA_IDLE;
  this->event = NENHUM_EVENTO;
  this->action = NENHUMA_ACAO;
  this->execute_action();
}

void StateMachineTask::spin() {
  if (this->is_timeout_timer_running) {
    if (get_time_ms() - this->timeout_timer_start_ms > timeout_ms) {
      rfidoor::queue::blackboard::event_queue.publish(TIMEOUT);
      this->is_timeout_timer_running = false;
    }
  }

  if (rfidoor::queue::blackboard::event_queue.read(&(this->event))) {
    this->action = this->get_action();
    this->state = this->get_next_state();
    this->execute_action();
  }
}

state_t StateMachineTask::get_state() { return this->state; }

state_t StateMachineTask::get_next_state() {
  return this->next_state_state_machine_table[this->state][this->event];
}

action_t StateMachineTask::get_action() {
  return this->action_state_machine_table[this->state][this->event];
}

void StateMachineTask::execute_action() {
  switch (this->action) {
  case A01:
    this->is_timeout_timer_running = true;
    this->timeout_timer_start_ms = get_time_ms();
    set_lock_state(UNLOCKED);
    break;
  case A02:
    this->is_timeout_timer_running = true;
    this->timeout_timer_start_ms = get_time_ms();
    break;
  case A03:
    blackboard::display_task.temporary_display("Sinal invalido!");
    this->is_timeout_timer_running = true;
    this->timeout_timer_start_ms = get_time_ms();
    break;
  case A04:
    blackboard::display_task.temporary_display(" Sinal valido! ");
    set_lock_state(UNLOCKED);
    this->is_timeout_timer_running = true;
    this->timeout_timer_start_ms = get_time_ms();
    break;
  case A05:
    this->is_timeout_timer_running = false;
    break;
  case A06:
    this->is_timeout_timer_running = false;
    blackboard::display_task.temporary_display("Senha invalida!");
    break;
  case A07:
    set_lock_state(UNLOCKED);
    blackboard::display_task.temporary_display(" Senha valida! ");
    this->is_timeout_timer_running = true;
    this->timeout_timer_start_ms = get_time_ms();
    break;
  case A08:
    set_lock_state(LOCKED);
    this->is_timeout_timer_running = false;
    // tranca e display padrão
    break;
  case A09:
    this->is_timeout_timer_running = false;
    break;
  case A10:
    this->is_timeout_timer_running = true;
    this->timeout_timer_start_ms = get_time_ms();
    break;
  case A11:
    this->is_timeout_timer_running = false;
    // habilitar registro e display registro
    break;
  case A12:
    this->is_timeout_timer_running = false;
    // desabilita registro e display sinal cadastrado
    break;
  case A13:
    this->is_timeout_timer_running = false;
    // desabilita registro e display senha cadastrado
    break;
  case A14:
    this->is_timeout_timer_running = false;
    // desabilita registro e display registro cancelado
    break;
  default:
    break;
  }

  rfidoor::semaphore::blackboard::display_semaphore.give();
}

void StateMachineTask::set_lock_state(lock_state_t lock_state) {
  switch (lock_state) {
    case LOCKED: {
      this->servo.write_angular_position_degrees(open_position);
      break;
    }

    case UNLOCKED: {
      this->servo.write_angular_position_degrees(close_position);
      break;
    }

    default: {
      break;
    }
  }
}

} // namespace rfidoor::task
