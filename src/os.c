/*
 * @Descripttion:
 * @version:
 * @Author: sueRimn
 * @Date: 2021-07-07 09:52:14
 * @LastEditors: Lance
 * @LastEditTime: 2023-03-30 20:32:44
 */
#include "os.h"
#include "stdio.h"
#include "stdint.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
// #include "tcpclient_nblock.h"
#include <errno.h>
#include "device/led.h"
#include "device/cpu-usage.h"
#include "device/local_time.h"

/**********信号量/互斥锁等**********/
// pthread_rwlock_t rwlock; // 声明读写锁

// pthread_rwlock_rdlock(&rwlock);
// pthread_rwlock_unlock(&rwlock);

// pthread_rwlock_wrlock(&rwlock);
// pthread_rwlock_unlock(&rwlock);

/**********任务的函数声明**********/
int thread_create(pthread_t *id, void *(*callback)(void *), void *arg, size_t ssize); // 线程创建

void OS_TEST_TASK(void);
void OS_Control_CPU_TASK(void);

pthread_t Monitoring_cpu_pid, // 线程pid
    test_task_pid;

#define Pthread_4MB_SIZE 4194304
#define Pthread_8MB_SIZE 4194304 * 2
#define Pthread_16MB_SIZE 4194304 * 4

/**********启动函数**********/
void OS_START(void) // 操作系统启动函数
{
    int ret = 0;

    ret = thread_create(&test_task_pid, NULL, (void *)OS_TEST_TASK, (size_t)NULL);
    if (ret != 0)
        os_error(__FILE__, __LINE__);

    ret = thread_create(&Monitoring_cpu_pid, NULL, (void *)OS_Control_CPU_TASK, (size_t)NULL);
    if (ret != 0)
        os_error(__FILE__, __LINE__);
}

void OS_TEST_TASK(void)
{

    sleep(1);
    while (1)
    {
        //OS_Control_CPU_TASK();
        sleep(10);
    }
}

void OS_Control_CPU_TASK(void) // 获取当前CPU使用率后调用LED显示不同颜色
{
    // 控制玩客云的灯光显示
    while (1)
    {
        time_t current_time = time(NULL);
        struct tm current_tm = *localtime(&current_time);
        if (is_time_in_range(&current_tm, &start_tm, &end_tm))
        {
            Set_LED_Color(LED_OFF);
            sleep(1);
        }
        else
        {
            switch (((int)get_cpu_usage()) / 10u) // 根据CPU的使用率刷新灯光
            {
            case 0:
            case 1:
                Set_LED_Color(LED_WHITE);
                break;

            case 2:
            case 3:
                Set_LED_Color(LED_CYAN);
                break;

            case 4:
            case 5:
                Set_LED_Color(LED_YELLOW);
                break;

            case 6:
            case 7:
                Set_LED_Color(LED_PURPLE);
                break;

            case 8:
            case 9:
            case 10:
                Set_LED_Color(LED_RED);
                break;

            default:
                Set_LED_Color(LED_RED);
                break;
            }
        }
    }
}
int thread_create(pthread_t *id, void *(*callback)(void *), void *arg, size_t ssize)
{
    pthread_attr_t thread_attr;
    size_t stack_size;
    int err;

    err = pthread_attr_init(&thread_attr);
    if (err != 0)
    {
        perror("pthread_attr_init err");
    }

    // 设置分离状态
    err = pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
    if (err != 0)
    {
        perror("pthread_attr_setdetachstate PTHREAD_CREATE_DETACHED err");
    }

    if (ssize != 0) // 设置线程大小
    {
        // 设置当前的线程的大小
        err = pthread_attr_setstacksize(&thread_attr, ssize);
        if (err != 0)
        {
            perror("pthread_attr_setstacksize err");
        }
    }

    // 得到当前的线程栈大小
    err = pthread_attr_getstacksize(&thread_attr, &stack_size);
    if (err != 0)
    {
        perror("pthread_attr_getstacksize err");
    }

    printf("stack_size default is %dMB\r\n", stack_size / 1024 / 1024); // default is 8M BYTE

    err = pthread_create((pthread_t *)id, &thread_attr, arg, callback);
    pthread_attr_destroy(&thread_attr);

    return err;
}

