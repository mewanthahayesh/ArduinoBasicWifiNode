#include "ESP8266.hpp"

bool ESP8266_UART::connectToWifiNetwork(const char* networkName,const char* password){
    char buf[100];
    memset(buf,0,100);
    sprintf(buf,"AT+CWJAP_DEF=\"%s\",\"%s\"",networkName,password);
    
    athandler1.sendAT(buf,strlen(buf));
    ATResponseConfig conf1;
    conf1.responseBuf=buf;
    conf1.expectedResponse="WIFI CONNECTED";
    conf1.responseBufLen=100;
    conf1.timeout=5000; //5 sec timeout

    if(!athandler1.receiveATResponse(conf1)){
        return true;
    } else {
        return false;
    }
}

void ESP8266_UART::initEspComm(SoftwareSerial *espserial){
    athandler1.initESP8266SerialComm(espserial);
}

bool  ESP8266_UART::checkComm(){
    char buf[100];
    //send AT and check if the device responds
    athandler1.sendAT("AT",strlen("AT"));
    ATResponseConfig conf1;
    conf1.responseBuf=buf;
    conf1.expectedResponse="OK"; //expect "OK" from the ESP
    conf1.responseBufLen=100;
    conf1.timeout=1000; //1 sec timeout

    if(athandler1.receiveATResponse(conf1)==0){
        return true;
    }else{
        return false;
    }
}

 bool ESP8266_UART::setStationMode(){
        char buf[100];
        athandler1.sendAT("AT+CWMODE_DEF=1",strlen("AT+CWMODE_DEF=1")); 
        ATResponseConfig conf1;
        conf1.responseBuf=buf;
        conf1.expectedResponse="OK"; //expect "OK" from the ESP
        conf1.responseBufLen=100;
        conf1.timeout=1000; //1 sec timeout

        if(athandler1.receiveATResponse(conf1)==0){
            return true;
        }else{
            return false;
        }
 }