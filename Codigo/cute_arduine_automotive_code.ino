#include <SoftwareSerial.h>

// Define os pinos para comunicação SoftwareSerial
SoftwareSerial BTSerial(8, 9); // RX, TX

//Definição pinos sensor distância
const int pinEcho = 11;
const int pinTrig = 10;
#define SOUND_SPEED 0.034

long duration;
float distanceCm;
float distancelnch;

//Definição pinos motores
int IN1 = 7;
int IN2 = 6; //Frente
int IN3 = 4; //Frente
int IN4 = 2;
int ENA = 5; // PWM para motor A
int ENB = 3; // PWM para motor B

//Definição pinos faróis
int farolRe_1 = A4;
int farolRe_2 = A5;

//Definição pino buzina
int buzzerPin = 12;
const float songSpeed = 1.0;

void setup() {
  // Define os pinos como saída
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(farolRe_1, OUTPUT);
  pinMode(farolRe_2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  BTSerial.begin("CARRINHO S2");
  Serial.println("Arduino está pronto");
  BTSerial.begin(9600);
}

void loop() {

  if (BTSerial.available() > 0) {
    int n = (int)BTSerial.read();

    Serial.print("Received: ");
    Serial.println(n);

    // Para todos os motores inicialmente
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

    // Move para frente com velocidade controlada
    if (n == 3) {
      paraFrente(128); // Velocidade média
    }
    // Move para trás com velocidade controlada
    else if (n == 4) {
      paraTras(128); // Velocidade média
      digitalWrite(farolRe_1, LOW);
      digitalWrite(farolRe_2, LOW);
    }
    // Gira para a direita
    else if (n == 5) {
      parar();
      // Lado A
      analogWrite(ENA, 128); // Velocidade média
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      // Lado B
      analogWrite(ENB, 128); // Velocidade média
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      delay(500);
      parar();
    }
    // Gira para a esquerda
    else if (n == 6) {
      parar();
      // Lado A
      analogWrite(ENA, 128); // Velocidade média
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      // Lado B
      analogWrite(ENB, 128); // Velocidade média
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      delay(500);
      parar();
    }
    //Precionando botão frente por mais tempo
    else if (n == 9) {
      modoTurbo(255);
    }
    // Botão música
    else if (n == 8) {
      tocarMusica();
    }
    // Botão parada
    else if (n == 7) {
      parar();
    }
  }
}


void parar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(1);
}

void paraFrente(int velocidade) {
  parar();
  // Lado A
  analogWrite(ENA, velocidade);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // Lado B
  analogWrite(ENB, velocidade);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(1);
}

void paraTras(int velocidade) {
  parar();
  digitalWrite(farolRe_1, HIGH);
  digitalWrite(farolRe_2, HIGH);
  // Lado A
  analogWrite(ENA, velocidade);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Lado B
  analogWrite(ENB, velocidade);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  for (int i = 10; i > 0; i--) {
    distanciaRe();
  }

  delay(1);
  parar();
}

void distanciaRe () {
  //Sensor Distância
  delay(200);
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  duration = pulseIn(pinEcho, HIGH);
  distanceCm = duration * SOUND_SPEED/2;
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  delay(50);
  
    if(distanceCm < 30) {
      parar ();
    }
}

void tocarMusica() {
  parar();
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

  delay(1);
}

void playTone(int frequency, int duration) {
  tone(buzzerPin, frequency);
  delay(duration);
  noTone(buzzerPin);
  delay(50); // Small delay to separate notes
}

void modoTurbo (int velocidade) {
  parar();
  // Lado A
  analogWrite(ENA, velocidade);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // Lado B
  analogWrite(ENB, velocidade);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(1);
}