# Bluetooth speaker

M5Core2（Bluetoothクラシック・A2DP対応）とxModの組み合わせで使用するBluetoothスピーカーのサンプルコードです。左右のチャンネルに音声スピーカー（主に中高音）とLRAによる振動（主に低音）が振り分けられるため、音源やチャンネルの工夫で振動と音声を組み合わせることが可能です。
※注意：M5 CoreS3はBluetoothスピーカー用のプロトコルA2DPに対応していないため本サンプルコードは動作しません（ビルドできません）。

起動:bluetoothSpeakerStart()

終了:bluetoothSpeakerEnd()

終了後再起動は不可

### 注意点

toio関連の処理と同時実行不可

起動時wifiが繋がらなくなる
