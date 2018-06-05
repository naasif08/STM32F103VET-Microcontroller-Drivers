
#include "stm32f10x.h"
#include "GPIO_Config.h"
#include "delay.h"
#include "SPI.h"

uint16_t val=0;

void SPI_Init(SPI_Properties *propSPI){
GPIO_Port_Properties pA;
	
	RCC->APB2ENR |= 1 << 0; // enable clock for AFIO
	
	
	if(propSPI->SPI_Settings.SPIx == SPI1){
	RCC->APB2ENR |= 1 << 12;	// enable clock for SPI1	
	}
	if(propSPI->SPI_Settings.SPIx == SPI2){
	
	RCC->APB1ENR |= 1 << 14;
	}

	if(propSPI->SPI_Settings.SPIx == SPI3){
	
	RCC->APB1ENR |= 1 << 15;
	}
	
	/* using my GPIO Driver*/
	pA.GPIOx=GPIOA;
	pA.GPIO_Port_Name=PortA;
	
	if(propSPI->SPI_Settings.Mode == SPI_Mode_Master){
	
	/* SCK- Must be AF push-pull , PA5  */
	pA.Mode[0]=Mode_Output_10MHz_Alternate_Push_Pull;
	pA.pins[0]=Pin5;
	
	
	/* MOSI- Must be AF push-pull , PA7*/
	pA.Mode[1]=Mode_Output_10MHz_Alternate_Push_Pull;
	pA.pins[1]=Pin7;

	
	/* MISO- Must be Input Pull-Up , PA6 */
	pA.Mode[2]=Mode_Input_In_PullUp;
	pA.pins[2]=Pin6;
	
 
	/* NSS- Canbe used as GPIO , PA4 */
	pA.Mode[3]=Mode_Output_10MHz_Push_Pull;
	pA.pins[3]=Pin4;
	
	}
	
		if(propSPI->SPI_Settings.Mode == SPI_Mode_Slave){
	
	/* SCK- Must be AF push-pull , PA5  */
	pA.Mode[0]=Mode_Input_In_Floating;
	pA.pins[0]=Pin5;
	
	
	/* MOSI- Must be AF push-pull , PA7*/
	pA.Mode[1]=Mode_Input_In_Floating;
	pA.pins[1]=Pin7;

	
	/* MISO- Must be Input Pull-Up , PA6 */
	pA.Mode[2]=Mode_Output_10MHz_Alternate_Push_Pull;
	pA.pins[2]=Pin6;
	
 
	/* NSS- Canbe used as GPIO , PA4 */
	pA.Mode[3]=Mode_Output_10MHz_Push_Pull;
	pA.pins[3]=Pin4;
	
	}
	
	
	setUpPort(pA);

propSPI->SPI_Settings.SPIx->CR1 |=propSPI->SPI_Settings.CPhase;

propSPI->SPI_Settings.SPIx->CR1 |=propSPI->SPI_Settings.CPol;

propSPI->SPI_Settings.SPIx->CR1 |=propSPI->SPI_Settings.Mode;

propSPI->SPI_Settings.SPIx->CR1 |=propSPI->SPI_Settings.BaudRatePrescaler;

propSPI->SPI_Settings.SPIx->CR1 |=propSPI->SPI_Settings.MSBorLSB;

propSPI->SPI_Settings.SPIx->CR1 |=propSPI->SPI_Settings.DataSize;

propSPI->SPI_Settings.SPIx->CR1 |=propSPI->SPI_Settings.Direction;





if(propSPI->SPI_Settings.NSS == SPI_NSS_Software){
propSPI->SPI_Settings.SPIx->CR1 |= 1 << 9; // setting SSM bit 1
propSPI->SPI_Settings.SPIx->CR1 |= 1 << 8; // setting SSI bit 1
}

if(propSPI->SPI_Settings.NSS == SPI_NSS_Hardware){
propSPI->SPI_Settings.SPIx->CR1 &= ~(1 << 9); // setting SSM bit 1
}
	

Enable_Txe_Interrupt(propSPI);
Enable_Rxe_Interrupt(propSPI);
Enable_Spi(propSPI);
propSPI->State = SPI_STATE_READY;	

}

void Enable_Spi(SPI_Properties *propSPI){

	if(propSPI->SPI_Settings.SPIx == SPI1){
	 NVIC_SetPriority(SPI1_IRQn,0x0A);	// setting up SPI1 interrupt priority
  NVIC_EnableIRQ(SPI1_IRQn);       // Enabling interrupt for SPI1
	}
	if(propSPI->SPI_Settings.SPIx == SPI2){
	 NVIC_SetPriority(SPI2_IRQn,0x0A);	// setting up SPI1 interrupt priority
  NVIC_EnableIRQ(SPI2_IRQn);       // Enabling interrupt for SPI1
	}
	if(propSPI->SPI_Settings.SPIx == SPI3){
	 NVIC_SetPriority(SPI3_IRQn,0x0A);	// setting up SPI1 interrupt priority
  NVIC_EnableIRQ(SPI3_IRQn);       // Enabling interrupt for SPI1
	}
	

propSPI->SPI_Settings.SPIx->CR1 |= 1 << 6;

	
}


