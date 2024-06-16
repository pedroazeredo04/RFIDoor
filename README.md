# RFIDoor

O projeto consiste na automação da fechadura de uma porta, utilizando ESP32 e sensores de leitura RF ID.

## Estrutura de código

O código está dividido em módulos, cada um com sua responsabilidade. A seguir, uma breve descrição de cada módulo:

- `peripherals`: Módulo contendo as classes relativas aos periféricos do sistema.
  - `rfid`: Módulo contendo as classes relativas ao sensor RFID.
  - `servo`: Módulo contendo as classes relativas ao servo motor.
  - `keyboards`: Módulo contendo as classes relativas ao teclado matricial 4x4.
  - `led`: Módulo contendo as classes relativas ao LED
  - `lcd`: Módulo contendo as classes relativas ao Liquid Crystal Display.
- `task`: Módulo contendo as classes relativas às tarefas do sistema.
  - `task`: Classe abstrata para as tasks RTOS.
  - `blinky`: Tarefa de piscar o LED interno da ESP32, para conferir o funcionamento do RTOS.
- `pinout`: Módulo responsável por declarar os pinos de conexão com os módulo e instanciar as classes de cada módulo.
- `task_blackboard`: Módulo responsável por instanciar as tarefas do sistema.
- `main`: Módulo principal do sistema, contendo a função `setup` e `loop`.
  - A função `setup` é responsável por inicializar o sistema. Nela, devem ser inicializadas as tasks RTOS e os periféricos necessários.
  - A função `loop` é responsável por executar o loop principal do sistema. Ela deve ser deixada vazia, pois o loop é executado pelas tasks RTOS do sistema.

## Formatação

O projeto usa o C-Lang para formatação. Para formatar o código, utilize o comando:

```bash
clang-format -i **.cpp **.hpp
```
