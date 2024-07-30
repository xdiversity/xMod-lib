#pragma once

#define AW9523_ADDR           0x59

#define AW9523_LED_MODE       0x03
#define AW9523_REG_CHIPID     0x10
#define AW9523_REG_SOFTRESET  0x7F
#define AW9523_REG_INPUT0     0x00
#define AW9523_REG_OUTPUT0    0x02
#define AW9523_REG_CONFIG0    0x04
#define AW9523_REG_INTENABLE0 0x06
#define AW9523_REG_GCR        0x11
#define AW9523_REG_LEDMODE    0x12
#define AW9523_REG_LED_DIM    0x20

#if defined(CONFIG_IDF_TARGET_ESP32)
// Core2
#define PORT_UART1_TX_PIN 14
#define PORT_UART1_RX_PIN 26
#define PORT_UART2_RX_PIN 13
#define PORT_UART2_TX_PIN 36
#elif defined(CONFIG_IDF_TARGET_ESP32S3)
// CoreS3
#define PORT_UART1_TX_PIN 17
#define PORT_UART1_RX_PIN 9
#define PORT_UART2_RX_PIN 18
#define PORT_UART2_TX_PIN 8
#endif

#define SPEAKER_BIT     0b00001000
#define LRA_BIT         0b00000100
#define LINEOUT_BIT     0b00000010
#define MIDI_BIT        0b00000001

// Define I2S pins for audio output
#define I2S_BCK_PIN  0  // Bit Clock (BCK)
#define I2S_WS_PIN   27  // Word Select (WS)
#define I2S_DOUT_PIN 2  // Data Output (DOUT)

#include <vector>
#include <string>
using namespace std;

#include <SD.h>
#include <Arduino.h>
#include <Wire.h>
#include <M5Unified.h>
#include <M5GFX.h>
#include <Toio.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <base64.h>
#include <ArduinoJson.h>