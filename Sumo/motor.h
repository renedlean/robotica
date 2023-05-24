#ifndef _MOTOR_H
#define _MOTOR_H

#include <arduino.h>

// Portas driver motor
#define MOTOR_IN1 7
#define MOTOR_IN2 6
#define MOTOR_IN3 10
#define MOTOR_IN4 9
#define MOTOR_EN1 5
#define MOTOR_EN2 11

void motorControl(int speedLeft, int speedRight);
void motorOption(char optin, int speedLeft, int speedRight);

void motorControl(int speedLeft, int speedRight) {
  // Função para controle do driver de motor

  // Definições das portas digitais
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MOTOR_IN3, OUTPUT);
  pinMode(MOTOR_IN4, OUTPUT);
  pinMode(MOTOR_EN1, OUTPUT);
  pinMode(MOTOR_EN2, OUTPUT);

  // Ajustes motor da esquerda
  if (speedLeft < 0) {
    speedLeft = -speedLeft;
    digitalWrite (MOTOR_IN3, HIGH);
    digitalWrite (MOTOR_IN4, LOW);
  } else {
    digitalWrite (MOTOR_IN3, LOW);
    digitalWrite (MOTOR_IN4, HIGH);
  }

  // Ajustes motor da direita
  if (speedRight < 0) {
    speedRight = -speedRight;
    digitalWrite (MOTOR_IN1, LOW);
    digitalWrite (MOTOR_IN2, HIGH);
  } else {
    digitalWrite (MOTOR_IN1, HIGH);
    digitalWrite (MOTOR_IN2, LOW);
  }

  analogWrite (MOTOR_EN1, speedLeft);
  analogWrite (MOTOR_EN2, speedRight);
}

void motorOption(char option, int speedLeft, int speedRight) {
  // Função para controle de motor com pre definições
  switch (option) {
    case '6': // Esquerda
      motorControl(-speedLeft, speedRight);
      break;
    case '4': // Direita
      motorControl(speedLeft, -speedRight);
      break;
    case '2': // Trás
      motorControl(-speedLeft, -speedRight);
      break;
    case '8': // Frente
      motorControl(speedLeft, speedRight);
      break;
    case '0': // Parar
      motorControl(0, 0);
      break;
  }
}

#endif
