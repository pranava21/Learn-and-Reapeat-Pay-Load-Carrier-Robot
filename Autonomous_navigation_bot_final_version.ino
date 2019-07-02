#include "IMU.h"
#include "motorControl.h"
#include "encoder.h"
#include "wirelessControl.h"



#include <TimerOne.h>


// PID time period in ms 
#define PID_TIME_PERIOD .1

//PID VALUES
          
  int errPrev=0;
  int sumError = 0;
  int masterPWM ;
             
  int slavePWM ; 
  int error=0;
  float kp= 17  ,ki= -.00001 , kd= 60 ;                    
        


//////////////////////

int index=0;

char arr_instruction  [200];
unsigned long int arr_encoder_data [200][2];

unsigned long int r=0,l=0;


char _dir = 'w';

void setup()
{
  pinMode(43,INPUT);
  encoder.SETUP();
  masterPWM = motor.getSpeed();

  Timer1.initialize(100);
  Timer1.attachInterrupt(PID_goStraight_ISR);
  Timer1.stop();
  
  MPU_setup();
    Serial.print("Calibrating");
  while(millis() < 20000 ){
         Serial.println('.');
         update_IMU_angle();
         
  }
 Serial.println("Done Calibrating");

}

void loop() {
       
       
       while (digitalRead(43) == 0){   
        update_IMU_angle();
            char user_input = BT.receivedChar();

                    routeDecisionLearn(user_input);
                    
                    if(user_input!= 10 && user_input!='N'){ 
                            
                            arr_instruction[index]=user_input;
                            if(index != 0){
                                  arr_encoder_data[index-1][0]= l;
                                  arr_encoder_data[index-1][1]= r;
                                  
                                  arr_encoder_data[index][0]= 0;
                                  arr_encoder_data[index][1]= 0;

                                  Serial.println(l);
                                  Serial.println(r);
                                  
                                          
                            }
                            index++;
                        
                  }
                    
       }
       
       while (digitalRead(43) == 1){
        update_IMU_angle();
                  char user_input = BT.receivedChar();
                  switch (user_input) {
                    
                          case  'z':
                          
                                 motor.setSpeed(DEFAULT_usSpeed);

                                 turn180();  
                            
                                 for(int i=0; i<200 ;i++){
                                          Serial.print(arr_instruction[i]);
                                          Serial.print("  ");
                                          Serial.print(arr_encoder_data[i][0]);
                                          Serial.print("  ");
                                          Serial.println(arr_encoder_data[i][1]);
              
                                          routeDecisionRepeatFw(i);
                                          
                                 }
                                 Serial.println("================================");
                                 
                                 break;


                          case 'x':
                                motor.setSpeed(DEFAULT_usSpeed);

                               turn180();                         
                              
                             for(int i=200; i>=0 ;i--){
                                      Serial.print(arr_instruction[i]);
                                      Serial.print("  ");
                                      Serial.print(arr_encoder_data[i][0]);
                                      Serial.print("  ");
                                      Serial.println(arr_encoder_data[i][1]);
                  
                                      routeDecisionRepeatRw(i);
                             }
                             Serial.println("================================");
                            
                             break;

                           case 'v':
                                   COE_DIGITAL();
                                
                           break;


                           case 'w':
                                  ANALOG_OFFICE();
                                
                           break;
                           case 'q':
                                  DIGITAL_ANALOG();
                                
                           break;
                           case 'y':

                                 // STORE.EEPROM_write(arr_instruction,1,200);
                                  //STORE.EEPROM_write2D(arr_encoder_data,2,200);
                                Serial.println("Done saving");
                           break;
                           case 'p':
                                  
                                //STORE.EEPROM_read(arr_instruction,1,200);
                                //STORE.EEPROM_read(arr_encoder_data[1],2,200);
                                Serial.println("Done reading");
                           break;
                                   
                   }
        }

}


void orient_south(){
for(int j=0;j<50;j++){ 
  for(int i=0;i<10;i++){
     
      update_IMU_angle();
    
      while( disp_angle  < 90){
       
        update_IMU_angle();
         motor.leftTurn();
        Serial.println(disp_angle);
        
      }
      while( disp_angle  > 90){
       
        update_IMU_angle();
         motor.rightTurn();
        Serial.println(disp_angle);
      }
  }
      
      motor.stop();
      //delay(10);
      
}
      
}


