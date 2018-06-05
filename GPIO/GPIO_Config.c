
#include "stdint.h"
#include "stm32f10x.h"
#include "GPIO_Config.h"

uint32_t counter=0;
GPIO_TypeDef *GPIOxt;

void setUpPort(GPIO_Port_Properties properties){
__IO int i=0,j=0,k=0;
__IO int val=0;		 
__IO uint32_t CRL=0, CRH=0 ;
__IO uint16_t ODR=0;	
	
RCC->APB2ENR |= 1<<properties.GPIO_Port_Name;

	
properties.GPIOx->LCKR =0x0000;	


	
for(i=0;i<=15;i++){
	
val=properties.pins[i];
	
	if(val>0){
	val=val-1;
	if(val>7){
	uint8_t temp=(val-8)*4;
		if(properties.Mode[i]==0xFF){
		properties.Mode[i]=0x08;
			ODR |=1<<temp;
		}
	CRH |= properties.Mode[i]<<temp;
		
		
	}else{
	uint8_t temp=val*4;
		if(properties.Mode[i]==0xFF){
		properties.Mode[i]=0x08;
			ODR |=1<<temp;
		}
	CRL |=properties.Mode[i]<<temp;
	
	}
}

}

properties.GPIOx->ODR  =ODR;
properties.GPIOx->CRH  =CRH;
properties.GPIOx->CRL  =CRL;	


}


void writePort(GPIO_Port_Properties properties, uint32_t data){

	properties.GPIOx->ODR = data;

}


uint8_t readPort(GPIO_Port_Properties properties){
return properties.GPIOx->IDR;
}
 
void setHigh(GPIO_Port_Properties properties, uint16_t pin){

	properties.GPIOx->ODR |= 1<<(pin=pin-1);

}

void setLow(GPIO_Port_Properties properties, uint16_t pin){

	properties.GPIOx->ODR &= ~(1<<(pin=pin-1));

}

uint16_t  readPin(GPIO_Port_Properties properties, uint16_t pin){
  
	
uint16_t temp= 1<<(pin=pin-1);	
	
uint16_t tempData=properties.GPIOx->IDR & temp;
	
	 tempData= tempData >>pin;
	
return  tempData;
}


void  writePin(GPIO_Port_Properties properties, uint16_t pin, uint32_t data){
	
if(data){
	
properties.GPIOx->ODR |= 1<<(pin=pin-1);
}else{
properties.GPIOx->ODR &= ~(1<<(pin=pin-1));
}

}

void Interrupt_Init(uint16_t port,uint16_t pin, uint16_t edge, uint16_t prio,IRQn_Type irq_no){
	uint32_t temp=0;
	int i=0,j=0, x=0, shift=-4;
	port=port-2;
	pin=pin-1;
RCC->APB2ENR |=0x01;
	/*
//AFIO->EVCR |=port<<4;	
//AFIO->EVCR |=pin;	
	*/
	for(i=3;i<=15;i=i+4){
	if(pin>i){
	x=x+1;
	}
	}
	
	for(j=0;j<=3;j++){
		temp=(x*4)+j;
		shift=shift+4;
	if(temp==pin){
	AFIO->EXTICR[x] |= port<<shift;
	}
	}
	
	EXTI->IMR |= 1<<pin;
	
	if(edge==Rising_Edge){
		EXTI->RTSR  |=1<<pin;
	}
	if(edge==Falling_Edge){
		EXTI->FTSR  |=1<<pin;
	}
	if(edge==Both_Edge){
		EXTI->RTSR  |=1<<pin;
		EXTI->FTSR  |=1<<pin;
	}
	
	NVIC_SetPriority(irq_no,prio);
	NVIC_EnableIRQ(irq_no);

}

void clear_interrupt(uint16_t pin){
	uint32_t tp=0x01;
	pin=pin-1;
	tp=tp<<pin;
 if(EXTI->PR & tp){
   EXTI->PR |=tp;		 
	 }

}

uint32_t checkPR(uint16_t pin){
uint32_t v=0;	
uint32_t pinS=0x01;
	
pin=pin-1;
pinS= pinS << pin;
v = EXTI->PR & pinS;
	
return v;
}

void AFIO_Activate(uint16_t port,uint16_t pin){
	port=port-2;
	
	if(port>4){ 
		/* if port value exceeds the value 4. 
		or We can say that PortA to PortE is only
		available for alternate function
		*/
	}
AFIO->EVCR |=port<<4;	
AFIO->EVCR |=pin;	


}

