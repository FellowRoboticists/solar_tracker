// solar_tracker Arduino sketch
//
// Copyright (c) 2013,2014 Dave Sieh
//
// See LICENSE.txt for details.

#include <Arduino.h>
#include "light_direction_sensor.h"

#define DEFAULT_TOLERANCE 20

LightDirectionSensor::LightDirectionSensor(
    int leftTopPin, 
    int rightTopPin, 
    int leftBottomPin, 
    int rightBottomPin) {

  this->_leftTopPin = leftTopPin;
  this->_rightTopPin = rightTopPin;
  this->_leftBottomPin = leftBottomPin;
  this->_rightBottomPin = rightBottomPin;
  this->_tolerance = DEFAULT_TOLERANCE;
}

void LightDirectionSensor::begin() {
  // Nothing at this point. You never know.
}

int LightDirectionSensor::tolerance() {
  return _tolerance;
}

void LightDirectionSensor::tolerance(int tolerance) {
  this->_tolerance = tolerance;
}

int LightDirectionSensor::averageTopValue() {
  return (_vLT + _vRT) / 2;
}

int LightDirectionSensor::averageBottomValue() {
  return (_vLB + _vRB) / 2;
}

int LightDirectionSensor::averageLeftValue() {
  return (_vLT + _vLB) / 2;
}

int LightDirectionSensor::averageRightValue() {
  return (_vRT + _vRB) / 2;
}

int LightDirectionSensor::differenceHorizontal() {
  return averageLeftValue() - averageRightValue();
}

int LightDirectionSensor::differenceVertical() {
  return averageBottomValue() - averageTopValue();
}

int LightDirectionSensor::horizontalDifferenceOutsideTolerance() {
  int diffHorz = differenceHorizontal();
  return (abs(diffHorz) > _tolerance) ? diffHorz : 0;
}

int LightDirectionSensor::verticalDifferenceOutsideTolerance() {
  int diffVert = differenceVertical();
  return (abs(diffVert) > _tolerance) ? diffVert : 0;
}

void LightDirectionSensor::readValues() {
  // Read the current values of the LDRs
  int vLT = analogRead(_leftTopPin);
  int vRT = analogRead(_rightTopPin);
  int vLB = analogRead(_leftBottomPin);
  int vRB = analogRead(_rightBottomPin);
  
  Serial.print("vLT = "); Serial.println(vLT);
  Serial.print("vRT = "); Serial.println(vRT);
  Serial.print("vLB = "); Serial.println(vLB);
  Serial.print("vRB = "); Serial.println(vRB);
  Serial.println("");
}