void orient_north(){
for(int j=0;j<50;j++){ 
  for(int i=0;i<10;i++){
   
      update_IMU_angle();
    
      while( disp_angle  < -90){
       
        update_IMU_angle();
         motor.leftTurn();
        Serial.println(disp_angle);
        
      }
      while( disp_angle > -90){
       
        update_IMU_angle();
         motor.rightTurn();
        Serial.println(disp_angle);
      }
  }
      
      motor.stop();
      //delay(10);
      
}
     
}

void orient_west(){
 for(int j=0;j<50;j++){
  for(int i=0;i<10;i++){
  
      update_IMU_angle();
    
      while( disp_angle  < 0){
       
        update_IMU_angle();
         motor.leftTurn();
        Serial.println(disp_angle);
        
      }
      while( disp_angle > 0){
       
        update_IMU_angle();
         motor.rightTurn();
        Serial.println(disp_angle);
      }
  }
      
      motor.stop();
      //delay(10);
}
      
}

void orient_east(){
for(int j=0;j<50;j++){ 
  for(int i=0;i<10;i++){
  
      update_IMU_angle();
    
      while( disp_angle  < -180){
       
        update_IMU_angle();
         motor.leftTurn();
        Serial.println(disp_angle);
        
      }
      while( disp_angle > -180){
       
        update_IMU_angle();
         motor.rightTurn();
        Serial.println(disp_angle);
      }
  }
      
      motor.stop();
      //delay(10);
}
      
}

void east_north(){
 
  for(int i=0;i<10;i++){
      update_IMU_angle();
    
      while( disp_angle  < -90){
       
        update_IMU_angle();
         motor.leftTurn();
        Serial.println(disp_angle);
        
      }
      while( disp_angle > -90){
       
        update_IMU_angle();
         motor.rightTurn();
        Serial.println(disp_angle);
      }
  }
      
      motor.stop();
      orient_north();
}

void east_south(){
  encoder.goDistanceRight(480);
  for(int i=0;i<10;i++){
      update_IMU_angle();
    
      while( disp_angle  < 90){
       
        update_IMU_angle();
         motor.leftTurn();
        Serial.println(disp_angle);
        
      }
      while( disp_angle > 90){
       
        update_IMU_angle();
         motor.rightTurn();
        Serial.println(disp_angle);
      }
  }
      
      motor.stop();
      orient_south();
}

void north_west(){
 
  for(int i=0;i<10;i++){
      update_IMU_angle();
    
      while( disp_angle  < 0){
       
        update_IMU_angle();
         motor.leftTurn();
        Serial.println(disp_angle);
        
      }
      while( disp_angle > 0){
       
        update_IMU_angle();
         motor.rightTurn();
        Serial.println(disp_angle);
      }
  }
      
      motor.stop();
      orient_west();
}

void north_east(){
 
  for(int i=0;i<10;i++){
      update_IMU_angle();
    
      while( disp_angle  < -180){
       
        update_IMU_angle();
         motor.leftTurn();
        Serial.println(disp_angle);
        
      }
      while( disp_angle > -180){
       
        update_IMU_angle();
         motor.rightTurn();
        Serial.println(disp_angle);
      }
  }
      
      motor.stop();
      orient_east();
}

void west_south(){
 
  for(int i=0;i<10;i++){
      update_IMU_angle();
    
      while( disp_angle  < 90){
       
        update_IMU_angle();
         motor.leftTurn();
        Serial.println(disp_angle);
        
      }
      while( disp_angle > 90){
       
        update_IMU_angle();
         motor.rightTurn();
        Serial.println(disp_angle);
      }
  }
      
      motor.stop();
      orient_south();
      
}

void west_north(){
 
  for(int i=0;i<10;i++){
      update_IMU_angle();
    
      while( disp_angle  < -90){
       
        update_IMU_angle();
         motor.leftTurn();
        Serial.println(disp_angle);
        
      }
      while( disp_angle > -90){
       
        update_IMU_angle();
         motor.rightTurn();
        Serial.println(disp_angle);
      }
  }
      
      motor.stop();
      orient_north();
      
}

