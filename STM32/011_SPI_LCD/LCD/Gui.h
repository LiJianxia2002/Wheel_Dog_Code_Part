#ifndef __GUI_H__
#define __GUI_H__

#include <main.h>
//���ù��λ��
void GUI_DrawPoint(uint16_t x,uint16_t y,uint16_t color);

//������COLOR���ָ������SX��SYΪ��ʼ���꣬EX��EYΪ��ֹ����
void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color);

//дһ��������Ӣ����ĸ
void LCD_ShowChar(uint16_t x,uint16_t y,uint16_t fc, uint16_t bc, uint8_t num,uint8_t size,uint8_t mode);

//дһ���ַ���,�ĸ�����Ϊ��������x��������y����ĸ�ߴ�size���ַ���mode
//����size������ĸ��С���ǹ̶���,���ִ�С��16��24��32����
void LCD_ShowString(uint16_t x,uint16_t y,uint8_t size,uint8_t *p,uint8_t mode);

uint32_t mypow(uint8_t m,uint8_t n);

//д���֣��������Ϊ��������X��������Y������Num�����ֳ���Len�����ֳߴ�size
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size);

void LCD_ShowfloatNum(uint16_t x,uint16_t y,float num,uint8_t len,uint8_t size);//��ʾ��һλС��,len �������ź�С����
//д�ߴ�Ϊ16X16�ĺ���
//����������������X��������Y��������ɫFc��������ɫBc�����ִ�S��mode����1��1��ʾ����ʾ������ɫ�����Ա�����ɫ������
void GUI_DrawFont16(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s,uint8_t mode);

//д�ߴ�Ϊ24X24�ĺ���
void GUI_DrawFont24(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s,uint8_t mode);

//д�ߴ�Ϊ32X32�ĺ���
void GUI_DrawFont32(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s,uint8_t mode);

//��ʾ�ַ����ִ���7������Ϊ��������X��������Y��������ɫFc��������ɫBc���ַ����ִ�str���ַ��ߴ�size��mode����1��1��ʾ����ʾ������ɫ�����Ա�����ɫ������
void Show_Str(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *str,uint8_t size,uint8_t mode);

//�������Ϸ��ĺ���Show_Str���������ã�������ʾ���ִ����ַ���
//����size������ĸ��С���ǹ̶���,���ִ�Сֻ����16
void Gui_StrCenter(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *str,uint8_t size,uint8_t mode);

//��ʾ40*40 QQͼƬ
void Gui_Drawbmp16(uint16_t x,uint16_t y,const unsigned char *p);

 //��ʾ60*60 QQͼƬ
void Gui_Drawbmp32(uint16_t x,uint16_t y,const unsigned char *p); //��ʾ60*60 QQͼƬ
#endif

