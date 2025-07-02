#include <REG52.H>

sbit keyL = P0^4;
sbit keyR = P0^6;

void UsartInit(){
  SCON = 0x50;
  TMOD = 0x20;
  PCON = 0x80;
  TH1 = 0xFA;
  TL1 = TH1;
  TR1 = 1;
}

void sendByte(unsigned char b){
  SBUF = b;
  while (!TI);
  TI = 0;
}

void main(){
  unsigned char Zkey[8] = 0x00;
  unsigned char Xkey[8] = 0x00;
  unsigned char BothKey[8] = 0x00;
  unsigned char NoKey[8] = 0x00;
  unsigned char i;

  Zkey[2] = 0x1D;
  Xkey[2] = 0x1B;
  BothKey[2] = 0x1D;
  BothKey[3] = 0x1B;
  
  UsartInit();

  while(1){
    if(keyL==1 & keyR==1){
      for(i=0;i<8;i++){
        sendByte(BothKey[i]);
      }
    }else if (keyL==1)
    {
      for(i=0;i<8;i++){
        sendByte(Zkey[i]);
      }
    }else if (keyR==1)
    {
      for(i=0;i<8;i++){
        sendByte(Xkey[i]);
      }
    }else{
      for(i=0;i<8;i++){
        sendByte(NoKey[i]);
      }
    }
  }
}