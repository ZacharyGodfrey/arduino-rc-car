// Adafruit Motor Shield V2
#include <Adafruit_MotorShield.h>

// RF24 for radio frequency input
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define BAUD_RATE 9600

#define RADIO_PIN_CE 7
#define RADIO_PIN_CSN 8
#define RADIO_ADDRESS "RCCAR"

#define STATE_NONE 0
#define STATE_BRAKE 1
#define STATE_COAST 2
#define STATE_DRIVE_SLOW 3
#define STATE_DRIVE_FAST 4
#define STATE_REVERSE_SLOW 5
#define STATE_REVERSE_FAST 6
#define STATE_LEFT_SLOW 7
#define STATE_LEFT_FAST 8
#define STATE_RIGHT_SLOW 9
#define STATE_RIGHT_FAST 10

#define SPEED_SLOW 50
#define SPEED_FAST 200

Adafruit_MotorShield motorShield = Adafruit_MotorShield();
Adafruit_DCMotor *leftFront = motorShield.getMotor(1);
Adafruit_DCMotor *rightFront = motorShield.getMotor(4);
Adafruit_DCMotor *leftRear = motorShield.getMotor(2);
Adafruit_DCMotor *rightRear = motorShield.getMotor(3);

RF24 radio(RADIO_PIN_CE, RADIO_PIN_CSN);

uint8_t currentState = STATE_NONE;

void setup() {
  Serial.begin(BAUD_RATE);

  motorShield.begin();

  const byte radioAddress[6] = RADIO_ADDRESS;

  radio.begin();
  radio.openReadingPipe(0, radioAddress);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  uint8_t nextState = getNextState(radio);
  bool stateChanged = processNextState(nextState);

  if (stateChanged) {
    currentState = nextState;
  }
}

uint8_t getNextState(const RF24 radio) {
  if (!radio.available()) {
    return STATE_NONE;
  }

  uint8_t input;

  radio.read(&input, sizeof(input));

  return input;
}

bool processNextState(const uint8_t nextState) {
  if (nextState == STATE_NONE || nextState == currentState) {
    return false; // Ignore missing or repeated input from RF.
  }

  switch (nextState) {
    case STATE_BRAKE: return brake();
    case STATE_COAST: return coast();

    case STATE_DRIVE_SLOW: return drive(SPEED_SLOW);
    case STATE_DRIVE_FAST: return drive(SPEED_FAST);

    case STATE_REVERSE_SLOW: return reverse(SPEED_SLOW);
    case STATE_REVERSE_FAST: return reverse(SPEED_FAST);

    case STATE_LEFT_SLOW: return turnLeft(SPEED_SLOW);
    case STATE_LEFT_FAST: return turnLeft(SPEED_FAST);

    case STATE_RIGHT_SLOW: return turnRight(SPEED_SLOW);
    case STATE_RIGHT_FAST: return turnRight(SPEED_FAST);

    default: return badInput(nextState);
  }
}

bool brake() {
  Serial.println("Brake");

  leftFront->setSpeed(0);
  rightFront->setSpeed(0);
  leftRear->setSpeed(0);
  rightRear->setSpeed(0);

  return true;
}

bool coast() {
  Serial.println("Coast");

  leftFront->run(RELEASE);
  rightFront->run(RELEASE);
  leftRear->run(RELEASE);
  rightRear->run(RELEASE);

  return true;
}

bool drive(const uint8_t speed) {
  Serial.print("Drive:");
  Serial.println(speed, DEC);

  leftFront->setSpeed(speed);
  rightFront->setSpeed(speed);

  leftRear->setSpeed(speed);
  rightRear->setSpeed(speed);

  leftFront->run(FORWARD);
  rightFront->run(FORWARD);

  leftRear->run(FORWARD);
  rightRear->run(FORWARD);

  return true;
}

bool reverse(const uint8_t speed) {
  Serial.print("Reverse:");
  Serial.println(speed, DEC);

  leftFront->setSpeed(speed);
  rightFront->setSpeed(speed);

  leftRear->setSpeed(speed);
  rightRear->setSpeed(speed);

  leftFront->run(BACKWARD);
  rightFront->run(BACKWARD);

  leftRear->run(BACKWARD);
  rightRear->run(BACKWARD);

  return true;
}

bool turnLeft(const uint8_t speed) {
  Serial.print("Left:");
  Serial.println(speed, DEC);

  leftFront->setSpeed(speed);
  leftRear->setSpeed(speed);

  rightFront->setSpeed(speed);
  rightRear->setSpeed(speed);

  leftFront->run(BACKWARD);
  leftRear->run(BACKWARD);

  rightFront->run(FORWARD);
  rightRear->run(FORWARD);

  return true;
}

bool turnRight(const uint8_t speed) {
  Serial.print("Right:");
  Serial.println(speed, DEC);

  leftFront->setSpeed(speed);
  leftRear->setSpeed(speed);

  rightFront->setSpeed(speed);
  rightRear->setSpeed(speed);

  leftFront->run(FORWARD);
  leftRear->run(FORWARD);

  rightFront->run(BACKWARD);
  rightRear->run(BACKWARD);

  return true;
}

bool badInput(const uint8_t input) {
  Serial.print("Bad Input: ");
  Serial.println(input, DEC);

  return false;
}