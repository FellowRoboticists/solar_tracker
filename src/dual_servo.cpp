// solar_tracker Arduino sketch
//
// Copyright (c) 2013,2014 Dave Sieh
//
// See LICENSE.txt for details.
//
#include <Arduino.h>
#include <Servo.h>
#include "dual_servo.h"

#define MIN_SERVO_ANGLE 0
#define MAX_SERVO_ANGLE 180

#define DEFAULT_HORIZONTAL_VALUE 90
#define DEFAULT_VERTICAL_VALUE 90

#define INCREMENT_VALUE 1

DualServo::DualServo(
    int horizontalPin, 
    int verticalPin) {

  this->_horizontalPin = horizontalPin;
  this->_verticalPin = verticalPin;
  this->_horizontalValue = DEFAULT_HORIZONTAL_VALUE;
  this->_verticalValue = DEFAULT_VERTICAL_VALUE;
}

void DualServo::begin() {
  _horizontal.attach(_horizontalPin);
  _horizontal.write(_horizontalValue);

  _vertical.attach(_verticalPin);
  _vertical.write(_verticalValue);
}

void DualServo::horizontalValue(int value) {
  int newValue = clampValue(value);
  if (newValue != _horizontalValue) {
    _horizontalValue = newValue;
    _horizontal.write(_horizontalValue);
  }
}

void DualServo::verticalValue(int value) {
  int newValue = clampValue(value);
  if (newValue != _verticalValue) {
    _verticalValue = newValue;
    _vertical.write(_verticalValue);
  }
}

void DualServo::bumpHorizontalValue(int bumpFlag) {
  if (bumpFlag > 0)
    horizontalValue(_horizontalValue + INCREMENT_VALUE);
  else
    horizontalValue(_horizontalValue - INCREMENT_VALUE);
}

void DualServo::bumpVerticalValue(int bumpFlag) {
  if (bumpFlag > 0)
    verticalValue(_verticalValue + INCREMENT_VALUE);
  else
    verticalValue(_verticalValue - INCREMENT_VALUE);
}

void DualServo::bumpServoLocations(
    int horzBumpFlag, 
    int vertBumpFlag) {

  bumpHorizontalValue(horzBumpFlag);
  bumpVerticalValue(vertBumpFlag);
}

int DualServo::clampValue(int value) {
  return constrain(value, 
                   MIN_SERVO_ANGLE, 
                   MAX_SERVO_ANGLE);
}
