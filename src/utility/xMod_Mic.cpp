#include "xMod_Mic.hpp"

namespace xdiversity
{
    void xMod_Mic::recordStart(String filename){
        filenameInfo = filename;
        recFlag = true;                                   //マイク録音開始
        xTaskCreatePinnedToCore(
            [](void* arg) {
                static_cast<xMod_Mic*>(arg)->xModRecordTask();
            },
            "xModRecordTask", 4096, this, 1, NULL, 1);
    }

    void xMod_Mic::recordStop(){
        recFlag = false;                           //録音処理終了フラグ
        delay(200); 
    }

    void xMod_Mic::xModRecordTask(){
        M5.Speaker.stop();
        M5.Speaker.end();
        M5.Mic.begin();

        size_t transBytes;                              //I2S取得データサイズ用
        int recPos = 0;                                       //録音データ初期位置
        uint8_t soundBuffer[BUFFER_LEN];      //DMA転送バッファ

        // 最初の一回にノイズが入るので、一回だけ録音して捨てる
        i2s_read(I2S_NUM_0, (char*)soundBuffer, 128, &transBytes, (100 / portTICK_RATE_MS));

        //SDカード処理
        File f = SD.open(filenameInfo, FILE_WRITE);

        //ヘッダー処理 recpos長めだけど大丈夫か
        recPos = SAMPLING_RATE * 16 * 1 * 10000 / 1000 / 8;
        // データサイズを計算 (実際に録音されたサイズ - WAVヘッダーのサイズ)
        int dataSize = recPos - sizeof(wavHeader);
        // ファイルサイズを計算 (全体のサイズ - 8バイト ('RIFF'とファイルサイズのフィールド))
        int fileSize = recPos - 8;

        // ファイルサイズとデータサイズをwavHeaderに直接更新
        wavHeader[4] = fileSize & 0xFF;
        wavHeader[5] = (fileSize >> 8) & 0xFF;
        wavHeader[6] = (fileSize >> 16) & 0xFF;
        wavHeader[7] = (fileSize >> 24) & 0xFF;
        wavHeader[40] = dataSize & 0xFF;
        wavHeader[41] = (dataSize >> 8) & 0xFF;
        wavHeader[42] = (dataSize >> 16) & 0xFF;
        wavHeader[43] = (dataSize >> 24) & 0xFF;

        f.write(wavHeader, sizeof(wavHeader));

        while (recFlag) {                                 //録音データ処理
            i2s_read(                                       //I2Sからデータ取得（マイク録音）
            I2S_NUM_0, (char*)soundBuffer, BUFFER_LEN, &transBytes, (100 / portTICK_RATE_MS));

            f.write(soundBuffer, BUFFER_LEN);
            //recPos += transBytes;

            vTaskDelay(1 / portTICK_RATE_MS);               //タスク待機
        }
        f.close();

        M5.Mic.end();
        M5.Speaker.begin();
        vTaskDelete(NULL);
    }
}