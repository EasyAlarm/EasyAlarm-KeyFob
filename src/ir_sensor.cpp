#include "ir_sensor.h"
#include <wiring_private.h>

bool IRSensor::IsTriggered()
{
    uint16_t value = 0;

    if (chrono.HasElpased())
    {
        digitalWrite(ledPin, HIGH);

        value = analogRead(photoDiodePin);
    }

    digitalWrite(ledPin, LOW);



    return value > threshold;
}

IRSensor::IRSensor(const uint16_t ledPin, const uint16_t photoDiodePin)
{
    this->ledPin = ledPin;
    this->photoDiodePin = photoDiodePin;

    chrono = Chrono(interval);
}

