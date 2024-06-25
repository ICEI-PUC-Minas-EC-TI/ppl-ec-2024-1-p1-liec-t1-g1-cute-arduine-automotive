#include <SoftwareSerial.h>

// Definindo os pinos RX e TX para comunicação Bluetooth
#define RX_PIN 10
#define TX_PIN 11

// Criando uma instância da classe SoftwareSerial
SoftwareSerial bluetoothSerial(RX_PIN, TX_PIN);

void setup() {
    // Iniciando a comunicação serial com o computador
    Serial.begin(9600);

    // Iniciando a comunicação serial com o módulo Bluetooth
    bluetoothSerial.begin(9600);

    // Esperando até que a serial esteja disponível
    while (!Serial) {
        ; // Esperando pela inicialização da serial
    }

    Serial.println("Bluetooth Teste Iniciado");
}

void loop() {
    // Enviando comando AT para o módulo Bluetooth
    bluetoothSerial.println("AT");

    // Esperando a resposta do módulo Bluetooth
    if (bluetoothSerial.available()) {
        String response = bluetoothSerial.readString();
        Serial.print("Resposta do Bluetooth: ");
        Serial.println(response);
    }

    // Se receber dados do serial monitor do computador, enviar para o Bluetooth
    if (Serial.available()) {
        char data = Serial.read();
        bluetoothSerial.write(data);
    }

    delay(1000); // Atraso de 1 segundo entre as leituras
}
