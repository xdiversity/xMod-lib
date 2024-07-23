#include "xMod_Button.hpp"

namespace xdiversity
{
    void xMod_Button::update(){
        uint8_t p0_key = i2c_read(AW9523_ADDR, AW9523_REG_INPUT0, 1);

        lastState = currentState;
        currentState = (getBit(p0_key, bitPosition) == 0x00);
    }

    bool xMod_Button::isPressed(){
        return currentState;
    }

    bool xMod_Button::wasPressed(){
        return !lastState && currentState;
    }

    bool xMod_Button::wasReleased(){
        return lastState && !currentState;
    }

    bool xMod_Button::isHeld(){
        return lastState && currentState;
    }
}