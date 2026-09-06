#ifndef _SERIAL_H
#define _SERIAL_H

#include <stdint.h>
#include <stdarg.h>

void Serial_Init(void);                // 启动串口并开启接收中断
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_Printf(char *format, ...); // 支持 printf 格式化输出
uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxData(void);

#endif

