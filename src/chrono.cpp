#include "chrono.h"
#include <wiring_private.h>

bool Chrono::HasElpased()
{
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;
        return true;
    }
    else
    {
        return false;
    }
}

Chrono::Chrono(unsigned long interval)
{
    this->interval = interval;
}

Chrono::Chrono() {}
