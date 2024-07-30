#include "xMod.hpp"

/// M5のようにグローバルインスタンスとして定義
xdiversity::xMod_Class xMod;

/// @brief  xModの初期化
/// @param cfg 
void xdiversity::xMod_Class::begin(config_t cfg) {
    M5.begin(cfg);
    M5.In_I2C.begin();

    // スピーカー関係の初期化
    auto spk_cfg        = M5.Speaker.config();
    spk_cfg.i2s_port    = I2S_NUM_1;
    spk_cfg.stereo      = true;
    spk_cfg.sample_rate = 48000;
#if defined(CONFIG_IDF_TARGET_ESP32)
    // Core2
    spk_cfg.pin_bck      = 0;
    spk_cfg.pin_ws       = 27;
    spk_cfg.pin_data_out = 2;
#elif defined(CONFIG_IDF_TARGET_ESP32S3)
    // CoreS3
    spk_cfg.pin_bck      = 0;
    spk_cfg.pin_ws       = 6;
    spk_cfg.pin_data_out = 13;
#endif
    M5.Speaker.config(spk_cfg);
    M5.Speaker.setVolume(128);
    M5.Speaker.begin();
    M5.Speaker.end();

    // マイク関係の初期化
#if defined(CONFIG_IDF_TARGET_ESP32)
    // Core2
#elif defined(CONFIG_IDF_TARGET_ESP32S3)
    // CoreS3
    auto mic_cfg          = M5.Mic.config();
    mic_cfg.over_sampling = 1;
    mic_cfg.i2s_port      = I2S_NUM_0;
    mic_cfg.pin_data_in   = 14;
    mic_cfg.pin_ws        = 0;
    mic_cfg.pin_bck       = -1;
    M5.Mic.config(mic_cfg);
#endif
    M5.Mic.begin();
    M5.Mic.end();

    // xMod基盤の初期設定
#if defined(CONFIG_IDF_TARGET_ESP32)
    // Core2
    aw9523_init_core2();
#elif defined(CONFIG_IDF_TARGET_ESP32S3)
    // CoreS3
    aw9523_init_cores3();
#endif
}

void xdiversity::xMod_Class::recordSound(int time){
    xMod.Mic.recordStart();
    delay(time);
    xMod.Mic.recordStop();
}

void xdiversity::xMod_Class::DisplayDebug(const String& message){
    if (debugMode == DEBUG_MODE_DISPLAY){
        const lgfx::IFont* userFont = M5.Display.getFont();
        int32_t cursorY = M5.Display.getCursorY();

        const int lineHeight = 8;  // デバッグ文字の高さ
        int32_t maxY = 240; //画面の広さ

        M5.Display.setFont(&fonts::Font0);

        if (cursorY + lineHeight > maxY) {
            // 画面からはみ出るようならクリア
            M5.Display.fillRect(0, 0, 320, 240, BLACK);
            M5.Display.setCursor(0, 0);
        }
        M5.Display.println(message);

        // 画面の更新
        M5.Display.display();
        //フォントを戻す
        M5.Display.setFont(userFont);
    } else if (debugMode == DEBUG_MODE_SERIAL){
        Serial.println(message);
    }
}

void xdiversity::xMod_Class::setDebugNone(){
    debugMode = DEBUG_MODE_NONE;
}

void xdiversity::xMod_Class::setDebugDisplay(){
    debugMode = DEBUG_MODE_DISPLAY;
}

void xdiversity::xMod_Class::setDebugSerial(){
    debugMode = DEBUG_MODE_SERIAL;
}

void xdiversity::xMod_Class::bluetoothSpeakerStart(){
    xMod.WaveOut.enable_Speaker();
    
    // Initialize I2S audio output
    i2s_pin_config_t pinConfig = {
        .bck_io_num = I2S_BCK_PIN,
        .ws_io_num = I2S_WS_PIN,
        .data_out_num = I2S_DOUT_PIN,
        .data_in_num = I2S_PIN_NO_CHANGE
    };

    // Set up Bluetooth A2DP sink
    a2dpSink.set_pin_config(pinConfig);
    a2dpSink.start("M5Stack Speaker");
}

