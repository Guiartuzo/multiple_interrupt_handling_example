#include "stm32f10x.h"                  			//Device header

void delay (uint32_t vezes);					//Declara protótipo da função

int main (void)	
	
{
	__disable_irq();					//Desabilita 
	
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;			//Habilita clock nas alternate functions
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;			//Habilita clock na porta C
	GPIOC->CRH |= 0x44344444;				//Seta GPIOC como output push pull, 50 Mhz
	
	AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PB;		//Habilita External interrupt pino 12, porta B
	AFIO->EXTICR[2] = AFIO_EXTICR2_EXTI5_PA;		//Habilita External interrupt pino 5, porta A
	
	EXTI->IMR |= EXTI_IMR_MR12;				//Unmask pino 12
	EXTI->IMR |= EXTI_IMR_MR5;				//Unmask pino 5

	EXTI->FTSR |= EXTI_FTSR_TR12;				//Seta como falling edge trigger pino 12
	EXTI->FTSR |= EXTI_FTSR_TR5;				//Seta como falling edge trigger pino 5
	
	NVIC_EnableIRQ(EXTI15_10_IRQn);				//Habilita NVIC para EXTI15 a EXTI10
	NVIC_EnableIRQ(EXTI9_5_IRQn);				//Habilita NVIC para EXTI9 a EXTI5
	
	__enable_irq();						//Habilita IRQ
	
	while(1)
	{

	}
	
}

void EXTI15_10_IRQHandler()					//Função de callback
{
	GPIOC->BSRR |= GPIO_BSRR_BS13;				//Seta GPIOC 13 nível lógico alto
	delay(1000000);						//Delay
	GPIOC->BSRR |= GPIO_BSRR_BR13;				//Reseta GPIOC 13, nível lógico baixo
	delay(1000000);						//Delay
	GPIOC->BSRR |= GPIO_BSRR_BS13;				//Seta GPIOC 13 nível lógico alto	
	delay(1000000);						//Delay
	GPIOC->BSRR |= GPIO_BSRR_BR13;				//Reseta GPIOC 13, nível lógico baixo
	delay(1000000);						//delay
	EXTI->PR |= EXTI_PR_PR12;				//Limpa pending bit
}

void EXTI9_5_IRQHandler()
{
	GPIOC->BSRR |= GPIO_BSRR_BS13;				//Seta GPIOC 13 nível lógico alto
	delay(1000000);						//delay
	GPIOC->BSRR |= GPIO_BSRR_BR13;				//Reseta GPIOC 13, nível lógico baixo
	delay(1000000);						//delay
	EXTI->PR |= EXTI_PR_PR5;				//Limpa pending bit
}


void delay (uint32_t vezes)					//Definição da função de delay
{
	int i;
	for (i=0; i<vezes ; i++);
}
