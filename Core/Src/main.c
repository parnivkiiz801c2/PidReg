/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
volatile uint8_t Data = 0x00; 
volatile uint8_t Begin_Command; 
volatile int UART_State =	1;
volatile int Device = 1; 
volatile uint8_t Koef; 
volatile float Value;
volatile uint8_t End_Command;
volatile char Err[] = {'E','R','R','O','R'};
volatile uint8_t KC;
volatile uint8_t KC2;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
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

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_UART_Receive_IT(&huart3, (uint8_t *) &Data,1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
    /* USER CODE END WHILE */
	HAL_UART_Receive_IT(&huart3, (uint8_t *) &Data,1);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enables the Clock Security System
  */
  HAL_RCC_EnableCSS();
}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 57600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart)
{
	if(huart == &huart3)
	{
		switch(UART_State)
		{
			case 1:
			{
				Begin_Command = Data;
				if(Begin_Command == '#')
				{
					UART_State++;
				}
				break;
			}
			case 2:
			{
				Device = Data;
				if(Device == '1')
				{
					UART_State++;
				}
				else
				{
					UART_State = 1;
				}
				break;
			}
			case 3:
			{
				Koef = Data;
				if(Koef == 'Y' || Koef == 'P' || Koef == 'I' || Koef == 'D' )
				{
					UART_State++;
				}
				else
				{
					UART_State = 1;
				}
				break;
			}
			
			case 4:
			{
				int i = 1;
				Value = Data; //opisat' ERROR
				while(i < 6)
					{
					HAL_UART_Receive_IT(&huart3, (uint8_t *) &Data,1);
					if(i == 1)
					{
						if('0' <=Value && Value <= '9')
						{
						  Value = Value - '0';
							Value = Value * 10;
							i++;
						}
					}
					
					else if(i == 2)
					{
						if('0' <=Value && Value <= '9')
						{
						  Value = Value - '0';
							Value += Value;
							i++;
							HAL_UART_Receive_IT(&huart3, (uint8_t *) &Data,1);

						}
					}
					else if(i == 3)
					{
						if(Value == '.')
						{
							i++;
							HAL_UART_Receive_IT(&huart3, (uint8_t *) &Data,1);
						}
					}
					
					else if(i == 4)
					{
						if('0' <=Value && Value <= '9')
						{
						  Value = Value - '0';
							Value += Value / 10;
							i++;
							HAL_UART_Receive_IT(&huart3, (uint8_t *) &Data,1);
						}
					}
					
					else if(i == 5)
					{
						if('0' <=Value && Value <= '9')
						{
						  Value = Value - '0';
							Value += Value / 100;
							i++;
							HAL_UART_Receive_IT(&huart3, (uint8_t *) &Data,1);
						}
					}
					
					else if(i == 6)
					{
						if('0' <=Value && Value <= '9')
						{
						  Value = Value - '0';
							Value += Value / 1000;
							i++;
							UART_State++;
							HAL_UART_Receive_IT(&huart3, (uint8_t *) &Data,1);
						}
					}
				break;
				}
			}
			case 5:
			{
				End_Command = Data;
				if(End_Command == '@')
				{
					UART_State++;
					HAL_UART_Receive_IT(&huart3, (uint8_t *) &Data,1);
				}
				else
				{
					HAL_UART_Transmit_IT(&huart3,(uint8_t *) &Err, 5);
					HAL_Delay(250);
				}
				break;
			}
			case 6:
			{
				int i = 1;
				
				while(i<3)
				{
					HAL_UART_Receive_IT(&huart3, (uint8_t *) &Data,1);
					if(i==1)
					{
						KC = Data;
						if('0' <= KC && KC <= '9')
						{
							KC = KC - 0x30;
							HAL_UART_Receive_IT(&huart3, (uint8_t *) &Data,1);
						}
						else
						{
							KC = KC - 0x37;
							HAL_UART_Receive_IT(&huart3, (uint8_t *) &Data,1);
						}
						i++;
					}
					
					if(i==2)
					{
						KC2 = Data;
						if('0' <= KC2 && KC2 <= '9')
						{
							KC2 = KC2 - 0x30;
							KC = KC<<4;
							KC = KC + KC2;
						}
						else
						{
							KC2 = KC2 - 0x37;
							KC = KC<<4;
							KC = KC + KC2;
						}
						UART_State = 1;
						i++;
					}
				}
				break;
			}
		}
	} 
}
void HAL_UART_TxCpltCallback (UART_HandleTypeDef *huart)
{
	if(huart == &huart3)
	{
		HAL_UART_Receive_IT(&huart3, (uint8_t *) &Data,10);
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
