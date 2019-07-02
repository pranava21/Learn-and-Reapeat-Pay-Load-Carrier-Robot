//--------------------- Includes ---------------------------//

#include "Arduino.h"
#include "motorControl.h"

//--------------------- Gobal variables ---------------------------//


#define BRAKE 0
#define CW    1
#define CCW   2

//MOTOR 1
#define MOTOR_R_A_PIN 4
#define MOTOR_R_B_PIN 9

//MOTOR 2
#define MOTOR_L_A_PIN 8
#define MOTOR_L_B_PIN 7

#define PWM_MOTOR_R 6
#define PWM_MOTOR_L 5

#define EN_PIN_R A1
#define EN_PIN_L A0

#define MOTOR_R 1
#define MOTOR_L 0


    int usSpeed;
    int usMotor_Status;
    


//--------------------- Functions ---------------------------//

motorControl::motorControl(){
 	usSpeed = DEFAULT_usSpeed;  //default motor speed
  usMotor_Status = BRAKE;
}

void motorControl::motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)         //Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
{
  if(motor == MOTOR_R)
  {
    if(direct == CW)
    {
      digitalWrite(MOTOR_R_A_PIN, LOW);
      digitalWrite(MOTOR_R_B_PIN, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(MOTOR_R_A_PIN, HIGH);
      digitalWrite(MOTOR_R_B_PIN, LOW);
    }
    else
    {
      digitalWrite(MOTOR_R_A_PIN, LOW);
      digitalWrite(MOTOR_R_B_PIN, LOW);
    }

    analogWrite(PWM_MOTOR_R, pwm);
  }
  else if(motor == MOTOR_L)
  {
    if(direct == CW)
    {
      digitalWrite(MOTOR_L_A_PIN, LOW);
      digitalWrite(MOTOR_L_B_PIN, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(MOTOR_L_A_PIN, HIGH);
      digitalWrite(MOTOR_L_B_PIN, LOW);
    }
    else
    {
      digitalWrite(MOTOR_L_A_PIN, LOW);
      digitalWrite(MOTOR_L_B_PIN, LOW);
    }

    analogWrite(PWM_MOTOR_L, pwm);
  }
}

void motorControl::SETUP() {
		  pinMode(MOTOR_R_A_PIN, OUTPUT);
		  pinMode(MOTOR_R_B_PIN, OUTPUT);

		  pinMode(MOTOR_L_A_PIN, OUTPUT);
		  pinMode(MOTOR_L_B_PIN, OUTPUT);

		  pinMode(PWM_MOTOR_R, OUTPUT);
		  pinMode(PWM_MOTOR_L, OUTPUT);

		  pinMode(EN_PIN_R, OUTPUT);
		  pinMode(EN_PIN_L, OUTPUT);

		  digitalWrite(EN_PIN_R, HIGH);
		  digitalWrite(EN_PIN_L, HIGH);

		//for debugging purposes. remove later. also remove all the Serial.print() statements in the other functions
		  Serial.begin(9600);

}



void motorControl::stop()
{
  Serial.println("Stop");
  usMotor_Status = BRAKE;
  motorGo(MOTOR_R, usMotor_Status, 0);
  motorGo(MOTOR_L, usMotor_Status, 0);
}



void motorControl::forward()
{
  Serial.println("Forward");
  usMotor_Status = CW;
 
  motorGo(MOTOR_R, usMotor_Status, usSpeed);
  motorGo(MOTOR_L, usMotor_Status, usSpeed);
}


void motorControl::reverse()
{
  Serial.println("Reverse");
  usMotor_Status = CCW;
  motorGo(MOTOR_R, usMotor_Status, usSpeed);
  motorGo(MOTOR_L, usMotor_Status, usSpeed);
}


void motorControl::rightTurn()
{
  Serial.println("rightTurn");
  motorGo(MOTOR_R, CCW, 0);
  motorGo(MOTOR_L, CW, usSpeed+10);
}


void motorControl::leftTurn()
{
  Serial.println("leftTurn");

  motorGo(MOTOR_R, CW, usSpeed+10);
  motorGo(MOTOR_L, CCW, 0);
}

void motorControl::increaseSpeed()
{
  usSpeed = usSpeed + 10;
  if(usSpeed > 255)
  {
    usSpeed = 255;
  }

  Serial.print("Speed +: ");
  Serial.println(usSpeed);

  motorGo(MOTOR_R, usMotor_Status, usSpeed);
  motorGo(MOTOR_L, usMotor_Status, usSpeed);
}


void motorControl::changeSpeedLeft(int pwm)
{
  usSpeed = usSpeed + pwm;
  
  if(usSpeed > 255)
  {
    usSpeed = 255;
  }
  else if(usSpeed < 0)
  {
    usSpeed = 0;
  }


 motorGo(MOTOR_L, usMotor_Status, usSpeed);
}


int motorControl::getSpeed()
{
      return usSpeed;
}

void motorControl::decreaseSpeed()
{
  usSpeed = usSpeed - 10;
  if(usSpeed < 0)
  {
    usSpeed = 0;
  }

  Serial.print("Speed -: ");
  Serial.println(usSpeed);

  motorGo(MOTOR_R, usMotor_Status, usSpeed);
  motorGo(MOTOR_L, usMotor_Status, usSpeed);
}


void motorControl::setSpeed(int speed)
{
  if(speed<=255 && speed >=0)
        usSpeed=speed;

  Serial.print("Speed set to : ");
  Serial.println(usSpeed);

  motorGo(MOTOR_R, usMotor_Status, usSpeed);
  motorGo(MOTOR_L, usMotor_Status, usSpeed);

}

motorControl motor = motorControl();
