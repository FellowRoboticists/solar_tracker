#ifndef _GESTURES_H_
#define _GESTURES_H_

#define DEFAULT_HORIZONTAL_POSITION 90
#define DEFAULT_VERTICAL_POSITION 30

#define GO_LEFT 0x00
#define GO_RIGHT 0x01
#define GO_UP 0x02
#define GO_DOWN 0x03

class DualServo;

/**
 * Provides a means of performing 'human scale' gestures. At least
 * it does it's best.
 */
class Gestures {
  public:

    /**
     * Constructs a new Gestures object
     *
     * servos - an instance of the DualServo object to control.
     * horizontalPosition - the starting position for the horz servo
     * verticalPostion - the starting position for the vert servo
     */
    Gestures(DualServo *servos, int horizontalPosition, int verticalPosition);

    /**
     * Prepares the gestures object for use. Typically called in the
     * setup() method of a sketch.
     */
    void begin();

    // Accessors
    
    void setMaxDelay(int delay);
    int getMaxDelay();

    void setFocus(int focus);
    int getFocus();

    void setMultiplier(int multiplier);
    int getMultiplier();

    int getHorizontalPosition();
    int getVerticalPosition();
    
    // Some canned gestures

    void shakeYourHead();
    void nodYourHead();
    void dejectedShakeYourHead();

    /**
     * A generic method to allow a vector of path information to
     * be followed by the servos. See one of the canned gestures
     * for an example.
     *
     * path - a vector of path information
     * length - the length of the path vector.
     */
    void followPath(byte *path, int length);

    void positionServos();
    void positionServos(int horizontalPosition, int verticalPosition);

  private:

    int calculateDelay(int x);

    DualServo *_servos;

    int _horizontalPosition;
    int _verticalPosition;

    int _maxDelay;
    int _focus;
    int _multiplier;
};

#endif
