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
#include <ulog.h>
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
    HARD_PUMP_1 = 1,
    HARD_PUMP_2,
    HARD_PUMP_3,
    HARD_PUMP_4,
    HARD_PUMP_5,
    HARD_PUMP_6,
    HARD_PUMP_7,
    HARD_PUMP_8,
    HARD_PUMP_9,
    HARD_PUMP_10,
    HARD_PUMP_11,
    HARD_PUMP_12,
    HARD_PUMP_13,
    HARD_PUMP_14,
    HARD_PUMP_15,
    HARD_PUMP_16,
    HARD_PUMP_17,
    HARD_PUMP_18,
    HARD_PUMP_19,
    HARD_PUMP_20,
    HARD_FAN,
    HARD_VALVE_1,
    HARD_VALVE_2,
    HARD_VALVE_3,
    HARD_VALVE_4,
    HARD_VALVE_5,
    HARD_VALVE_6,
    HARD_VALVE_7,
    HARD_VALVE_8,
    HARD_VALVE_9,
    HARD_VALVE_10,
    HARD_VALVE_11,
    HARD_VALVE_12,
    HARD_VALVE_13,
    HARD_VALVE_14,
    HARD_VALVE_15,
    HARD_VALVE_16,
    HARD_VALVE_17,
    HARD_VALVE_18,
    HARD_VALVE_19,
    HARD_VALVE_20,
} HARD_NAME;



typedef enum
{
  OFF = 0u,
  ON
} SWITCH_T;


typedef enum
{
  clockwise = 0u,
  anticlockwise
} DIRECTION_T;

#endif /* APPLICATIONS_SYS_APP_SYS_H_ */
