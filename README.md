# Sistema de Monitoramento Ambiental IoT (LoRa)

Plataforma integrada de hardware focada em pequenas propriedades de agricultura familiar para monitoramento de dados ambientais, otimização de recursos e redução de desperdícios no campo. Projeto desenvolvido com o apoio da Germinare Incubadora.

## 📡 Arquitetura de Hardware
* **Microcontrolador:** ESP32 (Heltec LoRa 32 V2)
* **Comunicação:** Rádio LoRa (Frequência: 915 MHz)
* **Display:** OLED 0.96" integrado para telemetria local

## 🚀 Estrutura do Projeto
O repositório está dividido em dois nós principais:
1. **Nó Transmissor (`/nó_transmissor`):** Responsável pela coleta de dados em campo e transmissão dos pacotes via rádio.
2. **Nó Receptor (`/nó_receptor`):** Responsável por interceptar os pacotes LoRa, extrair os dados e calcular o RSSI (qualidade do sinal) para testes de alcance.

## 🛠️ Configuração do Ambiente (Arduino IDE)
* Adicionar a URL do ESP32 no Gerenciador de Placas.
* Selecionar a placa **Heltec WiFi LoRa 32 (V2)**.
* Instalar o driver **CP2102** para comunicação Serial.
* Bibliotecas necessárias: `LoRa by Sandeep Mistry`, `Adafruit SSD1306`, `Adafruit GFX Library`.

## 📌 Próximos Passos (Roadmap)
- [x] Estabelecer comunicação ponto a ponto em 915 MHz.
- [x] Corrigir inicialização manual de hardware (OLED Reset).
- [ ] Integrar sensores reais (DHT22 / Umidade do Solo).
- [ ] Transformar o Nó Receptor em um Gateway LoRa-WiFi.
