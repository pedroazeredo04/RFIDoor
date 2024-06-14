#include "task/state_machine.hpp"

namespace rfidoor::task {

StateMachineTask::StateMachineTask(const task_config_t &config)
    : Task(config) {}

void StateMachineTask::init() {
    for(int state = 0; state < NUM_STATES; state++) {
        for(int event = 0; event < NUM_EVENTS; event++) {
            action_state_machine_table[state][event] = NENHUMA_ACAO;
            next_state_state_machine_table[state][event] = state;
        }
    }

    // Set the actions and next states for each event for TRANCADA_IDLE
    next_state_state_machine_table[TRANCADA_IDLE][SINAL_INVALIDO] = TRANCADA_IDLE;
    action_state_machine_table[TRANCADA_IDLE][SINAL_INVALIDO] = A03;
    next_state_state_machine_table[TRANCADA_IDLE][SINAL_VALIDO] = DESTRANCADA_FECHADA;
    action_state_machine_table[TRANCADA_IDLE][SINAL_VALIDO] = A04;
    next_state_state_machine_table[TRANCADA_IDLE][BOTAO] = DESTRANCADA_FECHADA;
    action_state_machine_table[TRANCADA_IDLE][BOTAO] = A01;
    next_state_state_machine_table[TRANCADA_IDLE][TECLA] = DIGITANDO_SENHA;
    action_state_machine_table[TRANCADA_IDLE][TECLA] = A02;

    // Set the actions and next states for each event for DIGITANDO_SENHA
    next_state_state_machine_table[DIGITANDO_SENHA][SINAL_INVALIDO] = DIGITANDO_SENHA;
    action_state_machine_table[DIGITANDO_SENHA][SINAL_INVALIDO] = A03;
    next_state_state_machine_table[DIGITANDO_SENHA][SINAL_VALIDO] = DESTRANCADA_FECHADA;
    action_state_machine_table[DIGITANDO_SENHA][SINAL_VALIDO] = A04;
    next_state_state_machine_table[DIGITANDO_SENHA][BOTAO] = DESTRANCADA_FECHADA;
    action_state_machine_table[DIGITANDO_SENHA][BOTAO] = A01;
    next_state_state_machine_table[DIGITANDO_SENHA][TIMEOUT] = TRANCADA_IDLE;
    action_state_machine_table[DIGITANDO_SENHA][TIMEOUT] = A05;
    next_state_state_machine_table[DIGITANDO_SENHA][SENHA_INVALIDA] = TRANCADA_IDLE;
    action_state_machine_table[DIGITANDO_SENHA][SENHA_INVALIDA] = A06;
    next_state_state_machine_table[DIGITANDO_SENHA][SENHA_VALIDA] = DESTRANCADA_FECHADA;
    action_state_machine_table[DIGITANDO_SENHA][SENHA_VALIDA] = A07;

    // Set the actions and next states for each event for DESTRANCADA_FECHADA
    next_state_state_machine_table[DESTRANCADA_FECHADA][TIMEOUT] = TRANCADA_IDLE;
    action_state_machine_table[DESTRANCADA_FECHADA][TIMEOUT] = A08;
    next_state_state_machine_table[DESTRANCADA_FECHADA][ABRIR] = ABERTA;
    action_state_machine_table[DESTRANCADA_FECHADA][ABRIR] = A09;

    // Set the actions and next states for each event for ABERTA
    next_state_state_machine_table[ABERTA][FECHAR] = DESTRANCADA_FECHADA;
    action_state_machine_table[ABERTA][FECHAR] = A10;
    next_state_state_machine_table[ABERTA][SEGURAR_ASTERISCO] = REGISTRO;
    action_state_machine_table[ABERTA][SEGURAR_ASTERISCO] = A11;

    // Set the actions and next states for each event for REGISTRO
    next_state_state_machine_table[REGISTRO][SINAL_CADASTRADO] = ABERTA;
    action_state_machine_table[REGISTRO][SINAL_CADASTRADO] = A12;
    next_state_state_machine_table[REGISTRO][SENHA_CADASTRADA] = ABERTA;
    action_state_machine_table[REGISTRO][SENHA_CADASTRADA] = A13;
    next_state_state_machine_table[REGISTRO][SEGURAR_ASTERISCO] = ABERTA;
    action_state_machine_table[REGISTRO][SEGURAR_ASTERISCO] = A14;
}

void StateMachineTask::spin() {
    //
}

} // namespace rfidoor::task