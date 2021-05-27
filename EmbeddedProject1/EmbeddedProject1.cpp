#include <stm32f1xx_hal.h>
#include <stm32_hal_legacy.h>
#include <string>

#ifdef __cplusplus
extern "C"
#endif
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

uint8_t sss = 0;

GPIO_InitTypeDef GPIO_InitStructure;


void initCol()
{
	GPIO_InitStructure.Pin = GPIO_PIN_1;   //col1  PB10
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_2;   //col2 PB1
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_3;   //col3  PB11
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void initRow()
{
	GPIO_InitStructure.Pin = GPIO_PIN_8;   //row1 PA8
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_15;   //row2 PB15
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_12;   //row3 PA14
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_14;   //row4  PB14
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
}


void col1Work()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);    
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
}

void col2Work()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);   
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET); //col2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);	
}


void col3Work()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);   
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET); 
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);	//col3
}


void pressKey(uint32_t col, uint32_t row)
{
	if (col == 1 && row == 1) {
		col1Work();
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_SET)
		{
			sss = '1';
		}
	}
	else if (col == 2 && row == 1) {
		col2Work();
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_SET)
		{
			sss = '2';
		} 			
	}
	else if (col == 3 && row == 1) {
		col3Work();
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == GPIO_PIN_SET)
		{
			sss = '3';
		}
	}		
	else if (col == 1 && row == 2) {
		col1Work();
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15) == GPIO_PIN_SET)
		{
			sss = '4';
		}
	}
}

int main(void)
{
	HAL_Init();
	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();
	initCol();
	initRow();
	while (true)
		pressKey(1, 2);
	
}


