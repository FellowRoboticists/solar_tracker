// solar_tracker Arduino sketch
//
// Copyright (c) 2013,2014 Dave Sieh
//
// See LICENSE.txt for details.

#include <Arduino.h>
#include <pspc_support.h>
#include "light_direction_sensor.h"

#define DEFAULT_TOLERANCE 20

LightDirectionSensor::LightDirectionSensor(
    int leftTopPin, 
    int rightTopPin, 
    int leftBottomPin, 
    int rightBottomPin,
    reportSensorValuePtr rptSV) {

  this->_leftTopPin = leftTopPin;
  this->_rightTopPin = rightTopPin;
  this->_leftBottomPin = leftBottomPin;
  this->_rightBottomPin = rightBottomPin;
  this->_tolerance = DEFAULT_TOLERANCE;
  this->_rptSensorValue = rptSV;
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

void LightDirectionSensor::differenceOutsideTolerance(int &hdot, int &vdot) {
  hdot = horizontalDifferenceOutsideTolerance();
  vdot = verticalDifferenceOutsideTolerance();
}

void LightDirectionSensor::readValues() {
  // Read the current values of the LDRs
  _vLT = analogRead(_leftTopPin);
  _vRT = analogRead(_rightTopPin);
  _vLB = analogRead(_leftBottomPin);
  _vRB = analogRead(_rightBottomPin);

  if (_rptSensorValue) _rptSensorValue(_vLT, _vLB, _vRT, _vRB);
  
#ifdef LDS_DEBUG
  Serial.print(P("vLT = ")); Serial.println(_vLT);
  Serial.print(P("vRT = ")); Serial.println(_vRT);
  Serial.print(P("vLB = ")); Serial.println(_vLB);
  Serial.print(P("vRB = ")); Serial.println(_vRB);
  Serial.println(P(""));
#endif
}
