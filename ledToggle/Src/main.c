#include <stdint.h>

//on STM32F103C8T6 output data register must be LOW which means 0. You can access this information from schematic of the MCU.

int main(void)
{

	uint32_t *pClkCtrlReg = (uint32_t*) 0x40021018;
	uint32_t *pPortCModeReg = (uint32_t*) 0x40011004;
	uint32_t *pPortCOutReg = (uint32_t*) 0x4001100C;

	//1.Enable the clock for GPIOC peripheral in the APB2ENR

	*pClkCtrlReg |= (1 << 4);
	*pPortCOutReg |= (1 << 13);
	//2.Configure the mode of the IO pin as output.
	//a. clear the 20th, 21th, 22th and 23th bit positions (CLEAR)
	*pPortCModeReg &= ~(0xF << 20);
	//b. make 20th and 21th bit positions as 1 (SET)
	*pPortCModeReg |= (3 << 20);

	while(1){

		*pPortCOutReg &= ~(1 << 13);

		for(uint32_t i = 0; i <= 200000; i++); //delay

		*pPortCOutReg |= (1 << 13);

		for(uint32_t i = 0; i <= 200000; i++); //delay
	}

}
