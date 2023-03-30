/*
 * @Descripttion:
 * @version:
 * @Author: sueRimn
 * @Date: 2021-07-07 09:52:14
 * @LastEditors: Lance
 * @LastEditTime: 2023-03-30 14:57:22
 */
#ifndef __MAIN_H_
#define __MAIN_H_

#include <sys/times.h>
#include <time.h>
#include "stdint.h"
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>
#include <math.h>

#define G24B 1 // 4网口4串口
#define G12A 2 // 2网口1串口

#define NONE "\e[0m"
#define BLACK "\e[0;30m"
#define L_BLACK "\e[1;30m"
#define RED "\e[0;31m"
#define L_RED "\e[1;31m"
#define GREEN "\e[0;32m"
#define L_GREEN "\e[1;32m"
#define BROWN "\e[0;33m"
#define YELLOW "\e[1;33m"
#define BLUE "\e[0;34m"
#define L_BLUE "\e[1;34m"
#define PURPLE "\e[0;35m"
#define L_PURPLE "\e[1;35m"
#define CYAN "\e[0;36m"
#define L_CYAN "\e[1;36m"
#define GRAY "\e[0;37m"
#define WHITE "\e[1;37m"

#define BOLD "\e[1m"
#define UNDERLINE "\e[4m"
#define BLINK "\e[5m"
#define REVERSE "\e[7m"
#define HIDE "\e[8m"
#define CLEAR "\e[2J" 25
#define CLRLINE "\r\e[K" // or "\e[1K\r"

#define DEBUG_INFO(fmt, args...) \
    ;                            \
    ; // printf("\033[33m[%s:%d]\033[0m "#fmt"\r\n", __FUNCTION__, __LINE__, ##args)
#define MQTT_DEBUG(fmt, args...) printf("\033[33m[MQTT]\033[0m " #fmt "\r\n", ##args)
#define JSON_DEBUG(fmt, args...) printf("\033[33m[json]\033[0m " #fmt "\r\n", ##args)
#define WEBSOCKET_DEBUG(fmt, args...) printf("\033[33m[websocket]\033[0m " #fmt "\r\n", ##args)
#define MODBUS_DEBUG(fmt, args...) printf("\033[33m[modbus]\033[0m " #fmt "\r\n", ##args)
#define WIFI_DEBUG(fmt, args...) printf("\033[33m[wifi]\033[0m " #fmt "\r\n", ##args)
#define BACNET_IP_DEBUG(fmt, args...) printf("\033[33m[BACnet-IP]\033[0m " #fmt "\r\n", ##args)
#define SIM_MODULE_DEBUG(fmt, args...) printf("\033[33m[SIM-MODULE]\033[0m " #fmt "\r\n", ##args)
#define SYSTEM_DEBUG(fmt, args...) printf("\033[33m[SYSTEM]\033[0m " #fmt "\r\n", ##args)

void os_error(char *files, int lines);

void hardware_reboot(); //硬重启

extern struct tm start_tm, end_tm;

#endif