#include "xMod.hpp"

// タッチパネル上にボタンを描画するための関数
void Button_Record_Write(void){
  M5.Display.drawRect(20, 170, 280, 60, WHITE);
}
void Button_Record_Delete(void){
  M5.Display.fillRect(20, 170, 280, 60, BLACK);
}
bool Button_Record_isPressed(void){
  /// タッチ操作の情報を取得する。
  auto touch_detail = M5.Touch.getDetail();

  if (touch_detail.isPressed()){
    if (170 <= touch_detail.y && touch_detail.y <= 230){
      M5.Display.drawRect(20, 170, 280, 60, GREENYELLOW);
      return true;
    }
  }
  return false;
}

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
  //タッチパネルのボタン表示リセット
  Button_Record_Write();

  // xModの物理ボタンが押されている場合
  if (xMod.BtnL.isPressed()){
    M5.Display.print("L");
  }
  else if (xMod.BtnR.isPressed()){
    M5.Display.print("R"); 
  }
  // M5Coreのボタンが押されている場合
  else if (M5.BtnA.isPressed()){
    M5.Display.print("A");
  }
  else if (M5.BtnB.isPressed()){
    M5.Display.print("B");
  } 
  else if (M5.BtnC.isPressed()){
    M5.Display.print("C");
  }
  else if (Button_Record_isPressed()){
    M5.Display.print("o");
  }
  
  delay(100);
}