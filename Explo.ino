#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

 
#define SS_PIN 10
#define RST_PIN 9


MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
const byte ROWS = 4; 
const byte COLS = 4; 


char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 


Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
Servo s1,s2,s3,s0;


int authori()
{
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
    {
        return 0;
    }
    if ( ! mfrc522.PICC_ReadCardSerial()) 
    {
        return 0;
    }
    Serial.print("UID tag :");
    String content= "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    if (content.substring(1) == "BD 31 15 2B") //change here the UID of the card/cards that you want to give access
    {
       Serial.println("Authorized access");
       Serial.println();
       delay(3000);
       return 1;
    }
    else   
    {
        Serial.println(" Access denied");
        delay(3000);
        return -1;
    }
}
void setup() {
  Serial.begin(9600);   
  SPI.begin();      
  mfrc522.PCD_Init();   
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  labelx :
  int x=authori();
  if(x==-1) goto labelx;
  lcd.begin(16, 2);
  s0.write(0);
  s0.attach(10);
  s1.write(0);
  s1.attach(11);
  s2.write(0);
  s2.attach(12);
  s3.write(0);
  s3.attach(13);
  lcd.print("DrillBit Dispenser");
  lcd.setCursor(0, 1);
  lcd.print("Enter Size: ");
}

void loop() {

  char whichKey = customKeypad.getKey();
  if(int(whichKey)!=0)
  {
    if (whichKey){
      Serial.println(whichKey);
    }
    if(whichKey == '0' || whichKey == '9' || whichKey == '8' || whichKey == '7' || whichKey == '6' || whichKey == '1' || whichKey == '*' || whichKey == '#' || whichKey == 'A' || whichKey == 'B' || whichKey == 'C' || whichKey == 'D')
  {
        lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  Invalid Key!");
      delay(1000);
        lcd.clear();
        setup();
  }
    else
    {
      lcd.setCursor(11,1);
      lcd.print(whichKey);
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   Dispensing");
        if(whichKey=='2')
        {
          lcd.setCursor(0, 1);
            s0.write(50); 
            delay(1500);  
            s0.write(0); 
        }
        else  if(whichKey=='3')
        {
            s1.write(50); 
            delay(1500);  
            s1.write(0); 
        } 
        else  if(whichKey=='4')
        {
            s2.write(50); 
            delay(1500);  
            s2.write(0); 
        }
        else  if(whichKey=='5')
        {
            s3.write(50); 
            delay(1500);  
            s3.write(0); 
        }
        lcd.print("      Done");
        delay(1000);
        lcd.clear();
        lcd.print("PutBack the Dril");
        lcd.setCursor(0,1);
        lcd.print("Pres # after put");
        label1 :
        char puty = customKeypad.getKey();
        if(puty=='#')
        {
            lcd.clear();
            lcd.print("Kept success");
            delay(2000);
            lcd.clear();
            setup();
        }
        else goto label1;
    }
  }
}
