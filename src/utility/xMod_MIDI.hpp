#ifndef __XMOD_MIDI_CLASS_H__
#define __XMOD_MIDI_CLASS_H__

#include "xMod_common.h"
#include "xMod_i2c.hpp"
#include <MIDI.h>
#include <queue>

#define MIDI_BAUDRATE 31250
#if defined(CONFIG_IDF_TARGET_ESP32)
// Core2
#define MIDI_OUT_RX_PIN 35
#define MIDI_OUT_TX_PIN 19
#define MIDI_IN_RX_PIN 19
#define MIDI_IN_TX_PIN 25
#elif defined(CONFIG_IDF_TARGET_ESP32S3)
// CoreS3 (MIDI_IN不明)
#define MIDI_OUT_RX_PIN 5
#define MIDI_OUT_TX_PIN 7
#define MIDI_IN_RX_PIN 7
#define MIDI_IN_TX_PIN 5
#endif

enum xMod_MIDIMode {
    MIDI_MODE_IN,
    MIDI_MODE_OUT
};

namespace xdiversity
{
    class xMod_MIDI : public midi::MidiInterface<midi::SerialMIDI<HardwareSerial>>
    {
        public:
            xMod_MIDI() : 
                MidiInterface(serialMIDI),
                serialMIDI(Serial2)
            {}

            void begin(midi::Channel inChannel = MIDI_CHANNEL_OMNI);
            void end();
            void update();

            void enable_MIDI();
            void disable_MIDI();
            void setMode(xMod_MIDIMode mode) { currentMode = mode; }

        private:
            midi::SerialMIDI<HardwareSerial> serialMIDI;
            xMod_MIDIMode currentMode = MIDI_MODE_OUT; // デフォルトはMIDI_OUT
    };
}

#endif