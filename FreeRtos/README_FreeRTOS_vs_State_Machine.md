# README: Ejemplos de FreeRTOS y Máquinas de Estado en ESP32

## ¿Qué es FreeRTOS?

FreeRTOS es un sistema operativo en tiempo real que permite gestionar tareas concurrentes en sistemas embebidos. Diseñado para dispositivos con recursos limitados, FreeRTOS se utiliza ampliamente en microcontroladores, incluyendo la ESP32, para aplicaciones que requieren respuestas inmediatas y la ejecución simultánea de varias tareas. FreeRTOS permite la creación de **tareas**, que son funciones que se ejecutan en paralelo, utilizando un planificador que decide cuándo y qué tarea debe ejecutarse según su prioridad.

### Características de FreeRTOS:
- **Multitarea**: Permite dividir el código en varias tareas que se ejecutan de manera independiente.
- **Planificador en tiempo real**: Determina la ejecución de las tareas en función de la prioridad asignada.
- **Primitivas de sincronización**: Proporciona semáforos, mutex y colas para permitir la comunicación segura entre tareas.

### Instrucciones y Comandos de FreeRTOS:

A continuación, se muestran algunos de los comandos más comunes que se utilizan para trabajar con FreeRTOS en proyectos de ESP32:

- **`xTaskCreate()`**: Permite crear una nueva tarea.
  ```cpp
  xTaskCreate(tareaLedRojo, "Tarea LED Rojo", 1024, NULL, 1, NULL);
  ```
  - **Parámetros**:
    - Función de la tarea.
    - Nombre de la tarea (cadena).
    - Tamaño de la pila en palabras.
    - Parámetro de entrada (en este ejemplo no se necesita).
    - Prioridad de la tarea.
    - Puntero al manejador de la tarea (en este ejemplo no se necesita).

- **`vTaskDelay()`**: Permite suspender una tarea durante un cierto tiempo sin bloquear el procesador.
  ```cpp
  vTaskDelay(1000 / portTICK_PERIOD_MS); // Esperar 1 segundo
  ```
  - **Parámetro**: Tiempo de espera en "ticks" del sistema (usualmente convertido a milisegundos).

- **`xSemaphoreCreateBinary()`**: Crea un semáforo binario, utilizado para la sincronización entre tareas.
- **`xSemaphoreTake()` y `xSemaphoreGive()`**: Permiten tomar y liberar semáforos, respectivamente, facilitando el acceso controlado a recursos compartidos.
- **`xQueueCreate()`**: Permite crear una cola para almacenar y transferir datos entre tareas de manera segura.
- **`xQueueSend()` y `xQueueReceive()`**: Envían y reciben datos a través de una cola.

### Estructura Básica para Crear un Programa en FreeRTOS

Para crear un programa utilizando FreeRTOS en la ESP32, se sigue la siguiente estructura básica:

1. **Incluir Librerías**: Incluir las librerías necesarias para trabajar con FreeRTOS y el hardware.
   ```cpp
   #include <Arduino.h>
   #include <freertos/FreeRTOS.h>
   #include <freertos/task.h>
   ```

2. **Definir los Recursos del Sistema**: Como los pines a utilizar y otros parámetros del hardware.
   ```cpp
   #define LED_PIN 2
   ```

3. **Definir las Funciones de las Tareas**: Estas funciones contendrán el código que se ejecutará de manera concurrente.
   ```cpp
   void tareaLed(void *pvParameters) {
     pinMode(LED_PIN, OUTPUT);
     while (true) {
       digitalWrite(LED_PIN, HIGH);  // Encender LED
       vTaskDelay(1000 / portTICK_PERIOD_MS); // Esperar 1 segundo
       digitalWrite(LED_PIN, LOW);   // Apagar LED
       vTaskDelay(1000 / portTICK_PERIOD_MS); // Esperar 1 segundo
     }
   }
   ```

4. **Configurar el `setup()`**: Crear las tareas con `xTaskCreate()` dentro de `setup()`.
   ```cpp
   void setup() {
     Serial.begin(115200); // Inicializar el puerto serie
     xTaskCreate(tareaLed, "Tarea LED", 1024, NULL, 1, NULL); // Crear la tarea
   }
   ```

5. **Bucle Principal `loop()`**: En la mayoría de los casos, el `loop()` permanece vacío cuando se usa FreeRTOS, ya que las tareas están manejando las acciones de manera independiente.
   ```cpp
   void loop() {
     // No se necesita código en el loop principal
   }
   ```

