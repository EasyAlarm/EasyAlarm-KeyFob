#ifndef __PAIR_H__
#define __PAIR_H__

#include <stdint.h>
#include "radio_manager.h"

class Pair
{

private:
    static const uint16_t EEPROM_ADDRESS = 0;
    RadioManager* radioManager;
    const uint16_t TIMEOUT = 10;

    void SaveNodeAddr(uint16_t nodeAddr);

    /* data */
public:
    static bool IsPaired();
    static void Pair::Reset();
    Pair(RadioManager* radioManager);
    bool Init();
};




#endif // __PAIR_H__