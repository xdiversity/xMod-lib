#ifndef __XMOD_UTILS_CLASS_H__
#define __XMOD_UTILS_CLASS_H__

#include "xMod_common.h"


namespace xdiversity
{
    class xMod_Utils {
        public:
            xMod_Utils(){}

            bool connectWifi(String ssid, String pass);

            void disconnectWifi();

            

        private:
        
    };
}

#endif