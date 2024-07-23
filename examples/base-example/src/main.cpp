#include "xMod.hpp"
#include "secrets.h"

#include <unordered_map>

String wifiSSID = SECRET_SSID;
String wifiPass = SECRET_PASS;

typedef byte DataByte;

// MIDIを入力モードと出力モードどちらで使うか
bool use_midi_in = false;

// 利用するtoioのID（ここは各自書き換える）
String toioID = "44f";

// MIDI入力時に呼ばれる関数
void handleNoteOn(byte channel, byte note, byte velocity) {
  Serial.printf("Note On: %d, %d, %d\n", channel, note, velocity);
  delay(100);
}

void handleNoteOff(byte channel, byte note, byte velocity) {
  Serial.printf("Note Off: %d, %d, %d\n", channel, note, velocity);
  delay(100);
}

void setup() {
  // xModの初期化
  xMod.begin();

  //デバッグ画面表示を許可
  xMod.setDebugMode(1);

  // M5Coreディスプレイの初期化
  M5.Display.begin(); 
  M5.Display.setFont(&fonts::Font2);
  M5.Display.fillRect(0, 0, 320, 240, BLACK);
  M5.Display.setCursor(0, 0);
  xMod.DisplayDebug("hello!"); 

  // xModの振動出力を有効化
  // この状態ではスピーカーとラインアウトは無効
  xMod.WaveOut.enable_LRA();
  xMod.WaveOut.begin();
  xMod.WaveOut.setVolume(200);

  // WaveOutの出力はSpeakerに切り替えることも可能だが、音を鳴らす関数は同じ
  // 現状、loopの中で出力先を変更しようとするとあまりうまくいかない
  // xMod.WaveOut.enable_Speaker();
  
  // Toio接続
  String toioName = xMod.Toio.searchToio(toioID);
  xMod.DisplayDebug(toioName);
  if (xMod.Toio.connect()){
    xMod.DisplayDebug("Toio Connected");
  } else {
    xMod.DisplayDebug("Toio Connection Failed");
  }

  // WiFi接続確立
  if (xMod.Utils.connectWifi(wifiSSID, wifiPass)){
    xMod.DisplayDebug("Wifi Connected");
  } else {
    xMod.DisplayDebug("Failed to connect Wifi");
  }

  // SDカードの接続確認
  xMod.SDM.begin();
  if (xMod.SDM.checkSD()){
    xMod.DisplayDebug("SD Connected");
  } else {
    xMod.DisplayDebug("No SDcard");
  }

  // MIDI入出力の有効化
  xMod.MIDI.enable_MIDI();
  if (use_midi_in) {
    xMod.MIDI.setMode(MIDI_MODE_IN);
    xMod.MIDI.begin();
    xMod.MIDI.setHandleNoteOn(handleNoteOn);
    xMod.MIDI.setHandleNoteOff(handleNoteOff);
  } else {
    xMod.MIDI.setMode(MIDI_MODE_OUT);
    xMod.MIDI.begin();
  }

  xMod.DisplayDebug("Setup End");
}

void loop() {
  //　xModの更新処理：M5の更新処理も内部で行われる
  xMod.update();

  // xModの物理ボタンが押されている場合
  if (xMod.BtnL.isPressed()){
    M5.Display.print("L");

    // 音声出力（初期設定では振動として出力）
    xMod.WaveOut.tone(50, 100, -1, false);

    // MIDI出力
    xMod.MIDI.sendNoteOn(60, 127, 1);
  }
  else if (xMod.BtnR.isPressed()){
    M5.Display.print("R"); 

    // 音声出力（初期設定では振動として出力）
    xMod.WaveOut.tone(500, 100, -1, false);

    // MIDI出力
    xMod.MIDI.sendNoteOn(60, 127, 2);
  }
  // M5Coreのボタンが押されている場合
  else if (M5.BtnA.isPressed()){
    M5.Display.println("A");

    // Toioで音を鳴らして動かす
    if (xMod.Toio.isConnected()){
      xMod.Toio.playSoundEffect(3);
      xMod.Toio.controlMotor(true, 10, false, 10, 1000); 
      delay(1000);
    }
  }
  else if (M5.BtnB.isPressed()){
    M5.Display.println("B");

    // SDカードに録音
    if (xMod.SDM.checkSD()){
      delay(500);
      M5.Display.println("Record Start");
      xMod.recordSound(2000);
      M5.Display.println("Record Stop"); 
      delay(500);

      M5.Display.println("Play Sound"); 
      xMod. WaveOut.playWavFile("/audio.wav");
      M5.Display.println("Play End"); 
    } else {
      M5.Display.println("No SDcard"); 
    }
  } 
  else if (M5.BtnC.isPressed()){
    M5.Display.println("C");

    // GPT APIにテキストを送信
    String response = xMod.OpenAI.GPT("hello!");
    if (response != ""){
      M5.Display.println(response);
    } else {
      M5.Display.println("No API response");
    }

  }
  
  delay(100);
}