#ifndef ESP8266UART
#define ESP8266UART

#include "ATHandler.hpp"

class ESP8266_UART{

    private:
    ATHandler athandler1;

    public:
    //connect to Wifi Network using network id and password
    bool connectToWifiNetwork(const char* networkName,const char* password);
    void initEspComm(SoftwareSerial *espserial);
    bool checkComm();
    bool setStationMode(); 

};

#endif