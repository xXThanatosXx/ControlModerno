#include <Arduino.h>

// Definir los pines de los LEDs del semáforo
#define LED_ROJO 15
#define LED_AMARILLO 2
#define LED_VERDE 4

void setup() {
  Serial.begin(115200); // Inicializar el puerto serie a 115200 baudios
  pinMode(LED_ROJO, OUTPUT);     // Configurar el pin del LED rojo como salida
  pinMode(LED_AMARILLO, OUTPUT); // Configurar el pin del LED amarillo como salida
  pinMode(LED_VERDE, OUTPUT);    // Configurar el pin del LED verde como salida
}

void loop() {
  // Encender el LED rojo durante 5 segundos
  digitalWrite(LED_ROJO, HIGH);  // Encender LED rojo
  delay(5000);                   // Esperar 5 segundos
  digitalWrite(LED_ROJO, LOW);   // Apagar LED rojo

  // Encender el LED amarillo durante 2 segundos
  digitalWrite(LED_AMARILLO, HIGH);  // Encender LED amarillo
  delay(2000);                      // Esperar 2 segundos
  digitalWrite(LED_AMARILLO, LOW);   // Apagar LED amarillo

  // Encender el LED verde durante 5 segundos
  digitalWrite(LED_VERDE, HIGH);  // Encender LED verde
  delay(5000);                    // Esperar 5 segundos
  digitalWrite(LED_VERDE, LOW);   // Apagar LED verde

  // Enviar datos por el puerto serie
  Serial.println("Ciclo de semáforo completado");
  delay(1000);  // Esperar 1 segundo antes de repetir el ciclo
}
