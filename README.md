# xModLib
xModを操作するためのライブラリです。M5Stack,Toioと共に利用することを想定しています。

## 始め方
1. Visual Studio CodeにPlatformIOをインストールする
  - Visual Studio Codeのインストール
    - https://code.visualstudio.com/download
  - PlatformIOのインストール
    - https://qiita.com/nextfp/items/f54b216212f08280d4e0

2. このリポジトリをダウンロードし、zipを解凍する
  - 緑の「Code」ボタン -> Download ZIP　をクリック

3. PlatformIOでサンプルプロジェクトを開く
  - PlatformIO(左のツールバー内の狐の顔のようなアイコン) -> PIO Home -> Projects -> Add Existing -> 解凍したフォルダ内のサンプル（例えば、xMod-lib-main/examples/basic/00_Test）を選択

4. 手持ちのM5Stackの種類に合わせて環境を選択
  - ページ下部の「Default (...)」の部分をクリックする
    - M5Stack Core2 なら env:m5stack-core2 (...) を選択
    - M5Stack Cores3 なら env:m5stack-cores3 (...) を選択

5. USBケーブルを使用して、PCとM5Stackを接続

6. プログラムした内容をビルドしてデバイスに書き込む
  -  ページ下部の「✓」ボタンを押す
  -  緑色でSUCCESSと表示されたら、ページ下部の「→」ボタンを押す

7. 書き込みが完了したら、実際にデバイスを動かしてみましょう

### 新しいプロジェクトを作る

1. xMod-lib-main/examples/projects/template を複製して、projects以下に新しい名前のフォルダを作る
  - 例えば、xMod-lib-main/examples/projects/project1 というフォルダにする。フォルダの深さが変わってしまうと、platform.iniの内容を修正しなければ動かない状態になるので注意してください。
    - (上級者向け) ``symlink://../../../``の行を修正すると相対パスを変更できます

2. 上記と同じように、PlatformIOでこの新しく作ったプロジェクトフォルダを開く

3. srcフォルダ内のmain.cppを書き換えて、同様にM5Stackに書き込む
  - 自分の好きなxModを作ってみましょう！

### もしPCがデバイスを見つけてくれない場合は
- USBドライバをダウンロードしてください。
  - https://docs.m5stack.com/en/download
      - USB DRIVER & OPEN SOURCE LIBRARY の欄からご自身の環境に合ったものを選択してください。

## 関数一覧
### Index

