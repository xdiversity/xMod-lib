#include "xMod_MIDI.hpp"

namespace xdiversity
{
    void xMod_MIDI::begin(midi::Channel inChannel)
    {
        switch (currentMode)
        {
        case MIDI_MODE_IN:
            Serial2.begin(MIDI_BAUDRATE, SERIAL_8N1, MIDI_IN_RX_PIN, MIDI_IN_TX_PIN);
            break;
        case MIDI_MODE_OUT:
            Serial2.begin(MIDI_BAUDRATE, SERIAL_8N1, MIDI_OUT_RX_PIN, MIDI_OUT_TX_PIN);
            break;
        }
        MidiInterface::begin(inChannel);
    }

    void xMod_MIDI::end() {
        Serial2.end();
    }

    void xMod_MIDI::update() {
        if(currentMode == MIDI_MODE_IN) read();
    }
    
    void xMod_MIDI::enable_MIDI() {
        enable_output(MIDI_BIT);
    }

    void xMod_MIDI::disable_MIDI() {
        disable_output(MIDI_BIT);
    }
}