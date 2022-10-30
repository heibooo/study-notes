#ifndef __OLED_DRIVER
#define __OLED_DRIVER

/*including*/
#include "stm32f1xx_hal.h"
#define WRITE_ADDRESS 0x78
#define READ_ADDRESS  0x79

/*******************************************/
//1.OLED I2C驱动
/*******************************************/

void OLED_WriteCmd(uint8_t cmd);
void OLED_WriteDate(uint8_t pdate);
void OLED_WriteNByte(uint8_t *buf,uint8_t psize);

/*******************************************/
//2.OLED 基本命令
/*******************************************/
void Set_Contrast_Control(uint8_t cmd);

//开启/关闭全显	
#define  	EntireDisplayON()     OLED_WriteCmd(0xA5)
#define   EntireDisplayOFF()    OLED_WriteCmd(0xA4)

//阴码显示或阳码显示
#define   NormalDisplay()       OLED_WriteCmd(0xA6)
#define   InverseDisplay()			OLED_WriteCmd(0xA7)

//打开/关闭显示
#define   DisplayON           OLED_WriteCmd(0xAF);
#define   DisplayOFF					OLED_WriteCmd(0xAE);

/*******************************************/
//3.OLED 滚动命令功能函数
/*******************************************/
typedef enum
{
	H_RIGHT=0X26,
	H_LEFT=0X27,

}H_SCROLL_DIR;
void HorizontalScroll(H_SCROLL_DIR dir ,uint8_t startpage,uint8_t fr_time,uint8_t endpage);


typedef enum
{
    HV_RIGHT    = 0x29,
    HV_LEFT     = 0x2A,
}HV_SCROLL_DIR;     // 水平和垂直滚动的方向
/*
 *  函数名：OLED_HV_Scroll
 *  功能描述：让指定页的像素朝着设置的方向按设置的频率水平滚动且会将像素的行地址进行偏移offset这么多个单位
 *  输入参数：dir--->滚动方向：朝左或者朝右
 *            start--->起始页
 *            fr_time--->滚动间隔时间，每隔这么多帧水平偏移一列滚动
 *            end--->结束页
 *            offset--->行偏移单位
 *  输出参数：无
 *  返回值：无
*/
extern void OLED_HV_Scroll(HV_SCROLL_DIR dir, uint8_t start, uint8_t fr_time, uint8_t end, uint8_t offset);

/* 
    开始或者停止滚动
*/
#define SCROLL_ON()             OLED_WriteCmd(0x2F)
#define SCROLL_OFF()            OLED_WriteCmd(0x2E)

/*
 *  函数名：OLED_SetVScrollArea
 *  功能描述：设置OLED像素垂直滚动的区域
 *  输入参数：area-->顶行区域
 *            row_num--->滚动的行区域
 *  输出参数：无
 *  返回值：无
*/
extern void OLED_SetVScrollArea(uint8_t area, uint8_t row_num);

/* 3. 地址设置功能函数 */
typedef enum
{
    H_ADDR_MODE     = 0,    // 水平地址模式
    V_ADDR_MODE     = 1,    // 垂直地址模式
    PAGE_ADDR_MODE  = 2,    // 页地址模式
}MEM_MODE;  // 内存地址模式

/*
 *  函数名：OLED_SetColAddr_PAGE
 *  功能描述：设置OLED在页地址模式下的显示起始行地址
 *  输入参数：addr-->起始行地址
 *  输出参数：无
 *  返回值：无
*/
extern void OLED_SetColAddr_PAGE(uint8_t addr);

/*
 *  函数名：OLED_SetMemAddrMode
 *  功能描述：设置OLED的地址模式
 *  输入参数：mode-->地址模式：页地址模式、水平地址模式、垂直地址模式
 *  输出参数：无
 *  返回值：无
*/
extern void OLED_SetMemAddrMode(MEM_MODE mode);

/*
 *  函数名：OLED_SetColAddr_HV
 *  功能描述：设置OLED在水平地址模式或垂直地址模式下像素显示的起始行地址和结束行地址
 *  输入参数：start-->起始行地址
 *            end --->结束行地址
 *  输出参数：无
 *  返回值：无
*/
extern void OLED_SetColAddr_HV(uint8_t start, uint8_t end);

/*
 *  函数名：OLED_SetPageAddr_HV
 *  功能描述：设置OLED在水平地址模式或垂直地址模式下像素显示的起始页地址和结束页地址
 *  输入参数：start-->起始页地址
 *            end --->结束页地址
 *  输出参数：无
 *  返回值：无
*/
extern void OLED_SetPageAddr_HV(uint8_t start, uint8_t end);

/*
 *  函数名：OLED_SetPageAddr_PAGE
 *  功能描述：设置OLED在页地址模式下的显示起始页地址
 *  输入参数：addr-->起始页地址
 *  输出参数：无
 *  返回值：无
*/
extern void OLED_SetPageAddr_PAGE(uint8_t addr);

/* 4. 硬件配置功能函数 */
/*
 *  函数名：OLED_SetDispStartLine
 *  功能描述：设置OLED从第line行开始显示，即将默认的0行偏移至line那一行
 *  输入参数：line-->显示的起始行
 *  输出参数：无
 *  返回值：无
*/
extern void OLED_SetDispStartLine(uint8_t line);

