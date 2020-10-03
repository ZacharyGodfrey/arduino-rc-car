#include <Adafruit_MotorShield.h> // Adafruit Motor Shield V2

Adafruit_MotorShield motorShield = Adafruit_MotorShield();
Adafruit_DCMotor *leftFront = motorShield.getMotor(1);
Adafruit_DCMotor *leftRear = motorShield.getMotor(2);
Adafruit_DCMotor *rightFront = motorShield.getMotor(3);
Adafruit_DCMotor *rightRear = motorShield.getMotor(4);

void setup() {
  Serial.begin(9600);
  motorShield.begin();
}

void loop() {
  Serial.println("Forward:50");
  moveForward(50);
  delay(2000);
  stopMotors();
  delay(1000);
  
  Serial.println("Forward:100");
  moveForward(100);
  delay(2000);
  stopMotors();
  delay(1000);
  
  Serial.println("Forward:150");
  moveForward(150);
  delay(2000);
  stopMotors();
  delay(1000);
  
  Serial.println("Forward:200");
  moveForward(200);
  delay(2000);
  stopMotors();
  delay(1000);
  
  Serial.println("Forward:250");
  moveForward(250);
  delay(2000);
  // Don't stop motors here, carry momentum into the coast

  Serial.println("Coasting...");
  coastMotors();
  delay(4000);
  
  Serial.println("Backward:50");
  moveBackward(50);
  delay(2000);
  stopMotors();
  delay(1000);
  
  Serial.println("Backward:100");
  moveBackward(100);
  delay(2000);
  stopMotors();
  delay(1000);
  
  Serial.println("Backward:150");
  moveBackward(150);
  delay(2000);
  stopMotors();
  delay(1000);
  
  Serial.println("Backward:200");
  moveBackward(200);
  delay(2000);
  stopMotors();
  delay(1000);
  
  Serial.println("Backward:250");
  moveBackward(250);
  delay(2000);
  // Don't stop motors here, carry momentum into the coast

  Serial.println("Coasting...");
  coastMotors();
  delay(4000);

  Serial.println("Left:50");
  moveLeft(50);
  delay(2000);
  stopMotors();
  delay(1000);

  Serial.println("Right:50");
  moveRight(50);
  delay(2000);
  stopMotors();
  delay(1000);
}

void stopMotors() {
  leftFront->setSpeed(0);
  rightFront->setSpeed(0);
  leftRear->setSpeed(0);
  rightRear->setSpeed(0);
}

void coastMotors() {
  leftFront->run(RELEASE);
  rightFront->run(RELEASE);
  leftRear->run(RELEASE);
  rightRear->run(RELEASE);
}

void moveForward(uint8_t speed) {
  leftFront->setSpeed(speed);
  rightFront->setSpeed(speed);
  
  leftRear->setSpeed(speed);
  rightRear->setSpeed(speed);
  
  leftFront->run(FORWARD);
  rightFront->run(FORWARD);
  
  leftRear->run(FORWARD);
  rightRear->run(FORWARD);
}

void moveBackward(uint8_t speed) {
  leftFront->setSpeed(speed);
  rightFront->setSpeed(speed);
  
  leftRear->setSpeed(speed);
  rightRear->setSpeed(speed);
  
  leftFront->run(BACKWARD);
  rightFront->run(BACKWARD);
  
  leftRear->run(BACKWARD);
  rightRear->run(BACKWARD);
}

void moveLeft(uint8_t speed) {
  leftFront->setSpeed(speed);
  leftRear->setSpeed(speed);
  
  rightFront->setSpeed(speed);
  rightRear->setSpeed(speed);
  
  leftFront->run(BACKWARD);
  leftRear->run(BACKWARD);
  
  rightFront->run(FORWARD);
  rightRear->run(FORWARD);
}

void moveRight(uint8_t speed) {
  leftFront->setSpeed(speed);
  leftRear->setSpeed(speed);
  
  rightFront->setSpeed(speed);
  rightRear->setSpeed(speed);
  
  leftFront->run(FORWARD);
  leftRear->run(FORWARD);
  
  rightFront->run(BACKWARD);
  rightRear->run(BACKWARD);
}
