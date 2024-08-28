#include "xMod.hpp"

//以下はサンプルコードです
//書き換えて使用してください

void setup() {
  // xModの初期化
  xMod.begin();

  // M5Coreディスプレイの初期化
  M5.Display.begin(); 
  //文字出力座標を指定
  M5.Display.setCursor(0, 0);

}

void loop() {
  //　xModの更新処理：M5の更新処理も内部で行われる
  xMod.update();

  // xModの物理ボタンが押されている場合
  if (xMod.BtnL.isPressed()){
    M5.Display.print("L");
  }
  else if (xMod.BtnR.isPressed()){
    M5.Display.print("R"); 
  }
  
  delay(100);
}