#include <IRremote.h>

const int RECV_PIN = 8; // Pino onde o receptor IR está conectado
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Inicializa o receptor IR
  Serial.println("IR Receiver is enabled and ready to receive signals");
}

void loop() {
  if (irrecv.decode()) {
    Serial.print("Código recebido: ");
    Serial.println(irrecv.decodedIRData.decodedRawData, HEX); // Imprime o código em hexadecimal
    irrecv.resume(); // Recebe o próximo valor
  }
}