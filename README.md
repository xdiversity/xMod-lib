# xModLib
xModを操作するためのライブラリです。m5stack,Toioと共に利用することを想定しています。

## ボタン

### クラス名：xMod.BtnX 
Xはボタンごとに異なります。

BtnL, BtnR(xMod上側面の物理ボタン)

BtnA, BtnB, BtnC(タッチパネル下部にある赤いボタン)

### `isPressed()` 

今ボタンが押されているかどうかをboolで返します。

#### プロトタイプ宣言

```c++
bool isPressed();
```

### `isPressed()` 

新たにボタンが押されたかどうかをboolで返します。

#### プロトタイプ宣言

```c++
bool wasPressed();
```

### `wasReleased()` 

ボタンが押されていない状態になったかどうかをboolで返します。

#### プロトタイプ宣言

```c++
bool wasReleased();
```

### `isHeld()` 

ボタンが押し続けられているかどうかをboolで返します。

#### プロトタイプ宣言

```c++
bool isHeld();
```

## マイク
### クラス名：xMod.Mic

### `recordStart()` 

録音を開始します。事前にSDカードのマウントが必要です。指定したファイル名で保存されます。ファイル形式はwavです。

#### プロトタイプ宣言

```c++
void recordStart(String filename);
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `filename`     | `String` |      | 録音結果を保存する先のファイル名です。.wavの形で指定してください。デフォルトは”audio.wav"となります。

### `recordStop()` 

録音を終了します。recordStard()で開始された録音はこの関数によって停止されるまで続きます。

#### プロトタイプ宣言

```c++
void recordStop();
```

## スピーカー・振動
### クラス名：xMod.WaveOut

### `begin()` 

スピーカー周辺機能を利用するための初期処理を行います。
このクラスを利用する際は最初に実行してください。

#### プロトタイプ宣言

```c++
void begin();
```

### `end()` 

スピーカー周辺機能の利用を終了します。

#### プロトタイプ宣言

```c++
void end();
```

### `isPlaying()` 

スピーカーが再生中かどうかをboolで返します。

#### プロトタイプ宣言

```c++
bool isPlaying();
```

### `setVolume()` 

スピーカーの音量を指定した値に調整します。

#### プロトタイプ宣言

```c++
void setVolume(uint8_t volume);
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `volume`     | `uint8_t` | ✔︎    | スピーカーの音の大きさ(0-255)

### `setVolume()` 

スピーカーの音量の大きさを取得します。

#### プロトタイプ宣言

```c++
uint8_t getVolume();
```

### `stop()` 

スピーカーの動作を中断します。

#### プロトタイプ宣言

```c++
void stop();
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `channel`     | `uint8_t` |      | 動作を止めるチャンネルを指定することもできます。指定しなければ全部のチャンネルの動作を止めます。

### `tone()` 

振動数で指定した高さの音を鳴らします。鳴らせたかどうかをboolで返します。

#### プロトタイプ宣言

```c++
bool tone(float frequency, uint32_t duration = UINT32_MAX, int channel = -1, bool stop_current_sound = true);
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `frequency`     | `float` | ✔︎   | 振動数
2   | `duration`     | `uint32_t` |      | 音を鳴らす長さ
3   | `channel`     | `int` |      | チャンネル
4   | `stop_current_sound`   | `bool` |      | すでに音が鳴っている場合に、その音を止めつつこの音を再生するかどうか

### `playWavFile()` 

指定したwavファイルを再生します。

#### プロトタイプ宣言

