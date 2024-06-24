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
int IN1 = 4;
int IN2 = 5; //Frente
int IN3 = 6; //Frente
int IN4 = 7;

//Definição pinos faróis
int farolRe_1 = 3;
int farolRe_2 = 2;

//Definição pino buzina
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
  pinMode(farolRe_1, OUTPUT);
  pinMode(farolRe_2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
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

    // Move para frente
    if (n == 3) {
      paraFrente();
    }
    // Move para trás
    else if (n == 4) {
      paraTras ();
      digitalWrite(farolRe_1, LOW);
      digitalWrite(farolRe_2, LOW);
    }
    // Gira para a esquerda
    else if (n == 6) {
      parar ();
      // Lado A
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      // Lado B
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      delay(500);
      parar();
    }
    // Gira para a direita
    else if (n == 5) {
      parar();
      // Lado A
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      // Lado B
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      delay(500);
      parar();
    }
    // Comando música
    else if (n == 8) {
      tocarMusica();
    }
    // Botão parada
    else if (n == 7) {
      parar();
    }
  }
}

void parar (){
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      delay(1);
}

void paraFrente (){
   parar ();
  // Lado A
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Lado B
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(2000);
  parar();
}

void paraTras () {
  parar();
  digitalWrite(farolRe_1, HIGH);
  digitalWrite(farolRe_2, HIGH);
  // Lado A
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // Lado B
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

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
  delay(100);
  
    if(distanceCm < 20) {
      parar ();
    }
}

void tocarMusica(){
// I'm a Barbie Girl
  tone(buzzerPin, 415);
  delay(234);
  noTone(buzzerPin);

  tone(buzzerPin, 330);
  delay(212);
  noTone(buzzerPin);

  tone(buzzerPin, 415);
  delay(234);
  noTone(buzzerPin);

  tone(buzzerPin, 554);
  delay(234);
  noTone(buzzerPin);

  tone(buzzerPin, 440);
  delay(830);
  noTone(buzzerPin);

// In a Barbie World
  tone(buzzerPin, 370);
  delay(234);
  noTone(buzzerPin);

  tone(buzzerPin, 311);
  delay(234);
  noTone(buzzerPin);

  tone(buzzerPin, 370);
  delay(234);
  noTone(buzzerPin);

  tone(buzzerPin, 494);
  delay(234);
  noTone(buzzerPin);

  tone(buzzerPin, 415);
  delay(472);
  noTone(buzzerPin);

  tone(buzzerPin, 370);
  delay(230);
  noTone(buzzerPin);

  tone(buzzerPin, 330);
  delay(720);
  noTone(buzzerPin);

// Life in plastic
  tone(buzzerPin, 330);
  delay(234);
  noTone(buzzerPin);

  tone(buzzerPin, 277);
  delay(234);
  noTone(buzzerPin);

  tone(buzzerPin, 370);
  delay(472);
  noTone(buzzerPin);

  tone(buzzerPin, 277);
  delay(900);
  noTone(buzzerPin);

  tone(buzzerPin, 370);
  delay(280);
  noTone(buzzerPin);

  tone(buzzerPin, 330);
  delay(230);
  noTone(buzzerPin);

  tone(buzzerPin, 415);
  delay(440);
  noTone(buzzerPin);

  tone(buzzerPin, 370);
  delay(400);
  noTone(buzzerPin);

// You can brush my hair
  tone(buzzerPin, 415);
  delay(210);
  noTone(buzzerPin);

  tone(buzzerPin, 330);
  delay(224);
  noTone(buzzerPin);

  tone(buzzerPin, 415);
  delay(234);
  noTone(buzzerPin);

  tone(buzzerPin, 554);
  delay(234);
  noTone(buzzerPin);

  tone(buzzerPin, 440);
  delay(850);
  noTone(buzzerPin);

// And dress me everywhereeeeeeeee
  tone(buzzerPin, 370);
  delay(250);
  noTone(buzzerPin);

  tone(buzzerPin, 311);
  delay(234);
  noTone(buzzerPin);

  tone(buzzerPin, 370);
  delay(222);
  noTone(buzzerPin);

  tone(buzzerPin, 494);
  delay(234);
  noTone(buzzerPin);

  tone(buzzerPin, 415);
  delay(472);
  noTone(buzzerPin);

  tone(buzzerPin, 370);
  delay(224);
  noTone(buzzerPin);

  tone(buzzerPin, 330);
  delay(800);
  noTone(buzzerPin);

// Imagination
  tone(buzzerPin, 277);
  delay(212);
  noTone(buzzerPin);

  tone(buzzerPin, 370);
  delay(472);
  noTone(buzzerPin);

  tone(buzzerPin, 277);
  delay(500);
  noTone(buzzerPin);

  tone(buzzerPin, 370);
  delay(500);
  noTone(buzzerPin);

  tone(buzzerPin, 370);
  delay(234);
  noTone(buzzerPin);

  tone(buzzerPin, 330);
  delay(200);
  noTone(buzzerPin);

  tone(buzzerPin, 415);
  delay(431);
  noTone(buzzerPin);

  tone(buzzerPin, 370);
  delay(400);
  noTone(buzzerPin); 
}