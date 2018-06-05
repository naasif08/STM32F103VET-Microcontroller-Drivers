#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H

#include "stdint.h"
#include "stm32f10x.h"
#define one 0x01
#define zero 0x00
// edge defined
#define Rising_Edge 1
#define Falling_Edge 2
#define Both_Edge 3

#define Priority_0  0x00
#define Priority_1  0x01
#define Priority_2  0x02
#define Priority_3  0x03
#define Priority_4  0x04
#define Priority_5  0x05
#define Priority_6_systick  0x06
#define Priority_7  0x07
#define Priority_8  0x08
#define Priority_9  0x09
#define Priority_10 0x0A
#define Priority_11 0x0B
#define Priority_12 0x0C
#define Priority_13 0x0D
#define Priority_14 0x0E
#define Priority_15 0x0F


// PORT NAMES Defined
#define PortA 2
#define PortB 3
#define PortC 4
#define PortD 5
#define PortE 6
#define PortF 7
#define PortG 8
// PORT NAME Defined
#define Pin0 1
#define Pin1 2
#define Pin2 3
#define Pin3 4
#define Pin4 5
#define Pin5 6
#define Pin6 7
#define Pin7 8
#define Pin8 9
#define Pin9 10
#define Pin10 11
#define Pin11 12
#define Pin12 13
#define Pin13 14
#define Pin14 15
#define Pin15 16

#define IRQ_Pin0 1
#define IRQ_Pin1 2
#define IRQ_Pin2 3
#define IRQ_Pin3 4
#define IRQ_Pin4 5
#define IRQ_Pin5 6
#define IRQ_Pin6 7
#define IRQ_Pin7 8
#define IRQ_Pin8 9
#define IRQ_Pin9 10
#define IRQ_Pin10 11
#define IRQ_Pin11 12
#define IRQ_Pin12 13
#define IRQ_Pin13 14
#define IRQ_Pin14 15
#define IRQ_Pin15 16

// PORT NAME Defined

#define Mode_Input_In_Analog                     0x00
#define Mode_Input_In_Floating                   0x04
#define Mode_Input_In_PullUp                     0xFF
#define Mode_Input_In_PullDown                   0x08

#define Mode_Output_10MHz_Push_Pull              0x01
#define Mode_Output_10MHz_Open_Drain             0x05
#define Mode_Output_10MHz_Alternate_Push_Pull    0x09
#define Mode_Output_10MHz_Alternate_Open_Drain   0x0D

#define Mode_Output_2MHz_Push_Pull               0x02
#define Mode_Output_2MHz_Open_Drain              0x06
#define Mode_Output_2MHz_Alternate_Push_Pull     0x0A
#define Mode_Output_2MHz_Alternate_Open_Drain    0x0E

#define Mode_Output_50MHz_Push_Pull              0x03
#define Mode_Output_50MHz_Open_Drain             0x07
#define Mode_Output_50MHz_Alternate_Push_Pull    0x0B
#define Mode_Output_50MHz_Alternate_Open_Drain   0x0F	







typedef struct
{
	uint8_t GPIO_Port_Name; 
	GPIO_TypeDef *GPIOx;
	uint32_t pins[16];  
	uint32_t Mode[16];  
	                 
}GPIO_Port_Properties;


void setUpPort(GPIO_Port_Properties properties);


void writePort(GPIO_Port_Properties properties, uint32_t data);
uint8_t readPort(GPIO_Port_Properties properties);

void setHigh(GPIO_Port_Properties properties, uint16_t pin);
void setLow(GPIO_Port_Properties properties, uint16_t pin);


uint16_t  readPin(GPIO_Port_Properties properties, uint16_t pin);
void  writePin(GPIO_Port_Properties properties, uint16_t pin, uint32_t data); 

void Interrupt_Init(uint16_t port,uint16_t pin ,uint16_t edge, uint16_t prio, IRQn_Type irq_no);
void clear_interrupt(uint16_t pin);
void  AFIO_Activate(uint16_t port,uint16_t pin);
uint32_t checkPR(uint16_t pin);


#endif 

