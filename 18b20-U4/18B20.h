// P65 P66  数据口
#define DQ_H  P6OUT|=BIT5
#define DQ_L  P6OUT&=~BIT5

void delay_ms1(unsigned int t)
{
    while(t--)
    {
        _NOP();
     }
}

unsigned char Read_DS(void)
{
    unsigned char i=0 ,v=0;
    for(i=8;i>0;i--)
    {
         P6DIR|=BIT5;
         DQ_L;
         v>>=1;
         DQ_H;//setfree bus
         P6DIR&=~BIT5;
         if((P6IN&BIT5)==BIT5)
         {
            v|=0x80;        
         }
          delay_ms1(4);
     }
      P6DIR|=BIT5;
      return(v);
}


void Write_DS(unsigned char dat)
{
  unsigned char i;
  for(i=0;i<8;i++)
  {
       P6DIR|=BIT5;
       DQ_L;
       if(dat&0x01)
       {
          DQ_H;
        }
        else
        {
           DQ_L;
         }
         delay_ms1(5);
         DQ_H;
         dat>>=1;
  }
   delay_ms(5);
}


void DS18B20_INIT(void)
{
   P6DIR|=BIT5;
   DQ_H;                       //DQ复位
   delay_ms1(8);                //稍做延时
   DQ_L;                       //单片机将DQ拉低
   delay_ms1(80);               //精确延时 大于 480us
   DQ_H;                       //拉高总线
   P6DIR&=~BIT5;
   while((P6IN&BIT5)==BIT5);
   delay_ms1(20);               //一定要延时够
}
unsigned int Read_T(void)
{
        unsigned char a=0;
        unsigned int b=0;
        DS18B20_INIT();
        Write_DS(0xcc);     //Skip ROM        
        Write_DS(0x44);     //Start convert
        delay_ms1(200);
        DS18B20_INIT();
        Write_DS(0xcc);        
        Write_DS(0xbe);     //read temp
        a=Read_DS();        //顺序读取的
        b=Read_DS();
        b<<=8;
        b|=a;

        return (b);
}
