/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-10-25     18452       the first version
 */
#ifndef APPLICATIONS_BSP_ADC128S102CIMTX_H_
#define APPLICATIONS_BSP_ADC128S102CIMTS_H_

#include "app_sys.h"



#define ADC128S_CS_PORT     SPI2_NSS_GPIO_Port
#define ADC128S_CS_PIN      SPI2_NSS_Pin

#define ADC128S_CS_SET(bit) if(bit) \
                            HAL_GPIO_WritePin(ADC128S_CS_PORT, ADC128S_CS_PIN, GPIO_PIN_SET);\
                            else    \
                            HAL_GPIO_WritePin(ADC128S_CS_PORT, ADC128S_CS_PIN, GPIO_PIN_RESET);


typedef enum
{
    ADC128S_Channel_1 = 0,
    ADC128S_Channel_2,
    ADC128S_Channel_3,
    ADC128S_Channel_4,
    ADC128S_Channel_5,
    ADC128S_Channel_6,
    ADC128S_Channel_7,
    ADC128S_Channel_8
}adc128s_channel_et;


#endif /* APPLICATIONS_BSP_ADC128S102CIMTX_H_ */
