#ifndef __XMOD_TOIO_CLASS_H__
#define __XMOD_TOIO_CLASS_H__

#include "xMod_common.h"

namespace xdiversity
{
    class xMod_Toio {
        public:
            xMod_Toio(){}

            String searchToio();
            String searchToio(String ID);

            String getAddress();

            String getName();

            bool connect();

            void disconnect();

            bool isConnected();

            String getBleProtocolVersion();

            void playSoundEffect(uint8_t sound_id, uint8_t volume = 0xff);

            void playSoundRaw(uint8_t* data, size_t length);

            void stopSound();

            void turnOnLed(uint8_t r, uint8_t g, uint8_t b);

            void turnOffLed();

            uint8_t getBatteryLevel();

            bool getButtonState();

            ToioCoreMotionData getMotion();

            void controlMotor(bool ldir, uint8_t lspeed, bool rdir, uint8_t rspeed, uint16_t duration = 0);

            void drive(int8_t throttle, int8_t steering);

            void controlMotorWithTarget(uint8_t distinction, uint8_t timeout, uint8_t movement_type, 
                uint8_t maximum_speed, uint8_t speed_change_type,
                uint16_t target_x, uint16_t target_y, 
                uint16_t target_angle_degree, uint8_t target_angle_and_rotation_bits = 0);

            void controlMotorWithMultipleTargets(uint8_t distinction, uint8_t timeout, uint8_t movement_type, 
                uint8_t maximum_speed, uint8_t speed_change_type,  uint8_t addition_setting,
                uint8_t target_num, ToioCoreTargetPos *target_positions);\

            void controlMotorWithAcceleration(uint8_t translational_speed, uint8_t acceleration,
                uint16_t rotational_velocity, uint8_t rotational_direction, uint8_t travel_direction,
                uint8_t priority, uint8_t duration);

            ToioCoreIDData getIDReaderData();
            

        private:
            // Toio オブジェクト生成
            Toio toio;
            ToioCore* toiocore;
            bool connected = false;

            std::vector<ToioCore*> toiocore_list;
    };
}

#endif