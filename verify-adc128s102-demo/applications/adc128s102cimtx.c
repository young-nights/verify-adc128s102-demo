/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-10-25     18452       the first version
 */


#include <adc128s102cimtx.h>




/* PI0~PI3 引脚定义 */
#define ADC128S102_CS_PIN   GET_PIN(I, 0)   /* PI0 片选 */
#define ADC128S102_SCK_PIN  GET_PIN(I, 1)   /* PI1 时钟 */
#define ADC128S102_MISO_PIN GET_PIN(I, 2)   /* PI2 主机输入 */
#define ADC128S102_MOSI_PIN GET_PIN(I, 3)   /* PI3 主机输出 */


/* 本地函数：软件 SPI 读写 16 位（Mode1：CPOL=0 CPHA=1） */
static rt_uint16_t soft_spi_xfer16(rt_uint16_t tx)
{
    rt_uint16_t rx = 0;
    int i;
    for (i = 15; i >= 0; --i)
    {
        /* 先置数据 */
        if (tx & (1u << i))
            rt_pin_write(ADC128S102_MOSI_PIN, PIN_HIGH);
        else
            rt_pin_write(ADC128S102_MOSI_PIN, PIN_LOW);

        rt_thread_mdelay(1);               /* 短延时，>50 ns 即可 */

        /* 上升沿移位（Mode1 采样在下降沿，移位在上升沿） */
        rt_pin_write(ADC128S102_SCK_PIN, PIN_HIGH);
        rt_thread_mdelay(1);

        /* 下降沿采样 MISO */
        if (rt_pin_read(ADC128S102_MISO_PIN) == PIN_HIGH)
            rx |= (1u << i);

        rt_pin_write(ADC128S102_SCK_PIN, PIN_LOW);
        rt_thread_mdelay(1);
    }
    return rx;
}



/* 读一次 ADC，channel 0~7 */
static rt_uint16_t adc128s102_read_raw(rt_uint8_t ch)
{
    rt_uint16_t tx, rx;
    RT_ASSERT(ch <= 7);


    tx = (ch & 0x07) << 11;

    rt_pin_write(ADC128S102_CS_PIN, PIN_LOW);   /* 选中 */
    rx = soft_spi_xfer16(tx);                   /* 双向 16 时钟 */
    rt_pin_write(ADC128S102_CS_PIN, PIN_HIGH);  /* 释放 */

    /* ADC128S102 回传格式：高 4 位无效 + 12 位数据 */
    return (rx & 0x0FFF);
}


/* RT-Thread 设备接口 ----------------------------------------------------*/
/* 引脚初始化，上电调用一次 */
void adc128s102_init(void)
{
    rt_pin_mode(ADC128S102_CS_PIN,   PIN_MODE_OUTPUT);
    rt_pin_mode(ADC128S102_SCK_PIN,  PIN_MODE_OUTPUT);
    rt_pin_mode(ADC128S102_MOSI_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(ADC128S102_MISO_PIN, PIN_MODE_INPUT);

    rt_pin_write(ADC128S102_CS_PIN,  PIN_HIGH);
    rt_pin_write(ADC128S102_SCK_PIN, PIN_LOW);
}



/* 把 12-bit 原始码值转成电压，单位 mV，Vref = 5 000 mV */
static rt_uint16_t adc128s102_raw_to_mv(rt_uint16_t raw)
{
    /* 避免溢出：先乘 5000 再除 4095 */
    return (rt_uint32_t)raw * 5000 / 4095;
}

/* 如果想直接得到浮点伏特，再包一层 */
static float adc128s102_raw_to_volt(rt_uint16_t raw)
{
    return raw * (5.0f / 4095.0f);
}


void adc128s102_thread_entry(void *parameter)
{
    adc128s102_init();

    while (1)
    {
        rt_uint16_t raw = adc128s102_read_raw(1);      /* 通道 1 */
        rt_uint16_t mv  = adc128s102_raw_to_mv(raw);   /* 整数毫伏 */
        float       v   = adc128s102_raw_to_volt(raw); /* 浮点伏特 */

        rt_kprintf("CH1 raw = %d  ->  %d mV  (%.3f V)\n", raw, mv, v);
        rt_thread_mdelay(100);
    }
}


static rt_thread_t adc128s_Task_Handle = RT_NULL;
int adc128s102_thread_init(void)
{
    adc128s_Task_Handle = rt_thread_create("adc128s102_thread_entry",adc128s102_thread_entry, RT_NULL,1024,9, 100);
    if(adc128s_Task_Handle != RT_NULL){
        LOG_I("LOG:%d. adc128s102_thread_entry is succeed!",Record.ulog_cnt++);
        rt_thread_startup(adc128s_Task_Handle);
    }
    else{
        LOG_E("LOG:%d. adc128s102_thread_entry is failed!",Record.ulog_cnt++);
    }

    return RT_EOK;
}
INIT_ENV_EXPORT(adc128s102_thread_init);






