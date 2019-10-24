#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "beep.h" 
#include "key.h"
#include "findpoint.h"


int main(void)
{								  
	u16 len,t,j,k,point=0;
	u16 i; 
	u16 times=0;
	u16 hand_data[1999]={0};    //存放1999个数据的数组
	float *smoy_p;
	
	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,115200); 	//串口初始化为115200
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口 
	
	j=0;
 	while(1)
	{
		if(USART_RX_STA&0x8000)
		{
			len=USART_RX_STA&0x3FFF;//得到此次接收到的数据长度
			printf("发送的长度为:\r\n%d\r\n",len);
			for(t=0,k=0;t<len;t++)
			{
				if(USART_RX_BUF[t]!=',')
				{
					k=k*10+USART_RX_BUF[t]-0x30;//截取字符串换算整型数组
				}else{
					hand_data[j++]=k;
					k=0;
				}
			}                  
			USART_RX_STA=0;
			if(j==1999){smoy_p=smoothdata(hand_data);}
			printf("发送了：%d个数据\r\n",j);
			for(i=0;i<j;i++)
			{
				printf("han_data:%d,%d\r\n",hand_data[i],i);
				if(j==1999){printf("smoy:%lf,%d\r\n",*(smoy_p+i),i);}
				LED1=!LED1;
				delay_ms(10);
			}
		}else
		{
			times++;
			if(times%200==0)
			{
				printf("请输入数据,以回车键结束\r\n");
				LED0=!LED0;
				delay_ms(20);
				LED0=!LED0;				
			}
			delay_ms(10);			
		}
		//point=findpoint(hand_data);
	}	
}

