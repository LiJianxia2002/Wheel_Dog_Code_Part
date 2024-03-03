#ifndef MENU
#define MENU
#include "Lcd.h"
#include "Gui.h"

#include "string.h"
#include "stdlib.h"
#include "usart.h"

#define BG LIGHTBLUE
uint8_t menu_Settings();
uint8_t menu_PID();
uint8_t menu1();
uint8_t PPP();
uint8_t III();
uint8_t DDD();
void remote_ctrl();

extern uint8_t menu2;
extern uint8_t menu3;

#endif