void south_east(){
  encoder.goDistanceLeft(480);
  for(int i=0;i<10;i++){
      update_IMU_angle();
    
      while( disp_angle  < -180){
       
        update_IMU_angle();
         motor.leftTurn();
        Serial.println(disp_angle);
        
      }
      while( disp_angle > -180){
       
        update_IMU_angle();
         motor.rightTurn();
        Serial.println(disp_angle);
      }
  }
      
      motor.stop();
      orient_east();
}

void south_west(){
 
  for(int i=0;i<10;i++){
      update_IMU_angle();
    
      while( disp_angle  < 0){
       
        update_IMU_angle();
         motor.leftTurn();
        Serial.println(disp_angle);
        
      }
      while( disp_angle > 0){
       
        update_IMU_angle();
         motor.rightTurn();
        Serial.println(disp_angle);
      }
  }
      
      motor.stop();
      orient_west();
}


void goReverse(int tick){
          
          int errPrev=0;
          int sumError = 0;
          int masterPWM = motor.getSpeed();
                     
          int slavePWM = masterPWM + 15; 
          int error=0;
          float kp= 17  ,ki= -.00001 , kd= 60 ;                    
          
          motor.changeSpeedLeft(slavePWM-masterPWM);
          //this will automatically print slavePWM
          
          //motoM1-> left motor(slave)
          
          encoder.resetEncoderValues();
          encoder.getPulsesLeft(&l);
          encoder.getPulsesRight(&r);

         
          motor.reverse();
         
          
          while( r < tick ){

                  
                  encoder.getPulsesLeft_no_reset(&l);
                  encoder.getPulsesRight_no_reset(&r);

                   
                  error = r - l;

                  int d=error- errPrev;
                  sumError +=error;

                  
                  //Serial.println(error);
        
                  float x  =  error * kp + ((PID_TIME_PERIOD * sumError)* ki) + ( (kd * d) /PID_TIME_PERIOD);
                  motor.changeSpeedLeft( (int)x );
                  
                 // Serial.println(x);
        
                 
            
                errPrev=error;
                delay(PID_TIME_PERIOD);
                  
          }
          
          motor.stop(); 
          motor.setSpeed(masterPWM);
          encoder.getPulsesRight(&r);
          Serial.println(r);
          encoder.resetEncoderValues();
}

void goStraight(int tick){
          
          int errPrev=0;
          int sumError = 0;
          int masterPWM = motor.getSpeed();
                     
          int slavePWM = masterPWM + 15; 
          int error=0;
          float kp= 17  ,ki= -.00001 , kd= 60 ;                    
          
          motor.changeSpeedLeft(slavePWM-masterPWM);
          //this will automatically print slavePWM
          
          //motoM1-> left motor(slave)
          
          encoder.resetEncoderValues();
          encoder.getPulsesLeft(&l);
          encoder.getPulsesRight(&r);

         
          motor.forward();
         
          
          while( r < tick ){

                  
                  encoder.getPulsesLeft_no_reset(&l);
                  encoder.getPulsesRight_no_reset(&r);

                   
                  error = r - l;

                  int d=error- errPrev;
                  sumError +=error;

                  
                  //Serial.println(error);
        
                  float x  =  error * kp + ((PID_TIME_PERIOD * sumError)* ki) + ( (kd * d) /PID_TIME_PERIOD);
                  motor.changeSpeedLeft( (int)x );
                  
                 // Serial.println(x);
        
                 
            
                errPrev=error;
                delay(PID_TIME_PERIOD);
                  
          }
          
          motor.stop(); 
          motor.setSpeed(masterPWM);
          encoder.getPulsesRight(&r);
          Serial.println(r);
          encoder.resetEncoderValues();
}

void PID_goStraight_start(){
          
          masterPWM = motor.getSpeed();
          slavePWM = masterPWM + 15; 
          
          motor.changeSpeedLeft(slavePWM-masterPWM);
          //this will automatically print slavePWM
          
          //motoM1-> left motor(slave)
         
          motor.forward();
         
          Timer1.start();
         
}

