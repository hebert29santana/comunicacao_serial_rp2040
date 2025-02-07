#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include "pico/stdlib.h"

// Definição dos pinos
#define LED_GREEN 11
#define LED_BLUE 12
#define BOTAO_A 5
#define BOTAO_B 6

// Inicializa LEDs e botões
void init_leds_buttons();

// Flags para indicar que um botão foi pressionado
extern volatile bool botao_a_pressionado;
extern volatile bool botao_b_pressionado;

// Estados dos LEDs
extern volatile bool led_green_state;
extern volatile bool led_blue_state;

// Função de interrupção para os botões
void gpio_irq_handler(uint gpio, uint32_t events);

#endif // LED_CONTROL_H
