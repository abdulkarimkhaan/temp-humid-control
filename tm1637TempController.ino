#include <dht.h>
#include "TM1637.h"
 
//{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
//0~9,A,b,C,d,E,F
const int button1Pin = 8; //enter set temperature
const int button2Pin = 9; //inc temperature
const int button3Pin = 10; //dec temperature
const int button4Pin = 11; //enter normal mode

#define greenLed 7
#define redLed 6
#define yellowLed 5
#define dht_pin 2 // Pin sensor is connected to
#define CLK 3//Pins for TM1637       
#define DIO 4

TM1637 tm1637(CLK,DIO);
dht DHT;
 
int button1State = 0;  
int button2State = 0;
int button3State = 0;    
int button4State = 0;  // variable for reading the pushbutton status
int flag = 0;  // enter set temp
int flag2 = 0; //inc
int flag3 = 0; //dec
void setup(){
   // initialize the LED pin as an output:
  pinMode(greenLed, OUTPUT); 
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);
  
  tm1637.init();
  tm1637.set(BRIGHT_DARKEST); 
  //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
 Serial.begin(9600);
 }
int pressinc = 0;
int pressdec = 0;
int t1 = 0;
int t2 = 0;

int temperature1 = 0;
int temperature2 = 0;

void loop(){
// read the state of the pushbutton value:

  
  button1State = digitalRead(button1Pin);
  if(button1State == LOW){
  flag = 1;
}

while(flag == 1){
//    tm1637.display(1,0);
//    tm1637.display(2,0);
//    tm1637.display(3,0);
//    tm1637.display(4,0);
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, HIGH);  
//inc
    button2State = digitalRead(button2Pin);   
    if(button2State == LOW){
    flag2 = 1;
    pressinc = 0;
    } 
    while(flag2 == 1 && flag == 1){
   //   tm1637.clearDisplay();
       
      if(button2State == LOW && pressinc == 0){
      temperature1++;
      pressinc = 1;
      flag2 = 0;
      if(temperature1 > 9)
      {
        temperature1 = 0;
        temperature2++;     
      }
      tm1637.display(3,temperature1);
      tm1637.display(2,temperature2);
     }
      delay(300);
    }

    button4State = digitalRead(button4Pin);  

    button4State = digitalRead(button4Pin);
    if(button4State == LOW){  
    flag = 0;
    t1= temperature1;
    t2=temperature2;
    }
    //dec
 button3State = digitalRead(button3Pin);   
    if(button3State == LOW){
    flag3 = 1;
    pressdec = 0;
    } 
    while(flag3 == 1 && flag == 1){
     // tm1637.clearDisplay();
       
      if(button3State == LOW && pressdec == 0){
      temperature1--;
      pressdec = 1;
      flag3 = 0;
      if(temperature1 < 0)
      {
        temperature1 = 9;
        temperature2--;     
      }
      tm1637.display(3,temperature1);
      tm1637.display(2,temperature2); 
      
     }
      delay(300);
    }

    button4State = digitalRead(button4Pin);  

    button4State = digitalRead(button4Pin);
    if(button4State == LOW){ 
    flag = 0;
    t1= temperature1;
    t2=temperature2;
    
}   
   
}

  digitalWrite(greenLed, HIGH);
  digitalWrite(yellowLed, LOW);
  
  DHT.read11(dht_pin);
 int temp = DHT.temperature;
 int humidity = DHT.humidity;
 
 int digitoneT = temp / 10;
 int digittwoT = temp % 10;
 
 int digitoneH = humidity / 10;
 int digittwoH = humidity % 10;
 if(digitoneT >= t2 && digittwoT > t1){
  digitalWrite(redLed, HIGH);
}else{
  digitalWrite(redLed, LOW);
}
   
 
    tm1637.display(1,digitoneT); 
    tm1637.display(2,digittwoT);
    tm1637.display(3,12);  // put a C at the end
    
    delay (2000);
  
    tm1637.display(1,25); 
    tm1637.display(2,digitoneH); 
    tm1637.display(3,digittwoH);
  
//  //Wait 3 seconds before accessing sensor again.
   
  //Fastest should be once every two seconds.
    delay(2000);
    
  
}// end loop() 