void PID_goStraight_stop(){
        Timer1.stop();
        motor.stop(); 
        motor.setSpeed(masterPWM);
       //encoder.resetEncoderValues();
}



void PID_goStraight_ISR(){
    encoder.getPulsesLeft_no_reset(&l);
    encoder.getPulsesRight_no_reset(&r);
     
    error = r - l;
  
    int d=error- errPrev;
    sumError +=error;
  
    float x  =  error * kp + ((PID_TIME_PERIOD * sumError)* ki) + ( (kd * d) /PID_TIME_PERIOD);
    motor.changeSpeedLeft( (int)x );
  
    errPrev=error;
    
    
}

void routeDecisionLearn(char user_input){
  switch (_dir) {
                          case  'e':
                            switch(user_input){

                                case 's':
                                        PID_goStraight_stop();
                                        encoder.getPulsesRight(&r) ;
                                        encoder.getPulsesLeft(&l) ; 
                                        motor.stop();
                                        orient_east();
                                        break;  
                                      
                                case 'o': 
                                        PID_goStraight_stop();
                                        orient_east(); 
                                        break;                                        
                                
                                case 'l':
                                        PID_goStraight_stop();
                                        encoder.getPulsesRight(&r) ;
                                        encoder.getPulsesLeft(&l) ;
                                        east_north();
                                        _dir = 'n';
                                        break;
                                
                                case 'r': 
                                        PID_goStraight_stop();
                                        encoder.getPulsesRight(&r) ;
                                        encoder.getPulsesLeft(&l) ;  
                                        east_south();
                                        _dir = 's';
                                        break;
                                
                                case 'g':
                                        update_IMU_angle();
                                        Serial.println(disp_angle);
                                        break;
                               
                                case 'f':
                                        encoder.getPulsesRight(&r) ;
                                        encoder.getPulsesLeft(&l) ;
                                        PID_goStraight_start(); 
                                        break;

                                case 'b': 
                                        PID_goStraight_stop(); 
                                        encoder.getPulsesRight(&r) ;
                                        encoder.getPulsesLeft(&l) ;
                                        motor.reverse(); 
                                        break;
                                
                                case '+':                   
                                        motor.increaseSpeed(); 
                                        break;
                              
                                case '-': 
                                          motor.decreaseSpeed(); 
                                          break;
                    
                              
                          };break;
                          
                          case 'n':
                             switch(user_input){

                                case 's':
                                        PID_goStraight_stop();
                                        encoder.getPulsesRight(&r) ;
                                        encoder.getPulsesLeft(&l) ; 
                                        motor.stop();
                                        orient_north(); 
                                        break;  
                              
                                case 'o': 
                                         PID_goStraight_stop();
                                         orient_north(); 
                                         break;
                                         
                                case 'l': 
                                         PID_goStraight_stop();
                                         encoder.getPulsesRight(&r) ;
                                         encoder.getPulsesLeft(&l) ;
                                         north_west();
                                         _dir = 'w'; 
                                         break;
                                         
                                case 'r': 
                                         PID_goStraight_stop();
                                         encoder.getPulsesRight(&r) ;
                                         encoder.getPulsesLeft(&l) ; 
                                         north_east();
                                         _dir = 'e'; 
                                         break;
                                         
                                case 'g':
                                        update_IMU_angle();
                                        Serial.println(disp_angle);
                                        break;

                                case 'f':
                                        encoder.getPulsesRight(&r) ;
                                        encoder.getPulsesLeft(&l) ;
                                        PID_goStraight_start(); 
                                        break;

                                case 'b': 
                                        PID_goStraight_stop(); 
                                        encoder.getPulsesRight(&r) ;
                                        encoder.getPulsesLeft(&l) ;
                                        motor.reverse(); 
                                        break;
                                
                                case '+':                   
                                        motor.increaseSpeed(); 
                                        break;
                              
                                case '-': 
                                          motor.decreaseSpeed(); 
                                          break;
                              
                          };break;
                          
                          case 'w':
                              switch(user_input){

                                case 's':
                                        PID_goStraight_stop();
                                        encoder.getPulsesRight(&r) ;
                                        encoder.getPulsesLeft(&l) ; 
                                        motor.stop();
                                        orient_west(); 
                                        break;  
                                        
                                case 'o': 
                                        PID_goStraight_stop();
                                        orient_west(); 
                                        break;

                                case 'l':
                                        PID_goStraight_stop();
                                        encoder.getPulsesRight(&r) ;
                                        encoder.getPulsesLeft(&l) ;
                                        west_south();
                                        _dir = 's'; 
                                        break;
                                        
                                case 'r': 
                                        PID_goStraight_stop();
                                        encoder.getPulsesRight(&r) ;
                                        encoder.getPulsesLeft(&l) ;
                                        west_north();
                                        _dir = 'n'; 
                                        break;
                                        
                                case 'g':
                                        update_IMU_angle();
                                        Serial.println(disp_angle);
                                        break;

                                case 'f':
                                        encoder.getPulsesRight(&r) ;
                                        encoder.getPulsesLeft(&l) ;
                                        PID_goStraight_start(); 
                                        break;

                                case 'b': 
                                        PID_goStraight_stop(); 
                                        motor.reverse(); 
                                        encoder.getPulsesRight(&r) ;
                                        encoder.getPulsesLeft(&l) ;
                                        
                                        break;
                                
                                case '+':                   
                                        motor.increaseSpeed(); 
                                        break;
                              
                                case '-': 
                                          motor.decreaseSpeed(); 
                                          break;
                    
                              
                          };break;
                          
                          case 's':
                              switch(user_input){

                                case 's':
                                        PID_goStraight_stop();
                                        encoder.getPulsesRight(&r) ;
                                        encoder.getPulsesLeft(&l) ; 
                                        motor.stop();
                                        orient_south(); 
                                        break;  
                                        
                                case 'o': 
                                        PID_goStraight_stop();
                                        orient_south(); 
                                        break;
                                        
                                case 'l': 
                                        PID_goStraight_stop();
                                        encoder.getPulsesRight(&r) ;
                                        encoder.getPulsesLeft(&l) ;
                                        south_east();
                                        _dir = 'e'; 
                                        break;
                                        
                                case 'r': 
                                        PID_goStraight_stop();
                                        encoder.getPulsesRight(&r) ;
                                        encoder.getPulsesLeft(&l) ;
                                        south_west();
                                        _dir = 'w'; 
                                        break;
                                        
                                case 'g':
                                        update_IMU_angle();
                                        Serial.println(disp_angle);
                                        break;

                                case 'f':
                                        encoder.getPulsesRight(&r) ;
                                        encoder.getPulsesLeft(&l) ;
                                        PID_goStraight_start(); 
                                        break;

                                case 'b': 
                                        PID_goStraight_stop(); 
                                        motor.reverse(); 
                                        encoder.getPulsesRight(&r) ;
                                        encoder.getPulsesLeft(&l) ;
                                        
                                        break;
                                
                                case '+':                   
                                        motor.increaseSpeed(); 
                                        break;
                              
                                case '-': 
                                          motor.decreaseSpeed(); 
                                          break;
                    
                              
                          };break;
                         
                    }
}

