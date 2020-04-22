#include <Keyboard.h>
#include <Stepper.h>
#include <LiquidCrystal.h>
#include <Servo.h>
boolean stringComplete = false;
String inputString = "";
int n = 0;
Servo s1,s2,s3,s4,s5,s6; 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

void setup() 
{
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  Serial.begin(9600); 
  s1.attach(9);
  s2.attach(10);
  s3.attach(11);
  s4.attach(12);
  s5.attach(13);
  s6.attach(14);  
  lcd.begin(16, 2);
  inputString.reserve(200);
}
void loop()
{
  
      char  x=Serial.read();
      char p=Serial.read();
      if(stringComplete)
      {
          Serial.println(inputString);
          stringComplete = false;
          if(x=='3')
          {
              s1.write(90); 
              delay(1000);  
              s1.write(0); 
          }
          else  if(x=='4')
          {
              s2.write(90); 
              delay(1000);  
              s2.write(0); 
          } 
          else if(x=='5')
          {
              s3.write(90); 
              delay(1000);  
              s3.write(0); 
          }
          else if(x=='6')
          {
              s4.write(90); 
              delay(1000);  
              s4.write(0); 
          }
          else if(x=='7')
          {
              s5.write(90); 
              delay(1000);  
              s5.write(0); 
          }
          else if(x=='8')
          {
              s6.write(90); 
              delay(1000);  
              s6.write(0); 
          }
          else 
          {
            Serial.println("Invalid Size Enter Again");
          }
    }
    else 
    {
      Serial.println("Invalid User");
    }
    if(p=='y')
    {
          inputString = "";
    }
}

void serialEvent()
{
     while(Serial.available())
     {
      n++;
      char inChar = (char) Serial.read();
      inputString += inChar;
           if(n>=12)
         {
            n=0;
           stringComplete = true;
     
         }
     }
}
