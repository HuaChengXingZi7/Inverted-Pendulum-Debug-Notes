#include "stm32f1xx_hal.h"
#include "adc.h"
uint16_t AD_GetValue(void)
{
    // 软件触发转换（如果 Rank 已配置为 Channel 8，则无需重新配置通道）
    HAL_ADC_Start(&hadc1);
    
    // 等待转换完成（带超时）
    if (HAL_ADC_PollForConversion(&hadc1, 100) != HAL_OK)
    {
        return 0;
    }
    
    // 读取转换结果
    return (uint16_t)HAL_ADC_GetValue(&hadc1);

}

