#include "xMod.hpp"

void setup() {
  // xModの初期化
  xMod.begin();

  // M5Coreディスプレイの初期化
  M5.Display.begin(); 
  M5.Display.setCursor(0, 0);

  // xModの振動モーターを有効化（スピーカ、振動モーター、ラインアウトのいずれか)
  xMod.WaveOut.enable_LRA();
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
    // 音声・振動出力（低い周波数）
    xMod.WaveOut.tone(50, 100, -1, false);
  }
  else if (xMod.BtnR.isPressed()){
    // 音声・振動出力（高い周波数）
    xMod.WaveOut.tone(500, 100, -1, false);
  }
  // M5Coreのボタンが押されている場合
  else if (M5.BtnA.isPressed()){
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
  else if (M5.BtnB.isPressed()){
    //音声出力をスピーカーで行う
    M5.Display.println("To Speaker");
    xMod.WaveOut.disable_LRA();
    xMod.WaveOut.enable_Speaker();
  } 
  else if (M5.BtnC.isPressed()){
    //音声出力を振動モーターで行う
    M5.Display.println("To LRA");
    xMod.WaveOut.disable_Speaker();
    xMod.WaveOut.enable_LRA();
  }
  
  delay(100);
}