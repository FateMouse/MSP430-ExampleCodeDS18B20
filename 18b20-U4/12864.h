
#define  LCD_RS_High   P6OUT|=0x04   // LCD_RS  �ߵ�ƽ   ��ʾ����         P62
#define  LCD_RS_Low    P6OUT&=0xfb   // LCD_RS  �͵�ƽ   ָ������   


 
#define  LCD_RW_High   P6OUT|=0x10   // LCD_RW  �ߵ�ƽ   ���ݶ���DB0_DB7   P64
#define  LCD_RW_Low    P6OUT&=0xef   // LCD_RW  �͵�ƽ   DB0_DB7 ����д��IR DR


#define  LCD_EN_High   P6OUT|=0x08   // LCD_EN  �ߵ�ƽ   ����Ч            P63
#define  LCD_EN_Low    P6OUT&=0xf7   // LCD_EN  �͵�ƽ   ʹ���ź�

#define LCD_PSB_High   P3OUT|=0x01;  //  ����   �ߵ�ƽ
#define LCD_PSB_Low    P3OUT&=0xfe;  //  ����   �͵�ƽ    P30

//P67 ����

void delay_ms(unsigned int timer)
{
  unsigned int i;
    for(i=0;i<1000;i--)
       for(;timer>0;timer--)
         ;
}


unsigned char lcd_busy()
 {                          
    unsigned char result;
    
     P4DIR=0x00;    
     LCD_RS_Low;          //  ָ������
     LCD_RW_High;
     LCD_EN_High;
        

     result = P4IN&0x80;   // ��ȡ���ݿ�����
     LCD_EN_Low; 
     
     return(result); 
 }
/*д���Һ��*/
void LCD_WCMD(unsigned char cmd)
{                          
  while(lcd_busy());

     P4DIR=0xff;          // OUT;
     LCD_RS_Low;          //  ָ������
     LCD_RW_Low;
     LCD_EN_High;
     P4OUT = cmd;
    

     LCD_EN_Low; 
}
/*д���ݵ�Һ��*/
void LCD_WDAT(unsigned char dat)
{                          
   while(lcd_busy());
   
     P4DIR=0xff;           // OUT;
     LCD_RS_High;          //  ����
     LCD_RW_Low;
     
     LCD_EN_High;
     P4OUT = dat;
     
    
     LCD_EN_Low; 
}
/*��ʾ���ַ���*/
void Display(unsigned char X,unsigned char Y,unsigned char *string)
{

   if (X==0)
     {X=0x80;}
   else if (X==1)
     {X=0x90;}
   else if (X==2)
     {X=0x88;}
   else if (X==3)
     {X=0x98;}

     LCD_WCMD(X+Y);
   
   while(*string )
    {                         //��ʾ�ַ�
      LCD_WDAT(*string++);
    }

}
void Display_number(unsigned char X,unsigned char Y,unsigned char number)
{
    if (X==0)
     {X=0x80;}
   else if (X==1)
     {X=0x90;}
   else if (X==2)
     {X=0x88;}
   else if (X==3)
     {X=0x98;}

     LCD_WCMD(X+Y);
     LCD_WDAT(number+48);
}

/*Һ����ʼ��*/
void LCD_init()
{
  
   P6DIR=0x1c;
   P3DIR=0x01;
   LCD_PSB_High;                 // Һ����ʾ  ���ڷ�ʽ  
   LCD_WCMD(0x34);               //����ָ�����
   LCD_WCMD(0x30);               //����ָ�����
   LCD_WCMD(0x0C);               //��ʾ�����ع��
   LCD_WCMD(0x01);               //���LCD����ʾ����
      
}
void LCD_show()
{
  Display(0,2, "����ģ��");    
  Display(1,0, "�¶�1:");     
  Display(2,0, "�¶�2:");
  Display(3,5, "numen");

}
  
  
  
