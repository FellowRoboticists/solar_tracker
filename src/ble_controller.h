#ifndef _BLE_CONTROLLER_H_
#define _BLE_CONTROLLER_H_

#define MAX_COMMANDS 10

typedef void (*commandPtr)(byte byte1, byte byte2);

class BLEController {
  public:

    BLEController();

    void begin();

    void addCommand(int index, commandPtr cmd);

    void processIncomingData();

    int connected();

    void processEvents();

  private:
    commandPtr _commands[MAX_COMMANDS];
};

#endif
