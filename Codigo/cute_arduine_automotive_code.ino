#include <SoftwareSerial.h>

// Define os pinos para comunicação SoftwareSerial
SoftwareSerial BTSerial(8, 9); // RX, TX

int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
int n = 2;
  
void setup()
{
  //Define os pinos como saida
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);
 Serial.begin(9600);
 Serial.println("Arduino está pronto");
 BTSerial.begin(9600);
}
  
void loop()
{
 if (BTSerial.available() > 0) {
    n = (int)BTSerial.read();
    Serial.print("Received: ");
    Serial.println(n);
 // Move para frente
    if (n == 3) {
        // Lado A
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        // Lado B
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        delay(2000);
    }    
    // Move para trás
    else if (n == 2) {
        // Lado A
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        // Lado B
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        delay(2000);
    }

    else if (n == 5) {
       //Gira o Motor A no sentido horario
       digitalWrite(IN1, HIGH);
       digitalWrite(IN2, LOW);
        delay(2000);
    } 
    

    else {
       digitalWrite(IN1, LOW);
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
    }
 
}
}