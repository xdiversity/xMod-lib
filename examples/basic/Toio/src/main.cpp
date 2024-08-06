#include "xMod.hpp"

//繋げたいtoioのID
String toioID = "11b";

bool LEDstatus = false;

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
  M5.Display.setCursor(0, 0);
  
  // Toio接続
  while (!xMod.Toio.isConnected()){
    xMod.Toio.searchToio(toioID);
    if (xMod.Toio.connect()){
      M5.Display.println("Toio Connected");
    } else {
      M5.Display.println("Toio Connection Failed");
    }
    delay(3000);
  }

}

void loop() {
  //　xModの更新処理：M5の更新処理も内部で行われる
  xMod.update();

  // xModの物理ボタンが押されている場合
  if (xMod.BtnL.isPressed()){
     M5.Display.println("Play sound effect");
    // Toioで音を鳴らす
    if (xMod.Toio.isConnected()){
      xMod.Toio.playSoundEffect(3);
      delay(100);
    }
  }
  else if (xMod.BtnR.isPressed()){
    //MIDIをToioで再生
    M5.Display.println("Play Charumera");
    xMod.Toio.playSoundRaw(charumera_data, 39);
    delay(2500);
  }
  // M5Coreのボタンが押されている場合
  else if (M5.BtnA.isPressed()){
    ToioCoreIDData data = xMod.Toio.getIDReaderData();
    //プレイマット上にいる場合、座標・角度検出
    if (data.type == ToioCoreIDTypePosition) {
      M5.Display.printf("(x,y)=(%d,%d) degree=%d", data.position.cubePosX, data.position.cubePosY, data.position.cubeAngleDegree);
      M5.Display.print("\n");
    } else {
      M5.Display.println("Toio is not on the mat");
    }
  }
  else if (M5.BtnB.isPressed()){
    M5.Display.println("Move");

    // Toioを動かす
    if (xMod.Toio.isConnected()){
      //前進
      xMod.Toio.controlMotor(true, 10, true, 10, 1000); 
      delay(1000);
      //後退
      xMod.Toio.controlMotor(false, 10, false, 10, 1000); 
      delay(1000);
      //右回転
      xMod.Toio.controlMotor(true, 10, false, 10, 1000); 
      delay(1000);
      //右回転
      xMod.Toio.controlMotor(false, 10, true, 10, 1000); 
      delay(1000);
    }
  } 
  else if (M5.BtnC.isPressed()){
    // 背面のLEDをOn/Offする
    if (xMod.Toio.isConnected()){
      if (!LEDstatus){
        M5.Display.println("LED ON");
        LEDstatus = true;
        xMod.Toio.turnOnLed(255,0,0);
      } else {
        M5.Display.println("LED OFF");
        LEDstatus = false;
        xMod.Toio.turnOffLed();
      }
    }
  }
  
  delay(100);
}