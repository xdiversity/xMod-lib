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

  M5.Display.setFont(&fonts::lgfxJapanGothic_20);
  M5.Display.setTextSize(1);

  xMod.WaveOut.begin();
  xMod.WaveOut.setVolume(200);

  M5.Display.setTextColor(WHITE);
  M5.Display.drawCenterString("xMod テスト", 160, 0);  // <<<<<<<<<<<  Modify version here
  M5.Display.fillRect(0, 30, 320, 210, BLACK);
  M5.Display.drawCenterString("Step 1 ボタン", 160, 30);
  M5.Display.drawCenterString("上側面のボタンを押してください", 160, 100);
  M5.Display.drawCenterString("画面タッチで次のテストへ", 160, 215);

}

void loop() {
  //　xModの更新処理：M5の更新処理も内部で行われる
  xMod.update();

  switch (test_step) {
    case 0:  // Button
      if (xMod.BtnL.isPressed()) {
        M5.Display.setTextColor(GREEN);
        M5.Display.drawCenterString("左のボタン", 160, 140);
        M5.Display.setTextColor(WHITE);
      } else {
        M5.Display.fillRect(0, 140, 320, 30, BLACK);
      } 
      if (xMod.BtnR.isPressed()) {
        M5.Display.setTextColor(GREEN);
        M5.Display.drawCenterString("右のボタン", 160, 170);
        M5.Display.setTextColor(WHITE);
      } else {
        M5.Display.fillRect(0, 170, 320, 30, BLACK);
      }
      break; 
    case 1: //Sound
      if (xMod.BtnL.wasPressed()) {
        M5.Display.setTextColor(GREEN);
        M5.Display.drawCenterString("低い音", 160, 140);
        M5.Display.setTextColor(WHITE);
        xMod.WaveOut.tone(50, 500, -1, false);
        delay(500);
        M5.Display.fillRect(0, 140, 320, 30, BLACK);
      } else if (xMod.BtnR.wasPressed()) {
        M5.Display.setTextColor(GREEN);
        M5.Display.drawCenterString("高い音", 160, 170);
        M5.Display.setTextColor(WHITE);
        xMod.WaveOut.tone(500, 500, -1, false);
        delay(500);
        M5.Display.fillRect(0, 170, 320, 30, BLACK);
      }
      break; 
    case 2: //Vibration
      if (xMod.BtnL.wasPressed()) {
        M5.Display.setTextColor(GREEN);
        M5.Display.drawCenterString("低い周波数の振動", 160, 140);
        M5.Display.setTextColor(WHITE);
        xMod.WaveOut.tone(50, 500, -1, false);
        delay(500);
        M5.Display.fillRect(0, 140, 320, 30, BLACK);
      } else if (xMod.BtnR.wasPressed()) {
        M5.Display.setTextColor(GREEN);
        M5.Display.drawCenterString("高い周波数の振動", 160, 170);
        M5.Display.setTextColor(WHITE);
        xMod.WaveOut.tone(500, 500, -1, false);
        delay(500);
        M5.Display.fillRect(0, 170, 320, 30, BLACK);
      }
      break;
    case 3: //Toio
      if (!xMod.Toio.isConnected()){
        M5.Display.fillRect(0, 215, 320, 25, BLACK);
        xMod.Toio.searchToio();
        if (xMod.Toio.connect()){ 
          M5.Display.fillRect(0, 100, 320, 50, BLACK);
          M5.Display.drawCenterString("toio接続完了！", 160, 100);
          delay(2000);
          M5.Display.fillRect(0, 100, 320, 30, BLACK);
          M5.Display.drawCenterString("ボタンを押すとtoioが動作します", 160, 100);
        } 
      }
      if (xMod.Toio.isConnected()){
        M5.Display.drawCenterString("画面タッチで次のテストへ", 160, 215);
        if (xMod.BtnL.wasPressed()) {
          M5.Display.setTextColor(GREEN);
          M5.Display.drawCenterString("音楽を再生", 160, 140);
          M5.Display.setTextColor(WHITE);
          xMod.Toio.playSoundRaw(charumera_data, 39);
          delay(4000);
          M5.Display.fillRect(0, 140, 320, 30, BLACK);
        } else if (xMod.BtnR.wasPressed()) {
          M5.Display.setTextColor(GREEN);
          M5.Display.drawCenterString("移動", 160, 170);
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
        M5.Display.fillRect(0, 30, 320, 185, BLACK);
        M5.Display.drawCenterString("Step 1 ボタン", 160, 30);
        M5.Display.drawCenterString("上側面のボタンに反応します", 160, 100);
        break;
      case 1:
        M5.Display.fillRect(0, 30, 320, 185, BLACK);
        M5.Display.drawCenterString("Step 2 サウンド", 160, 30);
        M5.Display.drawCenterString("ボタンを押すと音がなります", 160, 100);
        xMod.WaveOut.enable_Speaker();
        break;
      case 2:
        M5.Display.fillRect(0, 30, 320, 185, BLACK);
        M5.Display.drawCenterString("Step 3 振動", 160, 30);
        M5.Display.drawCenterString("ボタンを押すと振動します", 160, 100);
        xMod.WaveOut.disable_Speaker();
        xMod.WaveOut.enable_LRA();
        break;
      case 3:
        xMod.WaveOut.disable_LRA();
        M5.Display.fillRect(0, 30, 320, 185, BLACK);
        M5.Display.drawCenterString("Step 4 toio", 160, 30);
        if (!xMod.Toio.isConnected()){
          M5.Display.drawCenterString("toioを探しています...", 160, 100);
          M5.Display.drawCenterString("toioの電源をONにしてください", 160, 125);
          M5.Display.fillRect(0, 215, 320, 25, BLACK);
        } else {
          M5.Display.drawCenterString("ボタンを押すとtoioが動作します", 160, 100);
        }
        break;
      default:
        break;
    }
  }
  
  delay(100);
}