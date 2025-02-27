#include <stdio.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_http_client.h"
#include "driver/adc.h"
#include "secrets.h"  // Arquivo com credenciais Wi-Fi

#define JOYSTICK_X ADC1_CHANNEL_6  // GPIO 34 para ADC1
#define TAG "ESP32_SENSOR"

// 🛠 Função para inicializar Wi-Fi no modo STA
static void wifi_init(void) {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_config_t wifi_config;
    memset(&wifi_config, 0, sizeof(wifi_config));
    memcpy(wifi_config.sta.ssid, WIFI_SSID, sizeof(WIFI_SSID));
    memcpy(wifi_config.sta.password, WIFI_PASSWORD, sizeof(WIFI_PASSWORD));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "Conectando ao Wi-Fi...");
    while (esp_wifi_connect() != ESP_OK) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        ESP_LOGI(TAG, "Tentando reconectar...");
    }

    ESP_LOGI(TAG, "Wi-Fi conectado!");
}

// 🛠 Função para ler corrente do joystick (ADC)
float ler_corrente() {
    int leituraADC = adc1_get_raw(JOYSTICK_X);
    float corrente = (leituraADC / 4095.0) * 30;  // Simula corrente de 0 a 30A
    return corrente;
}

// 🛠 Função para enviar dados ao ThingSpeak
static void enviar_dados(float corrente) {
    char url[128];
    snprintf(url, sizeof(url), "%s%.2f", SERVER_URL, corrente);
    
    esp_http_client_config_t config = {
        .url = url,
        .method = HTTP_METHOD_GET
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK) {
        ESP_LOGI(TAG, "Dados enviados com sucesso!");
    } else {
        ESP_LOGE(TAG, "Erro ao enviar dados: %s", esp_err_to_name(err));
    }

    esp_http_client_cleanup(client);
}

// 🛠 Função principal
void app_main(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Inicializa Wi-Fi
    wifi_init();

    // Configura ADC para leitura do joystick
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(JOYSTICK_X, ADC_ATTEN_DB_12); 

    while (1) {
        float corrente = ler_corrente();
        ESP_LOGI(TAG, "Corrente Simulada: %.2f A", corrente);
        enviar_dados(corrente);
        vTaskDelay(pdMS_TO_TICKS(5000));  // Aguarda 5 segundos antes do próximo envio
    }
}
