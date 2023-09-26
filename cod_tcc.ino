#include <NewPing.h>

#define TRIGGER_PIN 4
#define ECHO_PIN 3
#define MOTOR_ENA 9
#define MOTOR_IN1 6
#define MOTOR_IN2 7

NewPing sonar(TRIGGER_PIN, ECHO_PIN);
int motorSpeed = 150; // Ajuste a velocidade do motor conforme necessário (0-255)
bool portaAberta = false; // Variável para rastrear o estado da porta

void setup() {
  pinMode(MOTOR_ENA, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  Serial.begin(9600);
}

void abrir() {
  // Gire o motor no sentido anti-horário
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, HIGH);
  analogWrite(MOTOR_ENA, motorSpeed);
  delay(2000); // Espere 2 segundos
  // Pare o motor
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_ENA, 0);
}

void aguardar() {
  // Pare o motor
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_ENA, 0);
  delay(2000); // Espere 2 segundos
}

void fechar() {
  // Gire o motor no sentido horário
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_ENA, motorSpeed);
  delay(2000); // Espere 2 segundos
  // Pare o motor
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_ENA, 0);
}

void loop() {
  delay(50); // Pequeno atraso para estabilidade

  int distance = sonar.ping_cm();

  if (distance < 5 && !portaAberta) {
    // Se o objeto estiver a menos de 5 cm e a porta estiver fechada,
    // execute o ciclo de abrir, aguardar e fechar
    abrir();
    aguardar();
    fechar();
    portaAberta = true; 
  } else if (distance >= 5) {
    // Se a distância for maior ou igual a 5 cm,
    // coloque o motor na função "aguardar"
    aguardar();
    portaAberta = false;
  }

  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");
}