#include "xMod.hpp"

static uint8_t test_step = 0;

uint8_t charumera_data[39] = {
  3,             // 制御の種類 
  1,             // 繰り返し回数
  12,            // Operation の数
  14,  69, 255,  // 140ms, A5
  14,  71, 255,  // 140ms, B5
  56,  73, 255,  // 560ms, C#6
  14,  71, 255,  // 140ms, B5
  14,  69, 255,  // 140ms, A5
  114, 128, 255, // 無音
  14,  69, 255,  // 140ms, A5
  14,  71, 255,  // 140ms, B5
  14,  73, 255,  // 560ms, C#6
  14,  71, 255,  // 140ms, B5
  14,  69, 255,  // 140ms, A5
  56,  71, 255   // 560ms, B5
};

void setup() {
  // xModの初期化
  xMod.begin();

  // M5Coreディスプレイの初期化
  M5.Display.begin(); 
  //文字出力座標を指定
  M5.Display.setCursor(0, 0);

  M5.Display.setFont(&fonts::Font4);
  M5.Display.setTextSize(1);

  xMod.WaveOut.begin();
  xMod.WaveOut.setVolume(200);

  M5.Display.setTextColor(WHITE);
  M5.Display.drawCenterString("xMod V0.0.1", 160, 0);  // <<<<<<<<<<<  Modify version here
  M5.Display.fillRect(0, 30, 320, 210, BLACK);
  M5.Display.drawCenterString("Step 1 Button Test", 160, 30);
  M5.Display.drawCenterString("Press upper side buttons", 160, 100);

}

void loop() {
  //　xModの更新処理：M5の更新処理も内部で行われる
  xMod.update();

  switch (test_step) {
    case 0:  // Button
      if (xMod.BtnL.isPressed()) {
        M5.Display.setTextColor(GREEN);
        M5.Display.drawCenterString("ButtonL pressed", 160, 140);
        M5.Display.setTextColor(WHITE);
      } else {
        M5.Display.fillRect(0, 140, 320, 30, BLACK);
      } 
      if (xMod.BtnR.isPressed()) {
        M5.Display.setTextColor(GREEN);
        M5.Display.drawCenterString("ButtonR pressed", 160, 170);
        M5.Display.setTextColor(WHITE);
      } else {
        M5.Display.fillRect(0, 170, 320, 30, BLACK);
      }
      break; 
    case 1: //Sound
      if (xMod.BtnL.wasPressed()) {
        M5.Display.setTextColor(GREEN);
        M5.Display.drawCenterString("Low Tone", 160, 140);
        M5.Display.setTextColor(WHITE);
        xMod.WaveOut.tone(50, 500, -1, false);
        delay(500);
        M5.Display.fillRect(0, 140, 320, 30, BLACK);
      } else if (xMod.BtnR.wasPressed()) {
        M5.Display.setTextColor(GREEN);
        M5.Display.drawCenterString("High Tone", 160, 170);
        M5.Display.setTextColor(WHITE);
        xMod.WaveOut.tone(500, 500, -1, false);
        delay(500);
        M5.Display.fillRect(0, 170, 320, 30, BLACK);
      }
      break; 
    case 2: //Vibration
      if (xMod.BtnL.wasPressed()) {
        M5.Display.setTextColor(GREEN);
        M5.Display.drawCenterString("Low Frequency", 160, 140);
        M5.Display.setTextColor(WHITE);
        xMod.WaveOut.tone(50, 500, -1, false);
        delay(500);
        M5.Display.fillRect(0, 140, 320, 30, BLACK);
      } else if (xMod.BtnR.wasPressed()) {
        M5.Display.setTextColor(GREEN);
        M5.Display.drawCenterString("High Frequency", 160, 170);
        M5.Display.setTextColor(WHITE);
        xMod.WaveOut.tone(500, 500, -1, false);
        delay(500);
        M5.Display.fillRect(0, 170, 320, 30, BLACK);
      }
      break;
    case 3: //Toio
      if (!xMod.Toio.isConnected()){
        xMod.Toio.searchToio();
        if (xMod.Toio.connect()){ 
          M5.Display.fillRect(0, 100, 320, 30, BLACK);
          M5.Display.drawCenterString("toio Connected", 160, 100);
          delay(2000);
          M5.Display.fillRect(0, 100, 320, 30, BLACK);
          M5.Display.drawCenterString("Press upper side buttons", 160, 100);
        } 
      }
      if (xMod.Toio.isConnected()){
        if (xMod.BtnL.wasPressed()) {
          M5.Display.setTextColor(GREEN);
          M5.Display.drawCenterString("Play Music", 160, 140);
          M5.Display.setTextColor(WHITE);
          xMod.Toio.playSoundRaw(charumera_data, 39);
          delay(4000);
          M5.Display.fillRect(0, 140, 320, 30, BLACK);
        } else if (xMod.BtnR.wasPressed()) {
          M5.Display.setTextColor(GREEN);
          M5.Display.drawCenterString("Move", 160, 170);
          M5.Display.setTextColor(WHITE);
          xMod.Toio.controlMotor(true, 10, true, 10, 1000); 
          delay(1000);
          xMod.Toio.controlMotor(false, 10, false, 10, 1000); 
          delay(1000);
          xMod.Toio.controlMotor(true, 10, false, 10, 1000); 
          delay(1000);
          xMod.Toio.controlMotor(false, 10, true, 10, 1000); 
          delay(1000);
          M5.Display.fillRect(0, 170, 320, 30, BLACK);
        }
      }
      break;
    default:
      break;
  }

  auto touch_detail = M5.Touch.getDetail(); // 画面タッチでモード変更
  if (touch_detail.wasClicked()){
  //if (M5.BtnPWR.wasClicked()) { //電源ボタンでモード変更
    test_step++;
    if (test_step > 3) {
        test_step = 0;
    }

    switch (test_step) {
      case 0:
        M5.Display.fillRect(0, 30, 320, 210, BLACK);
        M5.Display.drawCenterString("Step 1 Button Test", 160, 30);
        M5.Display.drawCenterString("Press upper side buttons", 160, 100);
        break;
      case 1:
        M5.Display.fillRect(0, 30, 320, 210, BLACK);
        M5.Display.drawCenterString("Step 2 Sound Test", 160, 30);
        M5.Display.drawCenterString("Press upper side buttons", 160, 100);
        xMod.WaveOut.enable_Speaker();
        break;
      case 2:
        M5.Display.fillRect(0, 30, 320, 210, BLACK);
        M5.Display.drawCenterString("Step 3 Vibration Test", 160, 30);
        M5.Display.drawCenterString("Press upper side buttons", 160, 100);
        xMod.WaveOut.disable_Speaker();
        xMod.WaveOut.enable_LRA();
        break;
      case 3:
        xMod.WaveOut.disable_LRA();
        M5.Display.fillRect(0, 30, 320, 210, BLACK);
        M5.Display.drawCenterString("Step 4 toio Test", 160, 30);
        if (!xMod.Toio.isConnected()){
          M5.Display.drawCenterString("Looking for toio...", 160, 100);
        } else {
          M5.Display.drawCenterString("Press upper side buttons", 160, 100);
        }
        break;
      default:
        break;
    }
  }
  
  delay(100);
}