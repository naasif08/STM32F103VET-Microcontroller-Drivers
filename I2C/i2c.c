#include "stm32f10x.h" 
#include "delay.h"
#include "GPIO_Config.h"
#include "i2c.h"


/*
*****- I have a confession and I have something to say. This I2C peripheral driver developing
was very complex I think. All the macros and finctions are not absolutely written by me sometimes
I had to take help of Examples developed by my instructor or teacher. Some functions are exactly
copied and modified in this I2C Driver. I2C is a complex thing! But in my SPI, GPIO and Delay drivers or
libraries development I had written all most of the code. I'm just saying no intention.

Since I'm writting this text I have developed GPIO, SPI, Delay and I2C Driver using CMSIS API. 
My Delay, SPI and GPIO drivers are tested with Hardware but this time in the case of I2C I don't have 
much time to test. So it's not tested by hardware yet. But I believe It will work! 

And I'm going to give credit to my instructor for teaching me such great things!


*/ 


#define  tmp    *( ( unsigned *) 0x123 )


void I2C_Init(I2C_Settings *i2c){
		
	GPIO_Port_Properties portB;
	uint32_t ccr=0;
/* Setting Up Clock for Alternate Function */
  RCC->APB2ENR |=0x01;
		

	portB.GPIOx=GPIOB;
	portB.GPIO_Port_Name= PortB;
	
	
	/* Enabling Clock for I2C1 */
	if(i2c->I2Cx == I2C1){
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;	
	/* GPIO Pins setup for I2C1 */	
	RCC->APB2ENR |= 1 << 3; // enabling clock for PORTB
		
		portB.pins[0]=Pin5;
		portB.Mode[0]=Mode_Output_10MHz_Open_Drain;
		
		portB.pins[1]=Pin6;
		portB.Mode[1]=Mode_Output_10MHz_Open_Drain;
		
		portB.pins[2]=Pin7;
		portB.Mode[2]=Mode_Output_10MHz_Open_Drain;
		
		
	}
	
	/* Enabling Clock for I2C2 */
	if(i2c->I2Cx == I2C2){
	RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
			/* GPIO Pins setup for I2C1 */	
		RCC->APB2ENR |= 1 << 3; // enabling clock for PORTB
		
		portB.pins[0]=Pin10;
		portB.Mode[0]=Mode_Output_10MHz_Open_Drain;
		
		portB.pins[1]=Pin11;
		portB.Mode[1]=Mode_Output_10MHz_Open_Drain;
		
		portB.pins[2]=Pin12;
		portB.Mode[2]=Mode_Output_10MHz_Open_Drain;
		
		
		
	}
	
	// setup port
	setUpPort(portB);
	
	
	
	     
	
	    // if in standard mode
			if(i2c->properties.ClockSpeed == ClockSpeed_Standard_Mode_100k){
				
				i2c->I2Cx->CCR &= (~(1 << 15)); // setting up standard mode 
			
			ccr = (i2c->properties.PERIPHERAL_CLK * 1000000)/(2 * ClockSpeed_Standard_Mode_100k); 	
			i2c->I2Cx->CCR |=ccr;
			
				
				
				
			}
			
	    // if in fast mode
	    if(i2c->properties.ClockSpeed == ClockSpeed_Fast_Mode_400k){
				
				
				 i2c->I2Cx->CCR |= (1 << 15);// setting up fast mode
			
				if(i2c->properties.DutyCycle == DutyCycle_1_to_1 || i2c->properties.DutyCycle == DutyCycle_1_to_2 ){
					
				 i2c->I2Cx->CCR &= (~(1 << 14));// setting up duty cycle 1:2
				
				 ccr = (i2c->properties.PERIPHERAL_CLK * 1000000)/(3 * ClockSpeed_Fast_Mode_400k); 
         i2c->I2Cx->CCR |=ccr;		
         			
             					
				
				}
			
				
				if(i2c->properties.DutyCycle == DutyCycle_9_to_16){
					
					i2c->I2Cx->CCR |= (1 << 14);	// setting up duty cycle 16:9
				
					 	ccr = (i2c->properties.PERIPHERAL_CLK * 1000000)/(25 * ClockSpeed_Fast_Mode_400k); 	
					  i2c->I2Cx->CCR |=ccr;
					 	
				
				}
			
				
			}
	
			/* checking I2C Peripheral clock frequency 2MHz*/
		if(i2c->properties.PERIPHERAL_CLK == PERIPHERAL_CLK_FREQ_2MHZ){
		i2c->I2Cx->CR2 |= PERIPHERAL_CLK_FREQ_2MHZ;
		}
		/* checking I2C Peripheral clock frequency 3MHz*/
		if(i2c->properties.PERIPHERAL_CLK == PERIPHERAL_CLK_FREQ_3MHZ){
		i2c->I2Cx->CR2 |= PERIPHERAL_CLK_FREQ_3MHZ;
		}	
		/* checking I2C Peripheral clock frequency 4MHz*/
		if(i2c->properties.PERIPHERAL_CLK == PERIPHERAL_CLK_FREQ_4MHZ){
		i2c->I2Cx->CR2 |= PERIPHERAL_CLK_FREQ_4MHZ;
		}		
			/* checking I2C Peripheral clock frequency 5MHz*/
		if(i2c->properties.PERIPHERAL_CLK == PERIPHERAL_CLK_FREQ_5MHZ){
		i2c->I2Cx->CR2 |= PERIPHERAL_CLK_FREQ_5MHZ;
		}	
		/* checking I2C Peripheral clock frequency 6MHz*/
		if(i2c->properties.PERIPHERAL_CLK == PERIPHERAL_CLK_FREQ_6MHZ){
		i2c->I2Cx->CR2 |= PERIPHERAL_CLK_FREQ_6MHZ;
		}		
		/* checking I2C Peripheral clock frequency 7MHz*/
		if(i2c->properties.PERIPHERAL_CLK == PERIPHERAL_CLK_FREQ_7MHZ){
		i2c->I2Cx->CR2 |= PERIPHERAL_CLK_FREQ_7MHZ;
		}		
		/* checking I2C Peripheral clock frequency 8MHz*/
		if(i2c->properties.PERIPHERAL_CLK == PERIPHERAL_CLK_FREQ_8MHZ){
		i2c->I2Cx->CR2 |= PERIPHERAL_CLK_FREQ_8MHZ;
		}		
		/* checking I2C Peripheral clock frequency 9MHz*/
		if(i2c->properties.PERIPHERAL_CLK == PERIPHERAL_CLK_FREQ_9MHZ){
		i2c->I2Cx->CR2 |= PERIPHERAL_CLK_FREQ_9MHZ;
		}		
		/* checking I2C Peripheral clock frequency 10MHz*/
		if(i2c->properties.PERIPHERAL_CLK == PERIPHERAL_CLK_FREQ_10MHZ){
		i2c->I2Cx->CR2 |= PERIPHERAL_CLK_FREQ_10MHZ;
		}		
			
			
			
		   /* clock streching enabled or disabled checking */	
			if(i2c->properties.ClockStretch_bit == ClockStretch_Enable){
            i2c->I2Cx->CR1 &= (~(1 << 7));				  
			}
			if(i2c->properties.ClockStretch_bit == ClockStretch_Disable){
            i2c->I2Cx->CR1 |= (1 << 7);				  
			}
			
			
			/* ACk Bit checking */	
			if(i2c->properties.ACK_Bit == ACK_Enable){
            i2c->I2Cx->CR1 |= 1 << 10;			  
			}
			/*  ACk Bit checking */	
			if(i2c->properties.ACK_Bit == ACK_Disable){
            i2c->I2Cx->CR1 &= (~(1 << 10));			  
			}
			
			
			/*  GeneralCall Mode checking */	
			if(i2c->properties.GeneralCallMode == GeneralCallMode_Enable){
            i2c->I2Cx->CR1 |= (1 << 6);			  
			}
			/* GeneralCall Mode checking */	
			if(i2c->properties.GeneralCallMode == GeneralCallMode_Disable){
            i2c->I2Cx->CR1 &= (~(1 << 6));			  
			}
			
			
			 /* Dual Addressing Mode checking in slave */	
			if(i2c->properties.DualAddressMode == DualAddressMode_Enable){
           i2c->I2Cx->OAR2 |= 1 << 0;	
				
				
				/*  Remember you can use only 7bit mode in dual addressing mode */
				if(i2c->properties.Addressing_7bit_or_10bit == Addressing_7bit){
				
				  i2c->I2Cx->OAR1 &= (~(1 << 15));	
					
					
					/* Putting Address into register*/	
				  i2c->I2Cx->OAR1 |= i2c->properties.Address1 << 1;
					
					/* Putting Address into register2*/	
				  i2c->I2Cx->OAR2 |= i2c->properties.Address2 << 1;
					
				}
            
				
			}
			
						
			/* Dual Addressing Mode checking in slave */	
			if(i2c->properties.DualAddressMode == DualAddressMode_Disable){
           i2c->I2Cx->OAR2 &= ~(1 << 0);	
				
							
				/* Addressing Mode checking in slave */	
			if(i2c->properties.Addressing_7bit_or_10bit == Addressing_7bit){
            
				i2c->I2Cx->OAR1 &= (~(1 << 15));			 
               
				
			/* Putting Address into register*/	
			i2c->I2Cx->OAR1 |= i2c->properties.Address1 << 1;
            				
			}
			
	
			
			/* Addressing Mode checking in slave */	
			if(i2c->properties.Addressing_7bit_or_10bit == Addressing_10bit){
           
				i2c->I2Cx->OAR1 |= 1 << 15;	
								
				/* Putting Address into register*/	
				i2c->I2Cx->OAR1 |= i2c->properties.Address1;
			}

				
				
			}
			// end of dual addressing mode based IF statement
			
			
			
			/* Enabling I2C, TXE & RXE Interrupt and other things */
			if(i2c->I2Cx == I2C1){
			NVIC_EnableIRQ(I2C1_ER_IRQn); 
			NVIC_EnableIRQ(I2C1_EV_IRQn);
			}
			
			if(i2c->I2Cx == I2C2){
			NVIC_EnableIRQ(I2C2_ER_IRQn); 
			NVIC_EnableIRQ(I2C2_EV_IRQn);
			}

			
	



}



