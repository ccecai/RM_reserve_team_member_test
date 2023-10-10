/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
int C_flag1 = 0,C_flag2 = 0,C_flag3 = 0,C_flag4 = 0,C_flag5 = 0;  //按键按下标志量
int J_flag1 = 0,J_flag2 = 0,J_flag3 = 0;//状态转换标志量
int suiji_flag =0;  //随机抽取的标志量
int L_flag1 = 0,L_flag2 = 0,L_flag3 = 0,L_flag4 = 0,L_flag5 = 0;//灯是否亮起的标志量
int A_flag1 = 0,A_flag2 = 0,A_flag3 = 0,A_flag4 = 0,A_flag5 = 0;//灯是否亮起的标志量
extern int count;
char str[50];//串口发送数据存储
int ret = 0;//随机量
int Ret=0;//输出量
int ccount=0,j = 0,k = 0;//定时器计数量
//int Count=0;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/**
  * @brief  按键扫描函数
  * @param  
  * @retval None
  */
void Key_Scan(void);
/**
  * @brief  通用定时器回调函数
  * @param  
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	ccount++;
	
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	int temp = 0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  MX_RTC_Init();
  MX_TIM10_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim10);
	__HAL_TIM_CLEAR_IT(&htim10,TIM_IT_UPDATE);
	
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	__HAL_TIM_CLEAR_IT(&htim2,TIM_CHANNEL_2);	
	
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
	__HAL_TIM_CLEAR_IT(&htim2,TIM_CHANNEL_3);	
	
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);
	__HAL_TIM_CLEAR_IT(&htim2,TIM_CHANNEL_4);
	
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	__HAL_TIM_CLEAR_IT(&htim3,TIM_CHANNEL_1);	
	
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
	__HAL_TIM_CLEAR_IT(&htim3,TIM_CHANNEL_2);
	
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);	
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);	
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);	
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);	
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);	//PWM初始化
	
	
	//以上均为初始化函数
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//		HAL_TIM_PeriodElapsedCallback(&htim10);
	
		HAL_TIM_PeriodElapsedCallback(&htim10);//取一直改变的数使得srand函数可以取随机数
		if(J_flag1 == 1)//在阶段2 下活动
		{
			
				Key_Scan();
			if(suiji_flag == 1)
			{
				HAL_TIM_PeriodElapsedCallback(&htim10);
				srand(ccount);
				ret=rand() % 5 + 1;//取随机数
				
				if(ret == 1)//判断取随机数后应打开哪个灯并且防止再次被读
				{
					A_flag1++;
					if(A_flag1 >= 2)
					{
						ret = 0;
						A_flag1= 1;
					}
					else if(A_flag1 == 1)
					{
						Ret = ret;
					}
				}
				
				if(ret == 2 )
				{
					A_flag2++;
					if(A_flag2 >= 2)
					{
						ret = 0;
						A_flag2= 1;
						
					}
					else if(A_flag2 == 1)
					{
						Ret = ret;
					}
				}
				
				if(ret == 3 )
				{
					A_flag3++;
					if(A_flag3 >= 2)
					{
						ret = 0;
						A_flag3= 1;
						
					}
					else if(A_flag3 == 1)
					{
						Ret = ret;
					}
				}
				
				if(ret == 4 )
				{
					A_flag4++;
					if(A_flag4 >= 2)
					{
						ret = 0;
						A_flag4= 1;
						
					}
					else if(A_flag4 == 1)
					{
						Ret = ret;
					}
				}
				
				if(ret == 5 )
				{
					A_flag5++;
					if(A_flag5 >= 2)
					{
						ret = 0;
						A_flag5 = 1;
						
					}
					else if(A_flag5 == 1)
					{
						Ret = ret;
					}
				}
				if(temp != Ret)
				{
					suiji_flag = 0;//当重复取时，重新取随机值
				}
				temp = Ret;
				
//				do{
//			
//					HAL_TIM_PeriodElapsedCallback(&htim10);
//					srand(cCount);
//					ret=rand() % 5 + 1;
//					
//				}while(ret == Ret[0] || ret == Ret[1]||ret == Ret[2]||ret == Ret[3]||ret == Ret[4]);	
//				
//				Ret[j++] = ret;
//				suiji_flag = 0;//很明显，这段函数更为简洁且具有相同逻辑，但是我不知道为啥跑不通
				
			}
			if(L_flag1 == 1&&L_flag2 == 1&&L_flag3 == 1&&L_flag4 == 1&&L_flag5 == 1)//所有灯亮起，进入阶段3
			{
				J_flag2 = 1;
				J_flag1 = 0;
			}
		
		}
		
		
		
		if(J_flag2 == 1)//阶段3呼吸灯
		{
//			
			for(int i=0;i<10;i++)
			{
				__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,i*100);	
				__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,i*100);	
				__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,i*100);	
				__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,i*100);	
				__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,i*100);	
				HAL_Delay(10);
			}
			for(int i=0;i<10;i++)
			{
				__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,1000-i*100);	
				__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,1000-i*100);	
				__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,1000-i*100);	
				__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,1000-i*100);	
				__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,1000-i*100);	
				HAL_Delay(10);
			}
			HAL_UART_Transmit_IT(&huart1,(uint8_t *)"已进入完全激活状态\n", 30);		
		}
	
			
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void Key_Scan(void)
{
	int i = 0;
	
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9) == GPIO_PIN_RESET)
	{
		
		HAL_Delay(20);
		
		do{
			i++;
		}while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9) == GPIO_PIN_RESET);
		if(i>1500000)
		{
			J_flag1 = 0;
			J_flag2 = 0;
			count = 0;
			i=0;
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);
		}
		C_flag1 = 1;
		HAL_Delay(20);
		
	}

	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4) == GPIO_PIN_RESET)
	{
		HAL_Delay(20);
		do{
		i++;
		}while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4) == GPIO_PIN_RESET);
		if(i>1500000)
		{
			J_flag1 = 0;
			J_flag2 = 0;
			count = 0;
			i=0;
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);
		}
		C_flag2 = 1;
		HAL_Delay(20);
	}
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9) == GPIO_PIN_RESET)
	{
		HAL_Delay(20);
		do{
			i++;
		}while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9) == GPIO_PIN_RESET);
		if(i>2000000)
		{
			J_flag1 = 0;
			J_flag2 = 0;
			count = 0;
			i=0;
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);
		}
		C_flag3 = 1;
		HAL_Delay(20);
	}
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15) == GPIO_PIN_RESET)
	{
		HAL_Delay(20);
		do{
			i++;
		}while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15) == GPIO_PIN_RESET);
		if(i>1500000)
		{
			J_flag1 = 0;
			J_flag2 = 0;
			count = 0;
			i=0;
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);
		}
		C_flag4 = 1;
		HAL_Delay(20);
	}
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13) == GPIO_PIN_RESET)
	{
		HAL_Delay(20);
		do{
			i++;
		}while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13) == GPIO_PIN_RESET);
		if(i>1500000)
		{
			J_flag1 = 0;
			J_flag2 = 0;
			count = 0;
			i=0;
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);
		}
		C_flag5 = 1;
		HAL_Delay(20);
	}
}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
