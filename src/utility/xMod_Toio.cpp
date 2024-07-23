#include "xMod_Toio.hpp"

namespace xdiversity
{
    String xMod_Toio::searchToio(){
        toiocore_list = toio.scan(3);
        size_t n = toiocore_list.size();
        if (n == 0) {
            return "Toio not found.";
        }
        toiocore = toiocore_list.at(0);
        return String(toiocore->getName().c_str());  //.substring(15,18)
    }
    String xMod_Toio::searchToio(String ID){
        toiocore_list = toio.scan(3);
        size_t n = toiocore_list.size();
        if (n == 0) {
            return "Toio not found.";
        }
        // toiocore->getName().c_str() == nameのtoioを探す
        for (size_t i = 0; i < n; i++) {
            String found_name = toiocore_list.at(i)->getName().c_str();
            // ID部分だけ比較
            if (found_name.substring(15,18) == ID) {
                toiocore = toiocore_list.at(i);
                return String(toiocore->getName().c_str());
            }
        }
        return "Toio not found.";
    }

    String xMod_Toio::getAddress(){
        if(connected){
            return String(toiocore->getAddress().c_str());
        }
    }

    String xMod_Toio::getName(){
        if(connected){
            return String(toiocore->getName().c_str());
        }
    }

    bool xMod_Toio::connect(){
        if (toiocore_list.size() == 0){
            // Serial.println("toioが見つかっていません、接続を中止します。");
            return false;
        }

        // Serial.println("- toio コア キューブに BLE 接続します。");
        connected = toiocore->connect();
        return connected;
    }

    void xMod_Toio::disconnect(){
        if(connected){
            toiocore->disconnect();
            connected = false;
        }
    }

    bool xMod_Toio::isConnected(){
        if(!connected){
            return false;
        }
        return toiocore->isConnected();
    }

    String xMod_Toio::getBleProtocolVersion(){
        return String(toiocore->getBleProtocolVersion().c_str());
    }

    void xMod_Toio::playSoundEffect(uint8_t sound_id, uint8_t volume){
        toiocore->playSoundEffect(sound_id, volume);
    }

    void xMod_Toio::playSoundRaw(uint8_t* data, size_t length){
        toiocore->playSoundRaw(data, length);
    }

    void xMod_Toio::stopSound(){
        toiocore->stopSound();
    }

    void xMod_Toio::turnOnLed(uint8_t r, uint8_t g, uint8_t b){
        toiocore->turnOnLed(r,g,b); 
    }

    void xMod_Toio::turnOffLed(){
        toiocore->turnOffLed();
    }

    uint8_t xMod_Toio::getBatteryLevel(){
        return toiocore->getBatteryLevel();
    }

    bool xMod_Toio::getButtonState(){
        return toiocore->getButtonState();
    }

    ToioCoreMotionData xMod_Toio::getMotion(){
        return toiocore->getMotion();
    }

    void xMod_Toio::controlMotor(bool ldir, uint8_t lspeed, bool rdir, uint8_t rspeed, uint16_t duration){
        toiocore->controlMotor(ldir, lspeed, rdir, rspeed, duration);
    }

    void xMod_Toio::drive(int8_t throttle, int8_t steering){
        toiocore->drive(throttle, steering);
    }

    void xMod_Toio::controlMotorWithTarget(uint8_t distinction, uint8_t timeout, uint8_t movement_type, 
        uint8_t maximum_speed, uint8_t speed_change_type,
        uint16_t target_x, uint16_t target_y, 
        uint16_t target_angle_degree, uint8_t target_angle_and_rotation_bits){
            toiocore->controlMotorWithTarget(distinction, timeout, movement_type, maximum_speed, speed_change_type, target_x, target_y, target_angle_degree, target_angle_and_rotation_bits);
        }

    void xMod_Toio::controlMotorWithMultipleTargets(uint8_t distinction, uint8_t timeout, uint8_t movement_type, 
        uint8_t maximum_speed, uint8_t speed_change_type,  uint8_t addition_setting,
        uint8_t target_num, ToioCoreTargetPos *target_positions){
            toiocore->controlMotorWithMultipleTargets(distinction, timeout, movement_type, maximum_speed, speed_change_type, addition_setting, target_num, target_positions);
        }

    void xMod_Toio::controlMotorWithAcceleration(uint8_t translational_speed, uint8_t acceleration,
        uint16_t rotational_velocity, uint8_t rotational_direction, uint8_t travel_direction,
        uint8_t priority, uint8_t duration){
            toiocore->controlMotorWithAcceleration(translational_speed, acceleration, rotational_velocity, rotational_direction, travel_direction, priority, duration);
        }

    ToioCoreIDData xMod_Toio::getIDReaderData(){
        return toiocore->getIDReaderData();
    }
}