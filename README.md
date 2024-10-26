# SPM Sender

M5Stack でボタンが押されたときに、押されたボタンをESP-NOW で送信します。

## 使い方

1. MAC の取得
   SPMServo（別プログラム）を実行して、受信する端末のMAC アドレスを取得します。
   例：以下のようなアドレスが取得できたとします
        01:23:45:67:89:0A
2. MAC の設定
   `./include/secret_base.hpp` を コピーして、`/include/secret.hpp` ファイルを作成します。

   ```secret.hpp
    constexpr uint8_t broadcastAddress[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0x0A};
   ```

   `secret.hpp` ファイルを編集し、broadcastAddress に先ほどをアドレスを記入します。
   各アドレスの前に、"0x" を付けます。
