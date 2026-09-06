/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "OLED.h"
#include "Key.h"
#include "encoder.h"
#include "serial.h"
#include "AD.h"
#include "LED.h"
#include "PWM.h"
#include "RP.h"
#include "PID.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#define CENTER_ANGEL	2064
#define CENTER_RANGE	500

uint8_t RunState;
uint16_t Angel;

int16_t PWM;	  
uint8_t KeyNum;
uint16_t RP1, RP2, RP3, RP4;
volatile int16_t speed = 0;
volatile int32_t location = 0;   // 位置用 32 位保存，防止溢出

PID_t AngelPID = {
	.Target = CENTER_ANGEL,
	.Kp = 0.350,
	.Ki = 0.006,
	.Kd = 0.307,
	.OutMax = 100,
	.OutMin = -100,

};

PID_t LocationPID = {
	.Target = 0,
	.Kp = 0.314,
	.Ki = 0.003,
	.Kd = 3.590,
	.OutMax = 100,
	.OutMin = -100,

};



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	OLED_Init();
	
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim1);	
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_ADCEx_Calibration_Start(&hadc1); 
  HAL_ADCEx_Calibration_Start(&hadc2);
  Encoder_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  
//-------------测试按键与LED是否正常-----------	  
	  
//	 KeyNum=Key_GetNum();
//		if(KeyNum==1)
//		{
//			LED_ON();
//		}	 
//		if(KeyNum==2)
//		{
//			LED_OFF();
//		}
//		if(KeyNum==3)
//		{
//			LED_ON();
//		}	 
//		if(KeyNum==4)
//		{
//			LED_OFF();
//		}
//	  
//--------------测试OLED，串口，姿态传感器以及旋钮是否正常---------------
	  
//		RP1 = RP_GetValue(1);
//		RP2 = RP_GetValue(2);
//		RP3 = RP_GetValue(3);
//		RP4 = RP_GetValue(4);

//		
//		
//		OLED_Printf(0, 0,OLED_8X16, "RP1:%04D", RP1);
//		OLED_Printf(0, 16,OLED_8X16, "RP2:%04D", RP2);
//		OLED_Printf(0, 32,OLED_8X16, "RP3:%04D", RP3);
//		OLED_Printf(0, 48,OLED_8X16, "RP4:%04D", RP4);	
//		OLED_Update();
//		
//		Serial_Printf("%d,%d,%d,%d\r\n",RP1,RP2,RP3,RP4);
//		HAL_Delay(10); 	  

//		OLED_Printf(0, 0,OLED_8X16, "AD:%04d", AD_GetValue());	
//		OLED_Update();	

//--------------------*编码器测试*---------------------------

//		OLED_Printf(0, 0, OLED_8X16, "speed:%+05d",speed);
//		OLED_Printf(0, 16, OLED_8X16, "location:%+05d",location);
//		OLED_Update();


//-----------------*电机测试*-------------------
//		KeyNum=Key_GetNum();
//		if(KeyNum==1)
//		{
//			PWM+=10;
//			if(PWM>100) {PWM=100;}				
//		}		
//		if(KeyNum==2)
//		{
//			PWM-=10;
//			if(PWM<-100) {PWM=-100;}
//		}		
//		if(KeyNum==3)
//		{
//			PWM=0;
//		}		

//		Motor_SetPWM(PWM);
//		
//		OLED_Printf(0, 0, OLED_8X16, "PWM:%+04d",PWM);

//		OLED_Update();

//----------------------正式倒立摆程序----------------------

		KeyNum = Key_GetNum();
		if(KeyNum == 1)
		{
			RunState = !RunState;	
		}
		
		if(RunState)
		{
			LED_ON();
		
		}
		else
		{
			LED_OFF();
		}
		
//		AngelPID.Kp =RP_GetValue(1) / 4095.0 * 1 ; 
//		AngelPID.Ki =RP_GetValue(2) / 4095.0 * 1 ; 
//		AngelPID.Kd =RP_GetValue(3) / 4095.0 * 1 ; 
		
//		LocationPID.Kp =RP_GetValue(1) / 4095.0 * 1 ; 
//		LocationPID.Ki =RP_GetValue(2) / 4095.0 * 1 ; 
//		LocationPID.Kd =RP_GetValue(3) / 4095.0 * 9 ; 
		
		OLED_Printf(0, 0, OLED_6X8,"Angel");
		OLED_Printf(0, 12, OLED_6X8,"kp:%05.3f",AngelPID.Kp);
		OLED_Printf(0, 20, OLED_6X8,"ki:%05.3f",AngelPID.Ki);
		OLED_Printf(0, 28, OLED_6X8,"kd:%05.3f",AngelPID.Kd);
		OLED_Printf(0, 40, OLED_6X8,"Tar:%04.0f",AngelPID.Target);
		OLED_Printf(0, 48, OLED_6X8,"Act:%04d",Angel);
		OLED_Printf(0, 56, OLED_6X8,"Out:%+04.0f",AngelPID.Out);
		
		OLED_Printf(64, 0, OLED_6X8,"Location");
		OLED_Printf(64, 12, OLED_6X8,"kp:%05.3f",LocationPID.Kp);
		OLED_Printf(64, 20, OLED_6X8,"ki:%05.3f",LocationPID.Ki);
		OLED_Printf(64, 28, OLED_6X8,"kd:%05.3f",LocationPID.Kd);
		OLED_Printf(64, 40, OLED_6X8,"Tar:%+05.0f",LocationPID.Target);
		OLED_Printf(64, 48, OLED_6X8,"Act:%+05d",location);
		OLED_Printf(64, 56, OLED_6X8,"Out:%+04.0f",LocationPID.Out);
		OLED_Update();
		
	  
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	
   	static uint16_t Count1, Count2;
	
    if (htim->Instance == TIM1)
    {
		Key_Tick();
		
		speed = Encoder_Get();
		location += speed;
		Angel = AD_GetValue();
		
		if(!(Angel > CENTER_ANGEL - CENTER_RANGE && Angel < CENTER_ANGEL + CENTER_RANGE))
		{
			RunState = 0;
		}
	
		if(RunState)
		{
			Count1++;
			if(Count1 >= 5)
			{
				Count1 = 0;
				AngelPID.Actual = Angel;
				PID_Update(&AngelPID);
				Motor_SetPWM(AngelPID.Out);
			}
			
			Count2++;
			if(Count2 >= 50)
			{
				Count2 = 0;
				LocationPID.Actual = location;
				PID_Update(&LocationPID);
				AngelPID.Target = CENTER_ANGEL - LocationPID.Out;
			
			}
			
		}
		else
		{
			
			Motor_SetPWM(0);
		
		}
    }
}

//---------------*编码器测试*-------------
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//    static uint16_t count = 0;
//    
//    if (htim->Instance == TIM1)   // 确认是 1ms 定时器中断
//    {
//        count++;
//        if (count >= 40)          // 40ms 一次
//        {
//            count = 0;
//            speed = Encoder_Get();      // 读取速度增量
//            location += speed;          // 累积位置
//        }
//    }
//}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
