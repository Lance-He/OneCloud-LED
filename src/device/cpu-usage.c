/*
 * @Descripttion:
 * @version: 1.0
 * @Author: Lance
 * @Date: 2023-03-28 13:04:41
 * @LastEditors: Lance
 * @LastEditTime: 2023-03-28 14:06:22
 * @FilePath: /OneCloud/OneCloud-Control-Plan/src/device/cpu-usage.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "device/cpu-usage.h"

// 定义一个结构体，用于存储/proc/stat文件中的各个字段值
typedef struct cpu_stat_
{
    unsigned long user;    // 用户模式
    unsigned long nice;    // 低优先级的用户模式
    unsigned long system;  // 内核模式
    unsigned long idle;    // 空闲处理器时间
    unsigned long iowait;  // 等待I/O完成的时间
    unsigned long irq;     // 硬件中断时间
    unsigned long softirq; // 软件中断时间
    unsigned long steal;   // 被强制等待（involuntary wait）虚拟 CPU 的时间
} cpu_stat_t;

// 获取CPU信息的函数，参数为CPU信息结构体指针
void get_cpu_stat(cpu_stat_t *cpu_stat)
{
    FILE *fp;
    char buff[256];

    fp = fopen("/proc/stat", "r"); // 打开/proc/stat文件
    if (fp == NULL)
    {
        perror("fopen:");
        exit(1);
    }

    fgets(buff, sizeof(buff), fp); // 读取第一行内容，即总的CPU信息

    sscanf(buff, "cpu %lu %lu %lu %lu %lu %lu %lu %lu", &cpu_stat->user, &cpu_stat->nice, &cpu_stat->system, &cpu_stat->idle, &cpu_stat->iowait, &cpu_stat->irq, &cpu_stat->softirq, &cpu_stat->steal); // 解析各个字段

    fclose(fp);
}

// 计算CPU利用率的函数，返回一个double类型的值
double cal_cpu_usage()
{
    cpu_stat_t cpu_stat1;
    cpu_stat_t cpu_stat2;
    double cpu_usage;

    get_cpu_stat(&cpu_stat1); // 第一次采样
    sleep(1);                 // 间隔一秒钟
    get_cpu_stat(&cpu_stat2); // 第二次采样
    sleep(1);                 // 间隔一秒钟

    unsigned long total_time1 = cpu_stat1.user + cpu_stat1.nice + cpu_stat1.system + cpu_stat1.idle + cpu_stat1.iowait + cpu_stat1.irq + cpu_stat1.softirq + cpu_stat1.steal; // 第一次采样的总时间
    unsigned long total_time2 = cpu_stat2.user + cpu_stat2.nice + cpu_stat2.system + cpu_stat2.idle + cpu_stat2.iowait + cpu_stat2.irq + cpu_stat2.softirq + cpu_stat2.steal; // 第二次采样的总时间

    unsigned long used_time = (total_time2 - total_time1) - (cpu_stat2.idle - cpu_stat1.idle); // 两次采样之间的使用时间

    if ((total_time2 - total_time1) != 0)
        cpu_usage = (double)used_time / (total_time2 - total_time1) * 100.0; // 计算CPU利用率
    else
        cpu_usage = 0;

    return cpu_usage;
}

float get_cpu_usage(void)
{
    float value = 0;

    value = (float)cal_cpu_usage();
    // printf("CPU usage: %.2f%%\n", value); // 打印CPU利用率

    return value;
}