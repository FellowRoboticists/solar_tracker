// -*- c -*-
// solar_tracker Arduino sketch
//
// Copyright (c) 2013,2014 Dave Sieh
//
// See LICENSE.txt for details.

#include <Servo.h> // Include the Servo Library
#include <ble_shield.h>
#include "dual_servo.h"
#include "light_direction_sensor.h"
#include "ble_controller.h"

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
    VERTICAL_SERVO_PIN,
    &reportServoValues);

LightDirectionSensor lds(LDR_LEFT_TOP, 
    LDR_RIGHT_TOP, 
    LDR_LEFT_BOTTOM, 
    LDR_RIGHT_BOTTOM,
    &reportLightSensorValues);

BLEController controller;

// This is a toggle that enables/disables use
// of the light sensor to control the positioning
// of the servos. Defaults to 'true'.
boolean lightSensing = true;

void setup() {
  Serial.begin(9600);

  // Initialize and start the BLE library
  // controller_begin();
  controller.begin();

  // Register the commands to be processed from
  // the bluetooth device
  controller.addCommand(0, &toggleLightDirectionSensing);
  controller.addCommand(1, &positionServos);

  // Set up the Servo connections 
  servos.begin();

  // Set up the light direction sensor
  lds.tolerance(LIGHT_TOLERANCE);
  lds.begin();

  Serial.println("Ready");
}

void loop() {

  if (lightSensing) {
    // Here we want the light sensors to control the servos
    processLightSensor();
  } else {
    // Here we just want to read the light sensors
    lds.readValues();
  }
  
  // Be aware that what this method does is to read any available
  // data from the BLE shield and invokes the commands registered
  // in the setup method.
  controller.processIncomingData();

  // Anything that only makes sense to do when the BLE Shield isn't
  // connected should be done here.
  if (!controller.connected()) {
    lightSensing = true;
  }

  // Allow BLE Shield to send/receive data
  controller.processEvents();  

  if (lightSensing) delay(DELAY_TIME);
}

void processLightSensor() {
  // Have the light detection sensor check out
  // what's going on.
  lds.readValues();

  // So here's the deal with hdot and vdot. The absolute value of the
  // variacontrollers is not important. Only the sign is of significance:
  //
  // *dot < 0 - means the servo must move left/down
  // *dot = 0 - means the servo can stay where it is
  // *dot > 0 - means the servo must move right/up
  //
  int hdot = 0;
  int vdot = 0;
  lds.differenceOutsideTolerance(hdot, vdot);

  servos.bumpServoLocations(hdot, vdot);
}

//
// The following are commands supported by the
// BLE Shield.
//

void toggleLightDirectionSensing(byte byte1, byte byte2) {
  Serial.println("TLDS");
  lightSensing = byte1 == 0x01;
}

void positionServos(byte byte1, byte byte2) {
  if (lightSensing) return;
  Serial.println("PS");
  servos.horizontalValue(byte1);
  servos.verticalValue(byte2);
}

//
// The following are callbacks to send outbound data
//

void reportLightSensorValues(int leftTop, 
                             int leftBottom, 
                             int rightTop, 
                             int rightBottom) {

  // Get out early if we're not connected to the BLE
  if (!controller.connected()) return;

  controller.sendCommand(0x10, leftTop);
  controller.sendCommand(0x11, leftBottom);
  controller.sendCommand(0x12, rightTop);
  controller.sendCommand(0x13, rightBottom);
}

void reportServoValues(byte horizontal, byte vertical) {
  // Get out early if we're not connected to the BLE
  if (!controller.connected()) return;

  controller.sendCommand(0x20, horizontal, vertical);
}
