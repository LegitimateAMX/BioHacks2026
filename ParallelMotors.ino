// --- Joystick Pins ---
const int joyXPin = A0; // Left/Right Movement
const int joyYPin = A1; // Forward/Backward Movement

// --- Motor 1 Pins (Left Side) ---
const int enablePin1 = 5;  
const int dirPin1_A = 4;    
const int dirPin1_B = 3;    

// --- Motor 2 Pins (Right Side) ---
const int enablePin2 = 6;  
const int dirPin2_A = 7;    
const int dirPin2_B = 8;    

void setup() {
  pinMode(enablePin1, OUTPUT);
  pinMode(dirPin1_A, OUTPUT);
  pinMode(dirPin1_B, OUTPUT);
  
  pinMode(enablePin2, OUTPUT);
  pinMode(dirPin2_A, OUTPUT);
  pinMode(dirPin2_B, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // 1. Read raw analog values from Joystick (0 to 1023)
  int joyX = analogRead(joyXPin);
  int joyY = analogRead(joyYPin);

  // 2. Map the values from (0 to 1023) to (-255 to 255) for motor speeds
  int mappedX = map(joyX, 0, 1023, -255, 255);
  int mappedY = map(joyY, 0, 1023, -255, 255);

  // 3. Apply Deadband
  // If the joystick is close to the center, force the value to 0 to stop creeping
  if (abs(mappedX) < 20) mappedX = 0;
  if (abs(mappedY) < 20) mappedY = 0;

  // 4. Differential Drive Mixing Algorithm
  // Combine Y (forward/back) and X (turning) for each motor
  int leftMotorSpeed = mappedY;
  int rightMotorSpeed = mappedY;

  // 5. Constrain the calculated speeds to the valid PWM limit (-255 to 255)
  leftMotorSpeed = constrain(leftMotorSpeed, -255, 255);
  rightMotorSpeed = constrain(rightMotorSpeed, -255, 255);

  // 6. Drive Motor 1 (Left)
  if (leftMotorSpeed > 0) {
    digitalWrite(dirPin1_A, HIGH);
    digitalWrite(dirPin1_B, LOW);
  } else if (leftMotorSpeed < 0) {
    digitalWrite(dirPin1_A, LOW);
    digitalWrite(dirPin1_B, HIGH);
  } else { // Stop
    digitalWrite(dirPin1_A, LOW);
    digitalWrite(dirPin1_B, LOW);
  }
  analogWrite(enablePin1, abs(leftMotorSpeed)); // Send positive PWM value

  // 7. Drive Motor 2 (Right)
  if (rightMotorSpeed > 0) {
    digitalWrite(dirPin2_A, HIGH);
    digitalWrite(dirPin2_B, LOW);
  } else if (rightMotorSpeed < 0) {
    digitalWrite(dirPin2_A, LOW);
    digitalWrite(dirPin2_B, HIGH);
  } else { // Stop
    digitalWrite(dirPin2_A, LOW);
    digitalWrite(dirPin2_B, LOW);
  }
  analogWrite(enablePin2, abs(rightMotorSpeed));

  delay(20); // Small delay to stabilize readings
}