void Enable_I2C_Peripheral(I2C_Settings *i2c){

i2c->I2Cx->CR1 |= 1<<0;

}


void Disable_I2C_Peripheral(I2C_Settings *i2c){

i2c->I2Cx->CR1 &= ~(1<<0);

}

void Enable_POS_Bit(I2C_Settings *i2c){

i2c->I2Cx->CR1 |= 1<<11;	

}

void Disable_POS_Bit(I2C_Settings *i2c){

i2c->I2Cx->CR1 &= ~(1<<11);

}

void Disable_START_CONDITION(I2C_Settings *i2c){

	i2c->I2Cx->CR1 &= ~(1<<8);

}

void Enable_START_CONDITION(I2C_Settings *i2c){

  i2c->I2Cx->CR1 |= 1<<8;

}


void Enable_STOP_CONDITION(I2C_Settings *i2c){

  i2c->I2Cx->CR1 |= 1<<9;

}

void Disable_STOP_CONDITION(I2C_Settings *i2c){


  i2c->I2Cx->CR1 &= ~(1<<9);

}


void Enable_ErrorInterrupt(I2C_Settings *i2c){

i2c->I2Cx->CR2 |= 1<<8;

}
void Disable_ErrorInterrupt(I2C_Settings *i2c){

i2c->I2Cx->CR2 &= ~(1<<8);

}