void xdiversity::xMod_Class::bluetoothSpeakerEnd(){
    a2dpSink.end("M5Stack Speaker");
    xMod.WaveOut.disable_Speaker();
}

void xdiversity::xMod_Class::aw9523_init_core2() {
    // Reset AW9523
    i2c_write(AW9523_ADDR, AW9523_REG_SOFTRESET, 1, 0x00, 1);
    vTaskDelay(30 / portTICK_RATE_MS);
    // P0 I/O Mode  0-OUTPUT 1-INPUT
    // P0_0 nAudio/TRS_SW   MIDI信号とオーディオ信号の切り替え  0-Audio 1-MIDI
    // P0_1 LO_PA_EN
    // P0_2 LRA_PA_EN
    // P0_3 SPK_PA_EN
    // P0_4 USER_KEY1
    // P0_5 USER_KEY2
    // P0_6 NC
    // P0_7 NC
    i2c_write(AW9523_ADDR, AW9523_REG_CONFIG0, 1, 0b00110000, 1);
    // P0 I/O Mode  0-OUTPUT 1-INPUT
    // P0_0 NC: Output
    // P0_1 NC: Output
    // P0_2 NC: Output
    // P0_3 NC: Output
    // P0_4 USER_KEY1: Input
    // P0_5 USER_KEY2: Input
    // P0_6 NC: Output
    // P0_7 NC: Output
    i2c_write(AW9523_ADDR, AW9523_REG_CONFIG0 + 1, 1, 0b00110000, 1);

    // GPIO Push-Pull mode
    i2c_write(AW9523_ADDR, AW9523_REG_GCR, 1, (1 << 4), 1);

    // P0 GPIO Default HIGH OUTPUT PIN
    i2c_write(AW9523_ADDR, AW9523_REG_OUTPUT0, 1, 0b0, 1);
    // P1 GPIO Default HIGH OUTPUT PIN
    i2c_write(AW9523_ADDR, AW9523_REG_OUTPUT0 + 1, 1, 0b00001100, 1);
}

void xdiversity::xMod_Class::aw9523_init_cores3() {
    // Reset AW9523
    i2c_write(AW9523_ADDR, AW9523_REG_SOFTRESET, 1, 0x00, 1);
    vTaskDelay(30 / portTICK_RATE_MS);
    // P0 I/O Mode  0-OUTPUT 1-INPUT
    // P0_0 nAudio/TRS_SW   MIDI signal and audio signal switch  0-Audio 1-MIDI
    // P0_1 LO_PA_EN
    // P0_2 LRA_PA_EN
    // P0_3 SPK_PA_EN
    // P0_4 USER_KEY1
    // P0_5 USER_KEY2
    // P0_6 NC
    // P0_7 NC
    i2c_write(AW9523_ADDR, AW9523_REG_CONFIG0, 1, 0b00110000, 1);
    // P0 I/O Mode  0-OUTPUT 1-INPUT
    // P0_0 NC: Output
    // P0_1 NC: Output
    // P0_2 NC: Output
    // P0_3 NC: Output
    // P0_4 USER_KEY1: Input
    // P0_5 USER_KEY2: Input
    // P0_6 NC: Output
    // P0_7 NC: Output
    i2c_write(AW9523_ADDR, AW9523_REG_CONFIG0 + 1, 1, 0b00110000, 1);

    // GPIO Push-Pull mode
    i2c_write(AW9523_ADDR, AW9523_REG_GCR, 1, (1 << 4), 1);

    // P0 GPIO Default HIGH OUTPUT PIN
    // i2c_write(AW9523_ADDR, AW9523_REG_OUTPUT0, 1, 0b1100, 1);
    i2c_write(AW9523_ADDR, AW9523_REG_OUTPUT0, 1, 0b0, 1);
    // P1 GPIO Default HIGH OUTPUT PIN
    // i2c_write(AW9523_ADDR, AW9523_REG_OUTPUT0 + 1, 1, 0b00001100, 1);
}
