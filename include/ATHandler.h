#ifndef ATHANDLER
#define ATHANDLER

#include <Arduino.h>

void sendAT(char* atcommand,uint16_t len);
void receiveATResponse(unsigned long timeout);


#endif