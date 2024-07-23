#ifndef __XMOD_BUTTON_CLASS_H__
#define __XMOD_BUTTON_CLASS_H__

#include "xMod_common.h"
#include "xMod_i2c.hpp"

#define getBit(x, y) ((x >> y) & 0x01)

namespace xdiversity
{
    class xMod_Button {
        public:
            xMod_Button(uint8_t position): bitPosition(position) {}

            void update();

            bool isPressed();

            bool wasPressed();

            bool wasReleased();

            bool isHeld();

        private:
            bool lastState = false;       // 前の状態
            bool currentState = false;    // 現在の状態
            uint8_t bitPosition;
    };
}

#endif