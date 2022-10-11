/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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

#include "bsp.h"

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

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void MPU_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */
#define TX_RX_SIZE 1*512
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

  /* MPU Configuration--------------------------------------------------------*/
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
    bsp_Init();
  /* USER CODE BEGIN 2 */
    uint8_t receive_ch;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    uint8_t char1[]="AT",char2[20]={"\0"},RXBUFF[TX_RX_SIZE],TXBUFF[TX_RX_SIZE],ucValue,ucValue3;
    uint16_t i=0,j=0;
  while (1)
  {
    /* USER CODE END WHILE */
//      if (comGetChar(COM3, &receive_ch))
//      {
//          printf("%c", receive_ch);
//      }
    /* USER CODE BEGIN 3 */
        if(comGetChar(COM1,&ucValue))
        {
            char2[i++]=ucValue;
            HAL_Delay(50);
            if((ucValue==0x0A)&&(i>2))
            {
                printf("huart1 receive:%s\r\n", char2);
            }
        }
        else
        {
            for(;i<20;i++)
            {
                char2[i]='\0';
            }
            if((i!=0)&&(char2[0]!=0))
            {
                comSendBuf(COM3,char2,sizeof(char2));
            }
            i=0;
            if(comGetChar(COM3,&ucValue3))
            {
                RXBUFF[j++]=ucValue3;
                HAL_Delay(100);
                //if((ucValue3==0x0A)&&(j>2)) // 排除掉前两位\r\n 删除
                if((j>4)&&(RXBUFF[j-4]==0x4F)&&(RXBUFF[j-3]==0x4B)&&
                    (RXBUFF[j-2]==0x0D)&&(RXBUFF[j-1]==0x0A))
                {
                    printf("j=%d\r\n", j);
                    printf("huart3 Receive:%s\r\n", RXBUFF);
                }
            }
            else
            {
                for(;j<TX_RX_SIZE;j++)
                {
                RXBUFF[j]='\0';
                }
                j=0;
            }
        }
  }
  /* USER CODE END 3 */
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
