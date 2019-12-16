#ifndef ATHANDLER
#define ATHANDLER

#include <Arduino.h>
#include <SoftwareSerial.h>


typedef struct {
    const char* expectedResponse;
    unsigned long timeout;
    char* responseBuf;
    uint16_t responseBufLen;

}ATResponseConfig;


class ATHandler{
    private:
        SoftwareSerial* espSerial;
    public:
        void sendAT(const char* atcommand,uint16_t len); //function to send AT commands to the ESP
        int receiveATResponse(ATResponseConfig responseRecv); //to receive AT responses from ESP
        void initESP8266SerialComm(SoftwareSerial* espSerial); //initializes the serial port to communicate
};


#endif