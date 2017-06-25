//����������STC15��Ƭ��ADC����ģ��
#include<STC15.h>

/*///////////////////////////////////////////////////////////////////////////////////
*��������ADC_Get
*�������ܣ�������STC15��Ƭ��ADC��ȡһ��ת�����
*�����б�
*   channel
*       �������ͣ�unsigned char������
*       ����������Ҫת����ͨ��
*����ֵ��unsigned int�����ݣ�ADCת���Ľ��
*////////////////////////////////////////////////////////////////////////////////////
unsigned int ADC_Get(unsigned char channel) 
{
	unsigned int temp = 0x0000;
	bit EADCBackup;
	EADCBackup = EADC;
	EADC = 0;
	
	P1ASF = 0x01 << channel;
	ADC_CONTR = 0xE8 | channel;	
	
	while(!(ADC_CONTR & 0x10));	//�ȴ�ת�����
	ADC_CONTR &= 0xEF;
	
	temp = ADC_RES;
	temp <<= 2;
	temp |= ADC_RESL;
	EADC = EADCBackup;
	return temp;
}
