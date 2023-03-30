/*
 * @Descripttion:
 * @version: 1.0
 * @Author: Lance
 * @Date: 2023-03-28 10:59:16
 * @LastEditors: Lance
 * @LastEditTime: 2023-03-30 16:20:32
 * @FilePath: /OneCloud/OneCloud-Control-Plan/inc/device/led.h
 */
#ifndef _LED_H_
#define _LED_H_
#include "main.h"

#define LED_RED_FILE "/sys/class/leds/onecloud:red:alive/brightness"
#define LED_BLUE_FILE "/sys/class/leds/onecloud:blue:alive/brightness"
#define LED_GREEN_FILE "/sys/class/leds/onecloud:green:alive/brightness"

#define LED_RED 0    // 红
#define LED_GREEN 1  // 绿
#define LED_BLUE 2   // 蓝
#define LED_YELLOW 3 // 黄
#define LED_CYAN 4   // 青
#define LED_PURPLE 5 // 紫
#define LED_WHITE 6  // 白
#define LED_OFF 7 //关闭灯光

uint8_t Get_LED_Value(char *LED_FILE);
uint8_t Change_LED_Status(char *LED_FILE, uint8_t change_value);
void Set_LED_Color(uint8_t LED_Color);
#endif