#include "Arduino.h"
#include "encoder.h"

#include "motorControl.h"

void encoder_class::SETUP() {
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), int_right, RISING );

  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), int_left, RISING );

  motor.SETUP();
}

void encoder_class::goDistanceForward(unsigned long int count){
    motor.forward();
    Serial.println(count);
    while(count > intr_count_r){
             Serial.print('a');               

    }

    motor.stop();
    intr_count_l=0;
    intr_count_r=0;

}


void encoder_class::goDistanceReverse(unsigned long int count){
    motor.reverse();
     Serial.println(count);
    while(count > intr_count_r){
         Serial.print('a');

    }

    motor.stop();
    intr_count_l=0;
    intr_count_r=0;
}

void encoder_class::goDistanceRight(unsigned long int count){
    motor.rightTurn();
     Serial.println(count);
    while(count > intr_count_l){
         Serial.print('a');

    }

    motor.stop();
    intr_count_l=0;
    intr_count_r=0;
}

void encoder_class::goDistanceLeft(unsigned long int count){
    motor.leftTurn();
     Serial.println(count);
    while(count > intr_count_r){
         Serial.print('a');

    }

    motor.stop();
    intr_count_l=0;
    intr_count_r=0;
  }
  
  void encoder_class::getPulsesLeft(unsigned long int *count_l){
    *count_l  =  intr_count_l;

    intr_count_l=0;
  }
  
  
  void encoder_class::getPulsesRight(unsigned long int *count_r){
    *count_r =  intr_count_r;

     intr_count_r=0;
  }

 void encoder_class::getPulsesLeft_no_reset(unsigned long int *count_l){
    *count_l  =  intr_count_l;

  }
  
  
  void encoder_class::getPulsesRight_no_reset(unsigned long int *count_r){
    *count_r =  intr_count_r;

  }


  void encoder_class::resetEncoderValues(){
     intr_count_l=0;
     intr_count_r=0;
     
}

static void encoder_class::int_left() {
   intr_count_l++;
}

static void encoder_class::int_right() {
   intr_count_r++;
}

encoder_class encoder = encoder_class();
