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
	u16 hand_data[1999]={0};    //���1999�����ݵ�����
	float *smoy_p;
	
	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ� 
	
	j=0;
 	while(1)
	{
		if(USART_RX_STA&0x8000)
		{
			len=USART_RX_STA&0x3FFF;//�õ��˴ν��յ������ݳ���
			printf("���͵ĳ���Ϊ:\r\n%d\r\n",len);
			for(t=0,k=0;t<len;t++)
			{
				if(USART_RX_BUF[t]!=',')
				{
					k=k*10+USART_RX_BUF[t]-0x30;//��ȡ�ַ���������������
				}else{
					hand_data[j++]=k;
					k=0;
				}
			}                  
			USART_RX_STA=0;
			if(j==1999){smoy_p=smoothdata(hand_data);}
			printf("�����ˣ�%d������\r\n",j);
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
				printf("����������,�Իس�������\r\n");
				LED0=!LED0;
				delay_ms(20);
				LED0=!LED0;				
			}
			delay_ms(10);			
		}
		//point=findpoint(hand_data);
	}	
}

