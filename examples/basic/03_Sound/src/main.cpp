#include "xMod.hpp"

uint8_t outputDestination = 0;

void setup() {
  // xModの初期化
  xMod.begin();

  // M5Coreディスプレイの初期化
  M5.Display.begin(); 
  M5.Display.setCursor(0, 0);

  // xModの振動モーターを有効化（振動モーター、スピーカー、ラインアウトのいずれか1つ)
  xMod.WaveOut.enable_Speaker();
  xMod.WaveOut.begin();
  xMod.WaveOut.setVolume(200);
  
  // SDカードの接続
  while (!xMod.SDM.checkSD()){
    xMod.SDM.begin();
    if (!xMod.SDM.checkSD()){
      xMod.DisplayDebug("No SDcard");
      delay(5000);
    }
  }
  M5.Display.println("SD Connected");
  
}

void loop() {
  //　xModの更新処理：M5の更新処理も内部で行われる
  xMod.update();

  // xModの物理ボタンが押されている場合
  if (xMod.BtnL.isPressed()){
    if (outputDestination == 0){
      M5.Display.println("Speaker");
    }
    else if (outputDestination == 1){
      M5.Display.println("LRA");
    }
    else if (outputDestination == 2){
      M5.Display.println("LineOut");
    }

    // 音声・振動出力（低い周波数）
    xMod.WaveOut.tone(50, 500, -1, false);
    delay(500);

    // 音声・振動出力（高い周波数）
    xMod.WaveOut.tone(500, 500, -1, false);
    delay(500);

    //出力先切り替え
    if (outputDestination == 0){
      xMod.WaveOut.disable_Speaker();
      xMod.WaveOut.enable_LRA();
      outputDestination = 1;
    }
    else if (outputDestination == 1){
      xMod.WaveOut.disable_LRA();
      xMod.WaveOut.enable_LineOut();
      outputDestination = 2;
    }
    else if (outputDestination == 2){
      xMod.WaveOut.disable_LineOut();
      xMod.WaveOut.enable_Speaker();
      outputDestination = 0;
    }
  }
  else if (xMod.BtnR.isPressed()){
    // SDカードに2秒録音、その後再生
    if (xMod.SDM.checkSD()){
      delay(500);
      M5.Display.println("Record Start");
      xMod.recordSound(2000, "/audio.wav");
      M5.Display.println("Record Stop"); 
      delay(500);

      M5.Display.println("Play Sound"); 
      xMod.WaveOut.playWavFile("/audio.wav");
      M5.Display.println("Play End"); 
    } else {
      M5.Display.println("No SDcard"); 
    }
  }
  
  delay(100);
}