void routeDecisionRepeatFw(int i){
  
                            switch (_dir) {
                                           case  'e':
                                                      switch(arr_instruction[i]){
                          
                                                          case 's':
                                                                  motor.stop();
                                                                  orient_east(); 
                                                                  delay(500);
                                                                  break;  
                                                                
                                                          case 'o': 
                                                                  orient_east(); 
                                                                  delay(1000);
                                                                  break;                                        
                                                          
                                                          case 'l':
                                                                  east_north();
                                                                  _dir = 'n';
                                                                  delay(500);
                                                                  break;
                                                          
                                                          case 'r': 
                                                                  east_south();
                                                                  _dir = 's';
                                                                  delay(500);
                                                                  break;
                                                          
                                                          case 'g':
                                                                  update_IMU_angle();
                                                                  Serial.println(disp_angle);
                                                                  break;
                                                         
                                                          case 'f':
                                                                  goStraight(arr_encoder_data[i][1]);
                                                                  delay(500);
                                                                  break;
                          
                                                          case 'b': 
                                                                  encoder.goDistanceReverse(arr_encoder_data[i][1]);
                                                                  delay(500);
                                                                  break;
                                                          
                                                          case '+':                   
                                                                  motor.increaseSpeed(); 
                                                                  break;
                                                        
                                                          case '-': 
                                                                    motor.decreaseSpeed(); 
                                                                    break;
                                              
                                                        
                                                    };break;
                                      
                                      case 'n':
                                               switch(arr_instruction[i]){
                  
                                                  case 's':
                                                          motor.stop();
                                                          orient_north(); 
                                                          delay(500);
                                                          break;  
                                                
                                                  case 'o': 
                                                           orient_north(); 
                                                           delay(1000);
                                                           break;
                                                           
                                                  case 'l': 
                                                           north_west();
                                                           _dir = 'w'; 
                                                           delay(500);
                                                           break;
                                                           
                                                  case 'r': 
                                                           north_east();
                                                           _dir = 'e'; 
                                                           delay(500);
                                                           break;
                                                           
                                                  case 'g':
                                                          update_IMU_angle();
                                                          Serial.println(disp_angle);
                                                          break;
                  
                                                  case 'f':
                                                          goStraight(arr_encoder_data[i][1]);
                                                          delay(500);
                                                          break;
                  
                                                  case 'b': 
                                                          encoder.goDistanceReverse(arr_encoder_data[i][1]);
                                                          delay(500);
                                                          break;
                                                          
                                                  case '+':                   
                                                          motor.increaseSpeed(); 
                                                          break;
                                                
                                                  case '-': 
                                                            motor.decreaseSpeed(); 
                                                            break;
                                                
                                            };break;
                                            
                                      case 'w':
                                          switch(arr_instruction[i]){
            
                                            case 's':
                                                    motor.stop();
                                                    orient_west(); 
                                                    delay(500);
                                                    break;  
                                                    
                                            case 'o': 
                                                    orient_west(); 
                                                    delay(1000);
                                                    break;
            
                                            case 'l':
                                                    west_south();
                                                    _dir = 's'; 
                                                    delay(500);
                                                    break;
                                                    
                                            case 'r': 
                                                    west_north();
                                                    _dir = 'n'; 
                                                    delay(500);
                                                    break;
                                                    
                                            case 'g':
                                                    update_IMU_angle();
                                                    Serial.println(disp_angle);
                                                    break;
            
                                            case 'f':
                                                    goStraight(arr_encoder_data[i][1]);
                                                    delay(500);
                                                    break;
            
                                            case 'b': 
                                                    encoder.goDistanceReverse(arr_encoder_data[i][1]);
                                                    delay(500);
                                                    break;
                                            
                                            case '+':                   
                                                    motor.increaseSpeed(); 
                                                    break;
                                          
                                            case '-': 
                                                      motor.decreaseSpeed(); 
                                                      break;
                                
                                          
                                      };break;
                                      
                                      case 's':
                                          switch(arr_instruction[i]){
            
                                            case 's':
                                                    motor.stop();
                                                    orient_south(); 
                                                    delay(500);
                                                    break;  
                                                    
                                            case 'o': 
                                                    orient_south(); 
                                                    delay(1000);
                                                    break;
                                                    
                                            case 'l': 
                                                    south_east();
                                                    _dir = 'e'; 
                                                    delay(500);
                                                    break;
                                                    
                                            case 'r': 
                                                    south_west();
                                                    _dir = 'w'; 
                                                    delay(500);
                                                    break;
                                                    
                                            case 'g':
                                                    update_IMU_angle();
                                                    Serial.println(disp_angle);
                                                    break;
            
                                            case 'f':
                                                    goStraight(arr_encoder_data[i][1]);
                                                    delay(500);
                                                    break;
            
                                            case 'b': 
                                                    encoder.goDistanceReverse(arr_encoder_data[i][1]);
                                                    delay(500);
                                                    break;
                                            
                                            case '+':                   
                                                    motor.increaseSpeed(); 
                                                    break;
                                          
                                            case '-': 
                                                      motor.decreaseSpeed(); 
                                                      break;
                                
                                          
                                      };break;
                                 
                                                
                                        }

  
}


