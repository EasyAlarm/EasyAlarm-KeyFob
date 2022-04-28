#ifndef RADIO_PACKET_H_
#define RADIO_PACKET_H_

#include <stdint.h>
#include <string.h>

enum class PayloadType : uint16_t
{
    PING, PONG, TRIGGERED, FIRE, CEASE, PAIR, OK
};

struct RadioPacket
{
    char header[4] = "rph";
    char address[7] = "a0000g";
    //dynamic allocaton
    char content[3];
    PayloadType payload;

    RadioPacket(PayloadType payload)
    {
        this->payload = payload;
    }
    RadioPacket(PayloadType payload, char* content)
    {
        strcpy(this->content, content);
        this->payload = payload;
    }

    RadioPacket() {};
};


#endif