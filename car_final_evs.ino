#include <NewPing.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <string.h>
#define TRIGGER_PIN_S1  34
#define ECHO_PIN_S1     32
#define TRIGGER_PIN_S2  38
#define ECHO_PIN_S2     36
#define TRIGGER_PIN_S3  42
#define ECHO_PIN_S3     40
#define LED_1_PIN 53
#define LED_2_PIN 49
#define LED_3_PIN 50
#define MAX_DISTANCE_front1  400
#define MAX_DISTANCE_front2  350 
#define MAX_DISTANCE_front3  300 
//NewPing Lib For HC-SR04 sensor

NewPing s1_front(TRIGGER_PIN_S1,ECHO_PIN_S1,MAX_DISTANCE_front1);
NewPing s2_front(TRIGGER_PIN_S2,ECHO_PIN_S2,MAX_DISTANCE_front2);
NewPing s3_front(TRIGGER_PIN_S3,ECHO_PIN_S3,MAX_DISTANCE_front3);

// initialize the library with the numbers of the interface pins
 /* The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 22
 * LCD D5 pin to digital pin 24
 * LCD D6 pin to digital pin 26
 * LCD D7 pin to digital pin 28
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

LiquidCrystal lcd(12, 11, 22, 24, 26, 28);
int rightm1=7;//gray rightback //true front
int rightm2=6;//purple rightfront //true back
int leftm1=5;//blue leftback //true back
int leftm2=4;//green lefttop // true front

//white wire rx
//gray wire tx
//black ground
//purple vcc
void forward(){
digitalWrite(rightm1,HIGH);
digitalWrite(rightm2,LOW);
digitalWrite(leftm1,LOW);
digitalWrite(leftm2,HIGH);
}
void left(){
digitalWrite(rightm1,LOW);
digitalWrite(rightm2,HIGH);
digitalWrite(leftm1,LOW);
digitalWrite(leftm2,HIGH);

}
void right(){
digitalWrite(rightm1,HIGH);
digitalWrite(rightm2,LOW);
digitalWrite(leftm1,HIGH);
digitalWrite(leftm2,LOW);
}
void backword(){
digitalWrite(rightm1,LOW);
digitalWrite(rightm2,HIGH);
digitalWrite(leftm1,HIGH);
digitalWrite(leftm2,LOW);
}
void setup(){
Serial.begin(9600);
// put your setup code here, to run once:
pinMode(rightm1,OUTPUT);
pinMode(rightm2,OUTPUT);
pinMode(leftm1,OUTPUT);
pinMode(leftm2,OUTPUT);
setledups();
stopMovements();
lcdsetup();
}
void setledups(){
 pinMode(LED_1_PIN,OUTPUT);
 pinMode(LED_2_PIN,OUTPUT);
 pinMode(LED_3_PIN,OUTPUT);
 offleds();  
}
void offleds(){
digitalWrite(LED_1_PIN,LOW); 
digitalWrite(LED_2_PIN,LOW);
digitalWrite(LED_3_PIN,LOW);  
}
void led1On(){
  digitalWrite(LED_1_PIN,HIGH); 
}
void led2On(){
  digitalWrite(LED_2_PIN,HIGH); 
}
void led3On(){
  digitalWrite(LED_3_PIN,HIGH); 
}
void lcdsetup(){
// set up the LCD's number of columns and rows:
 lcd.begin(16, 2);
// Print a message to the LCD.
printMessage("Welcome Mr.Aqib!");
delay(1000);
}

void printMessage(char message[]){
lcd.print(message);
}
void stopMovements(){
digitalWrite(rightm1,LOW);
digitalWrite(rightm2,LOW);
digitalWrite(leftm1,LOW);
digitalWrite(leftm2,LOW);
}
bool left_right=false;
bool move_up=false,move_down=false,move_left=false,move_right=false,stopC=false;
void loop(){
    lcd.setCursor(0, 0);
    int uS = s1_front.ping();
    int front_s1_distance=uS / US_ROUNDTRIP_CM;
     uS = s2_front.ping();
  int front_s2_distance=uS / US_ROUNDTRIP_CM;
     uS = s3_front.ping();
  int front_s3_distance=uS / US_ROUNDTRIP_CM;
 /* Serial.print("s1 : ");
    Serial.println(front_s1_distance);*/
    delay(2);
   /* Serial.print("s2 : ");
    Serial.println(front_s2_distance);
 */
    /*Serial.print("s3 : ");
  Serial.println(front_s3_distance);
  */
     if(front_s1_distance<=15  && front_s1_distance!=0){
      led1On();
      }else if(front_s2_distance<=15  && front_s2_distance!=0){
       led2On();
        }else if(front_s3_distance<=15  && front_s3_distance!=0){
          led3On();
          }else{
            offleds();
            }
   if(move_up){
//      if(front_s1_distance>=15 && front_s2_distance>=15 && front_s3_distance>=15    || (front_s1_distance==0 && front_s2_distance==0 && front_s3_distance==0)){
//        forward();
//     }else{
//      stopMovements();
//      }
printMessage("Moving Forward  ");
forward();
    }
    else if(move_down){
      printMessage("Moving Backword ");
       backword();
      }else if(move_left){
        printMessage("Moving Left     ");
        left();
        }else if(move_right){
          printMessage("Moving Right    ");
           right();
          }else if(stopC){
            printMessage("-----stopped----");
               stopMovements();
            }
    if(Serial.available() > 0){
      char value=Serial.read();
      Serial.println(value);
      if(value=='1'){
        left_right=false;
        move_up=true;
        move_down=false;move_left=false;move_right=false;
        }
        else if(value=='2'){
          left_right=false;
          move_up=false;
        move_down=true;move_left=false;move_right=false;
          }
          else if(value=='3'){
            left_right=true;
            move_up=false;
            move_down=false;move_left=true;move_right=false;            
            }
            else if(value=='4'){
              left_right=true;
             move_up=false;
             move_down=false;move_left=false;move_right=true;  
              }else if(value=='0'){
                 move_up=false;
             move_down=false;move_left=false;move_right=false;
             stopC=true; 
                }
      }
         if(left_right){
        delay(1);
              }else{
               delay(1); 
                }
                
  
    }
