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



struct adc128s102_dev
{
    struct rt_device parent;    //设备驱动框架的基类
    struct rt_spi_device *spi_dev;
    rt_mutex_t lock;
};

static struct adc128s102_dev _adc128s;




/* 对外注册函数：spi_bus_name = "spi1" 等，dev_name = "adc128s102" */
int adc128s102_init(const char *spi_bus_name, const char *dev_name)
{
    rt_memset(&_adc128s, 0, sizeof(_adc128s));

    _adc128s.spi_dev = (struct rt_spi_device *)rt_device_find(spi_bus_name);
    if (!_adc128s.spi_dev)
    {
        LOG_E("spi bus %s not found!", spi_bus_name);
        return -RT_ERROR;
    }

    _adc128s.lock = rt_mutex_create("adc_lock", RT_IPC_FLAG_FIFO);
    if (!_adc128s.lock)
        return -RT_ENOMEM;

    _adc128s.parent.type    = RT_Device_Class_Miscellaneous;
    _adc128s.parent.init    = _adc_init;
    _adc128s.parent.read    = _adc_read;
    _adc128s.parent.user_data = RT_NULL;

    rt_device_register(&_adc.parent, dev_name, RT_DEVICE_FLAG_RDWR);
    return RT_EOK;
}
INIT_DEVICE_EXPORT(adc128s102_init);   /* 如用自动初始化，可打开 */



