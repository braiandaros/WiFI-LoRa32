#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definições dos pinos do LoRa para a Heltec V2
#define LORA_SS 18
#define LORA_RST 14
#define LORA_DIO0 26

// Definições do Display OLED
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // --- RESET MANUAL DO OLED (Crucial para a Heltec V2) ---
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(50);
  digitalWrite(OLED_RST, HIGH);
  delay(50);
  // -------------------------------------------------------

  // Inicializa o Display
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) {
    Serial.println(F("Falha na inicialização do OLED"));
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Receptor LoRa...");
  display.display();

  // Configura os pinos do módulo LoRa
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  // Inicia o rádio na exata mesma frequência do Transmissor
  if (!LoRa.begin(915E6)) {
    Serial.println("Falha ao iniciar o modulo LoRa!");
    display.setCursor(0, 10);
    display.print("Erro no LoRa!");
    display.display();
    while (1);
  }

  Serial.println("Receptor Iniciado e Aguardando!");
  display.setCursor(0, 10);
  display.print("Aguardando dados...");
  display.display();
}

void loop() {
  // Verifica se chegou algum pacote na frequência de 915 MHz
  int packetSize = LoRa.parsePacket();
  
  // Se "packetSize" for maior que 0, significa que recebemos algo
  if (packetSize) {
    String pacoteRecebido = "";
    
    // Lê os caracteres recebidos e monta a String
    while (LoRa.available()) {
      pacoteRecebido += (char)LoRa.read();
    }

    // Lê a força do sinal (RSSI - Received Signal Strength Indicator)
    // Quanto mais próximo de 0 (ex: -40), mais forte. Quanto mais negativo (ex: -120), mais fraco.
    int rssi = LoRa.packetRssi();

    // Mostra no Monitor Serial do PC
    Serial.print("Recebido: ");
    Serial.print(pacoteRecebido);
    Serial.print(" | RSSI: ");
    Serial.println(rssi);

    // Atualiza o Display OLED com os dados fresquinhos
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("PACOTE RECEBIDO!");
    
    // Mostra a string que foi montada pelo transmissor
    display.setCursor(0, 20);
    display.println(pacoteRecebido);
    
    // Mostra a força do sinal
    display.setCursor(0, 45);
    display.print("Sinal (RSSI): ");
    display.print(rssi);
    display.display();
  }
}