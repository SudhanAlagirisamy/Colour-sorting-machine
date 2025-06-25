#include <Servo.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
const char * myWriteAPIKey = "9B6ILVOYMUSVOADA";
unsigned long myChannelNumber = 691885;
const char *ssid =  "Galaxy-M20";     // Enter your WiFi Name
const char *pass =  "ac312124"; // Enter your WiFi Password
WiFiClient client;
Servo pickServo;
Servo dropServo;
const int s0 = D4;  
const int s1 = D5;  
const int s2 = D6;  
const int s3 = D7;  
const int out = D8;   
int red = 0;  
int green = 0;  
int blue = 0; 
int color=0;
int redcolor = 0;
int greencolor = 0;
int orangecolor = 0;
int yellowcolor = 0;
int CLOSE_ANGLE = 30;  // The closing angle of the servo motor arm
int OPEN_ANGLE = 10;  // The opening angle of the servo motor arm
void setup()   
{  
  Serial.begin(9600); 
  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);  
  pinMode(out, INPUT);  
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, HIGH);  
  pickServo.attach(D2);
  dropServo.attach(D3);
  pickServo.write(30);
  dropServo.write(73);
  ThingSpeak.begin(client);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
     {
            delay(550);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
}  
void loop() 
{  
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);  
  //count OUT, pRed, RED  
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s3, HIGH);  
  //count OUT, pBLUE, BLUE  
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);  
  //count OUT, pGreen, GREEN  
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH); 
  Serial.print("R Intensity:");  
  Serial.print(red, DEC);  
  Serial.print(" G Intensity: ");  
  Serial.print(green, DEC);  
  Serial.print(" B Intensity : ");  
  Serial.print(blue, DEC);  
  if(red<39 & red>29 & green<93 & green>83 &blue<78 & blue>69){
    dropServo.write(73);
    delay(700);
    redcolor++;
    Serial.print("Red");
    open1();
    delay(200);
    close1();
    ThingSpeak.writeField(myChannelNumber, 1,redcolor, myWriteAPIKey);
  }
  if(green<75 & green>65 & blue<68 &blue>60){
    dropServo.write(107);
    delay(700);
    orangecolor++;
    Serial.print("Orange");
    open1();
    delay(200);
    close1();
    ThingSpeak.writeField(myChannelNumber, 2,orangecolor, myWriteAPIKey);
  }
  if(red<46 & red>36 & green<46 & green>37){
    dropServo.write(132);
    delay(700);
    greencolor++;
    Serial.print("Green");
    open1();
    delay(200);
    close1();
    ThingSpeak.writeField(myChannelNumber, 3,greencolor, myWriteAPIKey);
  }
  if(red<34 & red>25 & green<37 & green>28 & blue<53 & blue>43){
    dropServo.write(162);
    delay(700);
    yellowcolor++;
    Serial.print("Yellow");
    open1();
    delay(200);
    close1();
    ThingSpeak.writeField(myChannelNumber, 4,yellowcolor, myWriteAPIKey);
  } 
  Serial.println();  
 // delay(1000); 
} 
void open1(){ 
  pickServo.write(OPEN_ANGLE);   // Send the command to the servo motor to open the trap door
}
void close1(){ 
  pickServo.write(CLOSE_ANGLE);   // Send te command to the servo motor to close the trap door
}
