## システム概要
マイコン・・・EFM8SB10F8G-QFN24（SILICON LABS）https://jp.silabs.com/mcu/8-bit-microcontrollers/efm8-sleepy-bee/device.efm8sb10f8g-qfn24?tab=softwareandtools<br>
開発環境・・・simplicity studio（ver 5）<br>
温度センサ・・・TMP117<br>
LCD・・・I2C接続薄型16文字×2行液晶、型番：AQM1602XA-RN-GBW<br>

温度センサとLCDとのI2Cを行い、温度センサで計測した2進数16ビットの値をLCDにそのまま表示する

## 回路図
![スクリーンショット 2024-10-07 16 01 31](https://github.com/user-attachments/assets/72f6624f-7ad0-45eb-a198-edf9bd9b7b0b)
![スクリーンショット 2024-10-07 16 03 02](https://github.com/user-attachments/assets/5acee326-faf5-4dfb-9d93-e2e0b988ce99)

## SDA、SCLのピン設定について
### 設定の仕方
P0SKIP、P1SKIPレジスタの設定で決まる。<br>
ビット0でクロスバーの設定をスキップしない、ビット1でクロスバーの設定をスキップする。<br>
設定の記述はhttps://github.com/akaoni0000/temperature_measurement/blob/master/src/InitDevice.cの490行目以降<br>

SDAとSCLはスキップしないピンからSDA、SCLの順番で自動的に設定されていく。<br>
今回はSDAに0.3ピン、SCLに0.4ピンを割り当てた。<br>

### 参考 リファレンスマニュアルp217<br>
![スクリーンショット 2024-10-07 16 09 46](https://github.com/user-attachments/assets/73f20afb-77af-419f-b86e-71f19cd1e279)

## 割り込み処理について
### 割り込み処理が起こるタイミング
SMB0CN0_STA = 1;でI2Cを開始したとき（I2Cのスタートコンディションを発動したとき）<br>
I2Cのデータを送信し終わった時<br>
I2Cのデータを受信し終わった時<br>

### 割り込み処理を中断させるには
SMB0CN0_STO = 1;でストップコンディションを発動させる

### 参考 リファレンスマニュアルp221~224
![スクリーンショット 2024-10-07 16 15 09](https://github.com/user-attachments/assets/fd40abc9-11c8-4056-a06d-0abd9d4efb46)
![スクリーンショット 2024-10-07 16 15 17](https://github.com/user-attachments/assets/ffbf5a60-a3aa-4a05-aa16-ee8431047c73)

## 温度センサとのI2C
### スレイブアドレスについて
![スクリーンショット 2024-10-07 16 43 52](https://github.com/user-attachments/assets/469a2b81-d893-4e9e-8913-f38bb445b3f3)
![スクリーンショット 2024-10-07 16 44 11](https://github.com/user-attachments/assets/d84b4135-0112-4fea-b2bc-ff26b5684450)

ADD0をグランドに接続することでスレイブアドレスは0x90（書き込み）0x91（読み込み）になる

### 温度結果を読み取る方法
![スクリーンショット 2024-10-07 16 16 57](https://github.com/user-attachments/assets/fbf3ace5-6698-41f3-be5a-292da62fd1c0)

スタートコンディションー＞スレイブアドレス（書き込み：0x90）ー＞0x00ー＞スタートコンディションー＞スレイブアドレス（読み込み：0x91）ー＞測定結果（16ビット）ー＞ストップコンディション

### ビットの温度データ形式
![スクリーンショット 2024-10-07 16 20 07](https://github.com/user-attachments/assets/c21c1753-724f-4e12-830e-cd11c438b269)

### 実際のオシロスコープ観測結果
![スクリーンショット 2024-10-07 16 21 04](https://github.com/user-attachments/assets/a06596d4-0d4e-4a8b-85d8-e2cf44be18af)

## LCDとのI2C
### 初期設定
0x7Cはスレイブアドレス（書き込み）
```
void LCD_Init(){
smbus2(0x7C, 0x00, 0x38);
smbus2(0x7C, 0x00, 0x39);
smbus2(0x7C, 0x00, 0x14);
smbus2(0x7C, 0x00, 0x53);
smbus2(0x7C, 0x00, 0x73);
smbus2(0x7C, 0x00, 0x6C);
smbus2(0x7C, 0x00, 0x0C);
smbus2(0x7C, 0x00, 0x01);
}
```
この順番でデータを送信する
### 表示方法
最初に表示する場所の指定をするデータを送信する
```
smbus2(0x7C, 0x00, 0x80);//場所の指定
```
![スクリーンショット 2024-10-07 16 42 21](https://github.com/user-attachments/assets/9263c894-141d-4711-97a1-1041e67dfb79)<br>
![スクリーンショット 2024-10-07 16 28 05](https://github.com/user-attachments/assets/e23376f1-a2cb-427f-bfc8-689cc9a6ec30)<br>
表示する文字データを送信する 文字データの場合はスレイブアドレスの後に0x40を送信する
```
smbus2(0x7C, 0x40, 0x30);//文字コード 0
```
![スクリーンショット 2024-10-07 16 31 10](https://github.com/user-attachments/assets/afff2ac7-f436-4241-b805-469ca77a8095)<br>
### 参考
![Uploading スクリーンショット 2024-10-07 16.49.45.png…]()






