#include "xMod.hpp"

#include <driver/i2s.h>
#include <BluetoothA2DPSink.h>

BluetoothA2DPSink a2dpSink;

//bluetoothSpeakerとしての動作を始める
void bluetoothSpeakerStart(){
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

//bluetoothSpeakerとしての動作を終える(再開不可)
void bluetoothSpeakerEnd(){
    a2dpSink.end("M5Stack Speaker");
    xMod.WaveOut.disable_Speaker();
}


void setup() {
  // xModの初期化
  xMod.begin();

  //デバッグ画面表示を許可
  xMod.setDebugDisplay();

  // M5Coreディスプレイの初期化
  M5.Display.begin(); 
  M5.Display.fillRect(0, 0, 320, 240, BLACK);
  M5.Display.setCursor(0, 0);
  xMod.DisplayDebug("Bluetooth Speaker"); 

  bluetoothSpeakerStart();
}

void loop() {
  //　xModの更新処理：M5の更新処理も内部で行われる
  xMod.update();

  // xModの物理ボタンが押されている場合
  if (xMod.BtnL.isPressed()){
    M5.Display.println("End");
    bluetoothSpeakerEnd();
  }
  
  delay(100);
}