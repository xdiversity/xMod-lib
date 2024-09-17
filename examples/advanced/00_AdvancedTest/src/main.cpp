#include "xMod.hpp"

int nowID = -1;

void setup() {
  // xModの初期化
  xMod.begin();

  // M5Coreディスプレイの初期化
  M5.Display.begin(); 
  M5.Display.setCursor(0, 0);

  M5.Display.setFont(&fonts::lgfxJapanGothic_20);
  M5.Display.setTextSize(1);
  
  // Toio接続
  M5.Display.setTextColor(WHITE);
  M5.Display.drawCenterString("xMod Advancedテスト", 160, 0);
  M5.Display.drawCenterString("カードタイプのプレイマット", 160, 40);
  M5.Display.drawCenterString("を用意してください", 160, 65);
  delay(1000);
  M5.Display.drawCenterString("toioを探しています...", 160, 140);
  M5.Display.drawCenterString("toioの電源をONにしてください", 160, 165);
  while (!xMod.Toio.isConnected()){
    xMod.Toio.searchToio();  //Toioを探す（一番最初に見つけたものが探した結果となる）
    if (xMod.Toio.connect()){  //見つけたToioに接続する
      M5.Display.fillRect(0, 140, 320, 50, BLACK);
      M5.Display.drawCenterString("toio接続完了！", 160, 140);
      delay(2000);
      M5.Display.fillRect(0, 0, 320, 240, BLACK);
      break;
    }
    delay(1500);
  }

}

void loop() {
  //　xModの更新処理：M5の更新処理も内部で行われる
  xMod.update();

  ToioCoreIDData data = xMod.Toio.getIDReaderData();

  if (data.type == ToioCoreIDTypeStandard){
    String output = "";
    M5.Display.setFont(&fonts::lgfxJapanGothic_40);
    M5.Display.setTextSize(4);

    if (data.standard.standardID == 3670366) {
      output = "↑";
    } else if (data.standard.standardID == 3670367) {
      output = "↓";
    } else if (data.standard.standardID == 3670334) {
      output = "→";
    } else if (data.standard.standardID == 3670332) {
      output = "←";
    } else if (data.standard.standardID == 3670314) {
      output = "×";
    } else if (data.standard.standardID == 3670319) {
      output = "÷";
    } else {
      M5.Display.setTextSize(6,4);
      output = String(char(data.standard.standardID - 3670272)); //アスキーコードを参照
    }

    if (nowID != data.standard.standardID){
      M5.Display.fillRect(0, 0, 320, 240, BLACK);
      M5.Display.drawCenterString(output, 160, 40);
      nowID = data.standard.standardID;
    }

  } else {
    if (nowID != 0){
      M5.Display.fillRect(0, 0, 320, 240, BLACK);
      M5.Display.setFont(&fonts::lgfxJapanGothic_20);
      M5.Display.setTextSize(1);
      M5.Display.drawCenterString("プレイマットの上に置いてください", 160, 100);
      nowID = 0;
    }
  }
  
  delay(100);
}