//https://wokwi.com/projects/341776914153734739
#include <Arduino.h>

// Definir los pines de los LEDs y parámetros
#define LED_PIN 2

void setup() {
  Serial.begin(115200); // Inicializar el puerto serie a 115200 baudios
  pinMode(LED_PIN, OUTPUT); // Configurar el pin del LED como salida
}

void loop() {
  // Encender y apagar el LED cada 1 segundo
  digitalWrite(LED_PIN, HIGH);  // Encender LED
  delay(5000);                  // Esperar 1 segundo
  digitalWrite(LED_PIN, LOW);   // Apagar LED
  delay(5000);                  // Esperar 1 segundo

  // Enviar datos por el puerto serie cada 2 segundos
  Serial.println("Mensaje desde la tarea de envio por puerto serie");
  delay(100);                  // Esperar 2 segundos antes de enviar otro mensaje
}