## ¿Qué es una Máquina de Estados?

Una **máquina de estados** es un modelo matemático que define un sistema en el cual cada estado conduce a otro dependiendo de ciertos eventos o condiciones. En el contexto de sistemas embebidos, como el ESP32, una máquina de estados se utiliza para definir el comportamiento de un dispositivo en distintos estados predeterminados, como por ejemplo el comportamiento de un semáforo (rojo, amarillo, verde).

### Características de las Máquinas de Estado:
- **Estados Definidos**: Cada parte del sistema tiene estados claramente definidos que cambian en respuesta a ciertos eventos.
- **Control Lógico Sencillo**: Adecuado para sistemas con una lógica bien definida que no requieran la complejidad de un sistema operativo en tiempo real.

## Diferencias entre FreeRTOS y Máquinas de Estado

| Característica               | FreeRTOS                         | Máquinas de Estado                   |
|------------------------------|----------------------------------|----------------------------------------|
| **Enfoque**                  | Multitarea en tiempo real        | Control basado en transiciones de estado |
| **Complejidad**              | Alta complejidad, eficiente para tareas concurrentes | Menor complejidad, adecuado para sistemas secuenciales |
| **Uso de Recursos**          | Mayor consumo de memoria y CPU   | Uso eficiente de recursos               |
| **Sincronización**           | Utiliza semáforos, colas y mutex | Las transiciones son controladas por lógica simple |
| **Flexibilidad**             | Alta, ideal para aplicaciones complejas | Baja, ideal para aplicaciones sencillas y controladas |

## Ejemplos Explicados

### Ejemplo 1: Semáforo utilizando FreeRTOS
En este ejemplo, se utilizaron tres tareas distintas para controlar los LEDs de un semáforo (rojo, amarillo, verde) en una ESP32. Cada tarea se encarga de encender y apagar un LED específico durante un tiempo determinado.

- **Tarea LED Rojo**: Enciende el LED rojo por 5 segundos.
- **Tarea LED Amarillo**: Enciende el LED amarillo por 2 segundos después de que el rojo se apaga.
- **Tarea LED Verde**: Enciende el LED verde por 5 segundos después de que el amarillo se apaga.
- **Tarea de Enviar Datos al Puerto Serie**: Envía un mensaje por el puerto serie indicando que el ciclo del semáforo se ha completado.

Este enfoque muestra el uso de **multitarea** en FreeRTOS, permitiendo que los diferentes LEDs se controlen simultáneamente, mientras que otra tarea envía información al puerto serie.

### Ejemplo 2: Semáforo utilizando Máquinas de Estado
En el ejemplo de la máquina de estados, utilizamos una estructura de control `switch` para gestionar los diferentes estados del semáforo: rojo, amarillo y verde.

- **Estado ROJO**: El LED rojo se enciende durante 5 segundos.
- **Estado AMARILLO**: Una vez que el LED rojo se apaga, el LED amarillo se enciende durante 2 segundos.
- **Estado VERDE**: Luego, el LED verde se enciende por 5 segundos antes de volver al estado rojo.

En este ejemplo, la lógica es secuencial y no permite la concurrencia que FreeRTOS proporciona. Sin embargo, es más sencillo de implementar y adecuado para casos donde no se requiere multitarea.

## Cuándo Elegir FreeRTOS o una Máquina de Estados
- **FreeRTOS** es ideal para proyectos que requieren el control de múltiples tareas que se ejecutan de manera independiente, como aplicaciones de **IoT** y dispositivos **en tiempo real** con varios sensores y actuadores.
- **Máquinas de Estado** son más apropiadas cuando se tiene un flujo bien definido y se requiere un **control secuencial** y claro, como en sistemas con pocas funcionalidades o con una lógica de control simple (ejemplo: un semáforo).

## Conclusión
Ambos enfoques tienen ventajas y desventajas dependiendo del tipo de aplicación. FreeRTOS es más flexible y potente para aplicaciones complejas y con concurrencia, mientras que las máquinas de estado son más simples y eficientes para sistemas secuenciales. Los ejemplos proporcionados muestran cómo se pueden implementar ambas estrategias en una ESP32 para el control de un semáforo.

### Referencias
- [FreeRTOS Documentation](https://www.freertos.org/)
- [ESP32 Arduino Documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/)
