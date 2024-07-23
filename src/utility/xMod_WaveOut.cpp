#include "xMod_WaveOut.hpp"

namespace xdiversity
{
    void xMod_WaveOut::enable_Speaker() {
        enable_output(SPEAKER_BIT);
    }

    void xMod_WaveOut::disable_Speaker() {
        disable_output(SPEAKER_BIT);
    }

    void xMod_WaveOut::enable_LRA() {
        enable_output(LRA_BIT);
    }

    void xMod_WaveOut::disable_LRA() {
        disable_output(LRA_BIT);
    }

    void xMod_WaveOut::enable_LineOut() {
        enable_output(LINEOUT_BIT);
    }

    void xMod_WaveOut::disable_LineOut() {
        disable_output(LINEOUT_BIT);
    }

    void xMod_WaveOut::playWavFile(const char* filename){
        File wavFile = SD.open(filename);
        if (!wavFile) {
            Serial.println("Failed to open WAV file: " + String(filename));
            return;
        }

        WAVHeader header;
        wavFile.read((uint8_t*)&header, sizeof(WAVHeader));

        // WAVファイルのヘッダー情報を表示（デバッグ用）
        Serial.println("Sample Rate: " + String(header.sampleRate));
        Serial.println("Channels: " + String(header.numChannels));
        Serial.println("Bits Per Sample: " + String(header.bitsPerSample));

        // スピーカーを有効化
        enable_Speaker();

        // バッファを確保
        int16_t* buffer = (int16_t*)malloc(BUFFER_SIZE * sizeof(int16_t));
        if (!buffer) {
            Serial.println("Failed to allocate buffer");
            wavFile.close();
            return;
        }

        // ファイルを読み込んで再生
        while (wavFile.available()) {
            int bytesRead = wavFile.read((uint8_t*)buffer, BUFFER_SIZE * sizeof(int16_t));
            int samplesRead = bytesRead / sizeof(int16_t);
            
            if (samplesRead > 0) {
                playRaw(buffer, samplesRead, header.sampleRate, false);
                while (isPlaying()) {
                    delay(1);
                }
            }
        }

        // クリーンアップ
        free(buffer);
        wavFile.close();
        disable_Speaker();
    }
}