#include "xMod_Utils.hpp"

namespace xdiversity
{
    bool xMod_Utils::connectWifi(String ssid, String pass){
        WiFi.begin(ssid, pass);
        uint8_t tryNum = 0;
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.println("Connecting to WiFi...");
            tryNum += 1;
            if (tryNum > 4){
                Serial.println("Connecting faild");
                return false;
            }
        }
        Serial.println("Connected to WiFi");
        return true;
    }

    void xMod_Utils::disconnectWifi(){
        WiFi.disconnect();
    }

}