#include <SI_EFM8SB1_Register_Enums.h>                  // SI_SFR declarations
#include "InitDevice.h"

//SDA:0.3
//SCL:0.4

sbit pin05 = P0^5;
int send_data[3];
int ms;
int i;
uint8_t slave;
uint8_t send_data1;
uint8_t send_data2;
uint8_t max_count;
uint8_t receive_data_first;
uint8_t receive_data_second;

void delay_ms (ms);
void smbus0 (slave);//スレイブアドレスを送るだけ、読み込み用
void smbus1 (slave,send_data1);//スレイブアドレスに加えて1つデータを送る
void smbus2 (slave,send_data1, send_data2);//スレイブアドレスに加えて2つデータを送る
void LCD_Init(void);//LCDの設定をする
void LCD_Data(void);//LCDにデータを送る

void SiLabs_Startup (void) {}
int main (void)
{
	enter_DefaultMode_from_RESET();
	enter_Mode2_from_DefaultMode();
	LCD_Init();

	while(1){
	    smbus1(0x90, 0x00); //2つデータを送信
	    smbus0(0x91); //1つデータを送信
      LCD_Data();
	}
}

void smbus0 (slave)
{
  send_data[0] = slave;
  max_count = 0;
  SMB0CN0_STA = 1;
  delay_ms(10);
}

void smbus1 (slave, send_data1)
{
  send_data[0] = slave;
  send_data[1] = send_data1;
  max_count = 1;
  SMB0CN0_STA = 1;
  delay_ms(10);
}

void smbus2 (slave, send_data1, send_data2)
{
  send_data[0] = slave;
  send_data[1] = send_data1;
  send_data[2] = send_data2;
  max_count = 2;
  SMB0CN0_STA = 1;
  delay_ms(10);
}

void LCD_Init(){
  smbus2(0x7C, 0x00, 0x38);
  smbus2(0x7C, 0x00, 0x39);
  smbus2(0x7C, 0x00, 0x14);
  smbus2(0x7C, 0x00, 0x73);
  smbus2(0x7C, 0x00, 0x56);
  smbus2(0x7C, 0x00, 0x6C);
  smbus2(0x7C, 0x00, 0x38);
  smbus2(0x7C, 0x00, 0x01);
  smbus2(0x7C, 0x00, 0x0C);
}

void LCD_Data(){
  smbus2(0x7C, 0x00, 0x80);//場所の指定
  for(i = 7; i >= 0; i--) {
      char receive_data_bit =(receive_data_first>>i) & 1;
      if(receive_data_bit == 0){
          smbus2(0x7C, 0x40, 0x30);//文字コード 0
      }
      else{
          smbus2(0x7C, 0x40, 0x31);//文字コード 1
      }
  }

  for(i = 7; i >= 0; i--) {
      char receive_data_bit =(receive_data_second>>i) & 1;
      if(receive_data_bit == 0){
          smbus2(0x7C, 0x40, 0x30);//文字コード
      }
      else{
          smbus2(0x7C, 0x40, 0x31);//文字コード
      }
   }
}

void delay_ms (ms)
{
   TCON &= ~0x30;                      // Stop Timer0; Clear TCON_TF0
   TMOD &= ~0x0f;                      // 16-bit free run mode
   TMOD |=  0x01;

   CKCON0 |= 0x04;                      // Timer0 counts SYSCLKs

   while (ms) {
      TCON_TR0 = 0;                         // Stop Timer0
      TH0 = ((-24500000/1000) >> 8);     // Overflow in 1ms
      TL0 = ((-24500000/1000) & 0xFF);
      TCON_TF0 = 0;                         // Clear overflow indicator
      TCON_TR0 = 1;                         // Start Timer0
      while (!TCON_TF0);                    // Wait for overflow
      ms--;                            // Update ms counter
   }

   TCON_TR0 = 0;                            // Stop Timer0
}
