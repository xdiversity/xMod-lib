#ifndef __XMOD_H__
#define __XMOD_H__

#define LIB_VERSION "0.1"

#include "utility/xMod_common.h"
#include "utility/xMod_i2c.hpp"
#include "utility/xMod_Button.hpp"
#include "utility/xMod_WaveOut.hpp"
#include "utility/xMod_Toio.hpp"
#include "utility/xMod_Mic.hpp"
#include "utility/xMod_MIDI.hpp"
#include "utility/xMod_Utils.hpp"
#include "utility/xMod_SD.hpp"
#include "utility/xMod_OpenAI.hpp"

enum xMod_DebugMode {
    DEBUG_MODE_NONE,
    DEBUG_MODE_DISPLAY,
    DEBUG_MODE_SERIAL
};

namespace xdiversity
{
    struct config_t : public m5::M5Unified::config_t {
        // TODO: xMod固有の設定をここに追加
    };

    class xMod_Class {
        public:
            xMod_Class() {}

            // configを返すメソッド
            static config_t config() {
                config_t cfg;
                // M5のデフォルト設定をコピー
                static_cast<m5::M5Unified::config_t&>(cfg) = M5.config();
                cfg.external_spk = true;
                cfg.internal_spk = false;
                #if defined(CONFIG_IDF_TARGET_ESP32)
                    // Core2
                    cfg.internal_mic = true;
                #elif defined(CONFIG_IDF_TARGET_ESP32S3)
                    // CoreS3 (要検証)
                    cfg.internal_mic = false;
                #endif
                // TODO: xMod固有のデフォルト設定を上書き
                return cfg;
            }

            // xMod固有のコンポーネントへのアクセス
            xMod_Button BtnL = xMod_Button(4);
            xMod_Button BtnR = xMod_Button(5);
            xMod_WaveOut WaveOut;
            xMod_Toio Toio;
            xMod_Mic Mic;
            xMod_MIDI MIDI;
            xMod_Utils Utils;
            xMod_SDManager SDM;
            xMod_OpenAI OpenAI;

            void update() { 
                // M5の更新処理をここで行うべきかは要検討
                M5.update();
                
                // xMod固有の更新処理
                BtnL.update();
                BtnR.update();
                MIDI.update();
            }

            void begin(config_t cfg = config());

            void recordSound(int time, String filename = "/audio.wav");

            void DisplayDebug(const String& message);

            void setDebugMode(xMod_DebugMode mode){ debugMode = mode; }

        private:
            static void aw9523_init_core2();
            static void aw9523_init_cores3();

            xMod_DebugMode debugMode = DEBUG_MODE_NONE;
    };
}

extern xdiversity::xMod_Class xMod;

#endif