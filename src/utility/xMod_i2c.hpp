#ifndef __XMOD_I2C__
#define __XMOD_I2C__

#include "xMod_common.h"

namespace xdiversity
{
    static void i2c_write(uint8_t addr, uint8_t reg, uint8_t reg_len, uint8_t data, uint8_t data_len) 
    {
        M5.In_I2C.writeRegister(addr, reg, &data, 1, 100000U);
    }

    static uint8_t i2c_read(uint8_t addr, uint8_t reg, uint8_t reg_len) 
    {
        uint8_t data;
        M5.In_I2C.readRegister(addr, reg, &data, 1, 100000U);
        return data;
    }

    static void enable_output(uint8_t bit)
    {
        uint8_t output_state = i2c_read(AW9523_ADDR, AW9523_REG_OUTPUT0, 1);
        output_state |= bit;
        i2c_write(AW9523_ADDR, AW9523_REG_OUTPUT0, 1, output_state, 1);
    }

    static void disable_output(uint8_t bit)
    {
        uint8_t output_state = i2c_read(AW9523_ADDR, AW9523_REG_OUTPUT0, 1);
        output_state &= ~bit;
        i2c_write(AW9523_ADDR, AW9523_REG_OUTPUT0, 1, output_state, 1);
    }
}

#endif