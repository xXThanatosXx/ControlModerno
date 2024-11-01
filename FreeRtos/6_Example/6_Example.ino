#include <Arduino.h>

// Definir los pines de los LEDs del semáforo
#define LED_ROJO 15
#define LED_AMARILLO 2
#define LED_VERDE 4

// Definir los estados del semáforo
enum EstadoSemaforo { ROJO, AMARILLO, VERDE };
EstadoSemaforo estadoActual = ROJO;
unsigned long tiempoCambio = 0;

void setup() {
  Serial.begin(115200); // Inicializar el puerto serie a 115200 baudios
  pinMode(LED_ROJO, OUTPUT);     // Configurar el pin del LED rojo como salida
  pinMode(LED_AMARILLO, OUTPUT); // Configurar el pin del LED amarillo como salida
  pinMode(LED_VERDE, OUTPUT);    // Configurar el pin del LED verde como salida

  // Iniciar con el LED rojo encendido
  digitalWrite(LED_ROJO, HIGH);
  tiempoCambio = millis();
}

void loop() {
  unsigned long tiempoActual = millis();

  switch (estadoActual) {
    case ROJO:
      // Mantener el LED rojo encendido durante 5 segundos
      if (tiempoActual - tiempoCambio >= 5000) {
        digitalWrite(LED_ROJO, LOW);  // Apagar LED rojo
        digitalWrite(LED_AMARILLO, HIGH);  // Encender LED amarillo
        estadoActual = AMARILLO;
        tiempoCambio = tiempoActual;
      }
      break;

    case AMARILLO:
      // Mantener el LED amarillo encendido durante 2 segundos
      if (tiempoActual - tiempoCambio >= 2000) {
        digitalWrite(LED_AMARILLO, LOW);  // Apagar LED amarillo
        digitalWrite(LED_VERDE, HIGH);    // Encender LED verde
        estadoActual = VERDE;
        tiempoCambio = tiempoActual;
      }
      break;

    case VERDE:
      // Mantener el LED verde encendido durante 5 segundos
      if (tiempoActual - tiempoCambio >= 5000) {
        digitalWrite(LED_VERDE, LOW);  // Apagar LED verde
        digitalWrite(LED_ROJO, HIGH);  // Encender LED rojo
        estadoActual = ROJO;
        tiempoCambio = tiempoActual;
        Serial.println("Ciclo de semáforo completado"); // Enviar mensaje al puerto serie
      }
      break;
  }
}
