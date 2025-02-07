/*
    Hebert Costa Vaz Santana
    TIC370101235
    Grupo 7
*/

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "font.h"
#include "led_control.h"
#include "matrix.h"
#include "displayLCD.h"

// Informações dos Pinos dos LEDs
#define led_pin_g 11
#define led_pin_b 12
#define led_pin_r 13

// Variável global para o display
ssd1306_t ssd;

// Variável para armazenar o tempo da última interação
absolute_time_t ultima_interacao;

// Tempo de inatividade em milissegundos (10 segundos)
// Usado para voltar a animação que está na função exibir_animacao_inicial
#define TEMPO_INATIVIDADE_MS 10000

// Função para exibir a animação inicial
void exibir_animacao_inicial(ssd1306_t *ssd, bool cor) {
    ssd1306_fill(ssd, !cor); // Limpa o display
    ssd1306_rect(ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
    ssd1306_draw_string(ssd, "CEPEDI   TIC37", 8, 10); // Desenha uma string
    ssd1306_draw_string(ssd, "EMBARCATECH", 20, 30); // Desenha uma string
    ssd1306_draw_string(ssd, "HEBERT SANTANA", 8, 48); // Desenha uma string
    ssd1306_send_data(ssd); // Atualiza o display
}

int main()
{
    stdio_init_all(); // Inicializa comunicação USB CDC para monitor serial

    npInit(LED_PIN); // Inicializa a Matriz de LEDs 5x5
    npClear();

    // Inicializa o display
    ssd1306_t ssd;
    init_display(&ssd);

    init_leds_buttons(); // Inicializa os LEDs e os Botões
      
    // Configura os pinos dos LEDs como saída
    gpio_init(led_pin_r);
    gpio_set_dir(led_pin_r, GPIO_OUT);
    gpio_put(led_pin_r, 0); // Inicialmente desligado

    gpio_init(led_pin_g);
    gpio_set_dir(led_pin_g, GPIO_OUT);
    gpio_put(led_pin_g, 0); // Inicialmente desligado

    gpio_init(led_pin_b);
    gpio_set_dir(led_pin_b, GPIO_OUT);
    gpio_put(led_pin_b, 0); // Inicialmente desligado

    bool cor = true;
    exibir_animacao_inicial(&ssd, cor);

    // Inicializa o tempo da última interação
    ultima_interacao = get_absolute_time();
/*
    // Atualiza o conteúdo do display com animações
    ssd1306_fill(&ssd, !cor); // Limpa o display
    ssd1306_rect(&ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
    ssd1306_draw_string(&ssd, "CEPEDI   TIC37", 8, 10); // Desenha uma string
    ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 30); // Desenha uma string
    ssd1306_draw_string(&ssd, "HEBERT SANTANA", 8, 48); // Desenha uma string      
    ssd1306_send_data(&ssd); // Atualiza o display
*/
    sleep_ms(1000);

    while (true)
    {   
        // Verifica se o botão A foi pressionado
        if (botao_a_pressionado) {
            botao_a_pressionado = false; // Reseta a flag

            // Atualiza o tempo da última interação
            ultima_interacao = get_absolute_time();

            if (led_green_state) {
                npClear(); // Desliga a Matriz de LED para não ficar feio

                gpio_put(LED_GREEN, 0); // Desliga o LED verde
                printf("LED VERDE OFF\n");
                display_message(&ssd, "LED VERDE", "DESLIGADO"); // Exibe no display
                led_green_state = false;
            } else {
                npClear(); // Desliga a Matriz de LED para não ficar feio

                gpio_put(LED_GREEN, 1); // Liga o LED verde
                gpio_put(LED_BLUE, 0);  // Desliga o LED azul
                printf("LED VERDE ON\n");
                // printf("LED AZUL OFF\n");
                display_message(&ssd, "LED VERDE", "LIGADO"); // Exibe no display
                led_green_state = true;
                led_blue_state = false;
            }
        }

        // Verifica se o botão B foi pressionado
        if (botao_b_pressionado) {
            botao_b_pressionado = false; // Reseta a flag

            // Atualiza o tempo da última interação
            ultima_interacao = get_absolute_time();

            if (led_blue_state) {
                npClear(); // Desliga a Matriz de LED para não ficar feio

                gpio_put(LED_BLUE, 0); // Desliga o LED azul
                printf("LED AZUL OFF\n");
                display_message(&ssd, "LED AZUL", "DESLIGADO"); // Exibe no display
                led_blue_state = false;
            } else {
                npClear(); // Desliga a Matriz de LED para não ficar feio

                gpio_put(LED_BLUE, 1);  // Liga o LED azul
                gpio_put(LED_GREEN, 0); // Desliga o LED verde
                printf("LED AZUL ON\n");
                // printf("LED VERDE OFF\n");
                display_message(&ssd, "LED AZUL", "LIGADO"); // Exibe no display
                led_blue_state = true;
                led_green_state = false;
            }
        }
        
        cor = !cor;
        if (stdio_usb_connected())
        {   
            
            // Certifica-se de que o USB está conectado
            // Captura caractere do teclado sem bloquear a execução
            int ch = getchar_timeout_us(0);
            if (ch != PICO_ERROR_TIMEOUT)
            {
                char c = (char)ch;
                char message[2] = {c, '\0'};
                display_message(&ssd, "Caracter", message); // Exibe no display
                printf("Caracter digitado: %c\n", c);        // Exibe no terminal

                // Verifica se o caractere é um número entre 0 e 9
                if (c >= '0' && c <= '9')
                {
                    // Atualiza o tempo da última interação
                    ultima_interacao = get_absolute_time();

                    int number = c - '0';
                    // printf("NÚMERO %d RECEBIDO\n", number);
                    displayNumber(number);
                }
            }        
        }

        // Verifica se o tempo de inatividade foi atingido
        absolute_time_t agora = get_absolute_time();
        if (absolute_time_diff_us(ultima_interacao, agora) >= TEMPO_INATIVIDADE_MS * 1000) {
            // Exibe a animação inicial
            exibir_animacao_inicial(&ssd, cor);
            // Atualiza o tempo da última interação para evitar repetição
            ultima_interacao = get_absolute_time();
            npClear(); // Desliga a Matriz de LED para não ficar feio
        }

        sleep_ms(40);
    }
    return 0;
}