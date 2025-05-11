#include <WiFi.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h> // Biblioteca para LCD I2C
#include <Wire.h> // Biblioteca para comunicação I2C

// Definições do sensor ultrassônico
#define TRIG_PIN 2
#define ECHO_PIN 4

// Definições do LCD I2C
#define LCD_ADDRESS 0x27 // Endereço I2C do seu LCD (verifique o seu)
#define LCD_COLUMNS 16
#define LCD_ROWS 2
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

// Definições do Wi-Fi
const char* ssid = "Wokwi-GUEST";

// Definições do MQTT
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "nivel_agua";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    Serial.begin(115200);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    Wire.begin(); // Inicializa a comunicação I2C
    lcd.init(); // Inicializa o LCD
    lcd.backlight(); // Liga a luz de fundo do LCD
    lcd.print("Nivel da agua:");

    setup_wifi();
    client.setServer(mqtt_server, mqtt_port);
}

void setup_wifi() {
    delay(10);
    Serial.println();
    Serial.print("Conectando-se a ");
    Serial.println(ssid);

    WiFi.begin(ssid);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi conectado");
    Serial.println("Endereço IP: ");
    Serial.println(WiFi.localIP());
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Tentando conexão MQTT...");
        if (client.connect("ESP32Client")) {
            Serial.println("Conectado ao MQTT");
        } else {
            Serial.print("falhou, rc=");
            Serial.print(client.state());
            Serial.println(" tentando novamente em 5 segundos");
            delay(5000);
        }
    }
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    long duration, distance;
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = (duration / 2) / 29.1;

    Serial.print("Distância: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Exibe o nível no LCD I2C
    lcd.setCursor(0, 1);
    lcd.print("                "); // Limpa a linha
    lcd.setCursor(0, 1);
    lcd.print(distance);
    lcd.print(" cm");

    // Envia dados para o MQTT
    if (client.publish(mqtt_topic, String(distance).c_str())) {
        Serial.println("Mensagem MQTT publicada com sucesso!");
    } else {
        Serial.println("Falha ao publicar mensagem MQTT.");
    }

    delay(1000);
}