```c++
void playWavFile(const char* filename);
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `filename`     | `const char*` | ✔︎   | ファイル名。wavファイルを指定してください。

### `enable_Speaker()` 

音の出力を行う機器をスピーカーに指定します。事前に他の指定を行なっている場合はその指定を解除してから指定を行ってください。

#### プロトタイプ宣言

```c++
void enable_Speaker();
```

### `disable_Speaker()` 

スピーカーに対する音の出力を行う機器の指定を解除します。

#### プロトタイプ宣言

```c++
void disable_Speaker();
```

### `enable_LRA()` 

音の出力を行う機器を振動アクチュエータに指定します。事前に他の指定を行なっている場合はその指定を解除してから指定を行ってください。

#### プロトタイプ宣言

```c++
void enable_LRA();
```

### `disable_LRA()` 

振動アクチュエータに対する音の出力を行う機器の指定を解除します。

#### プロトタイプ宣言

```c++
void disable_LRA();
```

### `enable_LineOut()` 

音の出力を行う機器をラインアウト(イヤホンジャック)に指定します。事前に他の指定を行なっている場合はその指定を解除してから指定を行ってください。

#### プロトタイプ宣言

```c++
void enable_LineOut();
```

### `disable_LineOut()` 

ラインアウト(イヤホンジャック)に対する音の出力を行う機器の指定を解除します。

#### プロトタイプ宣言

```c++
void disable_LineOut();
```

           

## SDカード
### クラス名：xMod.SDM

### `begin()` 

SDカードのマウントを行います。これを行わないとxModがSDカードを認識しません。

#### プロトタイプ宣言

```c++
void begin();
```

### `checkSD()` 

SDカードがマウントされているかどうかをboolで返します。

#### プロトタイプ宣言

```c++
bool checkSD();
```

## OpenAI API

### クラス名：xMod.OpenAI

### `SetAPIKey()` 

OpenAIのAPIキーを登録します。OpanAI APIに関連した機能を利用するには必須です。

#### プロトタイプ宣言

```c++
void SetAPIKey(String key);
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `key`     | `String` | ✔︎   | APIキー

### `SetModel()` 

OpenAIのAPIキーにて利用するモデルを指定します。
デフォルトは"gpt-4o"になっています。
モデルの名前参考：https://platform.openai.com/docs/models

#### プロトタイプ宣言

```c++
void SetModel(String modelName);
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `modelName`     | `String` | ✔︎   | モデルの名前。実在するモデルを指定してください。

### `SetModel()` 

与えられたテキストをapiを通じてモデルに送信し、返答を得ます。
利用するにはwifiの接続が必要です。
#### プロトタイプ宣言

```c++
String GPT(String text);
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `text`     | `String` | ✔︎   | gptに送るメッセージ

## Toio操作
### クラス名 : xMod.Toio

### `searchToio()` 

指定されたIDのToioを探します。
IDが指定されていなければIDに関わらずToioを1つ探します。
もし見つかれば、見つかったToioの名前を返します。

#### プロトタイプ宣言

```c++
String searchToio();
String searchToio(String ID);
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `ID`     | `uint8_t*` | ✔     | ToioのID


### `connect()`

searchToio()で見つけたToioに接続します。接続結果をboolで返します。

#### プロトタイプ宣言

```c++
bool connect();
```

#### 引数

なし


### `disconnect()` 

接続したToioとの通信を切断します。

#### プロトタイプ宣言

```c++
void disconnect();
```

#### 引数

なし


### `isConnected()`

Toioとの接続状況をboolで返します。

#### プロトタイプ宣言

```c++
bool isConnected();
```

#### 引数

なし

### `getAddress()` 

Toioの MAC アドレスを返します。

#### プロトタイプ宣言

```c++
String getAddress();
```

#### 引数

なし

### `getName()`

接続しているToioの名前を取得します。

#### プロトタイプ宣言

```c++
String getName();
```

#### 引数

なし

### `getBleProtocolVersion()`

接続に利用しているBluetoothプロトコルのバージョンを得ます。

#### プロトタイプ宣言

```c++
String getBleProtocolVersion();
```

#### 引数

なし

### `playSoundEffect()` 

soundIDに対応した効果音を鳴らします。

#### プロトタイプ宣言

```c++
void playSoundEffect(uint8_t sound_id, uint8_t volume = 0xff);
```

#### 引数

No. | 変数名      | 型        | 必須   | 説明
:---|:-----------|:----------|:-------|:-------------
1   | `sound_id` | `uint8_t` | ✔     | 効果音の ID (0 ～ 10)
2   | `volume`   | `uint8_t` | &nbsp; | 音量 (0 ～ 255)。指定が無ければ 255。

効果音の ID の意味は以下の通りです。

効果音 ID | 効果音名称
:---------|:---------------
`0`       | Enter
`1`       | Selected
`2`       | Cancel
`3`       | Cursor
`4`       | Mat in
`5`       | Mat out
`6`       | Get 1
`7`       | Get 2
`8`       | Get 3
`9`       | Effect 1
`10`      | Effect 2

### `playSoundRaw()` 

Toioにて主に MIDI データを再生するために使います。

#### プロトタイプ宣言

```c++
void playSoundRaw(uint8_t* data, size_t length);
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `data`   | `uint8_t*` | ✔     | 書き込むデータのバイト列
2   | `length` | `size_t`   | ✔     | 書き込むバイト数

