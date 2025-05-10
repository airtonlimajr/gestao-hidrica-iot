# IoT - Monitoramento do Nível de Água em Reservatórios e Poços

Protótipo de baixo custo e fácil implementação para monitoramento remoto do nível de água, utilizando microcontrolador ESP32, sensor ultrassônico HC-SR04, display LCD I2C e comunicação via protocolo MQTT. O projeto visa contribuir para a eficiência hídrica e gestão sustentável dos recursos, prevenindo desperdícios e antecipando situações críticas.

---

## 📌 1. Descrição do Funcionamento e Uso

O sistema mede continuamente a distância entre o sensor ultrassônico e a superfície da água. Esses dados são processados pelo ESP32 e exibidos em um display LCD 16x2. Simultaneamente, os valores são enviados a um broker MQTT via conexão Wi-Fi, permitindo o monitoramento remoto em tempo real por meio de ferramentas como o WebSocket Client da HiveMQ.

### Como Reproduzir
1. Monte os componentes conforme o esquema elétrico (disponível em `/docs/esquemas/`).
2. Carregue o código presente em `src/main.ino` usando a Arduino IDE.
3. Conecte-se à rede Wi-Fi configurada no código.
4. Acesse o WebSocket Client e inscreva-se no tópico `nivel_agua` para visualizar os dados.

---

## 💻 2. Software Desenvolvido e Documentação de Código

O código-fonte está na pasta `/src`. Os principais arquivos incluem:

- `main.ino`: código principal que integra leitura do sensor, exibição no LCD e envio via MQTT.
- `config.h`: arquivo com parâmetros de configuração da rede Wi-Fi, broker MQTT e tópicos.
- Bibliotecas utilizadas:
  - `WiFi.h` – conexão à rede sem fio
  - `PubSubClient.h` – cliente MQTT
  - `LiquidCrystal_I2C.h` – controle do LCD via I2C
  - `Wire.h` – comunicação I2C

O código é modular e bem comentado, permitindo fácil adaptação para outros contextos.

---

## 🔧 3. Hardware Utilizado

| Componente             | Modelo                  | Função                                   |
|------------------------|-------------------------|------------------------------------------|
| Microcontrolador       | ESP32 DevKit V1         | Processamento e comunicação Wi-Fi        |
| Sensor de Distância    | HC-SR04                 | Medição da distância até a água          |
| Display LCD            | LCD 16x2 com módulo I2C | Exibição local dos dados                 |
| Protoboard / Fios      | Diversos                | Montagem do circuito                     |
| Fonte de Alimentação   | 5V (USB ou bateria)     | Alimentação do sistema                   |
---

## 🌐 4. Interfaces, Protocolos e Módulos de Comunicação

### Comunicação Serial:
- **I2C**: utilizada para conexão entre o ESP32 e o display LCD, nos pinos GPIO 21 (SDA) e GPIO 22 (SCL).

### Comunicação com a Internet:
- **Wi-Fi**: conexão do ESP32 à internet via rede local configurada no código.
- **MQTT**: protocolo leve utilizado para envio dos dados ao broker.

### Protocolo MQTT:
- Broker público utilizado: `broker.hivemq.com`
- Porta: `1883` (TCP) ou `8884` (WebSocket)
- Tópico publicado: `nivel_agua`

### Interface de Monitoramento:
- Ferramenta: [WebSocket Client - HiveMQ](https://www.hivemq.com/demos/websocket-client/)
- Basta inserir o broker e o tópico para visualizar os dados em tempo real.

---

## 🌎 5. Conectividade via TCP/IP e MQTT

O projeto cumpre os requisitos de comunicação via rede TCP/IP com envio contínuo de dados utilizando o protocolo MQTT. Essa arquitetura permite integração com aplicações em nuvem, dashboards remotos ou sistemas de alarme em tempo real.

---

## 📷 Capturas e Esquemas

Imagens, esquemas de ligação e capturas da interface estão disponíveis na pasta `/docs`.

---

## 📚 Referências

- [HiveMQ - MQTT WebSocket Client](https://www.hivemq.com/demos/websocket-client/)
- [Last Minute Engineers - HC-SR04](https://lastminuteengineers.com/arduino-sr04-ultrasonic-sensor-tutorial)
- [CircuitState - ESP32 DevKit V1](https://www.circuitstate.com/pinouts/doit-esp32-devkit-v1-wifi-development-board-pinout-diagram-and-reference)
- [Docs Wokwi - LCD I2C](https://docs.wokwi.com/pt-BR/parts/wokwi-lcd1602)

---

## ⚠️ Licença

Este projeto está sob a licença MIT. Consulte o arquivo `LICENSE` para mais detalhes.
