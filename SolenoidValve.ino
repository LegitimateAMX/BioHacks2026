const int valvePin = 9; 

void setup() {
  pinMode(valvePin, OUTPUT);
}

void loop() {
  Serial.println("Open");
  analogWrite(valvePin, 160); // 63% duty cycle for ~12V
  delay(3000);                // Valve open for 3 seconds
  
  Serial.println("Closed");
  analogWrite(valvePin, 0);   // 0V output
  delay(3000);                // Valve closed for 3 seconds
}
