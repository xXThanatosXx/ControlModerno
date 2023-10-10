const int PWM_PIN = 6;       // PWM output pin
const int SENSOR_PIN = A0;   // Analog input pin
const float ALPHA = 0.1;     // EMA smoothing factor

float currentInput = 0.0;    // Y in original code
float setPoint = 0.0;        // U in original code

int PWM_output = 0;
char serialBuffer[30];       // Buffer to hold serial input
byte bufferIndex = 0;        // Index to keep track of buffer position

float filteredInput = currentInput;  // EMA filtered value

void setup() {
  Serial.begin(9600);
  pinMode(PWM_PIN, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    readSerialInput();
    controlPWM();
    filterAndPrintInput();
  }
}

void readSerialInput() {
  memset(serialBuffer, 0, sizeof(serialBuffer));
  
  while (Serial.available() > 0) {
    serialBuffer[bufferIndex] = Serial.read();
    bufferIndex++;
    delay(3);  
  }
  
  bufferIndex = 0;
  setPoint = atof(serialBuffer);
}

void controlPWM() {
  PWM_output = map(setPoint, 0, 100, 0, 255);
  analogWrite(PWM_PIN, PWM_output);
}

void filterAndPrintInput() {
  currentInput = mapInput(analogRead(SENSOR_PIN));
  filteredInput = ALPHA * currentInput + (1.0 - ALPHA) * filteredInput;
  Serial.println(filteredInput);
}

float mapInput(int rawValue) {
  float mappedValue = map(rawValue, 40, 1023, 0, 100);
  return constrain(mappedValue, 0, 100);
}
