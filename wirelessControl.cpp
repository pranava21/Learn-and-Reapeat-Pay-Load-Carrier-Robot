#include "Arduino.h"
#include "wirelessControl.h"

char bluetooth::receivedChar() 
{
  char user_input;   

  while(Serial.available())
  {
    user_input = Serial.read(); 
      
    if (user_input =='1')
    {
      return 's';
    }
    else if(user_input =='2')
    {
      return 'f';
    }
    else if(user_input =='3')
    {
      return 'b';
    }
    else if(user_input =='+')
    {
      return '+';
    }
    else if(user_input =='-')
    {
      return '-';
    }
    else if(user_input =='4')
    {
       return 'r';
    }
    else if(user_input =='5')
    {
      return 'l';
    }
    else if(user_input =='0')
    { 
      return 'o';
    }
    else if(user_input =='6')
    { 
      return 'g';
    }
     else if(user_input =='7')
    { 
      return 'x';
    }
     else if(user_input =='8')
    { 
      return 'z';
    }
    
    else if(user_input =='v')
    { 
      return 'v';
    }
    
     else if(user_input =='w')
    { 
      return 'w';
    }
    else if(user_input =='q')
    { 
      return 'q';
    } 

     else if(user_input =='y')
    { 
      return 'y';
    } 
    else if(user_input =='p')
    { 
      return 'p';
    } 
      
  }
 return('N'); 
}

bluetooth BT = bluetooth();
