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

          goStraight(541 - 190);
          delay(500);
          
          encoder.goDistanceLeft(493);
                  
          orient_south();
          
          goStraight(10000 - 190);
          delay(500);
                    
          
          orient_south();
          
          goStraight(10000 - 190);
          delay(500);
                    
          
          orient_south();
           
          goStraight(10000 - 190);
          delay(500);
                    
          
          orient_south();
          
          goStraight(8139 - 190);
          delay(500);
                    
          
          orient_south();
           

}

void DIGITAL_ANALOG(){

           _dir='w';
           orient_west();

          encoder.goDistanceRight(493);        
                    
          orient_north();
           
          goStraight(6098 - 190);
          delay(500);

          encoder.goDistanceRight(493);        
          
          orient_east();
           
          goStraight(1624 - 190);
          delay(500);

          encoder.goDistanceLeft(493);        
          
          orient_north();
           
          goStraight(10356 - 190);
          delay(500);

          encoder.goDistanceLeft(493);        
          
          orient_west();
           
          goStraight(1826 - 190);
          delay(500);

          encoder.goDistanceRight(493);        
          
          orient_north();
           
          goStraight(12448 - 190);
          delay(500);

          encoder.goDistanceRight(493);        
          
          orient_east();
           
          goStraight(7216 - 190);
          delay(500);

          encoder.goDistanceRight(493);        
          
          orient_south();
}