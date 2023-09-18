/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void display7SEG(int num, GPIO_TypeDef *GPIOx);
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
   uint8_t green_counter = 4;
   uint8_t yellow_counter = 2;
   uint8_t status = 0;		// 0-green, 1-yellow, 2-across green, 3-across yellow
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, SET);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, SET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
{
  /* USER CODE END WHILE */
  if(status == 0){
	  green_counter--;
	  display7SEG(green_counter, GPIOB);
	  display7SEG(green_counter+yellow_counter, GPIOA);
	  if(green_counter <= 0){
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, SET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, RESET);
		  green_counter = 3;
		  status = 1;
	  }
  }else if(status == 1){
	  yellow_counter--;
	  display7SEG(yellow_counter, GPIOB);
	  display7SEG(green_counter+yellow_counter, GPIOA);
	  if(yellow_counter <= 0){
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, SET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, RESET);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, RESET);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, SET);
		  yellow_counter = 2;
		  status = 2;
	  }
  }else if(status == 2){
	  green_counter--;
	  display7SEG(green_counter, GPIOA);
	  display7SEG(green_counter+yellow_counter, GPIOB);
	  if(green_counter <= 0){
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, SET);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, RESET);
		  green_counter = 3;
		  status = 3;
	  }
  }else if(status == 3){
	  yellow_counter--;
	  display7SEG(yellow_counter, GPIOA);
	  display7SEG(green_counter+yellow_counter, GPIOB);
	  if(yellow_counter <= 0){
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, SET);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, SET);
		  yellow_counter = 2;
		  status = 0;
	  }
  }
  HAL_Delay(1000);
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
//  GPIO_InitTypeDef GPIO_InitStruct_1 = {0};
//  GPIO_InitTypeDef GPIO_InitStruct_2 = {0};
//  GPIO_InitTypeDef GPIO_InitStruct_3 = {0};
//  GPIO_InitTypeDef GPIO_InitStruct_4 = {0};
//  GPIO_InitTypeDef GPIO_InitStruct_5 = {0};
//  GPIO_InitTypeDef GPIO_InitStruct_6 = {0};
//  GPIO_InitTypeDef GPIO_InitStruct_7 = {0};
  GPIO_InitTypeDef GPIO_InitStruct_all = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_All, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_All, GPIO_PIN_RESET);
   /*Configure GPIO pin : all */
   GPIO_InitStruct_all.Pin = GPIO_PIN_All;
   GPIO_InitStruct_all.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct_all.Pull = GPIO_NOPULL;
   GPIO_InitStruct_all.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(GPIOA, &GPIO_InitStruct_all);
   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct_all);
/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

uint8_t LED[10] = {0x3F,		//decode for 0
				0x06, 			//decode for 1
				0x5B, 			//decode for 2
				0x4F, 			//decode for 3
				0x66, 			//decode for 4
				0x6D, 			//decode for 5
				0x7D, 			//decode for 6
				0x07, 			//decode for 7
				0x7F, 			//decode for 8
				0x6F};			//decode for 9

void display7SEG(int num, GPIO_TypeDef* GPIOx){
	HAL_GPIO_WritePin(GPIOx, GPIO_PIN_1, !((LED[num]>>0)&0x01));
	HAL_GPIO_WritePin(GPIOx, GPIO_PIN_2, !((LED[num]>>1)&0x01));
	HAL_GPIO_WritePin(GPIOx, GPIO_PIN_3, !((LED[num]>>2)&0x01));
	HAL_GPIO_WritePin(GPIOx, GPIO_PIN_4, !((LED[num]>>3)&0x01));
	HAL_GPIO_WritePin(GPIOx, GPIO_PIN_5, !((LED[num]>>4)&0x01));
	HAL_GPIO_WritePin(GPIOx, GPIO_PIN_6, !((LED[num]>>5)&0x01));
	HAL_GPIO_WritePin(GPIOx, GPIO_PIN_7, !((LED[num]>>6)&0x01));
}

/* USER CODE BEGIN 4 */

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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
