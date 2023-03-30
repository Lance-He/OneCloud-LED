/*
 * @Descripttion: 
 * @version: 1.0
 * @Author: Lance
 * @Date: 2023-03-28 09:48:57
 * @LastEditors: Lance
 * @LastEditTime: 2023-03-30 19:59:44
 * @FilePath: /OneCloud/OneCloud-Control-Plan/inc/os.h
 */
#ifndef __OS_H_
#define __OS_H_
#include <pthread.h>

void OS_START(void); //操作系统启动函数

// extern pthread_rwlock_t rwlock;
extern pthread_mutex_t serial1_mutex,serial2_mutex,serial3_mutex,serial4_mutex;    //定义互斥锁
extern pthread_mutex_t modbus_mutex;    //定义Modbus使用互斥锁
extern pthread_mutex_t condition_mlock; //条件变量互斥锁
extern pthread_cond_t cond;             //条件变量
extern pthread_mutex_t bacnet_mutex; //BACnet 互斥锁

#endif
