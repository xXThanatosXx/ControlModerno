const int SENSOR_INPUT_PIN = A0;
const int SETPOINT_INPUT_PIN = A1;
const int PWM_OUTPUT_PIN = 6;
const float ALPHA = 0.01;  // EMA smoothing factor
const int SAMPLE_TIME_MS = 35;  // Sampling time in ms

float ts = 0.35; // ts = SAMPLE_TIME_MS / 1000
float currentOutput = 0.0;
float controlEffort = 0.0;
float setPoint = 0.0;

int PWMValue = 0;

float currentError = 0.0;
float previousError = 0.0;
float Kp, Ki, Kd; // PID parameters

// Ziegler-Nichols Tuning Parameters
float Ku = 3.1836; // Replace with experimentally found value
float Tu =  0.50912;  // Replace with experimentally found value

unsigned long lastUpdateTime = 0;

float filteredOutput = currentOutput;

void setup() {
  Serial.begin(9600);
  pinMode(PWM_OUTPUT_PIN, OUTPUT);

  // Calculate PID parameters using Ziegler-Nichols tuning
  Kp = 0.6 * Ku;
  Ki = 2 * Kp / Tu;
  Kd = Kp * Tu / 8;
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
  readAndFilterOutput();
  readSetPoint();
  calculatePID();
  applyControl();
  printDebugData();
}

void readAndFilterOutput() {
  currentOutput = mapInput(analogRead(SENSOR_INPUT_PIN), 15, 850);
  filteredOutput = ALPHA * currentOutput + (1.0 - ALPHA) * filteredOutput;
}

float mapInput(int rawValue, int min, int max) {
  float mappedValue = map(rawValue, min, max, 0, 100);
  return constrain(mappedValue, 0, 100);
}

void readSetPoint() {
  setPoint = mapInput(analogRead(SETPOINT_INPUT_PIN), 0, 1023);
}

void calculatePID() {
  currentError = setPoint - filteredOutput;
  controlEffort +=  Kp * (currentError - previousError)
                  + Ki * SAMPLE_TIME_MS * 0.001 * 0.5 * (currentError + previousError)
                  + Kp * Kd / SAMPLE_TIME_MS * 0.001;
  previousError = currentError;
}

void applyControl() {
  controlEffort = constrain(controlEffort, 0, 100);
  PWMValue = map(controlEffort, 0, 100, 0, 255);
  analogWrite(PWM_OUTPUT_PIN, PWMValue);
}

void printDebugData() {
  Serial.print("SetPoint: ");
  Serial.print(setPoint);
  Serial.print(" Output: ");
  Serial.print(filteredOutput);
  Serial.print(" Error: ");
  Serial.println(currentError);
}
