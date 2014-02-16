// solar_tracker Arduino sketch
//
// Copyright (c) 2013,2014 Dave Sieh
//
// See LICENSE.txt for details.

#ifndef _LIGHT_DIRECTION_SENSOR_H_
#define _LIGHT_DIRECTION_SENSOR_H_

// Function prototype for a callback that receives updates
// to the current readings of the LDR's.
typedef void (*reportSensorValuePtr)(int leftTop, int leftBottom, int rightTop, int rightBottom);

/**
 * Responsible for managing the light direction sensor and the
 * associated LDR's.
 */
class LightDirectionSensor {
  public:

    /**
     * Constructs a new LightDirectionSensor object.
     *
     * leftTopPin     pin for the left top LDR
     * rightTopPin    pin for the right top LDR
     * leftBottomPin  pin for the left bottom LDR
     * rightBottomPin pin for the right bottom LDR
     * rptSV          the callback for reporting LDR values.
     */
    LightDirectionSensor(int leftTopPin, 
                         int rightTopPin, 
                         int leftBottomPin, 
                         int rightBottomPin,
                         reportSensorValuePtr rptSV);

    /**
     * Prepares the LightDirectionSensor for use. Typically
     * called in the sketch's setup method.
     */
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

    // The function pointer to report sensor values
    reportSensorValuePtr _rptSensorValue;

};

#endif
