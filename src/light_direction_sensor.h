// solar_tracker Arduino sketch
//
// Copyright (c) 2013,2014 Dave Sieh
//
// See LICENSE.txt for details.

#ifndef _LIGHT_DIRECTION_SENSOR_H_
#define _LIGHT_DIRECTION_SENSOR_H_

class LightDirectionSensor {
  public:

    LightDirectionSensor(int leftTopPin, 
                         int rightTopPin, 
                         int leftBottomPin, 
                         int rightBottomPin);

    void begin();

    // Get/set the tolerance value for light sensing
    int tolerance();
    void tolerance(int tolerance);

    // Request the current values from the LDRs
    void readValues();

    // Return the average value from the LDRs
    int averageTopValue();
    int averageBottomValue();
    int averageLeftValue();
    int averageRightValue();

    // Return the horizontal/vertical difference
    int differenceHorizontal();
    int differenceVertical();

    // Returns the horz/vert difference if the
    // difference is outside of tolerance, else
    // returns 0
    int horizontalDifferenceOutsideTolerance();
    int verticalDifferenceOutsideTolerance();
    void differenceOutsideTolerance(int &hdot, int &vdot);

  private:

    // The tolerance required for change
    int _tolerance;

    // The pins connected to the LDRs
    int _leftTopPin;
    int _rightTopPin;
    int _leftBottomPin;
    int _rightBottomPin;

    // The values read from the sensor
    int _vLT;
    int _vRT;
    int _vLB;
    int _vRB;

};

#endif
