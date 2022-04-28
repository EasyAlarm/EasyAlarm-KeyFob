#ifndef __IR_SENSOR_H__
#define __IR_SENSOR_H__

#include <stdint.h>
#include "chrono.h"

class IRSensor
{
private:
    uint16_t ledPin;
    uint16_t photoDiodePin;
    const uint16_t interval = 1000;
    const uint16_t threshold = 300;

    Chrono chrono;

public:
    bool IsTriggered();
    IRSensor(const uint16_t ledPin, const uint16_t photoDiodePin);
};




#endif // __IR_SENSOR_H__