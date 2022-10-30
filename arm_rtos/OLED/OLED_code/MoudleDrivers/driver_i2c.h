#ifndef __DRIVER_I2C
#define __DRIVER_I2C

/*including*/
#include "stm32f1xx_hal.h"

//封装宏
#define SCL_PIN   GPIO_PIN_10
#define SDA_PIN   GPIO_PIN_11
#define SCL_GPIO_PORT   GPIOF
#define SDA_GPIO_PORT   GPIOF

//封装宏函数
#define SCL_L     HAL_GPIO_WritePin(SCL_GPIO_PORT,SCL_PIN,GPIO_PIN_RESET)
#define SCL_H     HAL_GPIO_WritePin(SCL_GPIO_PORT,SCL_PIN,GPIO_PIN_SET)
#define SDA_L     HAL_GPIO_WritePin(SDA_GPIO_PORT,SDA_PIN,GPIO_PIN_RESET)
#define SDA_H     HAL_GPIO_WritePin(SDA_GPIO_PORT,SDA_PIN,GPIO_PIN_SET)
#define SDA_IN    HAL_GPIO_ReadPin(SDA_GPIO_PORT,SDA_PIN)

//函数声明
void I2C_GPIO_Reinit();
void I2c_Delay(uint32_t t);
void I2c_Start(void);
void I2c_Stop(void);
int GetAck(void);
void I2c_Ack(void);
void I2c_NAck(void);
void I2c_WriteByte(uint8_t date);
void I2c_ReadByte(uint8_t *pdate);


#endif    /*__DRIVER_I2C*/
