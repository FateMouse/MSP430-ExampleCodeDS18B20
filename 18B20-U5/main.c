#include  <msp430x14x.h>
#include  "12864.h"
#include  "18B20.h"


void chuli_float(float zhi)
{
  unsigned char temp1=0,temp2=0,temp3=0;
  temp1=(int)(zhi*10)/100;
  temp2=(int)zhi%10;
  temp3=(int)(zhi*10)%10;
  
  Display_number(1,3,temp1); 
  LCD_WDAT(temp2+48);

  Display(1,4,"."); 
  LCD_WDAT(temp3+48);
  
   Display(1,5,"℃"); 
}

void  main( void )
{
 float temperature;
  WDTCTL = WDTPW + WDTHOLD;        // Stop watchdog timer to prevent time out reset

  LCD_init();
  
  LCD_show();                     // 液晶初始化显示 
  
  while(1)
  {
    temperature=(float)Read_T()*0.065+0.05;   // 温度值
     chuli_float(temperature);
 
  }

}
