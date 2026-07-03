#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definições dos pinos do LoRa para a Heltec V2
#define LORA_SS 18
#define LORA_RST 14
#define LORA_DIO0 26

// Definições do Display OLED (Pinos I2C da Heltec)
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

int contadorPacotes = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);


  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(50);
  digitalWrite(OLED_RST, HIGH);
  delay(50);

  
  // Inicializa os pinos do OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) {
    Serial.println(F("Falha na inicialização do OLED"));
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Iniciando LoRa...");
  display.display();

  // Configura os pinos do módulo LoRa
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  // Inicializa o rádio na frequência do Brasil (915 MHz)
  if (!LoRa.begin(915E6)) {
    Serial.println("Falha ao iniciar o modulo LoRa!");
    display.setCursor(0, 10);
    display.print("Erro no LoRa!");
    display.display();
    while (1);
  }
  
  // Opcional: Ajustar a potência de transmissão (padrão é 17)
  LoRa.setTxPower(20); 

  Serial.println("LoRa Iniciado com Sucesso!");
  display.setCursor(0, 10);
  display.print("LoRa OK - 915MHz");
  display.display();
  delay(2000);
}

void loop() {
  // Simulando a leitura de um sensor ambiental
  float temperatura = 24.5 + random(0, 5); 
  float umidade = 60.0 + random(0, 10);

  Serial.print("Enviando pacote: ");
  Serial.println(contadorPacotes);

  // Inicia a construção do pacote LoRa
  LoRa.beginPacket();
  LoRa.print("ID:");
  LoRa.print(contadorPacotes);
  LoRa.print("|Temp:");
  LoRa.print(temperatura);
  LoRa.print("|Umid:");
  LoRa.print(umidade);
  LoRa.endPacket();

  // Atualiza o Display OLED para acompanhamento visual
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("TRANSMITINDO...");
  display.setCursor(0, 20);
  display.print("Pacote: ");
  display.println(contadorPacotes);
  display.setCursor(0, 40);
  display.print("T: "); display.print(temperatura); display.print("C  U: "); display.print(umidade); display.print("%");
  display.display();

  contadorPacotes++;
  
  // Aguarda 5 segundos antes de enviar o próximo pacote
  delay(5000);
}