#include "xMod_SD.hpp"

namespace xdiversity
{
    void xMod_SDManager::begin(){
        if (SD.begin(GPIO_NUM_4, SPI, 25000000)) {
            Serial.println("SD connected !");
            SDMounted = true;
        } else {
            Serial.println("No SD");
            SDMounted = false;
        }
    }

    bool xMod_SDManager::checkSD(){
        return SDMounted;
    }
    
}