#include "radio_packet_handler.h"
#include <string.h>

void RadioPacketHandler::SerializePacket(const RadioPacket* packet, unsigned char* outBuffer)
{
    memcpy(outBuffer, packet, sizeof(RadioPacket));
}

void RadioPacketHandler::DeserializePacket(const unsigned char* buffer, RadioPacket* outPacket)
{
    memcpy(outPacket, buffer, sizeof(RadioPacket));
}