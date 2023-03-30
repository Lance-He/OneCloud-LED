/*
 * @Descripttion:
 * @version: 1.0
 * @Author: Lance
 * @Date: 2023-03-30 11:17:54
 * @LastEditors: Lance
 * @LastEditTime: 2023-03-30 14:55:39
 * @FilePath: /OneCloud/OneCloud-Control-Plan/inc/device/local_time.h
 */
#ifndef _LOCAL_TIME_H_
#define _LOCAL_TIME_H_
#include "main.h"

void parse_time(const char *time_str, struct tm *tm_result);
int is_time_in_range(const struct tm *current_tm, const struct tm *start_tm, const struct tm *end_tm);
int get_system_time_hour(void);
#endif