void Enable_EventInterrupt(I2C_Settings *i2c){

	i2c->I2Cx->CR2 |= 1<<9;

}
void Disable_EventInterrupt(I2C_Settings *i2c){

	i2c->I2Cx->CR2 &= ~(1<<9);

}

void Enable_Tx_Rx_BufferInterrupt(I2C_Settings *i2c){

	i2c->I2Cx->CR2 |= (1<<10);

}

void Disable_Tx_Rx_BufferInterrupt(I2C_Settings *i2c){

	i2c->I2Cx->CR2 &= ~(1<<10);
	
}

void Manage_Acking(I2C_Settings *i2c,uint8_t val){

	if(val){
	
		i2c->I2Cx->CR1 |= I2C_CR1_ACK_High;
		
	
	}else{
	
	  i2c->I2Cx->CR1 &= I2C_CR1_ACK_Low;
		
	}



}


uint8_t I2C_Bus_Busy_or_Not(I2C_Settings *i2c){
	
	
if(i2c->I2Cx->CR2 & I2C_SR2_BUSY){

return 1;
}else{

return 0;
}

	
}


uint8_t I2C_Is_SB_Set(I2C_Settings *i2c){

if(i2c->I2Cx->SR1 & I2C_SR1_SB){
return 1;
}else{
return 0;
}


}

uint8_t I2C_Is_ADDR_Set(I2C_Settings *i2c){

if(i2c->I2Cx->SR1 & I2C_SR1_ADDR){

return 1;
}
else{

return 0;
}

}


 void Send_addr_first(I2C_Settings *i2c,uint8_t slave_address){
 
 
	 i2c->I2Cx->DR = slave_address;
 
 }

void Clear_ADDR_Flag(I2C_Settings *i2c){

	uint16_t val;
	
	val = i2c->I2Cx->SR1;
	val = i2c->I2Cx->SR2;

}

 void I2C_MemTxCpltCallback(I2C_Settings *i2c)
{
	/* this code I copied from my instructors examples
	 the aim of this macro is to prevent warnning. I have some 
  confusion also. I've been using it first time. 	
	
	*/
	
  /* Prevent unused argument(s) compilation warning */
  UNUSED(i2c);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I2C_TxCpltCallback could be implemented in the user file
   */
}
  void I2C_MasterTxCpltCallback(I2C_Settings *i2c)
{
	/* this code I copied from my instructors examples
	 the aim of this macro is to prevent warnning. I have some 
  confusion also. I've been using it first time. 	
	
	*/
  /* Prevent unused argument(s) compilation warning */
  UNUSED(i2c);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I2C_TxCpltCallback could be implemented in the user file
   */
}



 void I2C_MemRxCpltCallback(I2C_Settings *i2c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(i2c);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I2C_TxCpltCallback could be implemented in the user file
   */
}


 void I2C_SlaveRxCpltCallback(I2C_Settings *i2c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(i2c);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I2C_TxCpltCallback could be implemented in the user file
   */
}


 void I2C_SlaveTxCpltCallback(I2C_Settings *i2c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(i2c);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I2C_TxCpltCallback could be implemented in the user file
   */
}



 void I2C_MasterRxCpltCallback(I2C_Settings *i2c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(i2c);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I2C_TxCpltCallback could be implemented in the user file */
}
  



