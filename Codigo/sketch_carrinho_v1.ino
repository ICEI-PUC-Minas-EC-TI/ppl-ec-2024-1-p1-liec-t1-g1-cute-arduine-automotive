// Define os pinos para cada roda
#define in1 5
#define in2 6
#define in3 3
#define in4 4
#define enA 9
#define enB 10

// Define a velocidade inicial dos motores
int ENA = 110;
int ENB = 110;

void setup() {
  Serial.begin(9600);  // Inicia a comunicação serial
  // Define os pinos dos motores como saídas
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // Define a velocidade inicial dos motores
  analogWrite(enA, ENA);
  analogWrite(enB, ENB);
}

void loop() {
  if (Serial.available() > 0) {
    char n = Serial.read();
    
    // Move para frente
    if (n == '3') {
        // Lado A
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        // Lado B
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
    }
    // Move para trás
    else if (n == '2') {
        // Lado A
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        // Lado B
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
    }
    // Move para a esquerda
    else if (n == '5') {
        ENA = 160;
        ENB = 55;
        analogWrite(enA, ENA);
        analogWrite(enB, ENB);
    }
    // Move para a direita
    else if (n == '4') {
        ENA = 55;
        ENB = 160;
        analogWrite(enA, ENA);
        analogWrite(enB, ENB);
    }
    // Aumenta a velocidade
    else if (n == '6' && ENA < 226 && ENB < 226) { // Limita a velocidade máxima
      ENA += 29;
      ENB += 29;
      analogWrite(enA, ENA);
      analogWrite(enB, ENB);
    }
    // Restaura a velocidade inicial
    else if (n == '7') {
      ENA = 110;
      ENB = 110;
      analogWrite(enA, ENA);
      analogWrite(enB, ENB);
    }
    // Comando inválido ou nenhum comando recebido
    else {
        // Parar os motores
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
    }
  }
}