void routeDecisionRepeatRw(int i){
  
                            switch (_dir) {
                                           case  'e':
                                                      switch(arr_instruction[i]){
                          
                                                          case 's':
                                                                  motor.stop();
                                                                  orient_east(); 
                                                                  delay(500);
                                                                  break;  
                                                                
                                                          case 'o': 
                                                                  orient_east(); 
                                                                  delay(1000);
                                                                  break;                                        
                                                          
                                                          case 'r':
                                                                  east_north();
                                                                  _dir = 'n';
                                                                  delay(500);
                                                                  break;
                                                          
                                                          case 'l': 
                                                                  east_south();
                                                                  _dir = 's';
                                                                  delay(500);
                                                                  break;
                                                          
                                                          case 'g':
                                                                  update_IMU_angle();
                                                                  Serial.println(disp_angle);
                                                                  break;
                                                         
                                                          case 'f':
                                                                  goStraight(arr_encoder_data[i][1]);
                                                                  delay(500);
                                                                  break;
                          
                                                          case 'b': 
                                                                  encoder.goDistanceReverse(arr_encoder_data[i][1]);
                                                                  delay(500);
                                                                  break;
                                                          
                                                          case '+':                   
                                                                  motor.increaseSpeed(); 
                                                                  break;
                                                        
                                                          case '-': 
                                                                    motor.decreaseSpeed(); 
                                                                    break;
                                              
                                                        
                                                    };break;
                                      
                                      case 'n':
                                               switch(arr_instruction[i]){
                  
                                                  case 's':
                                                          motor.stop();
                                                          orient_north(); 
                                                          delay(500);
                                                          break;  
                                                
                                                  case 'o': 
                                                           orient_north(); 
                                                           delay(1000);
                                                           break;
                                                           
                                                  case 'r': 
                                                           north_west();
                                                           _dir = 'w'; 
                                                           delay(500);
                                                           break;
                                                           
                                                  case 'l': 
                                                           north_east();
                                                           _dir = 'e'; 
                                                           delay(500);
                                                           break;
                                                           
                                                  case 'g':
                                                          update_IMU_angle();
                                                          Serial.println(disp_angle);
                                                          break;
                  
                                                  case 'f':
                                                          goStraight(arr_encoder_data[i][1]);
                                                          delay(500);
                                                          break;
                  
                                                  case 'b': 
                                                          encoder.goDistanceReverse(arr_encoder_data[i][1]);
                                                          delay(500);
                                                          break;
                                                          
                                                  case '+':                   
                                                          motor.increaseSpeed(); 
                                                          break;
                                                
                                                  case '-': 
                                                            motor.decreaseSpeed(); 
                                                            break;
                                                
                                            };break;
                                            
                                      case 'w':
                                          switch(arr_instruction[i]){
            
                                            case 's':
                                                    motor.stop();
                                                    orient_west(); 
                                                    delay(500);
                                                    break;  
                                                    
                                            case 'o': 
                                                    orient_west(); 
                                                    delay(1000);
                                                    break;
            
                                            case 'r':
                                                    west_south();
                                                    _dir = 's'; 
                                                    delay(500);
                                                    break;
                                                    
                                            case 'l': 
                                                    west_north();
                                                    _dir = 'n'; 
                                                    delay(500);
                                                    break;
                                                    
                                            case 'g':
                                                    update_IMU_angle();
                                                    Serial.println(disp_angle);
                                                    break;
            
                                            case 'f':
                                                    goStraight(arr_encoder_data[i][1]);
                                                    delay(500);
                                                    break;
            
                                            case 'b': 
                                                    encoder.goDistanceReverse(arr_encoder_data[i][1]);
                                                    delay(500);
                                                    break;
                                            
                                            case '+':                   
                                                    motor.increaseSpeed(); 
                                                    break;
                                          
                                            case '-': 
                                                      motor.decreaseSpeed(); 
                                                      break;
                                
                                          
                                      };break;
                                      
                                      case 's':
                                          switch(arr_instruction[i]){
            
                                            case 's':
                                                    motor.stop();
                                                    orient_south(); 
                                                    delay(500);
                                                    break;  
                                                    
                                            case 'o': 
                                                    orient_south(); 
                                                    delay(1000);
                                                    break;
                                                    
                                            case 'r': 
                                                    south_east();
                                                    _dir = 'e'; 
                                                    delay(500);
                                                    break;
                                                    
                                            case 'l': 
                                                    south_west();
                                                    _dir = 'w'; 
                                                    delay(500);
                                                    break;
                                                    
                                            case 'g':
                                                    update_IMU_angle();
                                                    Serial.println(disp_angle);
                                                    break;
            
                                            case 'f':
                                                    goStraight(arr_encoder_data[i][1]);
                                                    delay(500);
                                                    break;
            
                                            case 'b': 
                                                    encoder.goDistanceReverse(arr_encoder_data[i][1]);
                                                    delay(500);
                                                    break;
                                            
                                            case '+':                   
                                                    motor.increaseSpeed(); 
                                                    break;
                                          
                                            case '-': 
                                                      motor.decreaseSpeed(); 
                                                      break;
                                
                                          
                                      };break;
                                 
                                                
                                        }

  
}