#### コードサンプル

以下のサンプルコードは、[チャルメラ](https://www.myojofoods.co.jp/charumera/play/index.html)を最大音量で再生します。 

```c++
uint8_t charumera_data[39] = {
  3,             // 制御の種類 (MIDI なら `3`)
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
xMod.Toio.playSoundRaw(charumera_data, 39);
```

### ` stopSound()` 

再生中の音の再生を止めます。

#### プロトタイプ宣言

```c++
void stopSound();
```

#### 引数

なし

### ` turnOnLed()`

Toioの背面にあるLEDを指定した色で点灯させます。

#### プロトタイプ宣言

```c++
void turnOnLed(uint8_t r, uint8_t g, uint8_t b);
```

#### 引数

No. | 変数名 | 型        | 必須   | 説明
:---|:------|:----------|:-------|:-------------
1   | `r`   | `uint8_t` | ✔     | 赤コンポーネント (`0` ～ `255`)
2   | `g`   | `uint8_t` | ✔     | 緑コンポーネント (`0` ～ `255`)
2   | `b`   | `uint8_t` | ✔     | 青コンポーネント (`0` ～ `255`)

### ` turnOffLed()`

Toioの背面にあるLEDを消灯させます。

#### プロトタイプ宣言

```c++
void turnOffLed();
```

#### 引数

なし

### ` getBatteryLevel()`

バッテリーの残量を取得します。

#### プロトタイプ宣言

```c++
uint8_t getBatteryLevel();
```

#### 引数

なし

### ` getButtonState()`

背面のLEDは押しボタンにもなっており、それが押されているかどうかを取得します。

#### プロトタイプ宣言

```c++
bool getButtonState();
```

#### 引数

なし

### `getMotion()`

Toioのモーションセンサーの状態を取得します。

#### プロトタイプ宣言

```c++
struct ToioCoreMotionData {
  bool flat;
  bool clash;
  bool dtap;
  uint8_t attitude;
  uint8_t shake;
};

ToioCoreMotionData getMotion();
```

#### 引数

なし

#### 戻値

`ToioCoreMotionData` 型の構造体が返されます。各メンバーの意味は以下の通りです。

名前       | 型        | 説明
:----------|:----------|:------------------------
`flat`     | `bool`    | 水平検出 (`true`: 水平, `false`: 水平でない) 
`clash`    | `bool`    | 衝突検出 (`true`: あり, `false`: なし)
`dtap`     | `bool`    | ダブルタップ検出 (`true`: あり, `false`: なし)
`attitude` | `uint8_t` | 姿勢検出 (後述)
`shake`    | `uint8_t` | シェイク検出 (0x00 検出なし, 0x01 ～ 0x0a 振った強さ)

姿勢検出 `attitude` が取る値とその意味は以下の通りです。

値  | toio コア キューブの姿勢
:---|:-----------------------
`1` | 天面が上
`2` | 底面が上
`3` | 背面が上
`4` | 正面が上
`5` | 右側面が上
`6` | 左側面が上

姿勢検出の詳細は [toio コア キューブ技術仕様](https://toio.github.io/toio-spec/docs/ble_sensor)をご覧ください。

#### コードサンプル

```c++
ToioCoreMotionData motion = xMod.Toio.getMotion();
M5.Display.printf("- 水平検出: %s\n", motion.flat ? "水平" : "水平でない");
M5.Display.printf("- 衝突検出: %s\n", motion.clash ? "あり" : "なし");
M5.Display.printf("- ダブルタップ検出: %s\n", motion.dtap ? "あり" : "なし");
M5.Display.printf("- 姿勢検出: %d\n",  motion.attitude);
M5.Display.printf("- シェイク検出: %d\n",  motion.shake);
```

### `controlMotor()`

Toioのモーターを制御します。

#### プロトタイプ宣言

```c++
void controlMotor(bool ldir, uint8_t lspeed, bool rdir, uint8_t rspeed, uint16_t duration = 0);
```

#### 引数

No. | 変数名      | 型         | 必須   | 説明
:---|:-----------|:-----------|:-------|:-------------
1   | `ldir`     | `bool`     | ✔     | 左モーターの回転方向 (`true`: 前進, `false`: 後進)
2   | `lspeed`   | `uint8_t`  | ✔     | 左モーターの速度 (`0` ～ `115`)
3   | `rdir`     | `bool`     | ✔     | 右モーターの回転方向 (`true`: 前進, `false`: 後進)
4   | `rspeed`   | `uint8_t`  | ✔     | 右モーターの速度 (`0` ～ `115`)
5   | `duration` | `uint16_t` | &nbsp; | モーターの制御時間 (ミリ秒)

`lspeed` および `rspeed` の値と実際の速度の対応は、[toio コア キューブ通信仕様](https://toio.github.io/toio-spec/docs/ble_motor)をご覧ください。

`duration` に `0` (デフォルト値) を指定すると、停止 (`lspeed`, `rspeed` に `0` をセット) 命令を受けるまで動き続けます。


#### コードサンプル

```c++
// 右に曲がりながら進む
xMod.Toio.controlMotor(true, 50, true, 40);
delay(5000);

// 停止
xMod.Toio.controlMotor(true, 0, true, 0);
delay(5000);

// 2 秒間だけ左に曲がりながら進む
xMod.Toio.controlMotor(true, 40, true, 50, 2000);
delay(5000);
```
### `drive()`

モーター制御をスロットルとステアリング操作に置き換えて行います。

#### プロトタイプ宣言

```c++
void drive(int8_t throttle, int8_t steering);
```

#### 引数

No. | 変数名      | 型        | 必須   | 説明
:---|:-----------|:----------|:-------|:-------------
1   | `throttle` | `int8_t`  | ✔     | スロットル (`-100` ～ `100`)
2   | `steering` | `int8_t`  | ✔     | ステアリング (`-100` ～ `100`)

`throttle` に正の値を指定すると前進、負の値を指定すると後進、`0` を指定すると停止します。`steering` に正の値を指定すると右に曲がり、負の値を指定すると左に曲がります。

#### コードサンプル

```c++
// ゆっくりと左に曲がる
xMod.Toio.drive(20, -10);
delay(5000);

// 停止
xMod.Toio.drive(0, 0);
```

### `controlMotorWithTarget()`

目標地点を一つ指定してモーターを制御し、キューブを自律的に移動させます。

#### プロトタイプ宣言

```c++
void controlMotorWithTarget(uint8_t distinction, uint8_t timeout, uint8_t movement_type, 
  uint8_t maximum_speed, uint8_t speed_change_type,
  uint16_t target_x, uint16_t target_y, 
  uint16_t target_angle_degree, uint8_t target_angle_and_rotation_bits = 0);
```

#### 引数

No. | 変数名         | 型        | 必須   | 説明
:---|:---------------|:----------|:-------|:-------------
1   | `distinction`  | `uint8_t`  | ✔     | 制御識別値
2   | `timeout`      | `uint8_t`  | ✔     | タイムアウト時間(秒)
3   | `movement_type` | `uint8_t`  | ✔     | 移動タイプ (`0` ～ `2`)
4   | `maximum_speed` | `uint8_t`  | ✔     | モーターの最大速度指示値 (`10` ～ `2550`)
5   | `speed_change_type` | `uint8_t`  | ✔ | モーターの速度変化タイプ (`0` ～ `3`)
6   | `target_x`     | `uint16_t`  | ✔     | 目標地点の X 座標値(`0` ～ `65535`)
7   | `target_y`     | `uint16_t`  | ✔     | 目標地点の Y 座標値 (`-0` ～ `65535`)
8   | `target_angle_degree` | `uint16_t`  | ✔     | 目標地点でのキューブの角度  (`0` ～ `0x1fff`) 
9   | `target_angle_and_rotation_bits` | `uint8_t`  | &nbsp;  |角度の意味と動き方の指定 (`0` ～ `6`)

#### コードサンプル

```c++
// 座標(150, 200)の位置、角度0の方向で止まるように速度80で移動
xMod.Toio.controlMotorWithTarget(1, 5, 0, 80, 0, 150, 200, 0);
delay(5000);
```

### `controlMotorWithMultipleTargets()`

目標地点を複数指定してモーターを制御し、キューブを自律的に移動させます。

#### プロトタイプ宣言

```c++
struct ToioCoreTargetPos {
  uint16_t posX; // 目標地点の X 座標値
  uint16_t posY; // 目標地点の Y 座標値 
  uint16_t angleDegree:13; // 目標地点でのキューブの角度(0～0x1fff)
  uint8_t angleAndRotation:3; //角度の意味と動き方(0～6)
};

void controlMotorWithMultipleTargets(uint8_t distinction, uint8_t timeout, uint8_t movement_type, 
      uint8_t maximum_speed, uint8_t speed_change_type,  uint8_t addition_setting,
      uint8_t target_num, ToioCoreTargetPos *target_positions);
```

#### 引数

No. | 変数名         | 型        | 必須   | 説明
:---|:---------------|:----------|:-------|:-------------
1   | `distinction`  | `uint8_t`  | ✔     | 制御識別値
2   | `timeout`      | `uint8_t`  | ✔     | タイムアウト時間(秒)
3   | `movement_type` | `uint8_t`  | ✔     | 移動タイプ (`0` ～ `2`)
4   | `maximum_speed` | `uint8_t`  | ✔     | モーターの最大速度指示値 (`10` ～ `2550`)
5   | `speed_change_type` | `uint8_t`  | ✔ | モーターの速度変化タイプ (`0` ～ `3`)
6   | `addition_setting` | `uint8_t`  | ✔ | 書き込み操作の追加設定(`0` ～ `1`)
7   | `target_num`     | `uint16_t`  | ✔     | ターゲット座標の数(`1` ～ `29`)
8   | `target_positions` | `ToioCoreTargetPos *`  | ✔     | ターゲット座標の配列へのポインタ

#### コードサンプル

```c++
// ５つの目標地点を指定して移動
  ToioTargetPos pos[5];
  pos[0].x = 250;
  pos[0].y = 250;
  pos[0].angle = 0;
  pos[1].x = 250;
  pos[1].y = 300;
  pos[1].angle = 90;
  pos[2].x = 300;
  pos[2].y = 300;
  pos[2].angle = 180;
  pos[3].x = 300;
  pos[3].y = 250;
  pos[3].angle = 270;
  pos[4].x = 250;
  pos[4].y = 250;
  pos[4].angle = 0;
  xMod.Toio.controlMotorWithMultipleTargets(0, 0, 0, 50, 0, 0, 5, pos);
  delay(5000);
```

### `controlMotorWithAcceleration()`

キューブの加速度を指定してモーターを制御します。

#### プロトタイプ宣言

```c++
void controlMotorWithAcceleration(uint8_t translational_speed, uint8_t acceleration,
  uint16_t rotational_velocity, uint8_t rotational_direction, uint8_t travel_direction,
  uint8_t priority, uint8_t duration);
```

#### 引数

No. | 変数名         | 型        | 必須   | 説明
:---|:---------------|:----------|:-------|:-------------
1   | `translational_speed`  | `uint8_t`  | ✔     | キューブの並進速度(`0` ～ `255`)
2   | `acceleration` | `uint8_t`  | ✔     | キューブの加速度(100 ミリ秒ごとの速度の増加分 `0` ～ `255`)
3   | `rotational_velocity` | `uint16_t`  | ✔     | キューブの向きの回転速度 (度/秒 `0` ～ `65535`)
4   | `rotational_direction` | `uint8_t`  | ✔     | キューブの向きの回転方向	 (`0` 正 ～ `1` 負)
5   | `travel_direction` | `uint8_t`  | ✔ | キューブの進行方向 (`0` 前進 ～ `1` 後退)
6   | `priority`     | `uint8_t`  | ✔     | 速度調整優先指定(`0` 並進優先回転調整  ～ `1` 回転優先速度調整)
7   | `duration`     | `uint8_t`  | ✔     | 制御時間  x10 ミリ秒 0は制限なし(`0` ～ `255`)

#### コードサンプル

```c++
// ゆっくり弧を描きながら 2 秒間移動します。
xMod.Toio.controlMotorWithAcceleration(50, 15, 30, 0, 0, 0, 200);
delay(5000);
```

### `getIDReaderData()`

Toioのプレイマット読み取りセンサーの状態を取得します。キューブがマット上にあるとき、マットからセンサーで読み取った値(ID)が取得できます。マットから読み取ることができるIDには、マット上の座標値を表すポジションIDと、キューブが乗っている領域を表すスタンダードIDがあり、どちらかの情報が返されます。

#### プロトタイプ宣言

```c++
struct ToioCoreIDData {
  ToioCoreIDType type; // 	情報の種類
  union {
    ToioCorePositionIDData position; // キューブの座標と角度
    ToioCoreStandardIDData standard; // キューブの下のStandard IDとキューブの角度
  };
};

struct ToioCorePositionIDData {
  uint16_t cubePosX; // 	キューブの中心の X 座標値
  uint16_t cubePosY; //   キューブの中心の Y 座標値
  uint16_t cubeAngleDegree; // キューブの角度
  uint16_t sensorPosX;  // 読み取りセンサーの X 座標値
  uint16_t sensorPosY;  // 読み取りセンサーの Y 座標値
  uint16_t sensorAngleDegree;  // 読み取りセンサーの角度
};

struct ToioCoreStandardIDData {
  uint32_t standardID;  // Standard ID の値
  uint16_t cubeAngleDegree; // キューブの角度
};

ToioCoreIDData getIDReaderData();
```

#### 引数

なし

#### 戻値

`ToioCoreIDData` 型の構造体が返されます。各メンバーの意味は以下の通りです。

名前       | 型        | 説明
:----------|:----------|:------------------------
`type`     | `ToioCoreIDType`    | IDタイプ (`ToioCoreIDTypeNone`: 読み取れなかった場合, `ToioCoreIDTypePosition`: ポジションIDの場合, `ToioCoreIDTypeStandard`: スタンダードIDの場合) 
`position`    | `ToioCorePositionIDData`    | ポジションID情報
`standard`     | `ToioCoreStandardIDData`    | スタンダードID情報

type が ToioCoreIDTypePosition の場合、position 値には、`ToioCorePositionIDData` 型の構造体が返されます。各メンバーの意味は以下の通りです。


名前       | 型        | 説明
:----------|:----------|:------------------------
`cubePosX`     | `uint16_t`    | キューブの中心の X 座標値
`cubePosY`     | `uint16_t`    | キューブの中心の Y 座標値
`cubeAngleDegree`     | `uint16_t`    | キューブの角度（度）
`sensorPosX`     | `uint16_t`    | 読み取りセンサーの中心の X 座標値
`sensorPosY`     | `uint16_t`    | 読み取りセンサーの中心の Y 座標値
`sensorAngleDegree`     | `uint16_t`    | 読み取りセンサーの角度（度）

type が ToioCoreIDTypeStandard の場合、standard 値には、`ToioCoreStandardIDData` 型の構造体が返されます。各メンバーの意味は以下の通りです。

名前       | 型        | 説明
:----------|:----------|:------------------------
`standardID`     | `uint32_t`    | Standard ID の値
`cubeAngleDegree`     | `uint16_t`    | キューブの角度（度）


position および standard の値の詳細仕様は、[toio コア キューブ通信仕様](https://toio.github.io/toio-spec/docs/ble_id)をご覧ください。

Standard IDの値については[Standard ID 一覧](https://toio.github.io/toio-spec/docs/hardware_standard_id)をご覧ください。

#### コードサンプル

```c++
ToioCoreIDData data = toiocore->getIDReaderData();
if (data.type == ToioCoreIDTypePosition) {
  M5.Log.printf("posX: %u posY: %u angle: %u\n",
    data.position.cubePosX, data.position.cubePosY, data.position.cubeAngleDegree);
}
else if (data.type == ToioCoreIDTypeStandard) {
  M5.Log.printf("Standard ID: %u\n", data.standard.standardID);
}
else {
  M5.Log.println("no id found.");
}
```


### 参考
本ライブラリのToio関数は以下のライブラリの機能を使用しています。さらに細かい情報が必要な場合は参照してください。

https://github.com/kenichi884/M5StackToio/blob/master/README_jp.md

## MIDI
### クラス名：xMod.MIDI

### `begin()` 
MIDIの利用に必要な初期処理を行います。

#### プロトタイプ宣言

```c++
void begin(midi::Channel inChannel =　MIDI_CHANNEL_OMNI);
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `inChannel`   | `midi::Channel` |   | 起動対象のチャンネルです。指定がなければ”MIDI_CHANNEL_OMNI"となります。

### `end()` 

MIDIの動作を終了します。

#### プロトタイプ宣言

```c++
void end();
```

### `enable_MIDI()` 

MIDIの動作を有効化します。

#### プロトタイプ宣言

```c++
void enable_MIDI();
```

### `disable_MIDI()` 

MIDIの動作を無効化します。

#### プロトタイプ宣言

```c++
void edisable_MIDI();
```

### `setMode()` 
MIDIを入力で利用するか、出力で利用するかを指定します。

#### プロトタイプ宣言

```c++
enum xMod_MIDIMode {
    MIDI_MODE_IN,
    MIDI_MODE_OUT
};

void setMode(xMod_MIDIMode mode)
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `mode`     | `xMod_MIDIMode` | ✔︎   | MIDIの入出力モード指定。入力モードなら"MIDI_MODE_IN"、出力モードなら”MIDI_MODE_OUT"を指定。

## その他
### `xMod.begin()` 
xModクラスに関連した初期処理を全て行います。基本的にsetup()内で実行してください。

#### プロトタイプ宣言

```c++
void begin();
```

### `xMod.recordSound()` 
指定されたミリ秒の分だけSDカード上に指定したファイル名で録音を行います。

#### プロトタイプ宣言

```c++
void recordSound(int time, String filename = "/audio.wav");
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `time`     | `int` | ✔︎   | 録音時間(ms)
2   | `filename`     | `String` |    | 録音先のファイル名。wavファイルを指定してください。デフォルトは"audio.wav"です。

### `xMod.Utils.connectWifi()` 
指定されたアクセスポイントとWifi接続を行います。接続に成功したかどうかをboolで返します。

#### プロトタイプ宣言

```c++
bool connectWifi(String ssid, String pass);
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `ssid`     | `String` | ✔︎   | アクセスポイントのSSID
2   | `pass`     | `String` |    |アクセスポイントのパスワード

### `xMod.Utils.disconnectWifi()` 
Wifiを切断します、

#### プロトタイプ宣言

```c++
void disconnectWifi();
```

### `xMod.DisplayDebug()` 
デバッグモードとして文字を表示します。
指定された出力先に文字が表示されます。

#### プロトタイプ宣言

```c++
void DisplayDebug(const String& message);
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `message`     | `const String&` | ✔︎   | 表示文章

### `xMod.setDebugMode()` 
デバッグモードの出力先を指定します。
出力なし、画面表示、シリアル出力があります。

#### プロトタイプ宣言

```c++
enum xMod_DebugMode {
    DEBUG_MODE_NONE,
    DEBUG_MODE_DISPLAY,
    DEBUG_MODE_SERIAL
};

 void setDebugMode(xMod_DebugMode mode);
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `mode`     | `xMod_DebugMode` | ✔︎   | 表示なしなら”DEBUG_MODE_NONE”、画面表示なら”DEBUG_MODE_DISPLAY”、シリアル出力なら”DEBUG_MODE_SERIAL”

