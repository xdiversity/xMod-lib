#ifndef __XMOD_WAVEOUT_CLASS_H__
#define __XMOD_WAVEOUT_CLASS_H__

#include "xMod_common.h"
#include "xMod_i2c.hpp"

namespace xdiversity
{
    class xMod_WaveOut {
        public:
            /// @brief コンストラクタ
            xMod_WaveOut() {}

            /// M5.Speakerの各種機能へのアクセスを提供
            void begin() { M5.Speaker.begin(); }
            void end() { M5.Speaker.end(); }
            bool isPlaying(void) { return M5.Speaker.isPlaying(); }
            void setVolume(uint8_t volume) { M5.Speaker.setVolume(volume); }
            uint8_t getVolume(void) { return M5.Speaker.getVolume(); }
            void stop(void) { M5.Speaker.stop(); }
            void stop(uint8_t channel) { M5.Speaker.stop(channel); }
            bool tone(float frequency, uint32_t duration = UINT32_MAX, int channel = -1, bool stop_current_sound = true) { 
                return M5.Speaker.tone(frequency, duration, channel, stop_current_sound); 
            }
            bool playWav(const uint8_t* wav_data, size_t data_len = ~0u, uint32_t repeat = 1, int channel = -1, bool stop_current_sound = false) { 
                return M5.Speaker.playWav(wav_data, data_len, repeat, channel, stop_current_sound); 
            }
            template<typename T>
            bool playRaw(const T* raw_data, size_t array_len, uint32_t sample_rate = 44100, bool stereo = false, uint32_t repeat = 1, int channel = -1, bool stop_current_sound = false) {
                return M5.Speaker.playRaw(raw_data, array_len, sample_rate, stereo, repeat, channel, stop_current_sound);
            }

            /// @brief スピーカー出力の有効化・無効化
            void enable_Speaker();
            void disable_Speaker();

            /// @brief リニア共振アクチュエータ出力の有効化・無効化
            void enable_LRA();
            void disable_LRA();

            /// @brief ラインアウト出力の有効化・無効化
            void enable_LineOut();
            void disable_LineOut();

            //Wavファイル再生
            void playWavFile(const char* filename);

        private:
            // WAVファイルのヘッダー構造体
            struct WAVHeader {
                char riff[4];
                uint32_t chunkSize;
                char wave[4];
                char fmt[4];
                uint32_t subchunk1Size;
                uint16_t audioFormat;
                uint16_t numChannels;
                uint32_t sampleRate;
                uint32_t byteRate;
                uint16_t blockAlign;
                uint16_t bitsPerSample;
                char data[4];
                uint32_t dataSize;
            };

            // バッファサイズ（必要に応じて調整）
            const int BUFFER_SIZE = 1024;
    };
}

#endif