void I2C_master_tx(I2C_Settings *i2c, uint8_t slave_address, uint8_t *buffer, uint32_t len){

/* Enable I2C Peripheral   */
	Enable_I2C_Peripheral(i2c);


/* Checking Bus is busy or not   */	
	while(I2C_Bus_Busy_or_Not(i2c));
	
i2c->state = I2C_STATE_BUSY_TX;	
	
	i2c->data = buffer;
	i2c->dataCount = len;
	i2c->dataSize = len;	
	
/* Generate Start Condition*/	
	Enable_START_CONDITION(i2c);
	

/* Disabling POS bit   */
i2c->I2Cx->CR1 &= I2C_CR1_POS_Low;	


	while(!I2C_Is_SB_Set(i2c));

Send_addr_first(i2c,slave_address);	
	
	while(!I2C_Is_ADDR_Set(i2c));
	
	Clear_ADDR_Flag(i2c);
	
	Enable_Tx_Rx_BufferInterrupt(i2c);
	Enable_ErrorInterrupt(i2c);
	Enable_EventInterrupt(i2c);
	

}



void I2C_master_rx(I2C_Settings *i2c, uint8_t slave_adr, uint8_t *buffer, uint32_t len){



/* Enable I2C Peripheral   */
	Enable_I2C_Peripheral(i2c);


/* Checking Bus is busy or not   */	
	while(I2C_Bus_Busy_or_Not(i2c));
	
	Disable_POS_Bit(i2c);
	
i2c->state = I2C_STATE_BUSY_RX;	
	
	i2c->data = buffer;
	i2c->dataCount = len;
	i2c->dataSize = len;	
	
	
	/* 
	  
		Here I guess someting is missing.
		For 1 byte of receiving data at the starting point
		there should be disabled ACKing means NACK. Actually I need a practial check.
		Or to make contact with my instructor.
		
   */
	Manage_Acking(i2c,ACK_Enable);
	
	
/* Generate Start Condition*/	
	Enable_START_CONDITION(i2c);
	

/* Disabling POS bit   */
i2c->I2Cx->CR1 &= I2C_CR1_POS_Low;	


	while(!I2C_Is_SB_Set(i2c));

  Send_addr_first(i2c, slave_adr);	
	
	while(!I2C_Is_ADDR_Set(i2c));
	
	Clear_ADDR_Flag(i2c);
	
	Enable_Tx_Rx_BufferInterrupt(i2c);
	Enable_ErrorInterrupt(i2c);
	Enable_EventInterrupt(i2c);
	


}


void I2C_slave_tx(I2C_Settings *i2c, uint8_t *buffer, uint32_t len){


	/* Enable I2C Peripheral   */
	Enable_I2C_Peripheral(i2c);
	
	Disable_POS_Bit(i2c);

	i2c->state = I2C_STATE_BUSY_TX; 

	i2c->data = buffer;
	i2c->dataCount = len;
	i2c->dataSize = len;	
	
	Manage_Acking(i2c,ACK_Enable);
	
	
	Enable_Tx_Rx_BufferInterrupt(i2c);
	Enable_ErrorInterrupt(i2c);
	Enable_EventInterrupt(i2c);
	

}


void I2C_slave_rx(I2C_Settings *i2c, uint8_t *buffer, uint32_t len){

	/* Enable I2C Peripheral   */
	Enable_I2C_Peripheral(i2c);
	
	//while(I2C_Bus_Busy_or_Not(i2c));
	
	Disable_POS_Bit(i2c);
	
	i2c->state = I2C_STATE_BUSY_RX; 
	
	i2c->data = buffer;
	i2c->dataCount = len;
	i2c->dataSize = len;	
	
	Manage_Acking(i2c,ACK_Enable);
	
	
	Enable_Tx_Rx_BufferInterrupt(i2c);
	Enable_ErrorInterrupt(i2c);
	Enable_EventInterrupt(i2c);

	



}


static void I2C_MasterTransmit_TXE(I2C_Settings *i2c){
	

	  /* Write data to DR */
  i2c->I2Cx->DR = (*i2c->data++);
  i2c->dataCount--;

  if(i2c->dataCount == 0)
  {
    /* Disable BUF interrupt */
		i2c->I2Cx->CR2 &= ~ (I2C_CR2_ITBUFEN);
  }
	

}


