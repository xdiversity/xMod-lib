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

            // M5の主要コンポーネントへの直接アクセスを提供
            // M5GFX& Display() { return M5.Display; }
            // M5GFX& Lcd() { return M5.Display; }
            // m5::Button_Class& BtnA() { return M5.BtnA; }
            // m5::Button_Class& BtnB() { return M5.BtnB; }
            // m5::Button_Class& BtnC() { return M5.BtnC; }
            // m5::I2C_Class& In_I2C() { return M5.In_I2C; }

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

            void recordSound(int time);

            void DisplayDebug(const String& message);

            void setDebugMode(int mode);

        private:
            static void aw9523_init_core2();
            static void aw9523_init_cores3();

            //デバッグ表示 0:表示なし 1:画面表示 2:シリアル表示
            uint8_t debugMode = 0;
    };
}

extern xdiversity::xMod_Class xMod;

#endif