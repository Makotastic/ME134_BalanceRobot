#include <Arduino.h>
#include <encoder.h>

//change these
const int ENCODER_CLK = 10;
const int ENCODER_DT = 13;

int currentStateCLK;
int lastStateCLK;
bool isCw;
int TotalTicks = 0;
int prevTicks = 0;
unsigned long pastTimeEncoder = micros();

bool getisCW() {
    return isCw;
}

float getTickRate() {
    float rate = (TotalTicks - prevTicks) * (float)(micros() - pastTimeEncoder) / 1000000;
    prevTicks = TotalTicks;
    pastTimeEncoder = micros();
    return rate;
}

float getTotalTicks() {
    return TotalTicks;
}

void handleCLK() {
  int clkState = digitalRead(ENCODER_CLK);
  int dtState = digitalRead(ENCODER_DT);

  // Determine the direction
  if (clkState != dtState) {
    TotalTicks++;  // Clockwise
    isCw = true;
  } else {
    TotalTicks--;  // Counterclockwise
    isCw = false;
  }
}

// Interrupt Service Routine (ISR) for DT pin
void handleDT() {
  int clkState = digitalRead(ENCODER_CLK);
  int dtState = digitalRead(ENCODER_DT);

  // Determine the direction
  if (clkState == dtState) {
    TotalTicks++;  // Clockwise
    isCw = true;
  } else {
    TotalTicks--;  // Counterclockwise
    isCw = false;
  }
}


void encoderSetup() {
    pinMode(ENCODER_CLK,INPUT);
	pinMode(ENCODER_DT,INPUT);

    lastStateCLK = digitalRead(ENCODER_CLK);

    attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), handleCLK, CHANGE);
	attachInterrupt(digitalPinToInterrupt(ENCODER_DT), handleDT, CHANGE);
}