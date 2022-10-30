#include "driver_i2c.h"


void I2C_GPIO_Reinit()
{
	//定义初始化GPIO的结构体
	GPIO_InitTypeDef GPIO_Init_Struct ={0};
	
	//先将已经初始化的引脚去初始化
	HAL_GPIO_DeInit(SCL_GPIO_PORT,SCL_PIN);
	HAL_GPIO_DeInit(SDA_GPIO_PORT,SDA_PIN);
	
	//使能GPIOF组的时钟
	 __HAL_RCC_GPIOF_CLK_ENABLE();
	
	//设置GPIO的模式
	GPIO_Init_Struct.Mode=GPIO_MODE_OUTPUT_OD;
	GPIO_Init_Struct.Speed=GPIO_SPEED_FREQ_HIGH;
	
	//设置引脚并初始化
	GPIO_Init_Struct.Pin=SCL_PIN;
	HAL_GPIO_Init(SCL_GPIO_PORT,&GPIO_Init_Struct);
	
	GPIO_Init_Struct.Pin=SDA_PIN;
	HAL_GPIO_Init(SDA_GPIO_PORT,&GPIO_Init_Struct);

}
void I2c_Delay(uint32_t t)
{
	volatile uint32_t time =t;
	while(time--);
}

/*
*I2c开始信号：SCL为高电平时，SDA由高拉低
*/
void I2c_Start(void)
{
	
	SCL_H;
	SDA_H;
	I2c_Delay(100);
	SDA_L;
	I2c_Delay(100);
	
}

/*
*I2c停止信号：SCL为高电平时，SDA由低拉高
*/
void I2c_Stop(void)
{
	SDA_L;
	SCL_H;
	I2c_Delay(100);
	SDA_H;
	I2c_Delay(100);
}

/*
*I2C获取应答信号：在传输完一个字节后，接收应答信号
*传输完一个字节后，将SDA拉高，然后通过检测SDA	是否被拉低
*来确认是否有应答
*输入参数：无
*输出参数：无
*返回值：成功收到应答：0   未应答：-1
*/
int GetAck(void)
{
	SCL_L;
	SDA_H;
	I2c_Delay(100);
	SCL_H;
	int i=0;
	while(SDA_IN!=0)
	{
		i++;
		if(i==100)
		{
			SCL_L;
			return -1;
		}
		I2c_Delay(10);
	}
	SCL_L;
	return 0;
}

/*
*发出应答信号: 主机读数据时，一个字节结束后，主机将SDA由高拉低，发出应答
*输入：无
*输出：无
*返回值：无
*/
void I2c_Ack(void)
{
	SCL_L;
	SDA_H;
	I2c_Delay(100);
	SCL_H;
	SDA_L;
}
/*
*发出非应答信号：一个字节结束后，主机释放SDA，SDA不被拉低
*/
void I2c_NAck(void)
{
	SCL_L;
	SDA_H;
	I2c_Delay(100);
	SCL_H;
}

/*
*描述：通过I2C写一个字节的数据
*输入：date 
*输出：无
*返回值：无
*/
void I2c_WriteByte(uint8_t date)
{
	int i=0;
	for(i=0;i<8;i++)
	{
		SCL_L;    //拉低时钟，准备数据
		I2c_Delay(100);
		if(0x80&date)
		{
			SDA_H;
		}
		else
		{
			SDA_L;
		}
		date<<=1;
		SCL_H;    //数据准备好了，拉高时钟，传输数据
		//I2c_Delay(100);
	}
	GetAck();
}


/*
*描述：通过I2c读一个字节的数据
*输入：无
*输出：pdate 读到的数据地址
*/
void I2c_ReadByte(uint8_t *pdate)
{
	int i=0;
	uint8_t tmp=0;
	for(i=0;i<8;i++)
	{
		SCL_L;
		I2c_Delay(100);   //SCL为低电平时，SDA准备数据
		SCL_H;
		I2c_Delay(100);   //SCL为高电平时，SDA读取数据
		if(SDA_IN)
		{
			tmp++;
		}
		else
		{
			tmp=tmp;
		}
		tmp<<=1;
	}
	//接收完成一个Byte，发出应答信号
	I2c_Ack();
	*pdate=tmp;
	
}






