#include <stdio.h>           // Biblioteca padrão de entrada e saída
#include "hardware/adc.h"    // Biblioteca para manipulação do ADC no RP2040
#include "hardware/pwm.h"    // Biblioteca para controle de PWM no RP2040
#include "pico/stdlib.h"     // Biblioteca padrão do Raspberry Pi Pico
#include "pico/wifi.h"       // Biblioteca para manipulação do WiFi no Pico
#include "secret.h"          // Arquivo com credenciais de rede e HTML do dashboard

// Definição dos pinos usados para o joystick e LEDs
const int VRX = 26;          // Pino de leitura do eixo X do joystick (conectado ao ADC)
const int VRY = 27;          // Pino de leitura do eixo Y do joystick (conectado ao ADC)
const int ADC_CHANNEL_0 = 0; // Canal ADC para o eixo X do joystick
const int ADC_CHANNEL_1 = 1; // Canal ADC para o eixo Y do joystick
const int SW = 22;           // Pino de leitura do botão do joystick

const int LED_B = 13;                    // Pino para controle do LED azul via PWM
const int LED_R = 11;                    // Pino para controle do LED vermelho via PWM
const float DIVIDER_PWM = 16.0;          // Divisor fracional do clock para o PWM
const uint16_t PERIOD = 4096;            // Período do PWM (valor máximo do contador)
uint16_t led_b_level, led_r_level = 100; // Inicialização dos níveis de PWM para os LEDs
uint slice_led_b, slice_led_r;           // Variáveis para armazenar os slices de PWM correspondentes aos LEDs

// Variável para armazenar a corrente simulada
float current = 0.0f;

// Defina a URL do servidor aqui
#define SERVER_URL "http://api.thingspeak.com/update?api_key=JH6GLMAQVDI5NC1Z&field1="

// Função para configurar o joystick (pinos de leitura e ADC)
void setup_joystick()
{
    adc_init();         // Inicializa o módulo ADC
    adc_gpio_init(VRX); // Configura o pino VRX (eixo X) para entrada ADC
    adc_gpio_init(VRY); // Configura o pino VRY (eixo Y) para entrada ADC
    gpio_init(SW);      // Inicializa o pino do botão
    gpio_set_dir(SW, GPIO_IN); // Configura o pino do botão como entrada
    gpio_pull_up(SW);          // Ativa o pull-up no pino do botão
}

// Função para configurar o PWM de um LED (genérica para azul e vermelho)
void setup_pwm_led(uint led, uint *slice, uint16_t level)
{
    gpio_set_function(led, GPIO_FUNC_PWM); // Configura o pino do LED como saída PWM
    *slice = pwm_gpio_to_slice_num(led);   // Obtém o slice do PWM associado ao pino do LED
    pwm_set_clkdiv(*slice, DIVIDER_PWM);   // Define o divisor de clock do PWM
    pwm_set_wrap(*slice, PERIOD);          // Configura o valor máximo do contador (período do PWM)
    pwm_set_gpio_level(led, level);        // Define o nível inicial do PWM para o LED
    pwm_set_enabled(*slice, true);         // Habilita o PWM no slice correspondente ao LED
}

// Função para configurar o WiFi
void setup_wifi()
{
    if (wifi_init()) {
        printf("WiFi inicializado com sucesso.\n");
    } else {
        printf("Falha ao inicializar o WiFi.\n");
        return;
    }

    if (wifi_connect(ssid, password)) {
        printf("Conectado à rede WiFi: %s\n", ssid);
    } else {
        printf("Falha ao conectar-se à rede WiFi.\n");
    }
}

// Função para enviar os dados para o ThingSpeak
void send_to_thingspeak(float current)
{
    // Formata a URL para enviar os dados para o ThingSpeak
    char url[256];
    snprintf(url, sizeof(url), "%s%f", SERVER_URL, current);

    // Envia os dados via HTTP GET
    printf("Enviando dados para o ThingSpeak: %s\n", url);
    wifi_http_get(url); // Função fictícia para enviar a requisição GET. Substitua por sua implementação de HTTP.
}

// Função de configuração geral
void setup()
{
    stdio_init_all();
    setup_joystick();
    setup_pwm_led(LED_B, &slice_led_b, led_b_level);
    setup_pwm_led(LED_R, &slice_led_r, led_r_level);
    setup_wifi();
}

// Função para ler os valores dos eixos do joystick (X e Y)
void joystick_read_axis(uint16_t *vrx_value, uint16_t *vry_value)
{
    adc_select_input(ADC_CHANNEL_0);
    sleep_us(2);
    *vrx_value = adc_read();

    adc_select_input(ADC_CHANNEL_1);
    sleep_us(2);
    *vry_value = adc_read();
}

// Função para simular a leitura do sensor de corrente com base no joystick
float read_current_simulation(uint16_t vrx_value)
{
    current = (vrx_value / 4095.0) * 5.0; // Corrente simulada entre 0 e 5A
    return current;
}

// Função principal
int main()
{
    uint16_t vrx_value, vry_value;
    setup();
    printf("Joystick-PWM com WiFi e Envio para ThingSpeak\n");

    while (1)
    {
        joystick_read_axis(&vrx_value, &vry_value);
        pwm_set_gpio_level(LED_B, vrx_value);
        pwm_set_gpio_level(LED_R, vry_value);
        
        // Simula a leitura da corrente
        read_current_simulation(vrx_value);

        // Envia a corrente para o ThingSpeak
        send_to_thingspeak(current);

        printf("Corrente simulada: %.2f A\n", current);

        sleep_ms(100);
    }
}
