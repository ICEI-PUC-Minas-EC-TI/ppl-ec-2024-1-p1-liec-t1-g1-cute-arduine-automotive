#include <IRremote.hpp>

int RECV_PIN = 8;
unsigned long armazenavalor;
bool turboMode = false; // Variável para controlar o modo turbo

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
int IN1 = 7;
int IN2 = 6;
int IN3 = 4;
int IN4 = 2;

// Definição pinos faróis
int farolRe_1 = A4;
int farolRe_2 = A5;

// Definição pino buzina
int buzzerPin = 12;

void setup() {
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

  Serial.begin(9600);
  Serial.println("Arduino está pronto");

  irrecv.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (irrecv.decode()) {
    armazenavalor = irrecv.decodedIRData.decodedRawData;
    Serial.print("Valor lido: ");
    Serial.println(armazenavalor, HEX);

    irrecv.resume();

    parar();

    if (armazenavalor == 0xE718FF00) { // Move para frente
      paraFrente(turboMode ? 255 : 128); // Aumenta a velocidade no modo turbo
    } else if (armazenavalor == 0xAD52FF00) { // Move para trás
      paraTras(turboMode ? 255 : 128); // Aumenta a velocidade no modo turbo
      digitalWrite(farolRe_1, LOW);
      digitalWrite(farolRe_2, LOW);
    } else if (armazenavalor == 0xA55AFF00) { // Gira para a direita
      girarDireita(turboMode ? 255 : 128, 1000);
    } else if (armazenavalor == 0xF708FF00) { // Gira para a esquerda
      girarEsquerda(turboMode ? 255 : 128, 1000);
    } else if (armazenavalor == 0xE916FF00) { // Botão música
      tocarMusica();
    } else if (armazenavalor == 0xE619FF00) { // Botão parada
      parar();
    } else if (armazenavalor == 0xF20DFF00) { // Novo botão para modo turbo
      turboMode = !turboMode; // Alterna o estado do modo turbo
      Serial.print("Modo turbo: ");
      Serial.println(turboMode ? "Ativado" : "Desativado");
    }
  }
}

void parar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(100);
}

void paraFrente(int velocidade) {
  parar();
  delay(100);

  analogWrite(IN1, velocidade);
  digitalWrite(IN2, LOW);
  analogWrite(IN3, velocidade);
  digitalWrite(IN4, LOW);

  unsigned long startTime = millis();
  while (millis() - startTime < 5000) {
    distanciaFrente();
    if (distanceCm < 20) {
      parar();
      break;
    }
    delay(100);
  }
}

void paraTras(int velocidade) {
  parar();
  delay(100);

  digitalWrite(farolRe_1, HIGH);
  digitalWrite(farolRe_2, HIGH);

  digitalWrite(IN1, LOW);
  analogWrite(IN2, velocidade);
  digitalWrite(IN3, LOW);
  analogWrite(IN4, velocidade);

  unsigned long startTime = millis();
  while (millis() - startTime < 5000) {
    distanciaRe();
    if (distanceCm < 20) {
      parar();
      break;
    }
    delay(100);
  }

  delay(100);
  parar();
}

void distanciaRe() {
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
  delay(100);

  playTone(415, 234);
  playTone(330, 212);
  playTone(415, 234);
  playTone(554, 234);
  playTone(440, 830);

  playTone(370, 234);
  playTone(311, 234);
  playTone(370, 234);
  playTone(494, 234);
  playTone(415, 472);
  playTone(370, 230);
  playTone(330, 720);

  playTone(330, 234);
  playTone(277, 234);
  playTone(370, 472);
  playTone(277, 900);
  playTone(370, 280);
  playTone(330, 230);
  playTone(415, 440);
  playTone(370, 400);

  playTone(415, 210);
  playTone(330, 224);
  playTone(415, 234);
  playTone(554, 234);
  playTone(440, 850);

  playTone(370, 250);
  playTone(311, 234);
  playTone(370, 222);
  playTone(494, 234);
  playTone(415, 472);
  playTone(370, 224);
  playTone(330, 800);

  delay(100);
}

void playTone(int frequency, int duration) {
  tone(buzzerPin, frequency);
  delay(duration);
  noTone(buzzerPin);
  delay(50);
}

void girarDireita(int velocidade, int duracao) {
  parar();
  delay(100);

  analogWrite(IN1, velocidade);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  analogWrite(IN4, velocidade);

  delay(duracao);
  parar();
}

void girarEsquerda(int velocidade, int duracao) {
  parar();
  delay(100);

  digitalWrite(IN1, LOW);
  analogWrite(IN2, velocidade);
  analogWrite(IN3, velocidade);
  digitalWrite(IN4, LOW);

  delay(duracao);
  parar();
}