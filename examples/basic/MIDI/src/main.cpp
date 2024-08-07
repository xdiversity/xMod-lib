#include "xMod.hpp"

void setup() {
  // xModの初期化
  xMod.begin();

  // M5Coreディスプレイの初期化
  M5.Display.begin(); 
  M5.Display.setCursor(0, 0);

  // MIDI出力の有効化
  xMod.MIDI.enable_MIDI();
  xMod.MIDI.setMode(MIDI_MODE_OUT);
  xMod.MIDI.begin();
  
}

void loop() {
  //　xModの更新処理：M5の更新処理も内部で行われる
  xMod.update();

  // xModの物理ボタンが押されている場合
  if (xMod.BtnL.isPressed()){
    M5.Display.print("L"); 
    // MIDI出力
    xMod.MIDI.sendNoteOn(60, 127, 1);
  }
  else if (xMod.BtnR.isPressed()){
    M5.Display.print("R"); 
    // MIDI出力
    xMod.MIDI.sendNoteOn(60, 127, 2);
  }
  
  delay(100);
}