/*
    行地址翻转或者不翻转
*/
#define OLED_SEG_REMAP()        OLED_WriteCmd(0xA1)
#define OLED_SEG_NOREMAP()      OLED_WriteCmd(0xA0)

/*
 *  函数名：OLED_SetMuxRatio
 *  功能描述：设置OLED复用率
 *  输入参数：ratio-->复用率值
 *  输出参数：无
 *  返回值：无
*/
extern void OLED_SetMuxRatio(uint8_t ratio);

/*
    COM引脚扫描方向正常扫描或者逆扫描
		表现为字符垂直反转，即一块显存以正向映射到COM上还是逆向
*/
#define OLED_SCAN_NORMAL()      OLED_WriteCmd(0xC0)    
#define OLED_SCAN_REMAP()       OLED_WriteCmd(0xC8)

/*
 *  函数名：OLED_SetDispOffset
 *  功能描述：设置OLED的COM引脚偏移值
 *  输入参数：offset-->COM偏移值
 *  输出参数：无
 *  返回值：无
*/
extern void OLED_SetDispOffset(uint8_t offset);

typedef enum
{
    COM_PIN_SEQ     = 0,
    COM_PIN_ALT     = 1,
}COM_PINS_MODE; // COM引脚属性
typedef enum
{
    COM_NOREMAP     = 0,
    COM_REMAP       = 1,
}COM_REMAP_STATE;   // COM引脚翻转

/*
 *  函数名：OLED_SetComConfig
 *  功能描述：设置OLED的COM引脚属性
 *  输入参数：mode-->COM引脚模式是连续的还是可选择的
 *            state-->COM引脚翻转与否
 *  输出参数：无
 *  返回值：无
*/
extern void OLED_SetComConfig(COM_PINS_MODE mode, COM_REMAP_STATE state);

/* 5. 时间设置功能函数 */
/*
 *  函数名：OLED_SetDCLK_Freq
 *  功能描述：设置OLED的扫描周期和晶振频率
 *  输入参数：div-->时钟分频系数
 *            freq-->晶振频率
 *  输出参数：无
 *  返回值：无
*/
extern void OLED_SetDCLK_Freq(uint8_t div, uint8_t freq);

/*
 *  函数名：OLED_SetPreChargePeriod
 *  功能描述：设置OLED的预充电周期
 *  输入参数：phase1-->预充电阶段1时间
 *            phase2-->预充电阶段2时间
 *  输出参数：无
 *  返回值：无
*/
extern void OLED_SetPreChargePeriod(uint8_t phase1, uint8_t phase2);
    
typedef enum
{
    LEVEL_0     = 0x00,
    LEVEL_1     = 0x20,
    LEVEL_2     = 0x30,
}VCOMH_LEVEL;   // 电压等级
/*
 *  函数名：OLED_SetVcomhLevel
 *  功能描述：设置OLED的电压等级
 *  输入参数：level-->电压等级
 *  输出参数：无
 *  返回值：无
*/
extern void OLED_SetVcomhLevel(VCOMH_LEVEL level);

/* 6. 电荷碰撞功能函数 */
typedef enum
{
    PUMP_DISABLE    = 0,
    PUMP_ENABLE     = 1,
}CHARGE_PUMP_STATE; // 打开或者关闭电荷泵
/*
 *  函数名：OLED_SetChargePump
 *  功能描述：打开或关闭OLED的电荷泵
 *  输入参数：state-->电荷泵打开或关闭
 *  输出参数：无
 *  返回值：无
*/
extern void OLED_SetChargePump(CHARGE_PUMP_STATE state);

/* 7. OLED初始化函数 */
extern void OLED_Init(void);

/* 8. 基本驱动功能函数 */
/*
 *  函数名：OLED_SetPosition
 *  功能描述：设置像素显示的起始页和起始列地址
 *  输入参数：page-->页地址模式下的起始页地址
 *            col-->页地址模式下的起始行地址
 *  输出参数：无
 *  返回值：无
*/
extern void OLED_SetPosition(uint8_t page, uint8_t col);

/*
 *  函数名：OLED_Clear
 *  功能描述：清屏函数
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
*/
extern void OLED_Clear(void);

/*
 *  函数名：OLED_PutChar
 *  功能描述：显示一个字符
 *  输入参数：page --> 起始页地址
 *            col --> 起始列地址
 *            c -->   显示的字符
 *  输出参数：无
 *  返回值：无
*/
extern void OLED_PutChar(uint8_t page, uint8_t col, char c);

/*
 *  函数名：OLED_PrintString
 *  功能描述：显示一个字符
 *  输入参数：page --> 起始页地址
 *            col --> 起始列地址
 *            c -->   显示的字符
 *  输出参数：无
 *  返回值：无
*/
extern void OLED_PrintString(uint8_t page, uint8_t col, char *str);

extern void OLED_PutString(uint8_t page,uint8_t col,char *string);

#endif /*__OLED_DRIVER*/
