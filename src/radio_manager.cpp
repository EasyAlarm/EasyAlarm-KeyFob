#include "radio_manager.h"
#include "radio_packet_handler.h"

RadioManager::RadioManager(uint16_t cePin, uint16_t csnPin, uint16_t thisNode)
{
    this->cePin = cePin;
    this->csnPin = csnPin;
    this->thisNode = thisNode;
}

RadioManager::RadioManager()
{

}

void RadioManager::Init()
{
    radio = RF24(cePin, csnPin);
    rfNetwork = new RF24Network(radio);


    radio.begin();
    rfNetwork->begin(90, thisNode);
    radio.setDataRate(RF24_2MBPS);
    radio.setRetries(3, 5);
}

void RadioManager::SendPacket(uint16_t receiverNode, RadioPacket* radioPacket)
{
    RF24NetworkHeader header(receiverNode);

    unsigned char serializedPacket[sizeof(RadioPacket)];

    RadioPacketHandler::SerializePacket(radioPacket, serializedPacket);

    rfNetwork->write(header, &serializedPacket, sizeof(serializedPacket));
}

bool RadioManager::HasReceivedPacket(RadioPacket* radioPacket)
{
    RF24NetworkHeader header;

    while (rfNetwork->available())
    {
        Serial.println("Received: ");
        unsigned char serializedBuffer[sizeof(RadioPacket)];

        rfNetwork->read(header, &serializedBuffer, sizeof(RadioPacket));

        RadioPacketHandler::DeserializePacket(serializedBuffer, radioPacket);

        return true;
    }

    return false;
}

void RadioManager::Update()
{
    rfNetwork->update();
}
