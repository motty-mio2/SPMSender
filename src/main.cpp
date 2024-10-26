#include <iostream>
#include <Arduino.h>
#include <M5Unified.hpp>
#include <esp_now.h>
#include "secret.hpp"
#include <WiFi.h>

esp_now_peer_info_t peerInfo;  // 受信側情報のパラメータオブジェクト

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Deli_Success" : "Deli_Fail");
}

void setup() {
  auto cfg = M5.config();

  cfg.serial_baudrate = 115200;

  M5.begin(cfg);
  M5.Display.begin();
  M5.Display.print("Hello World!!");

  // ESP Now
  WiFi.mode(WIFI_STA);  // Wi-Fi

  // ESP-NOWの初期化
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // ペア情報（受信側のアドレスとチャネルと暗号化の設定）
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // 受信側の情報追加
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
  // ESP-NOWでデータ送信した時のコールバック関数を登録
}

int temp;
char buf[2];
uint8_t data[2];

void loop() {
  while (true) {
    delay(1);
    M5.update();
    temp = 0;

    if (M5.BtnA.wasClicked()) {
      Serial.println("A is clicked");
      temp += 1;
    } else if (M5.BtnB.wasClicked()) {
      Serial.println("B is clicked");
      temp += 2;
    } else if (M5.BtnC.wasClicked()) {
      Serial.println("C is clicked");
      temp += 4;
    } else {
      continue;
    }
    sprintf(buf, "%d", temp);
    memcpy(data, buf, strlen(buf));
    auto err = esp_now_send(broadcastAddress, data, sizeof(buf));
  }
}
