#include "xMod.hpp"

static uint8_t test_step = 0;

void setup() {
  // xModの初期化
  xMod.begin();

  // M5Coreディスプレイの初期化
  M5.Display.begin(); 
  //文字出力座標を指定
  M5.Display.setCursor(0, 0);

  M5.Display.setFont(&fonts::Font4);
  M5.Display.setTextSize(1);

  M5.Display.setTextColor(WHITE);
  M5.Display.drawCenterString("xMod V0.0.1", 160, 0);  // <<<<<<<<<<<  Modify version here
  M5.Display.fillRect(0, 30, 320, 210, BLACK);
  M5.Display.drawCenterString("Step 1 Speaker Test", 160, 30);
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
    case 1:
      break; 
    default:
      break;
  }

  if (M5.BtnPWR.wasClicked()) {
    test_step++;
    if (test_step > 1) {
        test_step = 0;
    }

    switch (test_step) {
      case 0:
        M5.Display.fillRect(0, 30, 320, 210, BLACK);
        M5.Display.drawCenterString("Step 1 Speaker Test", 160, 30);
        M5.Display.drawCenterString("Press upper side buttons", 160, 100);
        break;
      case 1:
        M5.Display.fillRect(0, 30, 320, 210, BLACK);
        M5.Display.drawCenterString("Step 2 hoge Test", 160, 30);
        M5.Display.drawCenterString("hogehoge", 160, 100);
        break;
      default:
        break;
    }
  }
  
  delay(100);
}