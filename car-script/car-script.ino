// Adafruit Motor Shield V2
#include <Adafruit_MotorShield.h>

// RF24 for radio frequency input
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define SERIAL_BIT_RATE 9600
#define LOOP_DELAY_MS 2000

#define RADIO_PIN_CE 7
#define RADIO_PIN_CSN 8
#define RADIO_ADDRESS "RCCAR"

#define INPUT_NONE 0
#define INPUT_STOP 1
#define INPUT_COAST 2
#define INPUT_FORWARD_SLOW 3
#define INPUT_FORWARD_FAST 4
#define INPUT_BACKWARD_SLOW 5
#define INPUT_BACKWARD_FAST 6
#define INPUT_LEFT_SLOW 7
#define INPUT_LEFT_FAST 8
#define INPUT_RIGHT_SLOW 9
#define INPUT_RIGHT_FAST 10

#define SPEED_SLOW 50
#define SPEED_FAST 200

Adafruit_MotorShield motorShield = Adafruit_MotorShield();
Adafruit_DCMotor *leftFront = motorShield.getMotor(1);
Adafruit_DCMotor *leftRear = motorShield.getMotor(2);
Adafruit_DCMotor *rightFront = motorShield.getMotor(3);
Adafruit_DCMotor *rightRear = motorShield.getMotor(4);

RF24 radio(RADIO_PIN_CE, RADIO_PIN_CSN);

uint8_t currentState = 0;

void setup() {
  Serial.begin(SERIAL_BIT_RATE);
  
  motorShield.begin();

  const byte radioAddress[6] = RADIO_ADDRESS;
  
  radio.begin();
  radio.openReadingPipe(0, radioAddress);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  uint8_t newInput = INPUT_FORWARD_SLOW; // readInput();

  processInput(newInput);
  
  if (LOOP_DELAY_MS > 0) delay(LOOP_DELAY_MS);
}

uint8_t readInput() {
  if (!radio.available()) return INPUT_NONE;
  
  uint8_t input;
  
  radio.read(&input, sizeof(input));

  return input;
}

void processInput(const uint8_t input) {
  Serial.print("Processing input: ");
  Serial.println(input, DEC);

  if (input == currentState) Serial.println("Ignoring repeated input."); return;

  switch (input) {
    case INPUT_NONE: Serial.println("No input available."); return;
    
    case INPUT_STOP: stopMotors(); break;
    case INPUT_COAST: coastMotors(); break;
    
    case INPUT_FORWARD_SLOW: moveForward(SPEED_SLOW); break;
    case INPUT_FORWARD_FAST: moveForward(SPEED_FAST); break;
    
    case INPUT_BACKWARD_SLOW: moveBackward(SPEED_SLOW); break;
    case INPUT_BACKWARD_FAST: moveBackward(SPEED_FAST); break;
    
    case INPUT_LEFT_SLOW: moveLeft(SPEED_SLOW); break;
    case INPUT_LEFT_FAST: moveLeft(SPEED_FAST); break;
    
    case INPUT_RIGHT_SLOW: moveRight(SPEED_SLOW); break;
    case INPUT_RIGHT_FAST: moveRight(SPEED_FAST); break;

    default: Serial.println("Invalid input."); return;
  }

  currentState = input;
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
