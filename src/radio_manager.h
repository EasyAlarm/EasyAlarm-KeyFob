#ifndef RADIO_MANAGER_H_
#define RADIO_MANAGER_H_

#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>

#include "radio_packet.h"

class RadioManager
{
private:
    uint16_t cePin;
    uint16_t csnPin;

    uint16_t thisNode;

    RF24 radio;
    RF24Network* rfNetwork;


public:
    RadioManager(uint16_t cePin, uint16_t csnPin, uint16_t thisNode);
    RadioManager();
    void Init();
    void SendPacket(uint16_t receiverNode, RadioPacket* radioPacket);
    bool HasReceivedPacket(RadioPacket* radioPacket);
    void Update();
};

#endif