static void I2C_MasterTransmit_BTF(I2C_Settings *i2c){

if(i2c->dataCount!=0){
  /* Write data to DR */
  i2c->I2Cx->DR = (*i2c->data++);
  i2c->dataCount--;
}else{

	/* Disable EVT, BUF and ERR interrupt */
	
	Disable_Tx_Rx_BufferInterrupt(i2c);
	Disable_ErrorInterrupt(i2c);
	Disable_EventInterrupt(i2c);
	
	Enable_STOP_CONDITION(i2c);
	
  /* i2c->state = I2C_STATE_READY; */
	
	 if(i2c->state == I2C_STATE_MEM_BUSY_TX)
    {
      i2c->state = I2C_STATE_READY;

      I2C_MemTxCpltCallback(i2c);
    }
    else
    {
      i2c->state = I2C_STATE_READY;

      I2C_MasterTxCpltCallback(i2c);
    }

   

}



}


 static void  I2C_MasterReceive_RXNE(I2C_Settings *i2c){
	 
	uint32_t tmpp = 0;
  /* 
	 there we have to follow mechanism of receiveing N bytes data(check data sheet)
	 it is the standard way of receiving at the time of N-1th data we need to send NACK

	 */
  tmpp = i2c->dataCount;// checking data size
  if(tmp > 3) // when data is grater than n-2 then it's OK
  {
    /* Read data from DR */
    (*i2c->data++) = i2c->I2Cx->DR;
    i2c->dataCount--;
  }
  else if((tmp == 2) || (tmp == 3))
  {
    /* 
		when N-2 we need to
		Disable BUF interrupt
     datas won't be read at this stage
		BTF ISR will take care of this. since we disabled Buffer Interrupt BTF will be
		turned ON. and this time data register has been filled with data3
		
		*/
		i2c->I2Cx->CR2 &= ~ I2C_CR2_ITBUFEN;
  }
  else
  {
		
		/*

		When data lenth is 1, it will be executed

		So we will follow the procedure of sending 1 byte of data

		*/
		
		
    /* Disable EVT, BUF and ERR interrupt */
			i2c->I2Cx->CR2 &= ~ I2C_CR2_ITEVTEN;
			i2c->I2Cx->CR2 &= ~ I2C_CR2_ITBUFEN;
			i2c->I2Cx->CR2 &= ~ I2C_CR2_ITERREN;

    /* Read data from DR */
    (*i2c->data++) = i2c->I2Cx->DR;
     i2c->dataCount--;

    if(i2c->state == I2C_STATE_MEM_BUSY_RX)
    {
      i2c->state = I2C_STATE_READY;
       I2C_MemRxCpltCallback(i2c);
    }
    else
    {
      i2c->state = I2C_STATE_READY;
			I2C_MasterRxCpltCallback(i2c);
    }
  }
   

 
}



static void I2C_MasterReceive_BTF(I2C_Settings *i2c){

// Here we will read data3 and RXNE flag will be cleared 
	 if(i2c->dataCount == 3)
  {
    /* Disable Acknowledge */
    i2c->I2Cx->CR1 &= ~ I2C_CR1_ACK;

    /* Read data from DR */
    (*i2c->data++) = i2c->I2Cx->DR;
     i2c->data--;
		
		/* 
		since we have read data from DR and Data2 will be on DR
		and Data1 will be in shift register and at the same time 
		there will be a NACK. 


		*/
		
  }
  else if(i2c->dataCount == 2)
  {
    /* Generate Stop */
    i2c->I2Cx->CR1 |=I2C_CR1_STOP;

    /* Read data from DR */
    (*i2c->data++) = i2c->I2Cx->DR; // reading Data2
    i2c->dataCount--;

    /* Read data from DR */
    (*i2c->data++) = i2c->I2Cx->DR; // Reading Data1
    i2c->dataCount--;

    /* Disable EVT and ERR interrupt */
			i2c->I2Cx->CR2 &= ~ I2C_CR2_ITEVTEN;
			i2c->I2Cx->CR2 &= ~ I2C_CR2_ITERREN;

    if(i2c->state == I2C_STATE_MEM_BUSY_RX)
    {
      i2c->state = I2C_STATE_READY;
      I2C_MemRxCpltCallback(i2c);
      
    }
    else
    {
      i2c->state = I2C_STATE_READY;
      I2C_MasterRxCpltCallback(i2c);
     
    }
  }
  else
  {
    /* Read data from DR */
    (*i2c->data++) = i2c->I2Cx->DR;
    i2c->data--;
  }



}

