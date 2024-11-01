#include <Arduino.h>

// Definimos el pin al cual está conectado el LED
#define LED_PIN 2

// Definimos la función de la tarea
void tareaParpadeo(void *pvParameters) {
  // Configuramos el pin del LED como salida
  pinMode(LED_PIN, OUTPUT);
  
  while (true) {
    // Encender LED
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS); // Espera de 500 ms

    // Apagar LED
    digitalWrite(LED_PIN, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS); // Espera de 500 ms
  }
}

void setup() {
  Serial.begin(115200);
  // Crear la tarea para el parpadeo del LED
  xTaskCreate(
    tareaParpadeo,   // Función de la tarea
    "Tarea LED",     // Nombre de la tarea (para identificación)
    1024,            // Tamaño de la pila en palabras
    NULL,            // Parámetro de entrada (no se necesita en este ejemplo)
    1,               // Prioridad de la tarea (1 es baja prioridad)
    NULL             // Puntero al manejador de la tarea (no se necesita aquí)
  );
}

void loop() {
  // El loop principal está vacío porque la lógica está manejada por la tarea FreeRTOS
}
