#include "xMod.hpp"

String wifiSSID = "ssid";
String wifiPass = "pass";

String APIkey = "api_key";

void setup() {
  // xModの初期化
  xMod.begin();

  // M5Coreディスプレイの初期化
  M5.Display.begin(); 
  M5.Display.setCursor(0, 0);

  // WiFi接続確立
  if (xMod.Utils.connectWifi(wifiSSID, wifiPass)){
    M5.Display.println("Wifi Connected");
  } else {
    M5.Display.println("Failed to connect Wifi");
  }
  //APIKey登録
  xMod.OpenAI.SetAPIKey(APIkey);
}

void loop() {
  //　xModの更新処理：M5の更新処理も内部で行われる
  xMod.update();

  // 左のボタンが押された時
  if (xMod.BtnL.isPressed()){
    // GPT APIにテキストを送信
    String message = "hello!";
    M5.Display.printf("send : %s\n", message);
    String response = xMod.OpenAI.GPT(message);
    if (response != ""){
      M5.Display.print("response : ");
      M5.Display.println(response);
    } else {
      M5.Display.println("No API response");
    }
  }
  
  delay(100);
}