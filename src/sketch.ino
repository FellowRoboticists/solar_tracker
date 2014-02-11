// -*- c -*-
// solar_tracker Arduino sketch
//
// Copyright (c) 2013,2014 Dave Sieh
//
// See LICENSE.txt for details.

#include <Servo.h> // Include the Servo Library
#include "dual_servo.h"
#include "light_direction_sensor.h"

// Set up the initial pin connections for the LDRs
// name = analogpin
#define LDR_LEFT_TOP 0
#define LDR_RIGHT_TOP 1
#define LDR_LEFT_BOTTOM 2
#define LDR_RIGHT_BOTTOM 3

#define DELAY_TIME 200

// Set up the digital pin assignments
// We're going with pins 6 and 7 because we eventually want
// to incorporate the BLE shield and it eats up pins 9 and 10
// which are the pins most often referenced in servo sketches.
// The fact of the matter is that it works fine on just about
// any other digital pins.
#define HORIZONTAL_SERVO_PIN 6
#define VERTICAL_SERVO_PIN 7

#define LIGHT_TOLERANCE 20

DualServo servos(HORIZONTAL_SERVO_PIN, 
                 VERTICAL_SERVO_PIN);

LightDirectionSensor lds(LDR_LEFT_TOP, 
                         LDR_RIGHT_TOP, 
                         LDR_LEFT_BOTTOM, 
                         LDR_RIGHT_BOTTOM);

void setup() {
  Serial.begin(9600);
  
  // Set up the Servo connections 
  servos.begin();

  // Set up the light direction sensor
  lds.tolerance(LIGHT_TOLERANCE);
  lds.begin();

  Serial.println("Ready");
}

void loop() {
  // Have the light detection sensor check out
  // what's going on.
  lds.readValues();

  // So here's the deal with hdot and vdot. The absolute value of the
  // variables is not important. Only the sign is of significance:
  //
  // *dot < 0 - means the servo must move left/down
  // *dot = 0 - means the servo can stay where it is
  // *dot > 0 - means the servo must move right/up
  //
  int hdot = 0;
  int vdot = 0;
  lds.differenceOutsideTolerance(hdot, vdot);

  Serial.println("---------------------------------------------------");
  Serial.print("HDOT: "); Serial.println(hdot);
  Serial.print("VDOT: "); Serial.println(vdot);

  servos.bumpServoLocations(hdot, vdot);

  delay(DELAY_TIME);
}
