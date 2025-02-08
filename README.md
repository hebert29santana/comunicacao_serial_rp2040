# Projeto de Comunicação Serial com Raspberry Pi Pico W e Display LCD  
Este projeto demonstra a comunicação serial entre um Raspberry Pi Pico W e um display LCD, utilizando botões para controlar LEDs e exibir mensagens no display. O projeto também inclui uma funcionalidade de inatividade, onde o display volta a exibir uma animação inicial após um período sem interação.

## 🛠️ Componentes Utilizados  
Raspberry Pi Pico W: Microcontrolador principal.

Display LCD (SSD1306): Exibe mensagens e animações.

LEDs RGB: Controlados pelos botões.

Botões: Para interação do usuário (ligar/desligar LEDs).

Matriz de LEDs 5x5: Exibe números e animações.

## 📋 Funcionalidades
### Controle de LEDs:

Botão A: Liga/desliga o LED verde.

Botão B: Liga/desliga o LED azul.

Quando um LED é ligado, o outro é automaticamente desligado.

### Exibição de Mensagens no Display:

Ao pressionar um botão, uma mensagem é exibida no display LCD indicando o estado do LED (ligado/desligado).

### Entrada Serial:

O projeto permite a entrada de caracteres via comunicação serial (USB).

Se um número entre 0 e 9 for digitado, ele será exibido na matriz de LEDs.

### Funcionalidade de Inatividade:

Após 10 segundos sem interação (pressionamento de botões ou entrada serial), o display volta a exibir uma animação inicial.

## 🚀 Como Funciona
O código principal está no arquivo comunicacao_serial_rp2040.c.

O display LCD é controlado via I2C, e os botões e LEDs são gerenciados por interrupções e GPIOs.

Quando um botão é pressionado, o estado do LED correspondente é alterado, e uma mensagem é exibida no display.

Se nenhuma interação ocorrer por 10 segundos, o display volta a exibir a animação inicial.

## 🔧 Configuração do Ambiente
1. Instalação do VSCode e Extensões
Instale o Visual Studio Code.

### Adicione as extensões:

C/C++: Para suporte à linguagem C.

CMake: Para gerenciamento de builds.

Pico W SDK: Para desenvolvimento específico do Raspberry Pi Pico W.

2. Configuração do Toolchain
Siga as instruções no repositório oficial do Raspberry Pi Pico SDK para configurar o ambiente de desenvolvimento.

3. Compilação e Upload
No terminal, navegue até a pasta do projeto e execute:

bash
Copy
mkdir build
cd build
cmake ..
make
Conecte o Raspberry Pi Pico W ao computador via USB.

Mantenha pressionado o botão BOOTSEL enquanto conecta o USB.

O Pico aparecerá como um dispositivo de armazenamento. Copie o arquivo .uf2 gerado para ele.

## 📂 Estrutura do Projeto
comunicacao_serial_rp2040.c: Código principal do projeto.

displayLCD.c e displayLCD.h: Controle do display LCD.

led_control.c e led_control.h: Controle dos LEDs e botões.

matrix.c e matrix.h: Controle da matriz de LEDs 5x5.

## 🎥 Demonstração

Aqui está um link para o vídeo de demonstração: https://drive.google.com/file/d/1nrVcr-9WL5xTzZIzaXSBD-NujojhHVzU/view?usp=sharing

### Inicialização:

Ao ligar o Raspberry Pi Pico W, o display exibe uma animação inicial com o texto:

Copy
CEPEDI   TIC37
EMBARCATECH
HEBERT SANTANA
Interação com Botões:

Pressione o Botão A para ligar/desligar o LED verde. O display exibirá:

Copy
LED VERDE
LIGADO/DESLIGADO
Pressione o Botão B para ligar/desligar o LED azul. O display exibirá:

Copy
LED AZUL
LIGADO/DESLIGADO
Entrada Serial:

Conecte o Pico ao computador via USB.

No terminal serial, digite um número entre 0 e 9. O número será exibido na matriz de LEDs.

### Inatividade:

Após 10 segundos sem interação, o display volta a exibir a animação inicial.

## 🛑 Limitações
O tempo de inatividade é fixo em 10 segundos. Para alterar, modifique a constante TEMPO_INATIVIDADE_MS no código.

O projeto não suporta a entrada de caracteres especiais ou letras na matriz de LEDs.

## 📝 Licença
Este projeto é open-source e está licenciado sob a MIT License.

## Como Contribuir
Se você quiser contribuir para este projeto, sinta-se à vontade para abrir issues ou pull requests no repositório.

