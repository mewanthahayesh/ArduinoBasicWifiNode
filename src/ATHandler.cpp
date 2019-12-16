#include "ATHandler.hpp"


void ATHandler::sendAT(const char* atcommand,uint16_t len) { //function to send AT commands to the ESP
 espSerial->println(atcommand);
}
/*
return values:
 0 : expected response found
 -1: expected response not found
*/

int ATHandler::receiveATResponse(ATResponseConfig responseRecv) { //to receive AT responses from ESP
  
    unsigned long timestamp = millis(); //get time stamp for timing
    uint16_t bufCount = 0;
    bool expectedRespFound = false;
    memset(responseRecv.responseBuf,0,responseRecv.responseBufLen); //

    do {
        while(espSerial->available() > 0){
            if(bufCount>=responseRecv.responseBufLen){
                break;
            } else {
                responseRecv.responseBuf[bufCount++] = espSerial->read();
            }
        }

        if(strstr(responseRecv.responseBuf,responseRecv.expectedResponse)!=NULL) {//expected response found in the buffer
            expectedRespFound=true;
        }

        if(bufCount>(responseRecv.responseBufLen-2)){
       
            //clear the serial buffer
            while(espSerial->available()>0){
                espSerial->read();
            }
            break;
        }

    } while(expectedRespFound!=true&&(millis()-timestamp<responseRecv.timeout));

    Serial.println(responseRecv.responseBuf);


    if (expectedRespFound==false){
        return -1;
    } else {
        return 0;
    }
   

}
void ATHandler::initESP8266SerialComm(SoftwareSerial* espSerial) { //initializes the serial port to communicate
    this->espSerial = espSerial;
}

