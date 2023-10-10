/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim10;
extern UART_HandleTypeDef huart1;
/* USER CODE BEGIN EV */
extern int C_flag1,C_flag2 ,C_flag3 ,C_flag4 ,C_flag5 ;
extern int J_flag1 ,J_flag2 ,J_flag3 ;
extern int suiji_flag;
extern int L_flag1 ,L_flag2 ,L_flag3 ,L_flag4 ,L_flag5 ;
int count = 0,Count = 0;
extern int ret,j,Ret,ccount;
int stop_flag1 = 0,stop_flag2 = 0,stop_flag3 = 0,stop_flag4 = 0,stop_flag5 = 0;
extern void Key_Scan(void);
extern void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
int i = 1;
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */
	count++;
	
	
			
	if(count == 3000)//进入阶段2
	{
		J_flag1 = 1;
		suiji_flag = 1;
	}
	
	if(J_flag1 == 1&&Ret == 1)//进入后判断哪个灯该亮与闪烁
	{
		Count++;
		
		if(Count%500 == 0&& Count%1000!= 0)
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,1000);	
		if(Count%1000 == 0)
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);	//闪烁
		if(Count<3000 && C_flag1 == 1)//按下按键
		{
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,1000);	
			L_flag1 =1;
			Count = 0;
			suiji_flag = 1;C_flag1 = 0;
		}
		else if(Count >= 3000)//超时回到阶段1
		{
			J_flag1 = 0;
			Count = 0;
			count = 0;
			j = 0;C_flag1 = 0;
			C_flag1 = 0,C_flag2 = 0,C_flag3 = 0,C_flag4 = 0,C_flag5 = 0;
			L_flag1 = 0,L_flag2 = 0,L_flag3 = 0,L_flag4 = 0,L_flag5 = 0;
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);	
		}
		else if(ret == 1 &&(C_flag5 == 1||C_flag2 == 1||C_flag3 == 1||C_flag4 == 1))//判断是否按错
		{
			J_flag1 = 0;
			Count = 0;
			count = 0;
			C_flag1 = 0,C_flag2 = 0,C_flag3 = 0,C_flag4 = 0,C_flag5 = 0;
			L_flag1 = 0,L_flag2 = 0,L_flag3 = 0,L_flag4 = 0,L_flag5 = 0;
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);	
			j = 0;
		}
	}
	//以下逻辑同理
	if(J_flag1 == 1&&Ret == 5)
	{
		Count++;
		
		if(Count%500 == 0&& Count%1000!= 0)
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,1000);	
		if(Count%1000 == 0)
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);	
		if(Count<3000 && C_flag5 == 1)
		{
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,1000);	
			L_flag5 = 1;
			Count = 0;suiji_flag = 1;C_flag5 = 0;
		}
		else if(Count >= 3000)
		{
			J_flag1 = 0;
			Count = 0;
			count = 0;C_flag5 = 0;
			j = 0;
			C_flag1 = 0,C_flag2 = 0,C_flag3 = 0,C_flag4 = 0,C_flag5 = 0;
			L_flag1 = 0,L_flag2 = 0,L_flag3 = 0,L_flag4 = 0,L_flag5 = 0;
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);	
		}
		else if(ret == 5 &&(C_flag1 == 1||C_flag2 == 1||C_flag3 == 1||C_flag4 == 1))
		{
			J_flag1 = 0;
			Count = 0;count = 0;
			C_flag1 = 0,C_flag2 = 0,C_flag3 = 0,C_flag4 = 0,C_flag5 = 0;
			L_flag1 = 0,L_flag2 = 0,L_flag3 = 0,L_flag4 = 0,L_flag5 = 0;
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);	
			j = 0;
		}
	}
	
	if(J_flag1 == 1&&Ret == 2)
	{
		Count++;
		
		if(Count%500 == 0&& Count%1000!= 0)
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,1000);	
		if(Count%1000 == 0)
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);	
		if(Count<3000 && C_flag2 == 1)
		{
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,1000);	
			L_flag2 = 1;
			Count = 0;suiji_flag = 1;C_flag2 = 0;
		}
		else if(Count >= 3000)
		{
			J_flag1 = 0;
			Count = 0;
			count = 0;C_flag2 = 0;
			j = 0;
			C_flag1 = 0,C_flag2 = 0,C_flag3 = 0,C_flag4 = 0,C_flag5 = 0;
			L_flag1 = 0,L_flag2 = 0,L_flag3 = 0,L_flag4 = 0,L_flag5 = 0;
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);	
		}
		else if(ret == 2&&(C_flag1 == 1||C_flag5 == 1||C_flag3 == 1||C_flag4 == 1))
		{
			J_flag1 = 0;
			Count = 0;count = 0;
			C_flag1 = 0,C_flag2 = 0,C_flag3 = 0,C_flag4 = 0,C_flag5 = 0;
			L_flag1 = 0,L_flag2 = 0,L_flag3 = 0,L_flag4 = 0,L_flag5 = 0;
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);	
			j = 0;
		}
	}
	
	if(J_flag1 == 1&&Ret == 3)
	{
		Count++;
		
		if(Count%500 == 0&& Count%1000!= 0)
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,1000);	
		if(Count%1000 == 0)
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);	
		if(Count<3000 && C_flag3 == 1)
		{
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,1000);	
			L_flag3 = 1;
			Count = 0;suiji_flag = 1;C_flag3 = 0;
		}
		else if(Count >= 3000)
		{
			J_flag1 = 0;
			Count = 0;C_flag3 = 0;
			count = 0;
			j = 0;suiji_flag = 1;
			C_flag1 = 0,C_flag2 = 0,C_flag3 = 0,C_flag4 = 0,C_flag5 = 0;
			L_flag1 = 0,L_flag2 = 0,L_flag3 = 0,L_flag4 = 0,L_flag5 = 0;
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);	
		}
		else if(ret == 3 &&(C_flag1 == 1||C_flag2 == 1||C_flag5 == 1||C_flag4 == 1))
		{
			J_flag1 = 0;
			Count = 0;count = 0;
			C_flag1 = 0,C_flag2 = 0,C_flag3 = 0,C_flag4 = 0,C_flag5 = 0;
			L_flag1 = 0,L_flag2 = 0,L_flag3 = 0,L_flag4 = 0,L_flag5 = 0;
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);	
			j = 0;
		}
	}
	
	if(J_flag1 == 1&&Ret == 4)
	{
		Count++;
		
		if(Count%500 == 0&& Count%1000!= 0)
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,1000);	
		if(Count%1000 == 0)
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);	
		if(Count<3000 && C_flag4 == 1)
		{
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,1000);	
			L_flag4 = 1;
			Count = 0;
		C_flag4 = 0;
			suiji_flag = 1;
		}
		else if(Count >= 3000)
		{
			J_flag1 = 0;
			Count = 0;
			count = 0;
			j = 0;C_flag4 = 0;
			C_flag1 = 0,C_flag2 = 0,C_flag3 = 0,C_flag4 = 0,C_flag5 = 0;
			L_flag1 = 0,L_flag2 = 0,L_flag3 = 0,L_flag4 = 0,L_flag5 = 0;
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);	
		}
		else if(ret == 4 &&(C_flag1 == 1||C_flag2 == 1||C_flag3 == 1||C_flag5 == 1))
		{
			J_flag1 = 0;
			Count = 0;count = 0;
			C_flag1 = 0,C_flag2 = 0,C_flag3 = 0,C_flag4 = 0,C_flag5 = 0;
			L_flag1 = 0,L_flag2 = 0,L_flag3 = 0,L_flag4 = 0,L_flag5 = 0;
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);	
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);	
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);	
			j = 0;
		}
	}
	
  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM1 update interrupt and TIM10 global interrupt.
  */
void TIM1_UP_TIM10_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 0 */
	HAL_TIM_PeriodElapsedCallback(&htim10);
	
  /* USER CODE END TIM1_UP_TIM10_IRQn 0 */
  HAL_TIM_IRQHandler(&htim10);
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 1 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
