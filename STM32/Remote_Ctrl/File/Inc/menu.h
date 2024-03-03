#ifndef MENU
#define MENU

#include "main.h"
#include "nrf24L01.h"
#include "string.h"
#include "Lcd.h"
#include "Gui.h"
#include "remote_ctrl.h"


void menu_init();
uint8_t main_menu();
void menu_dynamic_test();
void hanzi_test();

void wheel_mode(); //¶þ¼¶²Ëµ¥
void Author();
uint8_t Setting_mode();
void walk_mode();
void P_SET();
void I_SET();
void Ratio_set();

extern uint8_t menu1_to_menu2;
extern uint8_t setting_to_menu3;
extern float ctrl_P;
extern float ctrl_I;
extern float ctrl_ratio;
#endif