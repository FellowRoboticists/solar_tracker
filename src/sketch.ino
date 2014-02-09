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

#define DELAY_TIME 100

// Set up the digital pin assignments
#define HORIZONTAL_SERVO_PIN 9
#define VERTICAL_SERVO_PIN 10

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

  int hdot = lds.horizontalDifferenceOutsideTolerance();
  int vdot = lds.verticalDifferenceOutsideTolerance();

  servos.bumpServoLocations(hdot, vdot);

  delay(DELAY_TIME);
}
