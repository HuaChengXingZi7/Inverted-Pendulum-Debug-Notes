#include "encoder.h"
#include "tim.h"   // 包含 htim3 句柄

/**
  * @brief 编码器初始化（启动定时器计数）
  */
void Encoder_Init(void)
{
    // CubeMX 已经帮我们初始化了 TIM3
    // 只需要启动计数器即可
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
}

/**
  * @brief 读取编码器计数值，并清零
  * @return 上次计数周期内的脉冲增量（有符号，表示方向和步数）
  */
int16_t Encoder_Get(void)
{
    int16_t Temp;
    
    // 读取当前计数值（TIM3->CNT）
    Temp = (int16_t)(__HAL_TIM_GET_COUNTER(&htim3));
    
    // 清零计数器（注意：HAL 里要用宏来清零）
    __HAL_TIM_SET_COUNTER(&htim3, 0);
    
    return Temp;
}

