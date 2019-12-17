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

 bool ESP8266_UART::connectToTCPServer(const char* ip,unsigned int port){ 
    char buf[100];
    memset(buf,0,100);
    sprintf(buf,"AT+CIPSTART=\"TCP\",\"%s\",%d",ip,port);
    
    athandler1.sendAT(buf,strlen(buf));
    ATResponseConfig conf1;
    conf1.responseBuf=buf;
    conf1.expectedResponse="OK";
    conf1.responseBufLen=100;
    conf1.timeout=5000; //5 sec timeout

    if(!athandler1.receiveATResponse(conf1)){
        return true;
    } else {
        return false;
    }
 }

 int ESP8266_UART:: checkTCPStatus(){
      char buf[100];
        athandler1.sendAT("AT+CIPSTATUS",strlen("AT+CIPSTATUS")); 
        ATResponseConfig conf1;
        conf1.responseBuf=buf;
        conf1.expectedResponse="OK"; //expect "OK" from the ESP
        conf1.responseBufLen=100;
        conf1.timeout=3000; //3 sec timeout

        if(athandler1.receiveATResponse(conf1)==0){
            //check if esp8266 is connected to the server
            if(strstr(buf,"STATUS:3")!=NULL){
                return 0;
            }else{
                return 1;
            }
        }else{
            return -1;
        }
 }

bool ESP8266_UART::sendTCPData(const char* data,unsigned int datalen){
    char buf[100];
    memset(buf,0,100);
    sprintf(buf,"AT+CIPSEND=%d",datalen);
    athandler1.sendAT(buf,strlen(buf)); 
    ATResponseConfig conf1;
    conf1.responseBuf=buf;
    conf1.expectedResponse=">"; //expect "OK" from the ESP
    conf1.responseBufLen=100;
    conf1.timeout=3000; //3 sec timeout

    if(athandler1.receiveATResponse(conf1)==0){
         athandler1.sendAT(data,datalen); 

        ATResponseConfig conf1;
        conf1.responseBuf=buf;
        conf1.expectedResponse="SEND OK"; //expect "OK" from the ESP
        conf1.responseBufLen=100;
        conf1.timeout=3000; //3 sec timeout

        if(athandler1.receiveATResponse(conf1)==0){
            return true;
        }else{
            return false;
        }

    }else{
        return false;
    }
}

bool ESP8266_UART::closeTCPConn(){
    
    char buf[100];
    athandler1.sendAT("AT+CIPCLOSE",strlen("AT+CIPCLOSE")); 
    ATResponseConfig conf1;
    conf1.responseBuf=buf;
    conf1.expectedResponse="OK"; //expect "OK" from the ESP
    conf1.responseBufLen=100;
    conf1.timeout=3000; //3 sec timeout

    if(athandler1.receiveATResponse(conf1)==0){
        return true;
    }else{
        return false;
    }
}
