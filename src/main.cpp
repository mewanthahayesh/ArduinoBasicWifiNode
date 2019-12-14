#include <Arduino.h>

//ESP RX connected to D9
//ESP TX connected to D8

#include <SoftwareSerial.h>

SoftwareSerial espserial(8,9);

#define lightSense A0
#define LEDPin 6

unsigned long timeStamp=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  espserial.begin(9600);
  pinMode(lightSense,INPUT);
  pinMode(LEDPin,OUTPUT);

  timeStamp=millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()>0){
    espserial.write(Serial.read());
  }

  while(espserial.available()>0){
    Serial.write(espserial.read());
  }

  if(millis()-timeStamp>1000){
    timeStamp=millis();
   // Serial.print("LDR value: ");
   // Serial.println(analogRead(lightSense));

    if(analogRead(lightSense)>500){
        digitalWrite(LEDPin,HIGH);
    } else{
       digitalWrite(LEDPin,LOW);
    }
  }
  
}