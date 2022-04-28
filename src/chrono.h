#ifndef __CHRONO_H__
#define __CHRONO_H__

class Chrono
{
private:
    unsigned long interval;
    unsigned long previousMillis;
public:
    Chrono(unsigned long interval);
    Chrono();
    bool HasElpased();
};


#endif // __CHRONO_H__