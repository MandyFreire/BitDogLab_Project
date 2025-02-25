#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "secrets.h"  // Arquivo com as credenciais e servidor

#define JOYSTICK_X 34  // Pino do eixo X do joystick

// Função para ler a corrente simulada do joystick
float lerCorrente() {
    int leituraADC = analogRead(JOYSTICK_X);  // Lê o valor do joystick
    float corrente = (leituraADC / 4095.0) * 30;  // Simula corrente entre 0-30A
    return corrente;
}

void setup() {
    Serial.begin(115200);
    
    // Conectar ao Wi-Fi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando ao Wi-Fi...");
    }
    Serial.println("Wi-Fi conectado!");
}

void loop() {
    // Chama a função para ler a corrente
    float corrente = lerCorrente();
    
    // Exibe a corrente simulada
    Serial.printf("Corrente Simulada: %.2f A\n", corrente);

    // Enviar os dados para o servidor
    HTTPClient http;
    String url = String(SERVER_URL) + String(corrente);
    http.begin(url);
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
        Serial.printf("Dados enviados com sucesso! Código: %d\n", httpResponseCode);
    } else {
        Serial.printf("Erro ao enviar dados: %d\n", httpResponseCode);
    }
    
    http.end();
    
    delay(5000);  // Atualiza a cada 5 segundos
}