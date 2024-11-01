#include <Arduino.h>

// Definir los pines de los LEDs y parámetros
#define LED_PIN 2

// Tarea para encender y apagar el LED
void tareaLed(void *pvParameters) {
  pinMode(LED_PIN, OUTPUT);
  while (true) {
    digitalWrite(LED_PIN, HIGH);  // Encender LED
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Esperar 1 segundo
    digitalWrite(LED_PIN, LOW);   // Apagar LED
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Esperar 1 segundo
  }
}

// Tarea para enviar datos por el puerto serie
void tareaEnvioSerie(void *pvParameters) {
  while (true) {
    Serial.println("Mensaje desde la tarea de envio por puerto serie");
    vTaskDelay(2000 / portTICK_PERIOD_MS); // Esperar 2 segundos antes de enviar otro mensaje
  }
}

void setup() {
  Serial.begin(115200); // Inicializar el puerto serie a 115200 baudios

  // Crear la tarea para manejar el LED
  xTaskCreate(
    tareaLed,          // Función de la tarea
    "Tarea LED",      // Nombre de la tarea
    1024,              // Tamaño de la pila en palabras
    NULL,              // Parámetro de entrada (no se necesita en este ejemplo)
    1,                 // Prioridad de la tarea (1 es baja prioridad)
    NULL               // Puntero al manejador de la tarea (no se necesita aquí)
  );

  // Crear la tarea para enviar datos por el puerto serie
  xTaskCreate(
    tareaEnvioSerie,   // Función de la tarea
    "Tarea Serie",    // Nombre de la tarea
    1024,              // Tamaño de la pila en palabras
    NULL,              // Parámetro de entrada (no se necesita en este ejemplo)
    1,                 // Prioridad de la tarea (1 es baja prioridad)
    NULL               // Puntero al manejador de la tarea (no se necesita aquí)
  );
}

void loop() {
  // El loop principal está vacío ya que todas las operaciones están manejadas por las tareas FreeRTOS
}
