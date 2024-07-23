#ifndef __XMOD_SD_CLASS_H__
#define __XMOD_SD_CLASS_H__

#include "xMod_common.h"
#include "xMod_WaveOut.hpp"

namespace xdiversity
{
    class xMod_SDManager {
        public:
            xMod_SDManager(){}

            void begin();

            bool checkSD();

        private:
            bool SDMounted = false; 
    };
}

#endif