static  void  I2C_Slave_STOP_Generation(I2C_Settings *i2c){
 
		
  /* Disable EVT, BUF and ERR interrupt */
		i2c->I2Cx->CR2 &= ~ I2C_CR2_ITEVTEN;
		i2c->I2Cx->CR2 &= ~ I2C_CR2_ITBUFEN;
		i2c->I2Cx->CR2 &= ~ I2C_CR2_ITERREN;

  /* Clear STOPF flag */
	Disable_STOP_CONDITION(i2c);
	
	 

  /* Disable Acknowledge */
  i2c->I2Cx->CR1 &= ~I2C_CR1_ACK;

  i2c->state = I2C_STATE_READY;
 I2C_SlaveRxCpltCallback(i2c);
 
 }

 
 static void   I2C_SlaveTransmit_TXE(I2C_Settings *i2c){
 
   if(i2c->data != 0)
  {
    /* Write data to DR */
    i2c->I2Cx->DR = (*i2c->data++);
    i2c->dataCount--;
  }
 
 }


static void I2C_SlaveTransmit_BTF(I2C_Settings *i2c){


 if(i2c->data != 0)
  {
    /* Write data to DR */
    i2c->I2Cx->DR = (*i2c->data++);
    i2c->I2Cx--;
  }
  


}
 
static void I2C_SlaveReceive_RXNE(I2C_Settings *i2c)
{
  if(i2c->dataCount != 0)
  {
    /* Read data from DR */
    (*i2c->data++) = i2c->I2Cx->DR;
     i2c->dataCount--;
  }
  
}


static void I2C_SlaveReceive_BTF(I2C_Settings *i2c)
{
  if(i2c->dataCount != 0)
  {
    /* Read data from DR */
    (*i2c->data++) = i2c->I2Cx->DR;
     i2c->dataCount--;
  }
  
}

static void I2C_Error_Routine(I2C_Settings *i2c)
{
  /*
	
	do something here....
	
	
	*/
}


