# xModLib

## m5stack + xMod 機能

### ボタン

#### クラス名
- xMod.BtnX (Xはボタンごとに異なる)
- BtnL, BtnR
  - xMod上側面の物理ボタン
- BtnA, BtnB, BtnC
  - タッチパネル下部分にある赤いボタン

#### 関数
- bool isPressed()
  - 今ボタンが押されているか
- bool wasPressed()
  - 新たにボタンが押されたか
- bool wasReleased()
  - ボタンが押されていない状態になったか
- bool isHeld()
  - ボタンが押し続けられているか

### マイク
#### クラス名
- xMod.Mic
#### 関数
- void recordStart(String filename)
  - SDカードマウントが必要
  - 録音を開始、”filename"という名前のファイルに保存される
- void recordStop()
  - 録音を終了

### スピーカー・振動
#### クラス名
- xMod.WaveOut
#### 関数
- void begin()
  - スピーカーを起動
- void end()
  - スピーカーを終了
- bool isPlaying()
  - スピーカーが再生中かどうか
- void setVolume(uint8_t volume)
  - 音量調整
- uint8_t getVolume() 
  - 音量を取得
- void stop()
  - スピーカーの動作を止める
- void stop(uint8_t channel) 
  - チャンネルを指定して動作を止める？
- bool tone(float frequency, uint32_t duration = UINT32_MAX, int channel = -1, bool stop_current_sound = true)
  - 振動数で指定した高さの音を鳴らす
- void playWavFile(const char* filename)
  - filenameで指定されたwavファイルを再生
- void enable_Speaker();
  - スピーカー出力の有効化
- void disable_Speaker();
  - スピーカー出力の無効化
- void enable_LRA();
  - 振動アクチュエータ出力の有効化
- void disable_LRA();
  - 振動アクチュエータ出力の無効化
- void enable_LineOut();
  - ラインアウト出力の有効化
- void disable_LineOut();
  - ラインアウト出力の無効化

           

### SDカード
#### クラス名
- xMod.SDM
#### 関数
- void begin()
  - SDカードのマウントを行う
  - SDカードを利用する場合は必須
- bool checkSD()
  - SDカードがマウントされているかを返す

### OpenAI API
#### クラス名
- xMod.OpenAI
#### 関数
- void SetAPIKey(String key)
  - APIキーをセットする
  - OpenAIの機能の利用には必須
- void SetModel(String modelName)
  - 利用するモデルを指定する
  - ex.gpt-4o, gpt-3.5-turbo
- String GPT(String text)
  - textの内容をChatGPTに送信し、返答を得る

### その他
#### クラス名
- xMod.Utils
#### 関数
- bool connectWifi(String ssid, String pass)
  - ssid,pass で指定されたアクセスポイントとwifi接続
  - 接続成功か否かを返す
- void disconnectWifi()
  - wifi接続を終了


## Toio操作
#### クラス名
- xMod.Toio
#### 関数
- String searchToio();
  - Toioを探し、見つけたToionのIDを返す
- String searchToio(String ID)
  - IDで指定したToioを探す
- bool connect();
  - 見つけているToioと接続する
- void disconnect()
  - Toioとの通信を切断する
- bool isConnected()
  - Toioとの接続状況を返す
- String getAddress();
  - 接続しているToioのMACアドレスを取得する
- String getName();
  - 接続しているToioの名前を取得する
- String getBleProtocolVersion();
  - 接続に利用しているBluetoothプロトコルのバージョンを得る
- void playSoundEffect(uint8_t sound_id, uint8_t volume = 0xff)
  - soundIDに対応した効果音を鳴らす
- void playSoundRaw(uint8_t* data, size_t length)
  - dataで指定したMIDI形式の音を再生する
- void stopSound()
  - 音の再生を止める
- void turnOnLed(uint8_t r, uint8_t g, uint8_t b)
  - Toioの背面にあるLEDを点灯させる
- void turnOffLed()
  - Toioの背面にあるLEDを消灯させる
- uint8_t getBatteryLevel()
  - バッテリー残量を取得
- bool getButtonState()
  LEDは押しボタンにもなっており、それが押されているかどうかを取得
- ToioCoreMotionData getMotion();
  - なんだっけ
- void controlMotor(bool ldir, uint8_t lspeed, bool rdir, uint8_t rspeed, uint16_t duration = 0);
- void drive(int8_t throttle, int8_t steering);
- void controlMotorWithTarget(uint8_t distinction, uint8_t timeout, uint8_t movement_type, 
                uint8_t maximum_speed, uint8_t speed_change_type,
                uint16_t target_x, uint16_t target_y, 
                uint16_t target_angle_degree, uint8_t target_angle_and_rotation_bits = 0);

- void controlMotorWithMultipleTargets(uint8_t distinction, uint8_t timeout, uint8_t movement_type, 
                uint8_t maximum_speed, uint8_t speed_change_type,  uint8_t addition_setting,
                uint8_t target_num, ToioCoreTargetPos *target_positions);\

- void controlMotorWithAcceleration(uint8_t translational_speed, uint8_t acceleration,
                uint16_t rotational_velocity, uint8_t rotational_direction, uint8_t travel_direction,
                uint8_t priority, uint8_t duration);

- ToioCoreIDData getIDReaderData();
- 参考：https://github.com/kenichi884/M5StackToio/blob/master/README_jp.md

## 外部モジュール共に利用する機能

### MIDI
#### クラス名
- xMod.MIDI
#### 関数
- void begin(midi::Channel inChannel = MIDI_CHANNEL_OMNI);
- void end();
- void update();
- void enable_MIDI();
- void disable_MIDI();
- void setMode(xMod_MIDIMode mode) { currentMode = mode; }

## その他
- xMod.begin()
  - xModクラスの初期化起動処理

- void recordSound(int time)
  - timeで指定されたミリ秒の分だけSDカードに録音を行う
  - ファイル名は”audio.wav"

### bluetoothスピーカー
- 外部ライブラリ ESP32-A2DPの導入が必要
- examples/advanced/BluetoothSpeaker を参照

### デバッグ
#### クラス名
- xMod
#### 関数
- void DisplayDebug(const String& message)
  - デバッグモードにて文字を表示する
- void setDebugNone();
  - デバッグモードの文字を表示しないようにする
- void setDebugDisplay();
  - デバッグモードの文字をディスプレイ上に表示するようにする
- void setDebugSerial();
  - デバッグモードの文字をシリアルモニタ上に表示するようにする
