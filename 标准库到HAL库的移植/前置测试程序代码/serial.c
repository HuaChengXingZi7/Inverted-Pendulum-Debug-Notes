#include "serial.h"
#include "usart.h"    // 包含 CubeMX 生成的 USART1 句柄
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// 接收数据缓存
static uint8_t RxData = 0;
static uint8_t RxFlag = 0;

/**
  * @brief 串口初始化（启动接收中断）
  */
void Serial_Init(void)
{
    // CubeMX 已经初始化了 USART1，这里只需要开启接收中断
    HAL_UART_Receive_IT(&huart1, &RxData, 1);
}

/**
  * @brief 发送一个字节
  */
void Serial_SendByte(uint8_t Byte)
{
    HAL_UART_Transmit(&huart1, &Byte, 1, 100);  // 超时 100ms
}

/**
  * @brief 发送数组
  */
void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
    HAL_UART_Transmit(&huart1, Array, Length, 100);
}

/**
  * @brief 发送字符串
  */
void Serial_SendString(char *String)
{
    uint16_t len = strlen(String);
    HAL_UART_Transmit(&huart1, (uint8_t*)String, len, 100);
}

/**
  * @brief 发送数字（十进制，固定长度）
  */
void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
    char buf[16];
    sprintf(buf, "%0*d", Length, Number);
    Serial_SendString(buf);
}

/**
  * @brief printf 格式化输出（重定向到串口）
  */
int fputc(int ch, FILE *f)
{
    Serial_SendByte((uint8_t)ch);
    return ch;
}

/**
  * @brief 格式化打印
  */
void Serial_Printf(char *format, ...)
{
    char String[256];
    va_list arg;
    va_start(arg, format);
    vsprintf(String, format, arg);
    va_end(arg);
    Serial_SendString(String);
}

/**
  * @brief 获取接收标志（并自动清零）
  */
uint8_t Serial_GetRxFlag(void)
{
    if (RxFlag == 1)
    {
        RxFlag = 0;
        return 1;
    }
    return 0;
}

/**
  * @brief 获取接收数据
  */
uint8_t Serial_GetRxData(void)
{
    return RxData;
}

/**
  * @brief HAL 库的接收中断回调（自动被 USART1_IRQHandler 调用）
  * @note  这个函数由 CubeMX 生成的 stm32f1xx_it.c 里的中断入口触发
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        RxFlag = 1;                    // 置标志
        // 重新开启下一次接收中断（必须！）
        HAL_UART_Receive_IT(&huart1, &RxData, 1);
    }

}

