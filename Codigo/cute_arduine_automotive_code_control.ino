#include <IRremote.hpp>

int RECV_PIN = 8;
unsigned long armazenavalor;  // Alterado para unsigned long

IRrecv irrecv(RECV_PIN);
decode_results results;

// Definição pinos sensor distância
const int pinEcho = 11;
const int pinTrig = 10;
#define SOUND_SPEED 0.034
const int pinEcho2 = A2;
const int pinTrig2 = A1;

long duration;
float distanceCm;

// Definição pinos motores
int IN1 = 7;   // out1
int IN2 = 6;   // out2
int IN3 = 4;   // out3
int IN4 = 2;   // out4

// Definição pinos faróis
int farolRe_1 = A4;
int farolRe_2 = A5;

// Definição pino buzina
int buzzerPin = 12;
const float songSpeed = 1.0;

void setup() {
  // Define os pinos como saída
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(pinTrig2, OUTPUT);
  pinMode(pinEcho2, INPUT);
  pinMode(farolRe_1, OUTPUT);
  pinMode(farolRe_2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600); // Inicializa a comunicação serial com o monitor serial

  Serial.println("Arduino está pronto");

  irrecv.begin(RECV_PIN, ENABLE_LED_FEEDBACK); // Inicializa o receptor IR com LED de feedback habilitado
}

void loop() {
  if (irrecv.decode()) {
    armazenavalor = irrecv.decodedIRData.decodedRawData;
    Serial.print("Valor lido: ");
    Serial.println(armazenavalor, HEX); // Imprime o código em hexadecimal

    irrecv.resume();

    // Para todos os motores inicialmente
    parar();

    // Move para frente
    if (armazenavalor == 0xE718FF00) {
      paraFrente(128);
    }
    // Move para trás
    else if (armazenavalor == 0xAD52FF00) {
      paraTras(128);
      digitalWrite(farolRe_1, LOW);
      digitalWrite(farolRe_2, LOW);
    }
    // Gira para a direita
    else if (armazenavalor == 0xA55AFF00) {
      girarDireita(128, 1000);
    }
    // Gira para a esquerda
    else if (armazenavalor == 0xF708FF00) {
      girarEsquerda(128, 1000);
    }
    // Botão música
    else if (armazenavalor == 0xE916FF00) {
      tocarMusica();
    }
    // Botão parada
    else if (armazenavalor == 0xE619FF00) {
      parar();
    }
  }
}

void parar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(100); // Atraso para garantir que os motores parem completamente
}

void paraFrente(int velocidade) {
  parar();
  delay(100); // Pequeno atraso antes de iniciar o movimento

  // Lado A (motor direito)
  analogWrite(IN1, velocidade);
  digitalWrite(IN2, LOW);

  // Lado B (motor esquerdo)
  analogWrite(IN3, velocidade);
  digitalWrite(IN4, LOW);

  while (true) {
    distanciaFrente();
    if (distanceCm < 20) {
      parar();
      break;
    }
  }
}

void paraTras(int velocidade) {
  parar();
  delay(100); // Pequeno atraso antes de iniciar o movimento

  digitalWrite(farolRe_1, HIGH);
  digitalWrite(farolRe_2, HIGH);

  // Lado A (motor direito)
  digitalWrite(IN1, LOW);
  analogWrite(IN2, velocidade);

  // Lado B (motor esquerdo)
  digitalWrite(IN3, LOW);
  analogWrite(IN4, velocidade);

  for (int i = 10; i > 0; i--) {
    distanciaRe();
    if (distanceCm < 20) {
      parar();
      break;
    }
  }

  delay(100); // Atraso após o movimento
  parar();
}

void distanciaRe() {
  // Sensor Distância
  delay(200);
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  duration = pulseIn(pinEcho, HIGH);
  distanceCm = duration * SOUND_SPEED / 2;
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  delay(50);
}

void distanciaFrente() {
  // Sensor Distância
  delay(200);
  digitalWrite(pinTrig2, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig2, LOW);
  duration = pulseIn(pinEcho2, HIGH);
  distanceCm = duration * SOUND_SPEED / 2;
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  delay(50);
}

void tocarMusica() {
  parar();
  delay(100); // Pequeno atraso antes de iniciar a música

  // I'm a Barbie Girl
  playTone(415, 234);
  playTone(330, 212);
  playTone(415, 234);
  playTone(554, 234);
  playTone(440, 830);

  // In a Barbie World
  playTone(370, 234);
  playTone(311, 234);
  playTone(370, 234);
  playTone(494, 234);
  playTone(415, 472);
  playTone(370, 230);
  playTone(330, 720);

  // Life in plastic
  playTone(330, 234);
  playTone(277, 234);
  playTone(370, 472);
  playTone(277, 900);
  playTone(370, 280);
  playTone(330, 230);
  playTone(415, 440);
  playTone(370, 400);

  // You can brush my hair
  playTone(415, 210);
  playTone(330, 224);
  playTone(415, 234);
  playTone(554, 234);
  playTone(440, 850);

  // And dress me everywhereeeeeeeee
  playTone(370, 250);
  playTone(311, 234);
  playTone(370, 222);
  playTone(494, 234);
  playTone(415, 472);
  playTone(370, 224);
  playTone(330, 800);

  delay(100); // Pequeno atraso após tocar a música
}

void playTone(int frequency, int duration) {
  tone(buzzerPin, frequency);
  delay(duration);
  noTone(buzzerPin);
  delay(50); // Pequeno atraso para separar notas
}

void girarDireita(int velocidade, int duracao) {
  parar();
  delay(100); // Pequeno atraso antes de iniciar o movimento

  // Lado A (motor direito)
  digitalWrite(IN1, LOW);
  analogWrite(IN2, velocidade);

  // Lado B (motor esquerdo)
  analogWrite(IN3, velocidade);
  digitalWrite(IN4, LOW);

  delay(duracao); // Mantém a rotação por 'duracao' milissegundos
  parar();
}

void girarEsquerda(int velocidade, int duracao) {
  parar();
  delay(100); // Pequeno atraso antes de iniciar o movimento

  // Lado A (motor direito)
  analogWrite(IN1, velocidade);
  digitalWrite(IN2, LOW);

  // Lado B (motor esquerdo)
  digitalWrite(IN3, LOW);
  analogWrite(IN4, velocidade);

  delay(duracao); // Mantém a rotação por 'duracao' milissegundos
  parar();
}