// solar_tracker Arduino sketch
//
// Copyright (c) 2013,2014 Dave Sieh
//
// See LICENSE.txt for details.

#ifndef _BLE_CONTROLLER_H_
#define _BLE_CONTROLLER_H_

// The maximum number of commands that can be 
// registered with the controller.
#define MAX_COMMANDS 10

// The prototype of a command function that can
// be registered with the controller to handle
// a particular incoming command.
typedef void (*commandPtr)(byte byte1, byte byte2);

/**
 * Manages the relationship between the Arduino and
 * a connected BLE application.
 */
class BLEController {
  public:

    /**
     * Constructs a new BLEController.
     */
    BLEController();

    /**
     * Prepares the BLEController for operations. Typically
     * called in the sketch setup.
     */
    void begin();

    /**
     * Adds a command to be invoked when it comes in on the
     * BLE. A maximum of MAX_COMMANDS can be registered with
     * the controller.
     *
     * index the index into to the array of commands. This
     *       doubles as the command identifier. So command
     *       0x00 is index 0, 0x01 is index 1, and so on.
     *
     * cmd   a pointer to the function to be invoked for a
     *       given command.
     */
    void addCommand(int index, commandPtr cmd);

    /**
     * Loops until all inbound data from the BLE has been
     * received and processed. As each set of commands is
     * read, they are interpreted as commands and processed
     * through the registered command handlers (see
     * addCommand(...).
     */
    void processIncomingData();

    /**
     * Responds true if the BLE is currently connected to
     * an application.
     */
    boolean connected();

    /**
     * Allows time for the BLE to trade information with the
     * connected application.
     */
    void processEvents();

    /**
     * Prepares a command to be sent to the connected 
     * application.
     *
     * command a byte of data identifying the command to the
     *         connected application. Application-specific.
     * byte1   the first byte of data associated with the
     *         command.
     * byte2   the second byte of data associated with the
     *         command.
     */
    void sendCommand(byte command, byte byte1, byte byte2);

    /**
     * Prepares a command to be sent to the connected
     * application.
     *
     * command a byte of data identifying the command to the
     *         connected application. Application-specific.
     * intValue the integer value associated with the 
     *          command.
     */
    void sendCommand(byte command, uint16_t intValue);

  private:
    commandPtr _commands[MAX_COMMANDS];
};

#endif
