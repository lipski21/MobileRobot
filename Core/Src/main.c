/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int x=800;
int left,right;
char tx_buffer[27]="L75R80DFC0X";
char array[27]="";
char receive[1]="N";
int length = sizeof(tx_buffer) / sizeof(char);
enum DIRECTION  {FRONT,BACK,LEFT,RIGHT,NONE};
enum DIRECTION direction = NONE;
uint32_t cm_value = 1000;
int sumCharArray(const char *array, int length) {
    int sum = 0;
    for (int i = 0; i < length; ++i) {
        sum += array[i];
    }
    return sum;
}
void intToCharArray(int number, char *result) {
    sprintf(result, "%d", number);
}


void senddata(){
//	memset(tx_buffer, '\0', sizeof(tx_buffer));
//	mem	set(array, '\0', sizeof(array));
	int abc=0;
	if(receive[0]==70){
			receive[0]='F';

		}
		else if(receive[0]==66){
			receive[0]='B';;

		}
		else if(receive[0]==76){
			receive[0]='L';

		}
		else if(receive[0]==82){
			receive[0]='R';

		}
		else{
			receive[0]='N';
		}
	if(cm_value>20){
		abc=0;
	}
	else
		abc=1;
	char tx_buffer[27]="";
	char buffer[27];
	strcat(tx_buffer,"l");
	sprintf(buffer,"%d", left/10);
	strcat(tx_buffer,buffer);
	strcat(tx_buffer,"r");
	sprintf(buffer,"%d", right/10);
	strcat(tx_buffer,buffer);
	strcat(tx_buffer,"D");
	sprintf(buffer,"%d", receive[0]);
	strcat(tx_buffer,buffer);
	strcat(tx_buffer,"C");
	sprintf(buffer,"%d", abc);
	strcat(tx_buffer,buffer);
	strcat(tx_buffer,"X");
	int sum=sumCharArray(tx_buffer, length);

	intToCharArray(sum, array);

	strcat(tx_buffer,array);
	HAL_UART_Transmit(&huart2, tx_buffer, 27, 10);
}
void changedir(){
	 left=x;
	 right=x;
	 TIM1->CCR1 = left;
	 TIM2->CCR3 = right;
	if(receive[0]==70){
		direction=FRONT;

	}
	else if(receive[0]==66){
		direction=BACK;

	}
	else if(receive[0]==76){
		direction=LEFT;

	}
	else if(receive[0]==82){
		direction=RIGHT;

	}
	else if(receive[0]==48){
		x=0;
	}
	else if(receive[0]==49){
		x=200;
	}
	else if(receive[0]==50){
		x=400;
		}
	else if(receive[0]==51){
		x=600;
		}
	else if(receive[0]==52){
		x=800;
		}
	else if(receive[0]==53){
		x=1000;
		}

	else{
		direction=NONE;

		 left=0;
		 right=0;
	}

	if(direction==FRONT){
				 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);
				 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
				 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);
				 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 0);
	}
	else if(direction==BACK){
				 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
				 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
				 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
				 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1);
	}
	else if(direction==RIGHT){
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1);
		}
	else if(direction==LEFT){
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 0);
		}
	else{
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 0);
	}
}
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
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

	 left=x;
	 right=x;
//	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);
//	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
//	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);
//	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 0);
	 TIM1->CCR1 = left;
	 TIM2->CCR3 = right;
	 HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	 HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);

	 HAL_TIM_IC_Start(&htim3, TIM_CHANNEL_1);
	 HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

	 uint32_t current_time_led = HAL_GetTick();
	 uint32_t current_time_sensor = HAL_GetTick();
	 uint32_t value = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	 //	  receive[0]="N";
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */




		  if(current_time_sensor + 100 < HAL_GetTick()){
	  	  value = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_1);
	  	  cm_value = ((value - 2235) / 58.0f); //2235
	  	 }

		  if(cm_value < 6){
			  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);
		  }
		  else if(cm_value > 150){
			  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);
		  }
		  else if(current_time_led + (cm_value * 10) < HAL_GetTick()){
	  		  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	  		  current_time_led = HAL_GetTick();
	  	  }


//	 if(HAL_GetTick()%4000>2000){
//		 left=x;
//		 right=x;
//		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);
//		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
//		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);
//		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 0);
//		 TIM1->CCR1 = left;
//		 TIM2->CCR3 = right;
//		 HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
//		 HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);

//	 }
//	 else{
//		 left=x;
//		 right=x;
//		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
//		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
//		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);
//		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 0);
//		 TIM1->CCR1 = left;
//		 TIM2->CCR3 = right;
//		 HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
//		 HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
//
//	 }
//	 if(HAL_GetTick()%1000>980){
//		 senddata();
//	 }


//	 x=x+10;
////	 left=x;
////	 right=x;
//	 if(x==1000){
//		 x=500;
//	 }
	 senddata();
	 HAL_UART_Receive(&huart2, receive,4,100);
	 changedir();

//	 x++;
//	 left=x;
//	 right=x;
//	 HAL_Delay(10);
//	 if(x==1000)
//		 x=200;
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
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
