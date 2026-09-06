#include "stm32f1xx_hal.h"
#include "adc.h"

// 定义一个临时通道配置结构（在函数外定义，避免反复分配栈空间）
static ADC_ChannelConfTypeDef sConfigTemp = {0};

/**
  * @brief  读取指定 ADC 通道的转换值（标准库风格动态切换通道）
  * @param  n: 通道编号 1~4，分别对应 PA2~PA5
  * @retval 12位 ADC 转换结果 (0~4095)
  */
uint16_t RP_GetValue(uint8_t n)
{
    uint32_t channel;
    
    // 1. 根据编号选择对应的 ADC 通道
    switch(n)
    {
        case 1: channel = ADC_CHANNEL_2; break;
        case 2: channel = ADC_CHANNEL_3; break;
        case 3: channel = ADC_CHANNEL_4; break;
        case 4: channel = ADC_CHANNEL_5; break;
        default: return 0;
    }

    // 2. 动态重配通道（每次读之前切换）
    sConfigTemp.Channel = channel;
    sConfigTemp.Rank = ADC_REGULAR_RANK_1;
    sConfigTemp.SamplingTime = ADC_SAMPLETIME_55CYCLES_5; // 与初始化保持一致
    if (HAL_ADC_ConfigChannel(&hadc2, &sConfigTemp) != HAL_OK)
    {
        return 0;   // 配置失败
    }

    // 3. 软件启动转换
    HAL_ADC_Start(&hadc2);

    // 4. 等待转换完成（超时 100ms）
    if (HAL_ADC_PollForConversion(&hadc2, 100) != HAL_OK)
    {
        return 0;
    }

    // 5. 读取并返回转换结果
    return (uint16_t)HAL_ADC_GetValue(&hadc2);
}