/*EV_IRQHandler*/
void EV_IRQHandler(I2C_Settings *i2c){
	
	uint32_t txe_flag, buf_inttr, BTF_flg, event_intr;

/* Master mode selected */
  if(( i2c->I2Cx->SR2 & I2C_SR2_MSL )){
		
	     /* I2C in mode Transmitter -----------------------------------------------*/
     if(( i2c->I2Cx->SR2 & I2C_SR2_TRA)){
		 
		 txe_flag =  (i2c->I2Cx->SR1  & I2C_SR1_TXE);
			 
			 // checking if we enabled buffer(TXE & RXE) interrupt
		 buf_inttr =  (i2c->I2Cx->CR2 & I2C_CR2_ITBUFEN);
			 
			 // checking BTF flag is 1 or 0
		 BTF_flg = (i2c->I2Cx->SR1 &  I2C_SR1_BTF);
			 
			// checking out if other events are enabled except TXE & RXE
		 event_intr = (i2c->I2Cx->CR2 & I2C_CR2_ITEVTEN);
			 
			/* TXE set and BTF reset -----------------------------------------------*/
      if(txe_flag && buf_inttr && (! BTF_flg))
      {
				/*  tmp= Txe flag && TXE&RXE interrupt enabled && ( btf flag is not set)  
				
				*/
				
				// now Master can transmit line is ok! 
				// In this functions the real data will be transmitted
        I2C_MasterTransmit_TXE(i2c);
      } 
			  else if((BTF_flg && event_intr ))
      {
				/* when other events are enabled and BTF flag is set. that means Data register
          and shift register becomes full or empty! 

				*/
				
				// now if we are in transmision mode then time to start generation
				// of if both are full then time to read data register.
        I2C_MasterTransmit_BTF(i2c);
      }
		 
		 
		 }/* I2C Master in Receiver mode*/	
		 else{
		 
		    /*
			     when you enter this else statement it means master in receiver mode
           because (i2c->I2Cx->SR2 & I2C_SR2_TRA)==0 that means bit on SR2 is 0.
			     that means data received

			 */  
			uint32_t rxe_flag, buf_inttr, BTF_flg, event_intr;
		
		 rxe_flag =  (i2c->I2Cx->SR1  & I2C_SR1_RXNE);  // checking if RXE is triggered
		 buf_inttr =  (i2c->I2Cx->CR2 & I2C_CR2_ITBUFEN); // checking BUFFer interrupt is enabled on register CR2 
		 BTF_flg = (i2c->I2Cx->SR1 &  I2C_SR1_BTF);  // checking id BTF flag is set or not
		 event_intr = (i2c->I2Cx->CR2 & I2C_CR2_ITEVTEN); // checking event interrupt is enabled or not in CR2 register
	   
		  /* RXNE set and BTF reset -----------------------------------------------*/
      if((rxe_flag) && (buf_inttr) && (! BTF_flg))
      {
				/*
				 this time RXE flag is set and buffer(RXE&TXE) interrupt is enabled and BTF flag is not set
				*/
				// so its time to receive datas and acking 
        I2C_MasterReceive_RXNE(i2c);
      } 
			/* BTF set -------------------------------------------------------------*/
      else if((BTF_flg) && (event_intr))
      {
        I2C_MasterReceive_BTF(i2c);
      }
		 
		 
		 
		 }
	
	
	
	}/* Slave mode selected */
  else
  {	
		/* slave mode starts here */
	
		 uint32_t addr_flag,TRAbit, STP_flg, event_intr;
		
		 addr_flag =  (i2c->I2Cx->SR1  & I2C_SR1_ADDR); // checking ADDR Flag
		 event_intr = (i2c->I2Cx->CR2 & I2C_CR2_ITEVTEN);	//  checking if Event Interrupt is enabled or not
		 STP_flg = (i2c->I2Cx->SR1 &  I2C_SR1_STOPF); // checking STOP flag
		 TRAbit =  (i2c->I2Cx->SR2 & I2C_SR2_TRA);  // checking TRA bit in Status register 2
		
		/* ADDR set --------------------------------------------------------------*/
    if((addr_flag ) && (event_intr))
    {
			/* if addr flag is 1 and event interrupt is enabled then this will be executed  */
			
      Clear_ADDR_Flag(i2c); // simply clearing the ADDR flag by two status registers
    }
		/* STOPF set --------------------------------------------------------------*/
    else if((STP_flg) && (TRAbit))
    {
			/*
			if STOP Flag is 1 and TRA bit =1 (That means data transmitted )
			That means all the datas are supposed to be sent are already sent
			and here TRA==1 is the indication and STOP condition is generated. 
      So stop.			
			
			*/
			
      I2C_Slave_STOP_Generation(i2c);
    }
		 
	    /* I2C in mode Transmitter -----------------------------------------------*/
    else if(TRAbit)
    {
			/*  
			  TRA bit high and that indicates that 
			  data transmision. 

			*/
		uint32_t tmp1 = 0, tmp2 = 0, tmp3 = 0, tmp4 = 0;
			
			tmp1 =  (i2c->I2Cx->SR1 &  I2C_SR1_TXE ); // checking TXE flag in SR1 register
			tmp2 =  (i2c->I2Cx->CR2 &  I2C_CR2_ITBUFEN); // checking out buffer interrupt is enabled or not in CR@ register
			tmp3 = (i2c->I2Cx->SR1 & I2C_SR1_BTF); // checking BTF flag in SR1 register
			tmp4 = (i2c->I2Cx->CR2 & I2C_CR2_ITEVTEN); // cheking out if event interrupt is enabled or not
			
      /* TXE set and BTF reset -----------------------------------------------*/
      if((tmp1) && (tmp2) && (! tmp3))
      {
				/*  
				tmp1=TXE=1  &&  tmp2=buffer_int=1 && tmp3=BTF!=1 or BTF=0
				
				*/
        I2C_SlaveTransmit_TXE(i2c); // this will just continue until count is 0.
      }
      /* BTF set -------------------------------------------------------------*/
      else if((tmp3) && (tmp4))
      {
				/*  
				  tmp3=BTF=1 && tmp4=event_inturrpt_enabled=1
          that means both data and shift register are empty				
				
				*/
				
        I2C_SlaveTransmit_BTF(i2c); // this will also continue until 0
				
      }
    }
    /* I2C in mode Receiver --------------------------------------------------*/
    else
    {
			uint32_t tmp1 = 0, tmp2 = 0, tmp3 = 0, tmp4 = 0;
      tmp1 =  (i2c->I2Cx->SR1 & I2C_SR1_RXNE); // checking if RXNE flag is set
			tmp2 =  (i2c->I2Cx->CR2 & I2C_CR2_ITBUFEN); // checking if Buffer Interupt is enabled in CR2 register
			tmp3 = (i2c->I2Cx->SR1  &   I2C_SR1_BTF); // Checking BTF flag in SR1 regiser
			tmp4 = (i2c->I2Cx->CR2  &   I2C_CR2_ITEVTEN); // checking if event interrupt is enabled or not
			
      /* RXNE set and BTF reset ----------------------------------------------*/
      if((tmp1 ) && (tmp2 ) && (! tmp3))
      {
				/*
				tmp1=RXNE flag=1 && bufferinterrupt=1 && BTF=0 or Not 1
				
				*/
        I2C_SlaveReceive_RXNE(i2c); // it's simple just reading data
      }
      /* BTF set -------------------------------------------------------------*/
      else if((tmp3) && (tmp4))
      {
				/* 
				 tmp3==btf flag=1 && tmp4=event interrupt=1 
				 this time both are empty
 
				*/
				
        I2C_SlaveReceive_BTF(i2c);
				// master will take care of ending communication. slave has nothing to do.
      }
    }	
		
	
	}


}




