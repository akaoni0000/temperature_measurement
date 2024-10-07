## システム概要
マイコン・・・EFM8SB10F8G-QFN24（SILICON LABS）https://jp.silabs.com/mcu/8-bit-microcontrollers/efm8-sleepy-bee/device.efm8sb10f8g-qfn24?tab=softwareandtools
開発環境・・・simplicity studio（ver 5）
温度センサ・・・TMP117
LCD・・・I2C接続薄型16文字×2行液晶、型番：AQM1602XA-RN-GBW

温度センサとLCDとのI2Cを行い、温度センサで計測した2進数16ビットの値をLCDにそのまま表示する

## 回路図
![スクリーンショット 2024-10-07 16 01 31](https://github.com/user-attachments/assets/72f6624f-7ad0-45eb-a198-edf9bd9b7b0b)

## SDA、SCLのピン設定について
## 割り込み処理について
## 温度センサとのI2C
## LCDとのI2C