* [ボタン](#class_button)
* [マイク](#class_mic)
* [スピーカー・振動](#class_speaker)
* [SDカード](#class_sd)
* [OpenAI API](#class_openai)
* [Toio操作](#class_toio)
* [MIDI](#class_midi)
* [その他](#class_others)
* [M5Unified・M5GFX提供機能](#m5unifiedGFX)

## <a id="class_button">ボタン</a>

### クラス名：xMod.BtnX 
Xはボタンごとに異なります。 

- BtnL(xMod上側面左の物理ボタン)
- BtnR(xMod上側面右の物理ボタン)

### index
* [isPressed()](#button_isPressed)
* [wasPressed()](#button_wasPressed)
* [wasReleased()](#button_wasReleased)
* [isHeld()](#button_isHeld)

### <a id = "button_isPressed">`isPressed()` </a>

今ボタンが押されているかどうかをboolで返します。

#### プロトタイプ宣言

```c++
bool isPressed();
```

### <a id = "button_wasPressed">`wasPressed()` </a>

新たにボタンが押されたかどうかをboolで返します。

#### プロトタイプ宣言

```c++
bool wasPressed();
```

### <a id = "button_wasReleased">`wasReleased()` </a>

ボタンが押されていない状態になったかどうかをboolで返します。

#### プロトタイプ宣言

```c++
bool wasReleased();
```

### <a id = "button_isHeld">`isHeld()` </a>

ボタンが押し続けられているかどうかをboolで返します。

#### プロトタイプ宣言

```c++
bool isHeld();
```

## <a id="class_mic">マイク</a>
### クラス名：xMod.Mic

### index
* [recordStart()](#mic_recordStart)
* [recordStop()](#mic_recordStop)

### <a id = "mic_recordStart">`recordStart()` </a>

録音を開始します。事前にSDカードのマウントが必要です。指定したファイル名で保存されます。ファイル形式はwavです。

#### プロトタイプ宣言

```c++
void recordStart(String filename);
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `filename`     | `String` |      | 録音結果を保存する先のファイル名です。.wavの形で指定してください。デフォルトは”audio.wav"となります。

### <a id = "mic_recordStop">`recordStop()` </a>

録音を終了します。recordStard()で開始された録音はこの関数によって停止されるまで続きます。

#### プロトタイプ宣言

```c++
void recordStop();
```

## <a id = "class_speaker">スピーカー・振動</a>
### クラス名：xMod.WaveOut

### index
* [begin()](#speaker_begin)
* [end()](#speaker_end)
* [isPlaying()](#speaker_isPlaying)
* [setVolume()](#speaker_setVolume)
* [getVolume()](#speaker_getVolume)
* [stop()](#speaker_stop)
* [tone()](#speaker_tone)
* [playWavFile()](#speaker_playWavFile)
* [enable_Speaker()](#speaker_enable_Speaker)
* [disable_Speaker()](#speaker_disable_Speaker)
* [enable_LRA()](#speaker_enable_LRA)
* [disable_LRA()](#speaker_disable_LRA)
* [enable_LineOut()](#speaker_enable_LineOut)
* [disable_LineOut()](#speaker_disable_LineOut)

### <a id = "speaker_begin">`begin()` </a>

スピーカー周辺機能を利用するための初期処理を行います。
このクラスを利用する際は最初に実行してください。

#### プロトタイプ宣言

```c++
void begin();
```

### <a id = "speaker_end">`end()` </a>

スピーカー周辺機能の利用を終了します。

#### プロトタイプ宣言

```c++
void end();
```

### <a id = "speaker_isPlaying">`isPlaying()` </a>

スピーカーが再生中かどうかをboolで返します。

#### プロトタイプ宣言

```c++
bool isPlaying();
```

### <a id = "speaker_setVolume">`setVolume()` </a>

スピーカーの音量を指定した値に調整します。

#### プロトタイプ宣言

```c++
void setVolume(uint8_t volume);
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `volume`     | `uint8_t` | ✔︎    | スピーカーの音の大きさ(0-255)

### <a id = "getVolume">`getVolume()` </a>

スピーカーの音量の大きさを取得します。

#### プロトタイプ宣言

```c++
uint8_t getVolume();
```

### <a id = "speaker_stop">`stop()` </a>

スピーカーの動作を中断します。

#### プロトタイプ宣言

```c++
void stop();
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `channel`     | `uint8_t` |      | 動作を止めるチャンネルを指定することもできます。指定しなければ全部のチャンネルの動作を止めます。

### <a id = "speaker_tone">`tone()` </a>

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

### <a id = "speaker_playWavFile">`playWavFile()` </a>

指定したwavファイルを再生します。

#### プロトタイプ宣言

```c++
void playWavFile(const char* filename);
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `filename`     | `const char*` | ✔︎   | ファイル名。wavファイルを指定してください。

### <a id = "speaker_enable_Speaker">`enable_Speaker()` </a>

音の出力を行う機器をスピーカーに指定します。事前に他の指定を行なっている場合はその指定を解除してから指定を行ってください。

#### プロトタイプ宣言

```c++
void enable_Speaker();
```

### <a id = "speaker_disable_Speaker">`disable_Speaker()` </a> 

スピーカーに対する音の出力を行う機器の指定を解除します。

#### プロトタイプ宣言

```c++
void disable_Speaker();
```

### <a id = "speaker_enable_LRA">`enable_LRA()` </a>

音の出力を行う機器を振動アクチュエータに指定します。事前に他の指定を行なっている場合はその指定を解除してから指定を行ってください。

#### プロトタイプ宣言

```c++
void enable_LRA();
```

### <a id = "disable_LRA">`disable_LRA()` </a>

振動アクチュエータに対する音の出力を行う機器の指定を解除します。

#### プロトタイプ宣言

```c++
void disable_LRA();
```

### <a id = "speaker_enable_LineOut">`enable_LineOut()` </a>

音の出力を行う機器をラインアウト(イヤホンジャック)に指定します。事前に他の指定を行なっている場合はその指定を解除してから指定を行ってください。

#### プロトタイプ宣言

```c++
void enable_LineOut();
```

### <a id = "speaker_disable_LineOut">`disable_LineOut()`</a> 

ラインアウト(イヤホンジャック)に対する音の出力を行う機器の指定を解除します。

#### プロトタイプ宣言

```c++
void disable_LineOut();
```

           

## <a id="class_sd">SDカード</a>
### クラス名：xMod.SDM

### index
* [begin()](#sd_begin)
* [checkSD()](#sd_checkSD)

### <a id = "sd_begin">`begin()` </a>

SDカードのマウントを行います。これを行わないとxModがSDカードを認識しません。

#### プロトタイプ宣言

```c++
void begin();
```

### <a id = "sd_checkSD">`checkSD()` </a>

SDカードがマウントされているかどうかをboolで返します。

#### プロトタイプ宣言

```c++
bool checkSD();
```

## <a id="class_openai">OpenAI API</a>

### クラス名：xMod.OpenAI

### index
* [SetAPIKey()](#openai_SetAPIKey)
* [SetModel()](#openai_SetModel)
* [GPT()](#openai_GPT)


### <a id = "openai_SetAPIKey">`SetAPIKey()` </a>

OpenAIのAPIキーを登録します。OpanAI APIに関連した機能を利用するには必須です。

#### プロトタイプ宣言

```c++
void SetAPIKey(String key);
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `key`     | `String` | ✔︎   | APIキー

### <a id = "openai_SetModel">`SetModel()` </a>

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

### <a id = "openai_GPT">`GPT()`</a> 

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

## <a id="class_toio">Toio操作</a>
### クラス名 : xMod.Toio

### index
* [searchToio()](#toio_searchToio)
* [connect()](#toio_connect)
* [disconnect()](#toio_disconnect)
* [isConnected()](#toio_isConnected)
* [getAddress()](#toio_getAddress)
* [getName()](#toio_getName)
* [getBleProtocolVersion()](#toio_getBleProtocolVersion)
* [playSoundEffect()](#toio_playSoundEffect)
* [playSoundRaw()](#toio_playSoundRaw)
* [stopSound()](#toio_stopSound)
* [turnOnLed()](#toio_turnOnLed)
* [turnOffLed()](#toio_turnOffLed)
* [getBatteryLevel()](#toio_getBatteryLevel)
* [getButtonState()](#toio_getButtonState)
* [getMotion()](#toio_getMotion)
* [controlMotor()](#toio_controlMotor)
* [drive()](#toio_drive)
* [controlMotorWithTarget()](#toio_controlMotorWithTarget)
* [controlMotorWithMultipleTargets()](#toio_controlMotorWithMultipleTargets)
* [controlMotorWithAcceleration()](#toio_controlMotorWithAcceleration)
* [getIDReaderData()](#toio_getIDReaderData)

### <a id="toio_searchToio">`searchToio()`</a>

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


### <a id="toio_connect">`connect()`</a>

searchToio()で見つけたToioに接続します。接続結果をboolで返します。

#### プロトタイプ宣言

```c++
bool connect();
```

#### 引数

なし


### <a id="toio_disconnect">`disconnect()`</a>

接続したToioとの通信を切断します。

#### プロトタイプ宣言

```c++
void disconnect();
```

#### 引数

なし


###  <a id="toio_isConnected">`isConnected()`</a>

Toioとの接続状況をboolで返します。

#### プロトタイプ宣言

```c++
bool isConnected();
```

#### 引数

なし

### <a id="toio_getAddress">`getAddress()`</a>

Toioの MAC アドレスを返します。

#### プロトタイプ宣言

```c++
String getAddress();
```

#### 引数

なし

### <a id="toio_getName">`getName()`</a>

接続しているToioの名前を取得します。

#### プロトタイプ宣言

```c++
String getName();
```

#### 引数

なし

### <a id="toio_getBleProtocolVersion">`getBleProtocolVersion()`</a>

接続に利用しているBluetoothプロトコルのバージョンを得ます。

#### プロトタイプ宣言

```c++
String getBleProtocolVersion();
```

#### 引数

なし

### <a id="toio_playSoundEffect">`playSoundEffect()`</a>

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

### <a id="toio_playSoundRaw">`playSoundRaw()`</a>

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

### <a id="toio_stopSound">`stopSound()`</a>

再生中の音の再生を止めます。

#### プロトタイプ宣言

```c++
void stopSound();
```

#### 引数

なし

### <a id="toio_turnOnLed">`turnOnLed()`</a>

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

### <a id="toio_turnOffLed">`turnOffLed()`</a>

Toioの背面にあるLEDを消灯させます。

#### プロトタイプ宣言

```c++
void turnOffLed();
```

#### 引数

なし

### <a id="toio_getBatteryLevel">`getBatteryLevel()`</a>

バッテリーの残量を取得します。

#### プロトタイプ宣言

```c++
uint8_t getBatteryLevel();
```

#### 引数

なし

### <a id="toio_getButtonState">`getButtonState()`</a>

背面のLEDは押しボタンにもなっており、それが押されているかどうかを取得します。

#### プロトタイプ宣言

```c++
bool getButtonState();
```

#### 引数

なし

### <a id="toio_getMotion">`getMotion()`</a>

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

### <a id="toio_controlMotor">`controlMotor()`</a>

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
### <a id="toio_drive">`drive()`</a>

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

### <a id="toio_controlMotorWithTarget">`controlMotorWithTarget()`</a>

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

### <a id="toio_controlMotorWithMultipleTargets">`controlMotorWithMultipleTargets()`</a>

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

### <a id="toio_controlMotorWithAcceleration">`controlMotorWithAcceleration()`</a>

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

### <a id="toio_getIDReaderData">`getIDReaderData()`</a>

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

## <a id="class_midi">MIDI</a>
### クラス名：xMod.MIDI

### index
* [begin()](#midi_begin)
* [end()](#midi_end)
* [enable_MIDI()](#midi_enable_MIDI)
* [disable_MIDI()](#midi_disable_MIDI)
* [setMode()](#midi_setMode)

### <a id="midi_begin">`begin()`</a>
MIDIの利用に必要な初期処理を行います。

#### プロトタイプ宣言

```c++
void begin(midi::Channel inChannel =　MIDI_CHANNEL_OMNI);
```

#### 引数

No. | 変数名    | 型         | 必須   | 説明
:---|:---------|:-----------|:-------|:-------------
1   | `inChannel`   | `midi::Channel` |   | 起動対象のチャンネルです。指定がなければ”MIDI_CHANNEL_OMNI"となります。

### <a id="midi_end">`end()`</a>

MIDIの動作を終了します。

#### プロトタイプ宣言

```c++
void end();
```

### <a id="midi_enable_MIDI">`enable_MIDI()`</a>

MIDIの動作を有効化します。

#### プロトタイプ宣言

```c++
void enable_MIDI();
```

### <a id="midi_disable_MIDI">`disable_MIDI()`</a>

MIDIの動作を無効化します。

#### プロトタイプ宣言

```c++
void edisable_MIDI();
```

### <a id="midi_setMode">`setMode()`</a>
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

## <a id="class_others">その他</a>

### index
* [xMod.begin()](#others_begin)
* [xMod.recordSound()](#others_recordSound)
* [xMod.Utils.connectWifi()](#others_connectWifi)
* [xMod.Utils.disconnectWifi()](#others_disconnectWifi)
* [xMod.DisplayDebug()](#others_DisplayDebug)
* [xMod.setDebugMode()](#others_setDebugMode)

### <a id = "others_begin">`xMod.begin()` </a>
xModクラスに関連した初期処理を全て行います。基本的にsetup()内で実行してください。

#### プロトタイプ宣言

```c++
void begin();
```

### <a id = "others_recordSound">`xMod.recordSound()` </a>
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

### <a id = "others_connectWifi">`xMod.Utils.connectWifi()` </a>
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

### <a id = "others_disconnectWifi">`xMod.Utils.disconnectWifi()` </a>
Wifiを切断します、

#### プロトタイプ宣言

```c++
void disconnectWifi();
```

### <a id = "others_DisplayDebug">`xMod.DisplayDebug()`</a> 
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

### <a id = "others_setDebugMode">`xMod.setDebugMode()` </a>
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

## <a id = "m5unifiedGFX">M5Unified・M5GFX提供機能</a>
M5stack core2/s3単体で実現する機能についてはM5Unifiedライブラリ、M5GFXライブラリをそのまま利用することができます。

M5UnifiedライブラリはM5stackの機能全般を扱えるライブラリで、M5GFXライブラリは画面表示に特化したライブラリです。

詳細については以下のドキュメントを参考にしてください。

https://docs.m5stack.com/ja/arduino/m5unified/helloworld

https://github.com/m5stack/M5Unified/tree/master

いくつか使用頻度が高いものを挙げます。

### ボタン

タッチパネル下部のボタンを扱います。左からボタンA、ボタンB、ボタンCという名前になっています。

それぞれM5.BtnXというクラスでアクセスすることができます。

#### コードサンプル

```c++
if (M5.BtnA.isPressed()){
    M5.Display.println("ボタンAが押されています");
} else {
    M5.Display.println("ボタンAは押されていません");
}
```

### 画面表示

M5GFXライブラリを用いてタッチパネル上の表示を実装することができます。

M5.Displayというクラスでアクセスすることができます。

#### コードサンプル

```c++
//文字出力座標を指定　左上(0,0)〜右下(320,240)
M5.Display.setCursor(0, 0);
//文章を表示
M5.Display.println("画面に文字を表示");
//(0,0)から辺の長さ100の正方形の枠を描画
M5.Display.drawRect(0, 0, 100, 100, WHITE);
//画面全体に黒で塗りつぶされた長方形を描画することで画面の削除を行う
M5.Display.fillRect(0, 0, 320, 240, BLACK);
```
