#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

bool getisCW();

float getTickRate();

void encoderSetup();

float getTotalTicks();

#endif