void Disable_Spi(SPI_Properties *propSPI){

	
	while(propSPI->State != SPI_STATE_READY );

	
	
	if(propSPI->SPI_Settings.SPIx == SPI1){
	NVIC_DisableIRQ(SPI1_IRQn);
	}
	
	if(propSPI->SPI_Settings.SPIx == SPI2){
	 NVIC_DisableIRQ(SPI2_IRQn);
	}
	
	if(propSPI->SPI_Settings.SPIx == SPI3){
	 NVIC_DisableIRQ(SPI2_IRQn);
	}
	
propSPI->SPI_Settings.SPIx->CR1 &= ~(1 << 6);

	propSPI->State = SPI_STATE_READY;	
	
}



void Enable_Txe_Interrupt(SPI_Properties *propSPI){

propSPI->SPI_Settings.SPIx->CR2 |= 1 << 7;			// setting TXE bit not masked

}


void Disable_Txe_Interrupt(SPI_Properties *propSPI){
	propSPI->SPI_Settings.SPIx->CR2 &= ~(1 << 7);			// clearing TXE bit not masked
propSPI->State = SPI_STATE_READY;
if((propSPI->SPI_Settings.Mode == SPI_Mode_Master) && (propSPI->State != SPI_STATE_BUSY_RX)){


}
	
}


void Enable_Rxe_Interrupt(SPI_Properties *propSPI){

propSPI->SPI_Settings.SPIx->CR2 |= 1 << 6;			// setting RXE bit not masked

}


void Disable_Rxe_Interrupt(SPI_Properties *propSPI){
propSPI->State=SPI_STATE_READY;
propSPI->SPI_Settings.SPIx->CR2 &= ~(1 << 6);			// Clearing RXE bit not masked

}



 void SPI_Irqn(SPI_Properties *propSPI){
	 
	delay_us(5);
	 
if((propSPI->SPI_Settings.SPIx->SR & 0x01)== 0x01){ // checking RXE bit

propSPI->Irq_State= Irq_State_RXE_Pending;
  if(propSPI->SPI_Settings.Mode == SPI_Mode_Master){
	Rx_Handle(propSPI);
	}else{
	
	Rx_Interrupt_Handle(propSPI);
	}

	
propSPI->Irq_State= Irq_State_RXE_Clear;
	
	}

if((propSPI->SPI_Settings.SPIx->SR & 0x02)== 0x02){ // checking TXE bit
	
propSPI->Irq_State= Irq_State_TXE_Pending;
	
	if(propSPI->SPI_Settings.Mode == SPI_Mode_Master){
	Tx_Handle(propSPI);
	}else{
		Tx_Interrupt_Handle(propSPI);
	}
	

	
propSPI->Irq_State= Irq_State_TXE_Clear;
	
	}

propSPI->Irq_State= Irq_State_No_Interrupt;


}


static void Rx_Interrupt_Handle(SPI_Properties *propSPI){
 
	if( propSPI->SPI_Settings.DataSize == SPI_DataSize_8Bit){
	
	(*propSPI->Transciver.Rx_data++) = propSPI->SPI_Settings.SPIx->DR;
		propSPI->Transciver.Rx_data_size--;
	}

	if( propSPI->SPI_Settings.DataSize == SPI_DataSize_16Bit){
	(*propSPI->Transciver.Rx_data) = propSPI->SPI_Settings.SPIx->DR;
		propSPI->Transciver.Rx_data = propSPI->Transciver.Rx_data+2;
		propSPI->Transciver.Rx_data_size =propSPI->Transciver.Rx_data_size-2;
	
	}
	if(propSPI->Transciver.Rx_data_size == 0){
	 while(propSPI->Irq_State != Irq_State_No_Interrupt);	 
	Disable_Rxe_Interrupt(propSPI);
	Disable_Spi(propSPI);		
	}
	

}


static void Tx_Interrupt_Handle(SPI_Properties *propSPI){


	if( propSPI->SPI_Settings.DataSize == SPI_DataSize_8Bit){
	
	  propSPI->SPI_Settings.SPIx->DR = (*propSPI->Transciver.Tx_data++);
		propSPI->Transciver.Tx_data_size--;
	}

	if( propSPI->SPI_Settings.DataSize == SPI_DataSize_16Bit){
		
	  propSPI->SPI_Settings.SPIx->DR = *((uint16_t*)propSPI->Transciver.Tx_data);
		propSPI->Transciver.Tx_data = propSPI->Transciver.Tx_data + 2;
	
		propSPI->Transciver.Tx_data_size = propSPI->Transciver.Tx_data_size - 2;
	
	}
	if(propSPI->Transciver.Tx_data_size == 0){
	
	Disable_Txe_Interrupt(propSPI);
	Disable_Spi(propSPI);	
	}
	


}


