// solar_tracker Arduino sketch
//
// Copyright (c) 2013,2014 Dave Sieh
//
// See LICENSE.txt for details.
//

#ifndef _DUAL_SERVO_H_
#define _DUAL_SERVO_H_


// Prototype for a callback that receives calls of updates
// to the servo locations.
typedef void (*reportServoValuesPtr)(byte horizontal, byte vertical);

class Servo;

class DualServo {
  public:

    /**
     * Constructs a new DualServo object.
     *
     * horizontalPin the pin to which the horizontal servo is connected.
     * verticalPin   the pin to which the vertical servo is connected.
     * rptSV         the callback to which servo location updates are made.
     */
    DualServo(int horizontalPin, int verticalPin, reportServoValuesPtr rptSV);

    /**
     * Called to prepare the DualServo object for use. Typically called
     * in the sketch setup method.
     */
    void begin();

    /**
     * Move the servos by an increment depending on the value of 
     * the bump flag. If the bump flag is 0, the servo position
     * will not change. If the bump flag is negative, the
     * position of the servo will be decremented. If the bump
     * flag is positive, the position of the servo will be
     * incremented.
     */
    void bumpServoLocations(int horzBumpFlag, int vertBumpFlag);

    /**
     * Move the horz/vert servo to the specified
     * angle. Automatically clamped to valid
     * value.
     */
    void horizontalValue(int value);
    void verticalValue(int value);

  private:
    /**
     * Returns the value clamped to valid values for the
     * servos.
     */
    int clampValue(int value);

    void bumpHorizontalValue(int bumpFlag);
    void bumpVerticalValue(int bumpFlag);

    int _horizontalPin;
    int _verticalPin;

    int _horizontalValue;
    int _verticalValue;

    Servo _horizontal;
    Servo _vertical;

    reportServoValuesPtr _reportServoValues;
};

#endif
