#include "pair.h"

#include <EEPROM.h>
#include "addresses.h"

Pair::Pair(RadioManager* radioManager)
{
    this->radioManager = radioManager;
}

bool Pair::IsPaired()
{
    if (EEPROM.read(EEPROM_ADDRESS) == 255)
        return false;

    return true;
}

void Pair::Reset()
{
    EEPROM.write(EEPROM_ADDRESS, 255);
}

void Pair::SaveNodeAddr(uint16_t nodeAddr)
{
    EEPROM.write(EEPROM_ADDRESS, nodeAddr);
}

bool Pair::Init()
{
    radioManager->SendPacket(HUB_NODE, &RadioPacket(PayloadType::PAIR));

    RadioPacket incomingRadioPacket;

    uint16_t count = 0;

    while (true)
    {
        delay(1000);

        radioManager->Update();
        count++;

        if (count > TIMEOUT)
        {
            return false;
        }

        if (!radioManager->HasReceivedPacket(&incomingRadioPacket))
            continue;

        if (incomingRadioPacket.payload == PayloadType::OK)
        {
            uint16_t nodeAddr = (uint16_t)strtoul(incomingRadioPacket.content, NULL, 16);

            SaveNodeAddr(nodeAddr);
            return true;
        }

    }
}
