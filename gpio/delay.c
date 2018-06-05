
#include "stm32f10x.h" 
#include "delay.h"

static __IO uint32_t sysTickCounter;

void SysTick_Handler(){
        SCB->ICSR |= 1<<25; // Clearing Pend Bit of Systick
     Decrement(); 

}

void Decrement(void) {
	
		sysTickCounter--;
	
}
 
void delay_us(long n) {
	sysTickCounter = n;
	
	SysTick_Config(SystemCoreClock / 1000000);
	NVIC_SetPriority(SysTick_IRQn,Priority_6_systick);
	while (sysTickCounter != 0) {
	}
	SysTick->CTRL=0x00;
}
 
void delay_ms(long n) {
	sysTickCounter = n;
	
	SysTick_Config(SystemCoreClock / 1000);
  NVIC_SetPriority(SysTick_IRQn,Priority_6_systick);
	while (sysTickCounter != 0) {
	}
	SysTick->CTRL=0x00;
}
 
