#include <Arduino.h>

// Definir los pines de los LEDs del semáforo
#define LED_ROJO 15
#define LED_AMARILLO 2
#define LED_VERDE 4

// Tarea para controlar el LED rojo
void tareaLedRojo(void *pvParameters) {
  pinMode(LED_ROJO, OUTPUT);
  while (true) {
    digitalWrite(LED_ROJO, HIGH);  // Encender LED rojo
    vTaskDelay(5000 / portTICK_PERIOD_MS); // Esperar 5 segundos
    digitalWrite(LED_ROJO, LOW);   // Apagar LED rojo
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Pequeño retraso para sincronización
  }
}

// Tarea para controlar el LED amarillo
void tareaLedAmarillo(void *pvParameters) {
  pinMode(LED_AMARILLO, OUTPUT);
  while (true) {
    vTaskDelay(5000 / portTICK_PERIOD_MS);  // Esperar hasta que termine el rojo
    digitalWrite(LED_AMARILLO, HIGH);  // Encender LED amarillo
    vTaskDelay(2000 / portTICK_PERIOD_MS); // Esperar 2 segundos
    digitalWrite(LED_AMARILLO, LOW);   // Apagar LED amarillo
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Pequeño retraso para sincronización
  }
}

// Tarea para controlar el LED verde
void tareaLedVerde(void *pvParameters) {
  pinMode(LED_VERDE, OUTPUT);
  while (true) {
    vTaskDelay(7000 / portTICK_PERIOD_MS);  // Esperar hasta que termine el amarillo
    digitalWrite(LED_VERDE, HIGH);  // Encender LED verde
    vTaskDelay(5000 / portTICK_PERIOD_MS); // Esperar 5 segundos
    digitalWrite(LED_VERDE, LOW);   // Apagar LED verde
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Pequeño retraso para sincronización
  }
}

// Tarea para enviar datos por el puerto serie
void tareaEnvioSerie(void *pvParameters) {
  while (true) {
    Serial.println("Ciclo de semáforo completado");
    vTaskDelay(10000 / portTICK_PERIOD_MS); // Enviar datos cada 10 segundos
  }
}

void setup() {
  Serial.begin(115200); // Inicializar el puerto serie a 115200 baudios

  // Crear las tareas para manejar los LEDs del semáforo y el envío de datos por serie
  xTaskCreate(
    tareaLedRojo,       // Función de la tarea
    "Tarea LED Rojo",  // Nombre de la tarea
    1024,               // Tamaño de la pila en palabras
    NULL,               // Parámetro de entrada (no se necesita en este ejemplo)
    1,                  // Prioridad de la tarea (1 es baja prioridad)
    NULL                // Puntero al manejador de la tarea (no se necesita aquí)
  );

  xTaskCreate(
    tareaLedAmarillo,   // Función de la tarea
    "Tarea LED Amarillo", 
    1024, 
    NULL, 
    1, 
    NULL
  );

  xTaskCreate(
    tareaLedVerde,      // Función de la tarea
    "Tarea LED Verde", 
    1024, 
    NULL, 
    1, 
    NULL
  );

  xTaskCreate(
    tareaEnvioSerie,    // Función de la tarea
    "Tarea Serie", 
    1024, 
    NULL, 
    1, 
    NULL
  );
}

void loop() {
  // El loop principal está vacío ya que todas las operaciones están manejadas por las tareas FreeRTOS
}
