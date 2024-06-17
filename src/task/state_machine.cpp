/**
 * @file state_machine.cpp
 *
 * @brief StateMachine class source code, that implements the state machine
 *
 * @date 06/2024
 */

#include "task/state_machine.hpp"
#include "blackboard/queue_blackboard.hpp"
#include "blackboard/semaphore_blackboard.hpp"

namespace rfidoor::task {

const uint8_t open_position{90};
const uint8_t close_position{0};

const uint16_t LCD_timeout_ms{3000};

StateMachineTask::StateMachineTask(rfidoor::peripheral::ServoController& servo, const task_config_t &config)
    : servo{servo}, Task(config) {}

void StateMachineTask::init() {
  this->state = TRANCADA_IDLE;
  this->event = NENHUM_EVENTO;

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
}

void StateMachineTask::spin() {
  if (rfidoor::queue::blackboard::event_queue.read(&(this->event))) {
    this->action = this->get_action();
    this->state = this->get_next_state();
    rfidoor::queue::blackboard::state_queue.publish(this->state);
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
    set_lock_state(UNLOCKED);
    // destranca e display botao
    break;
  case A03:
    // display sinal invalido
    break;
  case A04:
    set_lock_state(UNLOCKED);
    // destranca e display sinal valido
    break;
  case A05:
    // apaga display
    break;
  case A06:
    // display senha invalida e display padrão
    rfidoor::pinout::lcd.clear();
    rfidoor::pinout::lcd.set_cursor(0, 0);
    rfidoor::pinout::lcd.write("SENHA INVALIDA!");
    delay(LCD_timeout_ms);
    rfidoor::pinout::lcd.clear();
    rfidoor::pinout::lcd.set_cursor(0, 0);
    rfidoor::pinout::lcd.write("Digite a senha ");
    rfidoor::pinout::lcd.write_special_char(rfidoor::peripheral::LOCK_SPECIAL_CHAR);
    rfidoor::pinout::lcd.set_cursor(0, 1);
    break;
  case A07:
    set_lock_state(UNLOCKED);
    // destranca e display senha valida
    break;
  case A08:
    set_lock_state(LOCKED);
    // tranca e display padrão
    break;
  case A09:
    // corta a contagem do timeout e display porta aberta
    break;
  case A10:
    // comeca contagem do timeout e display porta destrancada fechada
    break;
  case A11:
    // habilitar registro e display registro
    break;
  case A12:
    // desabilita registro e display sinal cadastrado
    break;
  case A13:
    // desabilita registro e display senha cadastrado
    break;
  case A14:
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
