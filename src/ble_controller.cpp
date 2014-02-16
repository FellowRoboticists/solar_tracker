// solar_tracker Arduino sketch
//
// Copyright (c) 2013,2014 Dave Sieh
//
// See LICENSE.txt for details.

#include <ble_shield.h>
#include "ble_controller.h"

BLEController::BLEController() {
  for (int i=0; i<MAX_COMMANDS; i++) {
    _commands[i] = (commandPtr) 0;
  }
}

void BLEController::begin() {
  // Get the bluetooth shield going
  ble_begin();
}

void BLEController::addCommand(int index, commandPtr cmd) {
  _commands[index] = cmd;
}

void BLEController::processIncomingData() {
  // Read data until there is no more...
  while (ble_available()) {
    // read out command and data
    byte data0 = ble_read();
    byte data1 = ble_read();
    byte data2 = ble_read();

    if (data0 < MAX_COMMANDS && _commands[data0] != (commandPtr) 0) {
      _commands[data0](data1, data2);
    }
  }
}

boolean BLEController::connected() {
  ble_connected();
}

void BLEController::processEvents() {
  // Allow BLE Shield to send/receive data
  ble_do_events();  
}
void BLEController::sendCommand(byte command, byte byte1, byte byte2) {
  ble_write(command);
  ble_write(byte1);
  ble_write(byte2);
}

void BLEController::sendCommand(byte command, uint16_t intValue) {
  ble_write(command);
  ble_write(intValue >> 8);
  ble_write(intValue);
}
