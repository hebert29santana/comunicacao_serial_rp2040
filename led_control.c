#include "led_control.h"
#include "hardware/gpio.h"
#include <stdio.h>
//#include "displayLCD.h"
//#include "ssd1306.h"

// Variáveis de debounce
volatile uint32_t last_time_a = 0;
volatile uint32_t last_time_b = 0;
#define DEBOUNCE_DELAY 200 // 200ms para evitar acionamento duplo

// Flags para indicar que um botão foi pressionado
volatile bool botao_a_pressionado = false;
volatile bool botao_b_pressionado = false;

volatile bool led_green_state = false;
volatile bool led_blue_state = false;

// Inicializa LEDs e botões
void init_leds_buttons() {
    // Inicializa os LEDs como saída
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);

    // Desliga todos os LEDs no início
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_BLUE, 0);
    printf("Sistema iniciado. Todos os LEDs OFF\n");

    // Inicializa os botões como entrada com pull-up
    gpio_init(BOTAO_A);
    gpio_init(BOTAO_B);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_set_dir(BOTAO_B, GPIO_IN);
    gpio_pull_up(BOTAO_A);
    gpio_pull_up(BOTAO_B);

    // Configura a interrupção compartilhada para os botões
    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BOTAO_B, GPIO_IRQ_EDGE_FALL, true, gpio_irq_handler);
}

// Função de interrupção para os botões
void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    if (gpio == BOTAO_A) {
        if (current_time - last_time_a > DEBOUNCE_DELAY) {
            botao_a_pressionado = true; // Sinaliza que o botão A foi pressionado
            last_time_a = current_time;
        }
    } else if (gpio == BOTAO_B) {
        if (current_time - last_time_b > DEBOUNCE_DELAY) {
            botao_b_pressionado = true; // Sinaliza que o botão B foi pressionado
            last_time_b = current_time;
        }
    }
}