void turn180(){
   switch (_dir) {
            case  'e':
                 encoder.goDistanceRight(490);
                 orient_south();
                 goReverse(346);
                 delay(200);
                 encoder.goDistanceRight(490);
                 _dir='w';
                 orient_west();
                 delay(200);
            break;
            
            case  'w':
                  encoder.goDistanceRight(490);
                  orient_north();
                  goReverse(346);
                  delay(200);
                  encoder.goDistanceRight(490);
                   _dir='e';
                  orient_east();
                   delay(200);
            break;
            case  'n':
                  encoder.goDistanceRight(490);
                  orient_east();
                  goReverse(346);
                  delay(200);
                  encoder.goDistanceRight(490);
                  _dir='s';
                  orient_south();
                   delay(200);
            break;
            case  's':
                 encoder.goDistanceRight(490);
                  orient_west();
                  goReverse(346);
                  delay(200);
                  encoder.goDistanceRight(490);
                  _dir='n';
                 orient_north();
                  delay(200);
                 
            break;
  
}
}



void COE_DIGITAL(){
          _dir='w';
          orient_west();

          encoder.goDistanceLeft(493);        
          
          orient_south();
          
          goStraight(7585 - 190);
          delay(500);
          
          encoder.goDistanceRight(493);        
         
          orient_west();
          
          goStraight(7433 - 190);
          delay(500);
                    
          encoder.goDistanceRight(493);        
          
          orient_north();
          
          goStraight(5557 - 190);
          delay(500);
          
          encoder.goDistanceLeft(493);        
          
          orient_west();
          
          
//          goStraight(2000 - 190);
//          delay(500);

}

