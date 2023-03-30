/*
 * @Descripttion: 
 * @version: 1.0
 * @Author: Lance
 * @Date: 2022-10-18 16:59:57
 * @LastEditors: Lance
 * @LastEditTime: 2023-03-30 16:37:34
 * @FilePath: /OneCloud/OneCloud-Control-Plan/src/lib/log.c
 */
/*
 * Copyright (c) 2020 rxi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "log.h"
//#include "protocol/protocol-lib.h"
#include <string.h>
#include "stdint.h"

#define MAX_CALLBACKS 32

typedef struct
{
  log_LogFn fn;
  void *udata;
  int level;
} Callback;

static struct
{
  void *udata;
  log_LockFn lock;
  int level;
  bool quiet;
  Callback callbacks[MAX_CALLBACKS];
} L;

static const char *level_strings[] = {
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"};

#ifdef LOG_USE_COLOR
static const char *level_colors[] = {
    "\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"};
#endif

static void stdout_callback(log_Event *ev)
{
  char buf[16];
  buf[strftime(buf, sizeof(buf), "%H:%M:%S", ev->time)] = '\0';

#ifdef LOG_USE_COLOR
  fprintf(
      ev->udata, "%s %s%-5s\x1b[0m \x1b[90m%s:%d:%s:\x1b[0m ",
      buf, level_colors[ev->level], level_strings[ev->level],
      ev->file, ev->line, ev->module);
#else
  fprintf(
      ev->udata, "%s %-5s %s:%d:%s: ",
      buf, level_strings[ev->level], ev->file, ev->line, ev->module);

#endif
  vfprintf(ev->udata, ev->fmt, ev->ap);
  fprintf(ev->udata, "\n");
  fflush(ev->udata);
}

#if 0
static void HEXstdout_callback(log_Event *ev) // 16进制数组打印
{
  char buf[16];
  unsigned char *hex_buf = NULL;
  int addr;
  int len = 0;

  buf[strftime(buf, sizeof(buf), "%H:%M:%S", ev->time)] = '\0';

#ifdef LOG_USE_COLOR
  fprintf(
      ev->udata, "%s %s%-5s\x1b[0m \x1b[90m%s:%d:%s:\x1b[0m ",
      buf, level_colors[ev->level], level_strings[ev->level],
      ev->file, ev->line, ev->module);
#else
  fprintf(
      ev->udata, "%s %-5s %s:%d:%s: ",
      buf, level_strings[ev->level], ev->file, ev->line, ev->module);

#endif

  char *p_fmt = malloc(strlen(ev->fmt) + strlen(ev->ap));
  // printf("p_fmt addr:%d\n", p_fmt);
  if (p_fmt == NULL)
    return 0;
  memset(p_fmt, 0, strlen(ev->fmt) + 1);
  // printf("p_fmt addr:%d\n", p_fmt);
  strcpy(p_fmt, ev->fmt);
  // printf("p_fmt addr:%d\n", p_fmt);
  while (*(ev->fmt++) != '\0')
  {

    if (*(ev->fmt) == 'j') //%H代表数组指针地址
    {
      //addr = va_arg(ev->ap, int);
      //hex_buf = (unsigned char *)addr;
    }
    else if (*(ev->fmt) == 'L') //%L代表数组长度
    {
      len = va_arg(ev->ap, int);
      printf("len = %d\n", len);
    }

  }
  if (NULL == hex_buf)
    return;

  char *p_array = malloc(len * 3 + 1);
  memset(p_array, 0, len * 3 + 1);
  // printf("p_array addr:%d\n", p_array);

  // printf("%s\n",HEX2STRING(hex_buf[0]));
  for (int i = 0; i < len; i++)
  {
    sprintf(p_array, "%02X ", hex_buf[i]);
    p_array += 3;
  }
  p_array -= (len * 3);
  // printf("p_array addr:%d\n", p_array);

  printf("%s\n", p_array);

  // strcpy(p_fmt, strrpc(p_fmt, "%H", p_array));
  // // printf("p_fmt addr:%d\n", p_fmt);
  // //  printf("%s\n", p_fmt);

  // strcpy(p_fmt, strrpc(p_fmt, "%L", ""));
  // // printf("p_fmt addr:%d\n", p_fmt);

  // printf("\n%s\n", p_fmt);

  vfprintf(ev->udata, p_fmt, ev->ap);

  fprintf(ev->udata, "\n");
  fflush(ev->udata);

  free(p_array);
  free(p_fmt);
}
#endif
static void HEXstdout_callback(log_Event *ev) // 16进制数组打印
{
  char buf[1024];
  unsigned char *hex_buf = NULL;
  unsigned char *title = NULL;
  int addr;
  int len = 0;
  buf[strftime(buf, sizeof(buf), "%H:%M:%S", ev->time)] = '\0';

  // printf("00000\n");

#ifdef LOG_USE_COLOR
  fprintf(
      ev->udata, "%s %s%-5s\x1b[0m \x1b[90m%s:%d:%s:\x1b[0m ",
      buf, level_colors[ev->level], level_strings[ev->level],
      ev->file, ev->line, ev->module);
#else
  fprintf(
      ev->udata, "%s %-5s %s:%d:%s: ",
      buf, level_strings[ev->level], ev->file, ev->line, ev->module);
#endif
  // vfprintf(ev->udata, ev->fmt, ev->ap);
  // fprintf(ev->udata, "\n");
  // if (ev->fmt == '#') {
  //     hex_buf = va_arg(ev->ap,uint64_t);
  //     printf("buf addr:%p\n",hex_buf);
  //     ev->fmt++;
  // } else {
  //     printf("error 1.\n");
  //     return ;
  // }

  // if(ev->fmt == 'd') {
  //     len = va_arg(ev->ap,int);
  //     printf("buf len:%d\n",len);
  //     ev->fmt++;
  // }
  // printf("ddd:\n");
  while (*(ev->fmt++) != '\0')
  {
    // printf("%c",*(ev->fmt));
    if (*(ev->fmt) == 'p')
    {
      addr = va_arg(ev->ap, int);
      hex_buf = (unsigned char *)addr;
      // printf("buf len:%x\n",addr);
    }
    else if (*(ev->fmt) == 'd')
    {
      len = va_arg(ev->ap, int);
      // printf("buf len:%d\n",len);
    }
    else if (*(ev->fmt) == 's')
    {
      addr = va_arg(ev->ap, int);
      title = (unsigned char *)addr;
    }
  }

  if (NULL == title || NULL == hex_buf)
  {
    return;
  }

  fprintf(ev->udata, "%s(%d):", title, len);
  for (int32_t i = 0; i < len; i++)
  {
    fprintf(ev->udata, "%02X ", hex_buf[i]);
  }
  fprintf(ev->udata, "\n");
  fflush(ev->udata);
}
static void file_callback(log_Event *ev)
{
  char buf[64];
  buf[strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ev->time)] = '\0';
  fprintf(
      ev->udata, "%s %-5s %s:%d: ",
      buf, level_strings[ev->level], ev->file, ev->line);
  vfprintf(ev->udata, ev->fmt, ev->ap);
  fprintf(ev->udata, "\n");
  fflush(ev->udata);
}

static void lock(void)
{
  if (L.lock)
  {
    L.lock(true, L.udata);
  }
}

static void unlock(void)
{
  if (L.lock)
  {
    L.lock(false, L.udata);
  }
}

const char *log_level_string(int level)
{
  return level_strings[level];
}

void log_set_lock(log_LockFn fn, void *udata)
{
  L.lock = fn;
  L.udata = udata;
}

void log_set_level(int level)
{
  L.level = level;
}

void log_set_quiet(bool enable)
{
  L.quiet = enable;
}

int log_add_callback(log_LogFn fn, void *udata, int level)
{
  for (int i = 0; i < MAX_CALLBACKS; i++)
  {
    if (!L.callbacks[i].fn)
    {
      L.callbacks[i] = (Callback){fn, udata, level};
      return 0;
    }
  }
  return -1;
}

int log_add_fp(FILE *fp, int level)
{
  return log_add_callback(file_callback, fp, level);
}

static void init_event(log_Event *ev, void *udata)
{
  if (!ev->time)
  {
    time_t t = time(NULL);
    ev->time = localtime(&t);
  }
  ev->udata = udata;
}

void log_log(int level, const char *file, const char *mod, int line, const char *fmt, ...)
{
  log_Event ev = {
      .fmt = fmt,
      .file = file,
      .line = line,
      .level = level,
      .module = mod,
  };

  lock();

  if (!L.quiet && level >= L.level)
  {
    init_event(&ev, stderr);
    va_start(ev.ap, fmt);
     if (*fmt == '#')
      HEXstdout_callback(&ev);
    else
      stdout_callback(&ev);
    va_end(ev.ap);
  }

  for (int i = 0; i < MAX_CALLBACKS && L.callbacks[i].fn; i++)
  {
    Callback *cb = &L.callbacks[i];
    if (level >= cb->level)
    {
      init_event(&ev, cb->udata);
      va_start(ev.ap, fmt);
      cb->fn(&ev);
      va_end(ev.ap);
    }
  }

  unlock();
}