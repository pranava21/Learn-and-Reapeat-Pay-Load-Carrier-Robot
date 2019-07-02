#ifndef motorControl_h
#define motorControl_h


#include "Arduino.h"

#define DEFAULT_usSpeed 37
class motorControl{

  private:
    void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm);
  
  public:   
    motorControl();
    void SETUP();
    void stop();
    void forward();
    void reverse();
    void rightTurn();
    void leftTurn();
    void increaseSpeed();
    void decreaseSpeed();
    void setSpeed(int speed);
    void changeSpeedLeft(int pwm);
    int getSpeed();

};

extern motorControl motor;

#endif
