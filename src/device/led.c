/*
 * @Descripttion:
 * @version: 1.0
 * @Author: Lance
 * @Date: 2023-03-28 10:58:35
 * @LastEditors: Lance
 * @LastEditTime: 2023-03-30 16:19:47
 * @FilePath: /OneCloud/OneCloud-Control-Plan/src/device/led.c
 */
#include "device/led.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "log.h"

uint8_t Get_LED_Value(char *LED_FILE)
{
    FILE *fp;      // 文件指针
    int value = 0; // led 灯的值

    // 打开文件
    fp = fopen(LED_FILE, "r");
    if (fp == NULL)
    {
        perror("fopen");
        // exit(EXIT_FAILURE);
    }

    // 读取文件内容
    if (fscanf(fp, "%d", &value) != 1)
    {
        perror("fscanf");
        // exit(EXIT_FAILURE);
    }

    // 关闭文件
    fclose(fp);
    // 打印结果
    // printf("The value of the \" %s \" is %d\n.", LED_FILE, value);

    return value;
}

uint8_t Change_LED_Status(char *LED_FILE, uint8_t change_value)
{
    FILE *fp;                   // 文件指针
    int value = 0;              // led 灯的值
    uint8_t operate_status = 1; // 表示操作状态

    // 打开文件
    fp = fopen(LED_FILE, "r+");
    if (fp == NULL)
    {
        perror("fopen");
        operate_status = 0;
    }

    // 读取文件内容
    if (fscanf(fp, "%d", &value) != 1)
    {
        perror("fscanf");
        operate_status = 0;
    }

    if (change_value != value) // 如果读取的值和当前的值不同则修改
    {
        //因为发现玩客云好像是把灯状态存储文件存储在emmc里，并不是内核映射出来的，所有只针对发生变更才修改，减少emmc被写坏的概率。
        // log_debug("LED", "%s", "Change LED Status.");
        if (fprintf(fp, "%d", change_value) < 0) 
        {
            perror("fprintf");
            operate_status = 0;
        }
    }

    // 关闭文件
    fclose(fp);

    // 打印结果
    // printf("The value of the \" %s \" is %d\n.", LED_FILE, value);

    return operate_status;
}

void Set_LED_Color(uint8_t LED_Color)
{
    switch (LED_Color)
    {
    case LED_RED:
        Change_LED_Status(LED_RED_FILE, 1);
        Change_LED_Status(LED_GREEN_FILE, 0);
        Change_LED_Status(LED_BLUE_FILE, 0);
        break;

    case LED_GREEN:
        Change_LED_Status(LED_RED_FILE, 0);
        Change_LED_Status(LED_GREEN_FILE, 1);
        Change_LED_Status(LED_BLUE_FILE, 0);
        break;

    case LED_BLUE:
        Change_LED_Status(LED_RED_FILE, 0);
        Change_LED_Status(LED_GREEN_FILE, 0);
        Change_LED_Status(LED_BLUE_FILE, 1);
        break;

    case LED_YELLOW:
    {
        Change_LED_Status(LED_RED_FILE, 1);
        Change_LED_Status(LED_GREEN_FILE, 1);
        Change_LED_Status(LED_BLUE_FILE, 0);
    }
    break;

    case LED_CYAN:
        Change_LED_Status(LED_RED_FILE, 0);
        Change_LED_Status(LED_GREEN_FILE, 1);
        Change_LED_Status(LED_BLUE_FILE, 1);
        break;

    case LED_PURPLE:
    {
        Change_LED_Status(LED_RED_FILE, 1);
        Change_LED_Status(LED_GREEN_FILE, 0);
        Change_LED_Status(LED_BLUE_FILE, 1);
    }
    break;

    case LED_WHITE:
        Change_LED_Status(LED_RED_FILE, 1);
        Change_LED_Status(LED_GREEN_FILE, 1);
        Change_LED_Status(LED_BLUE_FILE, 1);
        break;

    case LED_OFF:
        Change_LED_Status(LED_RED_FILE, 0);
        Change_LED_Status(LED_GREEN_FILE, 0);
        Change_LED_Status(LED_BLUE_FILE, 0);
        break;

    default:
        Change_LED_Status(LED_RED_FILE, 1);
        Change_LED_Status(LED_GREEN_FILE, 1);
        Change_LED_Status(LED_BLUE_FILE, 1);
        break;
    }
}
