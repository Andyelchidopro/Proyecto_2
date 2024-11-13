// Nombre: Andres Degollado Munoz
// Asignatura: Proyecto 2

// Esta biblioteca permite el control remotro por infrarrojos del robot.
#include "IR_remote.h"
// Representa el mapeo de teclas para control remoto.
#include "keymap.h"   

// Inicializa receptor IR en el pin 3.
IRremote infrarrojo(3);

// Esta biblioteca sirve para controlar los servomotores.
#include <Servo.h>      

// Inicializa el servo conectado al pin 10.
Servo servo_10;  

// Representan las variables globales.
volatile float Sensibilidad_Izquierda;
volatile float Sensibilidad_Derecha;
volatile float f;
volatile int velocidad_1=76.8;
volatile int velocidad_1=76.2;
volatile float Angulo_Servo;
volatile char Modo_Carro_IR;
volatile boolean Flag_Modo_IR;

// Estas son las funciones de movimiento del automóvil robótico.
void Avanzar(int velocidad_1, int velocidad_2) {
  digitalWrite(2, HIGH); // Activa el motor izquierdo hacia adelante.
  analogWrite(5, velocidad_1); // Controla la velocidad del motor izquierdo.
  digitalWrite(4, LOW); // Activa el motor derecho hacia adelante.
  analogWrite(6, velocidad_2); // Controla la velocidad del motor derecho.
}

void Retroceder(int velocidad_1, int velocidad_2) {
  digitalWrite(2, LOW); // Activa el motor izquierdo hacia atrás.
  analogWrite(5, velocidad_1);
  digitalWrite(4, HIGH); // Activa motor derecho hacia atrás.
  analogWrite(6, velocidad_2);
}

void Girar_Izquierda(int velocidad_1, int velocidad_2) {
  digitalWrite(2, LOW); // Ambos motores giran hacia la izquierda.
  analogWrite(5, velocidad_1);
  digitalWrite(4, LOW);
  analogWrite(6, velocidad_2);
}

void Girar_Derecha(int velocidad_1, int velocidad_2) {
  digitalWrite(2, HIGH); // Ambos motores giran hacia la derecha.
  analogWrite(5, velocidad_1);
  digitalWrite(4, HIGH);
  analogWrite(6, velocidad_2);
}

void Detener() {
  digitalWrite(2, LOW);
  analogWrite(5, 0);  // Se apagan los motores.
  digitalWrite(4, HIGH);
  analogWrite(6, 0);
}

// Esta funcion representa el control remoto por infrarrojo
void controlRemotoIR() {
  switch (Modo_Carro_IR) {
    case 'b':
      Retroceder(110);
      delay(300);
      Detener();
      Modo_Carro_IR = ' ';
      break;
    case 'f':
      Avanzar(110);
      delay(300);
      Detener();
      Modo_Carro_IR = ' ';
      break;
    case 'l':
      Girar_Izquierda(110);
      delay(300);
      Detener();
      Modo_Carro_IR = ' ';
      break;
    case 'r':
      Girar_Derecha(110);
      delay(300);
      Detener();
      Modo_Carro_IR = ' ';
      break;
    case 's':
      Detener();
      Modo_Carro_IR = ' ';
      break;
    case '+':
      Angulo_Servo += 3;
      if (Angulo_Servo >= 180) {
        Angulo_Servo = 180;
      }
      servo_10.write(round(Angulo_Servo));
      delay(0);
      Modo_Carro_IR = ' ';
      break;
    case '-':
      Angulo_Servo -= 3;
      if (Angulo_Servo <= 0) {
        Angulo_Servo = 0;
      }
      servo_10.write(round(Angulo_Servo));
      delay(0);
      Modo_Carro_IR = ' ';
      break;
  }

  // Verifica teclas presionadas y actualiza el modo de operación
  if (infrarrojo.getIrKey(infrarrojo.getCode(), 1) == IR_KEYCODE_UP) {
    Modo_Carro_IR = 'f';
    Flag_Modo_IR = true;
  } else if (infrarrojo.getIrKey(infrarrojo.getCode(), 1) == IR_KEYCODE_LEFT) {
    Modo_Carro_IR = 'l';
    Flag_Modo_IR = true;
  } else if (infrarrojo.getIrKey(infrarrojo.getCode(), 1) == IR_KEYCODE_DOWN) {
    Modo_Carro_IR = 'b';
    Flag_Modo_IR = true;
  } else if (infrarrojo.getIrKey(infrarrojo.getCode(), 1) == IR_KEYCODE_RIGHT) {
    Modo_Carro_IR = 'r';
    Flag_Modo_IR = true;
  } else if (infrarrojo.getIrKey(infrarrojo.getCode(), 1) == IR_KEYCODE_OK) {
    Modo_Carro_IR = 's';
    Flag_Modo_IR = true;
  } else if (infrarrojo.getIrKey(infrarrojo.getCode(), 1) == IR_KEYCODE_2) {
    Modo_Carro_IR = '+';
    Flag_Modo_IR = true;
  } else if (infrarrojo.getIrKey(infrarrojo.getCode(), 1) == IR_KEYCODE_8) {
    Modo_Carro_IR = '-';
    Flag_Modo_IR = true;
  }
