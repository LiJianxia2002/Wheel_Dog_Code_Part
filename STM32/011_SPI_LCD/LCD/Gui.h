#ifndef __GUI_H__
#define __GUI_H__

#include <main.h>
//设置光标位置
void GUI_DrawPoint(uint16_t x,uint16_t y,uint16_t color);

//用任意COLOR填充指定区域，SX、SY为起始坐标，EX、EY为终止坐标
void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color);

//写一个单独的英文字母
void LCD_ShowChar(uint16_t x,uint16_t y,uint16_t fc, uint16_t bc, uint8_t num,uint8_t size,uint8_t mode);

//写一个字符串,四个参数为：横坐标x，纵坐标y，字母尺寸size，字符串mode
//不论size填多大，字母大小都是固定的,汉字大小由16、24、32三种
void LCD_ShowString(uint16_t x,uint16_t y,uint8_t size,uint8_t *p,uint8_t mode);

uint32_t mypow(uint8_t m,uint8_t n);

//写数字，五个参数为：横坐标X，纵坐标Y，数字Num，数字长度Len，数字尺寸size
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size);

void LCD_ShowfloatNum(uint16_t x,uint16_t y,float num,uint8_t len,uint8_t size);//显示第一位小数,len 包括符号和小数点
//写尺寸为16X16的汉字
//六个参数：横坐标X，纵坐标Y，字体颜色Fc，背景颜色Bc，汉字串S，mode都填1，1表示不显示背景颜色，所以背景颜色可任意
void GUI_DrawFont16(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s,uint8_t mode);

//写尺寸为24X24的汉字
void GUI_DrawFont24(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s,uint8_t mode);

//写尺寸为32X32的汉字
void GUI_DrawFont32(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s,uint8_t mode);

//显示字符或汉字串，7个参数为：横坐标X，纵坐标Y，字体颜色Fc，背景颜色Bc，字符或汉字串str，字符尺寸size，mode都填1，1表示不显示背景颜色，所以背景颜色可任意
void Show_Str(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *str,uint8_t size,uint8_t mode);

//引用了上方的函数Show_Str（），作用：居中显示汉字串或字符串
//不论size填多大，字母大小都是固定的,汉字大小只能是16
void Gui_StrCenter(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *str,uint8_t size,uint8_t mode);

//显示40*40 QQ图片
void Gui_Drawbmp16(uint16_t x,uint16_t y,const unsigned char *p);

 //显示60*60 QQ图片
void Gui_Drawbmp32(uint16_t x,uint16_t y,const unsigned char *p); //显示60*60 QQ图片
#endif

