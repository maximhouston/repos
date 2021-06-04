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
using namespace std;

uint8_t sss = 0;

GPIO_InitTypeDef GPIO_InitStructure;


void initCol()
{
	GPIO_InitStructure.Pin = GPIO_PIN_2;    //col1  PB2
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_1;    //col2 PB1
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_15;    //col3  PC15
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void initRow()
{
	GPIO_InitStructure.Pin = GPIO_PIN_8;    //row1 PA8
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_15;    //row2 PB15
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_12;    //row3 PA12
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_14;    //row4  PB14
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_12;     //cancel  PB12
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_13;      //sos PB13
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);	

	GPIO_InitStructure.Pin = GPIO_PIN_15;       //call PA15
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.Pin = GPIO_PIN_3;        //call PB3
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);		
}


void col1Work()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1 | GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_Delay(100);
	
}

void col2Work()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2 | GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);   //col2
	HAL_Delay(100);
}


void col3Work()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1 | GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET); 	//col3
	HAL_Delay(100);
}


uint8_t ReadPin(GPIO_TypeDef *Type_gpi, uint32_t pin, uint8_t sss) {
	if (HAL_GPIO_ReadPin(Type_gpi, pin) == GPIO_PIN_SET)
		return sss;
	else 
		return 0;
}


void pressKey(uint32_t col, uint32_t row)
{
	switch (col)
	{
	case 1:
		col1Work();
		switch (row)
		{
		case 1:
			sss = ReadPin(GPIOA, GPIO_PIN_8, 1);
			break;
		case 2:
			sss = ReadPin(GPIOB, GPIO_PIN_15, 4);
			break;
		case 3:
			sss = ReadPin(GPIOA, GPIO_PIN_12, 7);
			break;
		}
		break;
	case 2:
		col2Work();
		switch (row)
		{
		case 1:
			sss = ReadPin(GPIOA, GPIO_PIN_8, 2);
			break;
		case 2:
			sss = ReadPin(GPIOB, GPIO_PIN_15, 5);
			break;
		case 3:
			sss = ReadPin(GPIOA, GPIO_PIN_12, 8);
			break;
		case 4:
			sss = ReadPin(GPIOB, GPIO_PIN_14, 00);
			break;			
		}		
		break;
	case 3:
		col3Work();
		switch (row)
		{
		case 1:
			sss = ReadPin(GPIOA, GPIO_PIN_8, 3);
			break;
		case 2:
			sss = ReadPin(GPIOB, GPIO_PIN_15, 6);
			break;
		case 3:
			sss = ReadPin(GPIOA, GPIO_PIN_12, 9);
			break;		
		}			
		break;
	}
}

enum str_code {
	eCancel,
	eSos,
	eCall,
	eConcierge,
};

str_code hashit(string const& inString) {
	if (inString == "Cancel") return eCancel;
	if (inString == "Sos") return eSos;
	if (inString == "Call") return eCall;	
	if (inString == "Concierge") return eConcierge;		
}
void pressKey(string row)
{
	switch (hashit(row))
	{
	case eCancel:
		sss = ReadPin(GPIOB, GPIO_PIN_12, 777); 
		break;
	case eSos:
		sss = ReadPin(GPIOB, GPIO_PIN_13, 112); 
		break;
	case eCall:
		sss = ReadPin(GPIOA, GPIO_PIN_15, 888); 
		break;	
	case eConcierge:
		sss = ReadPin(GPIOB, GPIO_PIN_3, 999); 
		break;				
	}
	
}

int main(void)
{
	HAL_Init();
	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();
	initCol();
	initRow();
	while (1) {
		pressKey(1, 1);  // 1
		pressKey(1, 2);   // 4
		pressKey(1, 3); 	 // 7
		pressKey(2, 1);	 // 2
		pressKey(2, 2); 	 // 5
		pressKey(2, 3);   // 8
		pressKey(2, 4);   // 0				
	 pressKey(3, 1);  // 3
		pressKey(3, 2);   // 6
		pressKey(3, 3);   // 9
		pressKey("Cancel");
		pressKey("Sos");	
		pressKey("Call");
		pressKey("Concierge");			
	}
	
}