static void I2C_Slave_AF(I2C_Settings *i2c)
{  
  /* Disable EVT, BUF and ERR interrupt */
	i2c->I2Cx->CR2 &= ~ I2C_CR2_ITEVTEN;
	i2c->I2Cx->CR2 &= ~ I2C_CR2_ITBUFEN;
	i2c->I2Cx->CR2 &= ~ I2C_CR2_ITERREN;

  /* Clear AF flag */
  i2c->I2Cx->SR1 &= ~ (I2C_SR1_AF);

  /* Disable Acknowledge */
  i2c->I2Cx->CR1 &= ~I2C_CR1_ACK;

  i2c->state = I2C_STATE_READY;
	I2C_SlaveTxCpltCallback(i2c);
 
}







/*ER_IRQHandler*/
void ER_IRQHandler(I2C_Settings *i2c){

  uint32_t tmp1 = 0, tmp2 = 0, tmp3 = 0;
	
	
	tmp1 =  (i2c->I2Cx->SR1 & I2C_SR1_BERR);// checking out Bus error is happened or not
  tmp2 = (i2c->I2Cx->CR2 & I2C_CR2_ITERREN); // checking out is error interrupt is enabled or not
  
	/* I2C Bus error interrupt occurred ----------------------------------------*/
  if((tmp1) && (tmp2 ))
  {
		/* 
		 this if satatement will be executed when Bus error is happened 
		*/
    i2c->ErrorCode |= I2C_ERROR_BERR; // Here simply we are putting Error Status on Error Code

    /* Clear BERR flag */
		i2c->I2Cx->SR1 &= ~ (I2C_SR1_BERR); // clearing the Bus error flag
  }

  tmp1 =  (i2c->I2Cx->SR1 & I2C_SR1_ARLO); // checking Arbitration Lost flag
  tmp2 = (i2c->I2Cx->CR2 & I2C_CR2_ITERREN); // checking out is error interrupt is enabled or not
  /* I2C Arbitration Loss error interrupt occurred ---------------------------*/
  if((tmp1 ) && (tmp2))
  {
		/*
		 tmp1= ARLO_Flag=1 && temp2= Interrupt is enabled=1
		
		*/
    i2c->ErrorCode |= I2C_ERROR_ARLO; // putting error code

    /* Clear ARLO flag */
    i2c->I2Cx->SR1 &= ~ (I2C_SR1_ARLO); 
  }

  tmp1 =  (i2c->I2Cx->SR1 & I2C_SR1_AF); // Acknowledge Failure flag checking
  tmp2 = (i2c->I2Cx->CR2 & I2C_CR2_ITERREN );  // checking out is error interrupt is enabled or not 
  /* I2C Acknowledge failure error interrupt occurred ------------------------*/
  if((tmp1 ) && (tmp2 ))
  {
		/*
		tmp1= Acknowledge failure=1 && temp2= Interrupt is enabled=1
		
		*/
		
    tmp1 = ( i2c->I2Cx->SR2 & I2C_SR2_MSL );// checking Master Mode or not
    tmp2 = i2c->dataCount; // putting count value
    tmp3 = i2c->state; // putting state
    if(( ! tmp1 ) && (tmp2 == 0) && (tmp3 == I2C_STATE_BUSY_TX))
    {
			/*
			!tmp1(0)=1 && count==0 && state is busy Tx
			 THat means if device is in slave mode this will work
			
			*/
			// Handling slave AF function
      I2C_Slave_AF(i2c);
    }
    else
    { /*
			 Now it's in master mode and AckF happened
			
			*/
      i2c->ErrorCode |= I2C_ERROR_AF;
      /* Clear AF flag */
       i2c->I2Cx->SR1 &= ~ (I2C_SR1_AF);
    }
  }

 tmp1 =  (i2c->I2Cx->SR1 & I2C_SR1_OVR); // checking Overrun/Underrun on SR1
  tmp2 = (i2c->I2Cx->CR2 & I2C_CR2_ITERREN); // checking Interrupt
  /* I2C Over-Run/Under-Run interrupt occurred -------------------------------*/
  if((tmp1) && (tmp2))
  {
		/*
		In reception when a new byte is received (including ACK pulse) and the DR register has not 
		been read yet. New received byte is lost.
    –In transmission when a new byte should be sent and the DR register has not been written yet.
 		The same byte is sent twice
		
		*/
    i2c->ErrorCode |= I2C_ERROR_OVR;
    /* Clear OVR flag */
    i2c->I2Cx->SR1 &= ~ (I2C_SR1_OVR);
  }

  if(i2c->ErrorCode != I2C_ERROR_NONE)
  { /* 
		THis time we are checking out if there is something error occured and 
		we have to make dicission

		*/
    i2c->state = I2C_STATE_READY; // make state is ready
    
    /* Disable Pos bit in I2C CR1 when error occurred in Master/Mem Receive IT Process */
    i2c->I2Cx->CR1 &= ~I2C_CR1_POS;
		
		// Do something there Like RED LED Blinking
		I2C_Error_Routine(i2c);
    
  }

	
}














