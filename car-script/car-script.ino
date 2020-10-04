// Adafruit Motor Shield V2
#include <Adafruit_MotorShield.h>

// RF24 for radio frequency input
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define SERIAL_BIT_RATE 9600

#define RADIO_PIN_CE 7
#define RADIO_PIN_CSN 8
#define RADIO_ADDRESS "RCCAR"

Adafruit_MotorShield motorShield = Adafruit_MotorShield();
Adafruit_DCMotor *leftFront = motorShield.getMotor(1);
Adafruit_DCMotor *leftRear = motorShield.getMotor(2);
Adafruit_DCMotor *rightFront = motorShield.getMotor(3);
Adafruit_DCMotor *rightRear = motorShield.getMotor(4);
RF24 radio(RADIO_PIN_CE, RADIO_PIN_CSN);

void setup() {
  Serial.begin(SERIAL_BIT_RATE);
  motorShield.begin();
  radio.begin();
  radio.openReadingPipe(0, byte(RADIO_ADDRESS));
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  Serial.println("Reading and processing 2 characters from RF");
  
  processInput(readInput(2));
  
  delay(2000);
  
  // testDrive();
}

char* readInput(const unsigned int size) {
  if (!radio.available()) return NULL;
  
  char input[size];
  radio.read(&input, size);

  return &input;
}

void processInput(const char* input) {
  if (input == "ff") Serial.println("Forward:Slow"); return;
  if (input == "FF") Serial.println("Forward:Fast"); return;
  if (input == "bb") Serial.println("Backward:Slow"); return;
  if (input == "BB") Serial.println("Backward:Fast"); return;
  if (input == "ll") Serial.println("Left:Slow"); return;
  if (input == "LL") Serial.println("Left:Fast"); return;
  if (input == "rr") Serial.println("Right:Slow"); return;
  if (input == "RR") Serial.println("Right:Fast"); return;
}

void testDrive() {
  moveForward(50);
  delay(2000);
  stopMotors();
  delay(1000);
  
  moveForward(100);
  delay(2000);
  stopMotors();
  delay(1000);
  
  moveForward(150);
  delay(2000);
  stopMotors();
  delay(1000);
  
  moveForward(200);
  delay(2000);
  stopMotors();
  delay(1000);
  
  moveForward(250);
  delay(2000);
  // Don't stop motors here, carry momentum into the coast

  coastMotors();
  delay(4000);
  
  moveBackward(50);
  delay(2000);
  stopMotors();
  delay(1000);
  
  moveBackward(100);
  delay(2000);
  stopMotors();
  delay(1000);
  
  moveBackward(150);
  delay(2000);
  stopMotors();
  delay(1000);
  
  moveBackward(200);
  delay(2000);
  stopMotors();
  delay(1000);
  
  moveBackward(250);
  delay(2000);
  // Don't stop motors here, carry momentum into the coast

  coastMotors();
  delay(4000);

  moveLeft(50);
  delay(2000);
  stopMotors();
  delay(1000);

  moveRight(50);
  delay(2000);
  stopMotors();
  delay(1000);
}

void stopMotors() {
  Serial.println("STOPPING all motors");
  
  leftFront->setSpeed(0);
  rightFront->setSpeed(0);
  leftRear->setSpeed(0);
  rightRear->setSpeed(0);
}

void coastMotors() {
  Serial.println("COASTING all motors");
  
  leftFront->run(RELEASE);
  rightFront->run(RELEASE);
  leftRear->run(RELEASE);
  rightRear->run(RELEASE);
}

void moveForward(uint8_t speed) {
  Serial.print("Moving FORWARD at ");
  Serial.println(speed, DEC);
  
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
  Serial.print("Moving BACKWARD at ");
  Serial.println(speed, DEC);
  
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
  Serial.print("Moving LEFT at ");
  Serial.println(speed, DEC);
  
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
  Serial.print("Moving RIGHT at ");
  Serial.println(speed, DEC);
  
  leftFront->setSpeed(speed);
  leftRear->setSpeed(speed);
  
  rightFront->setSpeed(speed);
  rightRear->setSpeed(speed);
  
  leftFront->run(FORWARD);
  leftRear->run(FORWARD);
  
  rightFront->run(BACKWARD);
  rightRear->run(BACKWARD);
}
