#include <Arduino.h>
#include <Servo.h>
#include <pspc_support.h>
#include "gestures.h"
#include "dual_servo.h"

// Defaults for curve attributes
#define FOCUS 2
#define MAX_DELAY 10
#define DEFAULT_MULTIPLIER 10

Gestures::Gestures(DualServo *servos, int horizontalPosition, int verticalPosition) {
  _servos = servos;
  _horizontalPosition = horizontalPosition;
  _verticalPosition = verticalPosition;
  _maxDelay = MAX_DELAY;
  _focus = FOCUS;
  _multiplier = DEFAULT_MULTIPLIER;
}

void Gestures::begin() {
}

void Gestures::positionServos() {
  // Position the servos where we want them
  _servos->horizontalValue(_horizontalPosition);
  _servos->verticalValue(_verticalPosition);
}

void Gestures::positionServos(int horizontalPosition, int verticalPosition) {
  _horizontalPosition = horizontalPosition;
  _verticalPosition = verticalPosition;
  positionServos();
}

void Gestures::setMaxDelay(int delay) {
#ifdef GESTURE_DEBUG
  Serial.print(P("Delay: ")); Serial.println(delay);
#endif
  _maxDelay = delay;
}

int Gestures::getMaxDelay() {
  return _maxDelay;
}

void Gestures::setFocus(int focus) {
#ifdef GESTURE_DEBUG
  Serial.print(P("Focus: ")); Serial.println(delay);
#endif
  _focus = focus;
}

int Gestures::getFocus() {
  return _focus;
}

void Gestures::setMultiplier(int multiplier) {
#ifdef GESTURE_DEBUG
  Serial.print(P("Multiplier: ")); Serial.println(multiplier);
#endif
  _multiplier = multiplier;
}

int Gestures::getMultiplier() {
  return _multiplier;
}

int Gestures::getHorizontalPosition() {
  return _horizontalPosition;
}

int Gestures::getVerticalPosition() {
  return _verticalPosition;
}

void Gestures::shakeYourHead() {
  int len = 8;
  byte path[] = { 10, GO_LEFT, 20, GO_RIGHT, 20, GO_LEFT, 10, GO_RIGHT };
  followPath(path, len);
}

void Gestures::nodYourHead() {
  int len = 8;
  byte path[] = { 10, GO_UP, 20, GO_DOWN, 20, GO_UP, 10, GO_DOWN };
  followPath(path, len);
}

void Gestures::dejectedShakeYourHead() {
  int len = 12;
  byte path[] = { 20, GO_DOWN, 10, GO_LEFT, 20, GO_RIGHT, 20, GO_LEFT, 10, GO_RIGHT, 20, GO_UP };
  followPath(path, len);
}

int Gestures::calculateDelay(int x) {
  return abs(_multiplier * (_maxDelay - int(sqrt(4 * _focus * x))));
}

void Gestures::followPath(byte *path, int length) {
#ifdef GESTURE_DEBUG
  Serial.print(P("Length of path: ")); Serial.println(length);
#endif
  for (int p=0; p<length; p += 2) {
    int degrees = path[p];
    byte direction = path[p + 1];
#ifdef GESTURE_DEBUG
    Serial.print(P("Degrees: ")); Serial.println(degrees);
    Serial.print(P("Direction: ")); Serial.println(direction);
#endif
    int halfArc = int(degrees / 2);
    for (int a=0; a < degrees; a++) {
      int x = (a < halfArc) ? a : (degrees - a);
      int delayTime = calculateDelay(x + 1);
#ifdef GESTURE_DEBUG
      Serial.print(P("Degree, Delay ")); Serial.print(a); Serial.print(P(",")); Serial.println(delayTime);
#endif
      delay(delayTime);
      switch (direction) {
        case GO_LEFT:
          _servos->horizontalValue(--_horizontalPosition);
          break;
        case GO_RIGHT:
          _servos->horizontalValue(++_horizontalPosition);
          break;
        case GO_UP:
          _servos->verticalValue(++_verticalPosition);
          break;
        case GO_DOWN:
          _servos->verticalValue(--_verticalPosition);
          break;
      }
    }
  }
}
