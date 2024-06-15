#include "task/state_machine.hpp"

namespace rfidoor::task {

StateMachineTask::StateMachineTask(const task_config_t &config)
    : Task(config) {}

void StateMachineTask::init() {
    this->state = TRANCADA_IDLE;
    this->event = NENHUM_EVENTO;

  for (int state = 0; state < NUM_STATES; state++) {
    for (int event = 0; event < NUM_EVENTS; event++) {
      this->action_state_machine_table[state][event] = NENHUMA_ACAO;
      this->next_state_state_machine_table[state][event] = state;
    }
  }

  // Set the actions and next states for each event for TRANCADA_IDLE
  this->next_state_state_machine_table[TRANCADA_IDLE][SINAL_INVALIDO] = TRANCADA_IDLE;
  this->action_state_machine_table[TRANCADA_IDLE][SINAL_INVALIDO] = A03;
  this->next_state_state_machine_table[TRANCADA_IDLE][SINAL_VALIDO] =
      DESTRANCADA_FECHADA;
  this->action_state_machine_table[TRANCADA_IDLE][SINAL_VALIDO] = A04;
  this->next_state_state_machine_table[TRANCADA_IDLE][BOTAO] = DESTRANCADA_FECHADA;
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
  this->next_state_state_machine_table[DIGITANDO_SENHA][BOTAO] = DESTRANCADA_FECHADA;
  this->action_state_machine_table[DIGITANDO_SENHA][BOTAO] = A01;
  this->next_state_state_machine_table[DIGITANDO_SENHA][TIMEOUT] = TRANCADA_IDLE;
  this->action_state_machine_table[DIGITANDO_SENHA][TIMEOUT] = A05;
  this->next_state_state_machine_table[DIGITANDO_SENHA][SENHA_INVALIDA] =
      TRANCADA_IDLE;
  this->action_state_machine_table[DIGITANDO_SENHA][SENHA_INVALIDA] = A06;
  this->next_state_state_machine_table[DIGITANDO_SENHA][SENHA_VALIDA] =
      DESTRANCADA_FECHADA;
  this->action_state_machine_table[DIGITANDO_SENHA][SENHA_VALIDA] = A07;

  // Set the actions and next states for each event for DESTRANCADA_FECHADA
  this->next_state_state_machine_table[DESTRANCADA_FECHADA][TIMEOUT] = TRANCADA_IDLE;
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
    if (rfidoor::queue::events_queue.read(&(this->event)) == pdPASS) {
        this->action = this->get_action();
        this->state = this->get_next_state();
        this->execute_action();  
    }
}

uint8_t StateMachineTask::get_state() {
  return this->state;
}

uint8_t StateMachineTask::get_next_state() {
  return this->next_state_state_machine_table[this->state][this->event];
}

uint8_t StateMachineTask::get_action() {
  return this->action_state_machine_table[this->state][this->event];
}

void StateMachineTask::execute_action() {
    switch (this->action) {
    case A01:
        // destranca e display botao
        break;
    case A02:
        // display padrao senha e vai pro tratamento de senha
        rfidoor::pinout::lcd.set_cursor(0, 0);
        rfidoor::pinout::lcd.write("OMG SENHA!      ");
        rfidoor::pinout::lcd.set_cursor(1, 1);
        break;
    case A03:
        // display sinal invalido
        break;
    case A04:
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
        delay(2000);
        rfidoor::pinout::lcd.clear();
        rfidoor::pinout::lcd.set_cursor(0, 0);
        rfidoor::pinout::lcd.write("Digite a senha ");
        rfidoor::pinout::lcd.write_special_char(
            rfidoor::peripheral::LOCK_SPECIAL_CHAR);
        rfidoor::pinout::lcd.set_cursor(0, 1);
        break;
    case A07:
        // destranca e display senha valida
        break;
    case A08:
        // tranca e display padrão
        break;
    case A09:
        // desativa timeout e display porta aberta
        break;
    case A10:
        // ativa timeout e display porta destrancada fechada
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
}

}  // namespace rfidoor::task
