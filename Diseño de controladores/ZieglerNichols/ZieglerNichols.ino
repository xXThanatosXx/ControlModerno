const int SENSOR_INPUT_PIN = A0;
const int SETPOINT_INPUT_PIN = A1;
const int PWM_OUTPUT_PIN = 6;
const float ALPHA = 0.01;  // EMA smoothing factor
const int SAMPLE_TIME_MS = 35;  // Sampling time in ms

float ts = 0.35; // ts = SAMPLE_TIME_MS / 100
float currentOutput = 0.0;
float controlEffort = 0.0;
float setPoint = 0.0;

int PWMValue = 0;

float currentError = 0.0;
float previousError = 0.0;
float Kc, ti, td; // PID parameters

// Ziegler-Nichols Tuning Parameters
float Kp = 3.1804; // Remplazar con los valores de identificación
float Tau =  0.50713;  // Remplazar con los valores de identificación
float theta = 0.0182;
unsigned long lastUpdateTime = 0;
float previousError1 = 0.0;
float previousError2 = 0.0;
float filteredOutput = currentOutput;

float L;


void setup() {
  Serial.begin(9600);
  pinMode(PWM_OUTPUT_PIN, OUTPUT);

  // Parametros PID con Ziegler-Nichols 

  L = theta + ts/2;
  Kc = (1.2*Tau)/(Kp*L);
  ti = 2*L;
  td = 0.5*L;
}

void loop() {
  if (isSampleTimeElapsed()) {
    processControlLoop();
    lastUpdateTime = millis();
  }
}

bool isSampleTimeElapsed() {
  return millis() - lastUpdateTime >= SAMPLE_TIME_MS;
}

void processControlLoop() {
  ReadAndFilterOutput();
  ReadSetPoint();
  CalculatePID();
  ApplyControl();
  PrintDebugData();
}

void ReadAndFilterOutput() {
  currentOutput = mapInput(analogRead(SENSOR_INPUT_PIN), 15, 850);
  filteredOutput = ALPHA * currentOutput + (1.0 - ALPHA) * filteredOutput;
}

float mapInput(int rawValue, int min, int max) {
  float mappedValue = map(rawValue, min, max, 0, 100);
  return constrain(mappedValue, 0, 100);
}

void ReadSetPoint() {
  setPoint = mapInput(analogRead(SETPOINT_INPUT_PIN), 0, 1023);
}

void CalculatePID() {
  // Calcula el error actual
  currentError = setPoint - filteredOutput;

  // Calcula los coeficientes del PID discreto
  float q0 = Kc * (1 + SAMPLE_TIME_MS / (2 * ti) + td / SAMPLE_TIME_MS);
  float q1 = -Kc * (1 - SAMPLE_TIME_MS / (2 * ti) + (2 * td) / SAMPLE_TIME_MS);
  float q2 = (Kc * td) / SAMPLE_TIME_MS;

  // Calcula el esfuerzo de control según la fórmula discreta de PID
  controlEffort = controlEffort + q0 * currentError + q1 * previousError + q2 * previousError1;

  // Actualiza los errores para el próximo ciclo
  previousError2 = previousError1;
  previousError1 = previousError;
  previousError = currentError;
}

void ApplyControl() {
  controlEffort = constrain(controlEffort, 0, 100);
  PWMValue = map(controlEffort, 0, 100, 0, 255);
  analogWrite(PWM_OUTPUT_PIN, PWMValue);
}

void PrintDebugData() {
  Serial.print("SetPoint: ");
  Serial.print(setPoint);
  Serial.print(" Output: ");
  Serial.print(filteredOutput);
  Serial.print(" Error: ");
  Serial.println(currentError);
}
