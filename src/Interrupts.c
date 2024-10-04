#include <SI_EFM8SB1_Register_Enums.h>

//sbit pin04 = P0^4;
//sbit pin05 = P0^5;
extern int send_data[3];
extern uint8_t max_count;
extern uint8_t receive_data_first;
extern uint8_t receive_data_second;
int send_data_count;
int receive_data_count;

SI_INTERRUPT(SMBUS0_ISR, SMBUS0_IRQn)
{
  //pin04 = 0;
  //pin05 = 0;
  switch (SMB0CN0 & 0xF0)
  {
     case 0xE0://スレイブアドレスを送信
        SMB0DAT = send_data[0];
        SMB0CN0_STA = 0;
        send_data_count = 1;
        receive_data_count = 1;
        break;

     case 0xC0://データ送信
        if(SMB0CN0_ACK && send_data_count<=max_count)
        {
            SMB0DAT = send_data[send_data_count];
            send_data_count++;
        }
        else {
            if(max_count!=0){
                SMB0CN0_STO = 1;
            }
        }
        break;

     case 0x80:
       if (receive_data_count <=1){
            receive_data_first = SMB0DAT;
            SMB0CN0_ACK = 1;
            receive_data_count ++;
       }
       else {
            receive_data_second = SMB0DAT;
            SMB0CN0_ACK = 0;
            SMB0CN0_STO = 1;
       }
       break;
  }
  //pin04 = 1;
  //pin05 = 1;
  SMB0CN0_SI = 0;
}



