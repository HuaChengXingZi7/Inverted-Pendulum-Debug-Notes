#include "stm32f1xx_hal.h"                   // Device header

uint8_t Key_Num;

static uint8_t key_filter[4] = {0};
static uint8_t key_last[4] = {0};
static uint8_t key_stable[4] = {0};    // 当前稳定状态（1按下，0松开）
static uint8_t key_triggered[4] = {0}; // 是否已触发（防止重复）
#define KEY_DEBOUNCE_MS  20            // 消抖时间，可调（建议5~15）


void Key_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;      
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; 
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);	
}

uint8_t Key_GetNum(void)
{
	uint8_t Temp;
	if (Key_Num)
	{
		Temp = Key_Num;
		Key_Num = 0;
		return Temp;
	}
	return 0;
}

uint8_t Key_GetState(void)
{
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == GPIO_PIN_RESET)
	{
		return 1;
	}
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) == GPIO_PIN_RESET)
	{
		return 2;
	}
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_RESET)
	{
		return 3;
	}
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == GPIO_PIN_RESET)
	{
		return 4;
	}	
	return 0;
}

void Key_Tick(void)
{
    uint8_t pins[4];
    pins[0] = !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10);
    pins[1] = !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11);
    pins[2] = !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11);
    pins[3] = !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12);
    
    for (uint8_t i = 0; i < 4; i++) {
        if (pins[i] == key_last[i]) {
            if (key_filter[i] < 255) key_filter[i]++;
            if (key_filter[i] >= KEY_DEBOUNCE_MS) {
                // 电平已稳定，检查状态变化
                if (pins[i] != key_stable[i]) {
                    // 状态变化事件
                    if (key_stable[i] == 1 && pins[i] == 0) {
                        // 释放（上升沿稳定）→ 立即清除触发标志，允许下次按下
                        key_triggered[i] = 0;
                    }
                    else if (key_stable[i] == 0 && pins[i] == 1 && key_triggered[i] == 0) {
                        // 按下（下降沿稳定）且未触发过 → 触发
                        key_triggered[i] = 1;
                        Key_Num = i + 1;        // 记录键值
                    }
                    key_stable[i] = pins[i];    // 更新稳定状态
                }
            }
        } else {
            key_filter[i] = 0;      // 电平跳动，重置计数
            key_last[i] = pins[i];
        }
    }
}
