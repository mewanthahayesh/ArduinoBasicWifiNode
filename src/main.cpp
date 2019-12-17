#include <Arduino.h>

//ESP RX connected to D9
//ESP TX connected to D8
#include "ESP8266.hpp"


#define lightSense A0
#define LEDPin 6

unsigned long timeStamp=0;

SoftwareSerial espserial(8,9);
ESP8266_UART esp1;


void setup() {
  // put your setup code here, to run once:
 // Serial.begin(9600);
  espserial.begin(9600);
  pinMode(lightSense,INPUT);
  pinMode(LEDPin,OUTPUT);

  esp1.initEspComm(&espserial);
  bool stat = esp1.checkComm();
  if(stat==true){
    Serial.println("ESP Responded");
  } else{
    Serial.println("ESP Unresponsive!");
  }

  stat = esp1.setStationMode();
  if(stat==true){
    Serial.println("ESP STA OK");
  } else{
    Serial.println("ESP NO STA");
  }


  //************UNCOMMENT THE FOLLOWING TO CONNECT TO YOUR WIFI NETWORK******************
  //Change SSID and PASSWORD to your wifi credentials
  /*
  stat = esp1.connectToWifiNetwork("SSID","PASSWORD");
  if(stat){
      Serial.println("WIFI Connected!");
  }else {
      Serial.println("WIFI NOT Connected!");
  }
  */

   stat = esp1.connectToTCPServer("52.63.133.79",1234);
  if(stat==true){
    Serial.println("Connected");
  } else{
    Serial.println("Conn. error");
  }
  
  timeStamp = millis();

}

void loop() {
  // put your main code here, to run repeatedly:
  // while(Serial.available()>0){
  //   espserial.write(Serial.read());
  // }

  // while(espserial.available()>0){
  //   Serial.write(espserial.read());
  // }

  // if(millis()-timeStamp>1000){
  //   timeStamp=millis();
  //  // Serial.print("LDR value: ");
  //  // Serial.println(analogRead(lightSense));

  //   if(analogRead(lightSense)>500){
  //       digitalWrite(LEDPin,HIGH);
  //   } else{
  //      digitalWrite(LEDPin,LOW);
  //   }
  // }


if(millis()-timeStamp>15000){

for(int i=0;i<3;i++) {
  bool stat = esp1.checkTCPStatus();
  if(stat!=0){
     esp1.connectToTCPServer("52.63.133.79",1234);
  }else{
    break;
  }
}

  //send data to the server
  int ldrVal = analogRead(lightSense);
  char buf[100];
  memset(buf,0,100);
  sprintf(buf,"{\"ldr\":%d}",ldrVal);

  if(esp1.sendTCPData(buf,strlen(buf))){
    Serial.println("MSG send success!");
  }else{
    Serial.println("MSG send fail");
  }

  //esp1.closeTCPConn();
  timeStamp=millis();

}

delay(3000);

}