void  ANALOG_OFFICE(){
          _dir='w';
          orient_west();
          delay(500);

          goStraight(541 - 190);
          delay(500);
          
          encoder.goDistanceLeft(493);
                  
          orient_south();
          delay(500);

          goStraight(10000 - 190);
                    
          
          orient_south();
          delay(500);
          
          goStraight(10000 - 190);
          
          orient_south();

          delay(500);

          goStraight(10000 - 190);
          
          orient_south();

          delay(500);
          goStraight(8139 - 190);
          
          orient_south();
           

}

void DIGITAL_ANALOG(){

           _dir='w';
           orient_west();

          encoder.goDistanceRight(493);        
                    
          orient_north();

           delay(500);

          goStraight(6098 - 190);
       delay(500);
          encoder.goDistanceRight(493);        
          
          orient_east();
           
          goStraight(1575 - 190);//1624
          delay(500);

          encoder.goDistanceLeft(493);        
          delay(500);

          orient_north();
          
          delay(500);
           
          goStraight(5100 - 190);//10356
delay(500);

          orient_north();
          delay(500);
          
          goStraight(5000 - 190);//10356
delay(500);
          encoder.goDistanceLeft(493);        
                    
          orient_west();
          delay(500);
 
          goStraight(1285 - 190); //1826
delay(500);
          encoder.goDistanceRight(493);        
          
          orient_north();
          delay(500);
 
          goStraight(6548 - 190);
           orient_north();
            delay(500);
          
          goStraight(6000 - 190);
delay(500);
          encoder.goDistanceRight(493);        

          orient_east();
          delay(500);
           
          goStraight(7216 - 190);
delay(500);
          encoder.goDistanceRight(493);        
          
          orient_south();
} 
