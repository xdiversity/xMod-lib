#ifndef __XMOD_MIC_CLASS_H__
#define __XMOD_MIC_CLASS_H__

#include "xMod_common.h"
#include "xMod_i2c.hpp"

#define SAMPLING_RATE (16384)  
#define BUFFER_LEN    (1024 *  1)   

namespace xdiversity
{
    class xMod_Mic {
        public:
            xMod_Mic() {}

            void recordStart(String filename = "/audio.wav");
            void recordStop();

            void xModRecordTask();

        private:
            String filenameInfo = "/audio.wav";
            bool recFlag;
            uint8_t wavHeader[44] = {
                0x52, 0x49, 0x46, 0x46, // 'RIFF'
                0x00, 0x00, 0x00, 0x00, // ファイルサイズ (後で更新)
                0x57, 0x41, 0x56, 0x45, // 'WAVE'
                0x66, 0x6D, 0x74, 0x20, // 'fmt '
                0x10, 0x00, 0x00, 0x00, // フォーマットチャンクサイズ
                0x01, 0x00,             // オーディオフォーマット (1 = PCM)
                0x01, 0x00,             // チャンネル数
                0x40, 0x3E, 0x00, 0x00, // サンプルレート (16384Hz)
                0x80, 0x7C, 0x00, 0x00, // バイトレート (16384 * 16 / 8)
                0x02, 0x00,             // ブロックアライン (16 / 8 * 1)
                0x10, 0x00,             // ビット深度 (16ビット)
                0x64, 0x61, 0x74, 0x61, // 'data'
                0x00, 0x00, 0x00, 0x00  // データサイズ (後で更新)
            };
    };
}

#endif