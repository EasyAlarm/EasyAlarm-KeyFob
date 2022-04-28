#ifndef RADIO_PACKET_HANDLER_H_
#define RADIO_PACKET_HANDLER_H_

#include "radio_packet.h"

class RadioPacketHandler
{
private:

public:
    static void SerializePacket(const RadioPacket* packet, unsigned char* outBuffer);
    static void DeserializePacket(const unsigned char* buffer, RadioPacket* outPacket);
};

#endif
