/*
 * @Descripttion:
 * @version: 1.0
 * @Author: Lance
 * @Date: 2021-07-07 09:52:14
 * @LastEditors: Lance
 * @LastEditTime: 2023-03-30 19:57:37
 */
#include <stdio.h>
#include "os.h"
#include <time.h>
#include "main.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/reboot.h>
#include <sys/times.h>
#include "log.h"
#include <stdlib.h>
#include <getopt.h>
#include "device/led.h"
#include "device/local_time.h"

struct tm start_tm, end_tm;

pthread_mutex_t MUTEX_LOG;
void log_lock(bool lock, void *udata);
void judge_bigend_littleend(void);
#if 1
int main(int argc, char *argv[])
{
    //sleep(10); //开启延迟10秒
    if (argc != 3)
    {
        printf("Usage: %s <start time> <end time>\n", argv[0]);
        printf("Time format: HH:MM:SS\nExample: ./main \"15:50:00\" \"15:51:00\"\n");
        return 1;
    }

    parse_time(argv[1], &start_tm);
    parse_time(argv[2], &end_tm);

    //=====================log初始化
    log_set_level(0);
    log_set_quiet(0);

    pthread_mutex_init(&MUTEX_LOG, NULL);
    log_set_lock(log_lock, &MUTEX_LOG);

    //======================各种初始化部分
    printf(L_GREEN "OneCloud\n" NONE);

    judge_bigend_littleend();
    //======================操作系统启动部分
    OS_START(); // 操作系统启动

    while (1)
    {
        sleep(100);
    }
}
#endif
void judge_bigend_littleend(void)
{
    union
    {
        int i;
        char c;
    } un;
    un.i = 1;

    printf("The system is ");
    if (un.c == 1)
    {
        printf(YELLOW "little-endian.\n" NONE);
    }
    else
    {
        printf(YELLOW "big-endian.\n" NONE);
    }
}

// os_error(__FILE__,__LINE__);
void os_error(char *files, int lines)
{
    printf(RED "The error occurred in the %d line of the %s file.\r\n" NONE, lines, files);
    exit(0);
}

void hardware_reboot() // 硬重启
{
    printf(RED "\r\n\r\nReboot device now.\r\n\r\n" NONE);
    reboot(RB_AUTOBOOT);
}

void log_lock(bool lock, void *udata)
{
    pthread_mutex_t *LOCK = (pthread_mutex_t *)(udata);
    if (lock)
        pthread_mutex_lock(LOCK);
    else
        pthread_mutex_unlock(LOCK);
}
