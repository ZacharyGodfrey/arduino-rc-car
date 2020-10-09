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

// TODO: Map these to actual pin numbers
#define PIN_UP 0
#define PIN_DOWN 0
#define PIN_LEFT 0
#define PIN_RIGHT 0
#define PIN_GAS 0
#define PIN_BRAKE 0

RF24 radio(RADIO_PIN_CE, RADIO_PIN_CSN);

void setup() {
  Serial.begin(BAUD_RATE);

  const byte radioAddress[6] = RADIO_ADDRESS;

  radio.begin();
  radio.openWritingPipe(radioAddress);
  radio.stopListening();
}

void loop() {
  uint8_t nextState = getNextState();

  sendNextState(nextState);

  delay(2000); // TODO: Remove after testing.
}

uint8_t getNextState() {
  return STATE_DRIVE_SLOW; // TODO: Remove after testing.
}

void sendNextState(const uint8_t nextState) {
  radio.write(&nextState, sizeof(nextState));
}
