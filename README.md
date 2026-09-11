# Inverted-Pendulum-Debug-Notes

A record of problems encountered and solutions during the development and debugging of a physical inverted-pendulum system (control software, HAL 移植与仿真尝试).

## 一句话简介
基于 STM32/HAL 的倒立摆控制工程的调试记录与最终实现代码，包含 Simulink 调试日志、PID 参数整定实验（包括 Ziegler–Nichols 尝试）、以及从标准库到 HAL 的逐步移植与调试代码。

## 关键特性 / 包含内容
- 调试笔记（中文）：Simulink 调试日志、Z-N 参数整定思路与实验记录、各类问题的排查与结论。
- 移植与实现：将基于标准库或例程的外设/控制代码移植到 STM32 HAL，包含完整的外设驱动（PWM、ADC、编码器、定时器、串口、OLED 等）和控制循环（PID）。
- 改进记录：对串级 PID、微分先行等策略的错误根因、修复与优化思路的记录，以及实际代码示例。
- 完整代码：`标准库到HAL库的移植/倒立摆的最终实现完整代码/` 包含 main.c、PID.c、tim.c、adc.c、OLED.c、encoder.c 等模块化 C 文件。

## 仓库结构
Simulink调试/
  Simulink调试日志.md          Simulink 建模与脚本生成的调试笔记
倒立摆pid算法改进/
  结构体未初始化...md          串级 PID 问题排查与解决
  新的优化办法.md              PID 改进思路
标准库到HAL库的移植/
  倒立摆的最终实现.md          最终实现的概述
  倒立摆的最终实现完整代码/    主程序与外设驱动代码（main.c, PID.c, OLED.c, tim.c, adc.c, encoder.c, serial.c ...）
齐格勒-尼科尔斯（Z-N）法进行系统性参数整定/
  Z-N法的...md                 Ziegler–Nichols 尝试记录与思路
