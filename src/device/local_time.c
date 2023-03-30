/*
 * @Descripttion:
 * @version: 1.0
 * @Author: Lance
 * @Date: 2023-03-30 11:17:44
 * @LastEditors: Lance
 * @LastEditTime: 2023-03-30 16:23:47
 * @FilePath: /OneCloud/OneCloud-Control-Plan/src/device/local_time.c
 */
#include "device/local_time.h"
#include <time.h>
#include <sys/time.h>

// 获取当前系统的小时
int get_system_time_hour(void)
{
    time_t now;
    struct tm *tm_now;
    struct timeval tv_now;

    // 获取当前系统时间
    time(&now);
    tm_now = localtime(&now);
    gettimeofday(&tv_now, NULL);

    // printf("%04d-%02d-%02d %02d:%02d:%02d.%06ld\n",
    //        tm_now->tm_year + 1900, tm_now->tm_mon + 1, tm_now->tm_mday,
    //        tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec, tv_now.tv_usec);

    return tm_now->tm_hour;
}

void parse_time(const char *time_str, struct tm *tm_result)
{
    memset(tm_result, 0, sizeof(struct tm));
    strptime(time_str, "%H:%M:%S", tm_result);
}

int is_time_in_range(const struct tm *current_tm, const struct tm *start_tm, const struct tm *end_tm)
{
    int current_time_value = current_tm->tm_hour * 3600 + current_tm->tm_min * 60 + current_tm->tm_sec;
    int start_time_value = start_tm->tm_hour * 3600 + start_tm->tm_min * 60 + start_tm->tm_sec;
    int end_time_value = end_tm->tm_hour * 3600 + end_tm->tm_min * 60 + end_tm->tm_sec;

    if (start_time_value <= end_time_value)
    {
        return current_time_value >= start_time_value && current_time_value <= end_time_value;
    }
    else
    {
        return current_time_value >= start_time_value || current_time_value <= end_time_value;
    }
}