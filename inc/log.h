/*
 * @Descripttion:
 * @version: 1.0
 * @Author: Lance
 * @Date: 2022-07-06 13:28:38
 * @LastEditors: Lance
 * @LastEditTime: 2023-03-30 16:37:18
 * @FilePath: /OneCloud/OneCloud-Control-Plan/inc/log.h
 */
/**
 * Copyright (c) 2020 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>

#define LOG_VERSION "0.1.0"

#define LOG_USE_COLOR 1

typedef struct
{
  va_list ap;
  const char *fmt;
  const char *file;
  struct tm *time;
  const char *module;
  void *udata;
  int line;
  int level;
} log_Event;

typedef void (*log_LogFn)(log_Event *ev);
typedef void (*log_LockFn)(bool lock, void *udata);

enum
{
  LOG_TRACE,
  LOG_DEBUG,
  LOG_INFO,
  LOG_WARN,
  LOG_ERROR,
  LOG_FATAL
};

#if 0
#define log_trace(...) log_log(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...) log_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...) log_log(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...) log_log(LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) log_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...) log_log(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)
#else
#define filename(x) strrchr(x, '/') ? strrchr(x, '/') + 1 : x
#define log_trace(x, ...) log_log(LOG_TRACE, filename(__FILE__), x, __LINE__, __VA_ARGS__)
#define log_debug(x, ...) log_log(LOG_DEBUG, filename(__FILE__), x, __LINE__, __VA_ARGS__)
#define log_info(x, ...) log_log(LOG_INFO, filename(__FILE__), x, __LINE__, __VA_ARGS__)
#define log_warn(x, ...) log_log(LOG_WARN, filename(__FILE__), x, __LINE__, __VA_ARGS__)
#define log_error(x, ...) log_log(LOG_ERROR, filename(__FILE__), x, __LINE__, __VA_ARGS__)
#define log_fatal(x, ...) log_log(LOG_FATAL, filename(__FILE__), x, __LINE__, __VA_ARGS__)
#endif

const char *log_level_string(int level);
void log_set_lock(log_LockFn fn, void *udata);
void log_set_level(int level);
void log_set_quiet(bool enable);
int log_add_callback(log_LogFn fn, void *udata, int level);
int log_add_fp(FILE *fp, int level);

void log_log(int level, const char *file, const char *mod, int line, const char *fmt, ...);

#endif