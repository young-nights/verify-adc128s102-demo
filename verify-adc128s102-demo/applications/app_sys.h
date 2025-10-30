/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-10-21     18452       the first version
 */
#ifndef APPLICATIONS_SYS_APP_SYS_H_
#define APPLICATIONS_SYS_APP_SYS_H_

/* RTT实时操作系统的头文件 */
#include <rtthread.h>
#include <drv_common.h>
#include <board.h>
#include <rtdevice.h>
#include <rthw.h>
#include <rtdbg.h>
#include "main.h"
#include "rtdef.h"
#include "math.h"
#include <string.h>


typedef struct {
    rt_uint8_t   Empty;
    rt_uint16_t  kprintf_cnt;
    rt_uint16_t  ulog_cnt;
    //------------------------------------------------------------

}RecordStruct;
extern RecordStruct Record;




typedef enum
{
  OFF = 0u,
  ON
} SWITCH_T;



#endif /* APPLICATIONS_SYS_APP_SYS_H_ */