void Rx_Master(SPI_Properties *propSPI, uint8_t *buffer, uint32_t length){
uint8_t dummy_tx[10]={0x01,0x02,0x03,0x04,0x05};



propSPI->Transciver.Tx_data= dummy_tx;
propSPI->Transciver.Tx_data_size=length;

propSPI->Transciver.Rx_data = buffer;
propSPI->Transciver.Rx_data_size=length;

propSPI->State= SPI_STATE_BUSY_RX;

Enable_Txe_Interrupt(propSPI);
Enable_Rxe_Interrupt(propSPI);
Enable_Spi(propSPI);
}

void Tx_Master(SPI_Properties *propSPI, uint8_t *buffer, uint32_t length){


propSPI->Transciver.Tx_data = buffer;
propSPI->Transciver.Tx_data_size=length;
propSPI->Transciver.Rx_data_size=length;

propSPI->State=SPI_STATE_BUSY_TX;
	
Enable_Txe_Interrupt(propSPI);	
Enable_Spi(propSPI);
}

void SPI_Slave_Rx(SPI_Properties *propSPI, uint8_t *Rx_Data, uint32_t length){

propSPI->Transciver.Rx_data = Rx_Data;
propSPI->Transciver.Rx_data_size=length;

propSPI->State= SPI_STATE_BUSY_RX;

Enable_Rxe_Interrupt(propSPI);
Enable_Spi(propSPI);
while(propSPI->Irq_State != Irq_State_No_Interrupt);

}

void SPI_Slave_Tx(SPI_Properties *propSPI, uint8_t *Tx_Data, uint32_t length){
uint8_t dummy_rx[10]={0};

propSPI->Transciver.Rx_data=dummy_rx;
propSPI->Transciver.Rx_data_size=length;

propSPI->Transciver.Tx_data=Tx_Data;
propSPI->Transciver.Tx_data_size=length;

propSPI->State=SPI_STATE_BUSY_TX;

Enable_Txe_Interrupt(propSPI);
Enable_Rxe_Interrupt(propSPI);
Enable_Spi(propSPI);
while(propSPI->Irq_State != Irq_State_No_Interrupt);

}





	
static void Rx_Handle(SPI_Properties *propSPI){

	if( propSPI->SPI_Settings.DataSize == SPI_DataSize_8Bit){
	 *propSPI->Transciver.Rx_data = propSPI->SPI_Settings.SPIx->DR;

	}

	if( propSPI->SPI_Settings.DataSize == SPI_DataSize_16Bit){
		
	  propSPI->SPI_Settings.SPIx->DR = *((uint16_t*)propSPI->Transciver.Tx_data);
		propSPI->Transciver.Tx_data = propSPI->Transciver.Tx_data + 2;
	
		propSPI->Transciver.Tx_data_size = propSPI->Transciver.Tx_data_size - 2;
	
	}
	
	Disable_Rxe_Interrupt(propSPI);
	Disable_Spi(propSPI);	
	


}

static void Tx_Handle(SPI_Properties *propSPI){

	if( propSPI->SPI_Settings.DataSize == SPI_DataSize_8Bit){
	 propSPI->SPI_Settings.SPIx->DR= *propSPI->Transciver.Tx_data;

	}

	if( propSPI->SPI_Settings.DataSize == SPI_DataSize_16Bit){
		
	  propSPI->SPI_Settings.SPIx->DR = *((uint16_t*)propSPI->Transciver.Tx_data);
		propSPI->Transciver.Tx_data = propSPI->Transciver.Tx_data + 2;
	
		propSPI->Transciver.Tx_data_size = propSPI->Transciver.Tx_data_size - 2;
	
	}
	

	Disable_Txe_Interrupt(propSPI);
	Disable_Spi(propSPI);	
	


}


void SPI_Master_Tx(SPI_Properties *propSPI, uint8_t Tx_Data){

  *propSPI->Transciver.Tx_data=Tx_Data;
  
	Enable_Txe_Interrupt(propSPI);
  Enable_Spi(propSPI);
  while(propSPI->Irq_State != Irq_State_No_Interrupt);	 

}


uint8_t  SPI_Master_Rx(SPI_Properties *propSPI){
         
	uint8_t  dummy=0xDD;
 *propSPI->Transciver.Tx_data=dummy;
	

  Enable_Txe_Interrupt(propSPI);
	Enable_Rxe_Interrupt(propSPI);
  Enable_Spi(propSPI);

while(propSPI->Irq_State != Irq_State_No_Interrupt);
	
	return  *propSPI->Transciver.Rx_data;
}












