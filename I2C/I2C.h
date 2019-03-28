#ifndef I2C_H
#define I2C_H

#include "stdint.h"
#include "stm32f10x.h"
 
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

 
/* I2C CR1 Register */
#define I2C_CR1_PE_High          I2C_CR1_PE
#define I2C_CR1_PE_Low           (~I2C_CR1_PE)
#define I2C_CR1_SMBUS_High       I2C_CR1_SMBUS
#define I2C_CR1_SMBUS_Low        (~I2C_CR1_SMBUS)
#define I2C_CR1_SMBTYPE_High     I2C_CR1_SMBTYPE
#define I2C_CR1_SMBTYPE_Low      (~I2C_CR1_SMBTYPE)
#define I2C_CR1_ENARP_High       I2C_CR1_ENARP
#define I2C_CR1_ENARP_Low        (~I2C_CR1_ENARP)
#define I2C_CR1_ENPEC_High       I2C_CR1_ENPEC
#define I2C_CR1_ENPEC_Low        (~I2C_CR1_ENPEC)
#define I2C_CR1_ENGC_High        I2C_CR1_ENGC
#define I2C_CR1_ENGC_Low         (~I2C_CR1_ENGC)
#define I2C_CR1_NOSTRETCH_High   I2C_CR1_NOSTRETCH
#define I2C_CR1_NOSTRETCH_Low    (~I2C_CR1_NOSTRETCH)
#define I2C_CR1_START_High       I2C_CR1_START
#define I2C_CR1_START_Low        (~I2C_CR1_START)
#define I2C_CR1_STOP_High        I2C_CR1_STOP
#define I2C_CR1_STOP_Low         (~I2C_CR1_STOP)
#define I2C_CR1_ACK_High         I2C_CR1_ACK
#define I2C_CR1_ACK_Low          (~I2C_CR1_ACK)
#define I2C_CR1_POS_High          I2C_CR1_POS
#define I2C_CR1_POS_Low          (~I2C_CR1_POS)
 
 	
#define UNUSED(x) ((void)(x))	
 
#define I2C_ERROR_NONE       ((uint32_t)0x00000000)    /*!< No error           */
#define I2C_ERROR_BERR       ((uint32_t)0x00000001)    /*!< BERR Bus error         */
#define I2C_ERROR_ARLO       ((uint32_t)0x00000002)    /*!< ARLO Arbitration lost (master mode) error         */
#define I2C_ERROR_AF         ((uint32_t)0x00000003)    /*!< AF Acknowledge failure error           */
#define I2C_ERROR_OVR        ((uint32_t)0x00000004)    /*!< OVR  Overrun/Underrun error          */
#define I2C_ERROR_DMA        ((uint32_t)0x00000005)    /*!< DMA transfer error */
#define I2C_ERROR_TIMEOUT    ((uint32_t)0x00000006)    /*!< Timeout Timeout or Tlow error  Error      */ 
 
 
 
 


#define PERIPHERAL_CLK_FREQ_2MHZ      ((uint32_t)2 )  
#define PERIPHERAL_CLK_FREQ_3MHZ      ((uint32_t)3 )  
#define PERIPHERAL_CLK_FREQ_4MHZ     ((uint32_t)4 )  
#define PERIPHERAL_CLK_FREQ_5MHZ     ((uint32_t)5 )  
#define PERIPHERAL_CLK_FREQ_6MHZ     ((uint32_t)6 )  
#define PERIPHERAL_CLK_FREQ_7MHZ     ((uint32_t)7 )  
#define PERIPHERAL_CLK_FREQ_8MHZ     ((uint32_t)8 ) 
#define PERIPHERAL_CLK_FREQ_9MHZ     ((uint32_t)9 )  
#define PERIPHERAL_CLK_FREQ_10MHZ     ((uint32_t)10 ) 


#define  ClockSpeed_Fast_Mode_400k         400000
#define  ClockSpeed_Standard_Mode_100k     100000


#define  DutyCycle_1_to_1          0x01
#define  DutyCycle_1_to_2          0x02
#define  DutyCycle_9_to_16         0x03


#define  ClockStretch_Enable       0x01
#define  ClockStretch_Disable      0x02

#define  ACK_Enable                 0x01
#define  ACK_Disable                0x00







#define  Mode_Master                0x01
#define  Mode_Slave                 0x02


#define GeneralCallMode_Enable      0x01
#define GeneralCallMode_Disable     0x02

#define  Addressing_7bit            0x01
#define  Addressing_10bit           0x02

#define  DualAddressMode_Enable     0x01
#define  DualAddressMode_Disable    0x02

/* value of FCLK must me 10MHz*/
#define  Standard_Mode_CCR_1_to_1   0x32 

#define  Fast_Mode_CCR_1_to_1       0x32 
#define  Fast_Mode_CCR_1_to_2       0x32 
#define  Fast_Mode_CCR_9_to_16      0x32 



typedef enum
{
  I2C_STATE_RESET             = 0x01,  /*!< I2C not yet initialized or disabled         */
  I2C_STATE_READY             = 0x02,  /*!< I2C initialized and ready for use           */
  I2C_STATE_BUSY              = 0x03,  /*!< I2C internal process is ongoing             */
  I2C_STATE_BUSY_TX           = 0x04,  /*!< Data Transmission process is ongoing        */
  I2C_STATE_BUSY_RX           = 0x05,  /*!< Data Reception process is ongoing           */
  I2C_STATE_MEM_BUSY_TX       = 0x06,  /*!< Memory Data Transmission process is ongoing */
  I2C_STATE_MEM_BUSY_RX       = 0x07,  /*!< Memory Data Reception process is ongoing    */
  I2C_STATE_TIMEOUT           = 0x08,  /*!< I2C timeout state                           */
  I2C_STATE_ERROR             = 0x09   /*!< I2C error state                             */
	
}I2C_State;




typedef struct
{
	uint32_t   PERIPHERAL_CLK; 
	uint32_t   ClockSpeed;     
	uint32_t   DutyCycle; 
  uint32_t   ClockStretch_bit;   
	uint32_t   ACK_Bit; 
	uint8_t    Mode_Master_or_Slave;	
	uint32_t   GeneralCallMode; 
	uint32_t   Addressing_7bit_or_10bit;  
  uint32_t   DualAddressMode; 	
	uint32_t   Address1;   
	uint32_t   Address2;   
	
}I2C_Properties;




typedef struct
{
	I2C_TypeDef       *I2Cx;               
	I2C_Properties    properties;
	I2C_State         state;             
	uint8_t           *data;              
  uint32_t          dataSize;            
  uint32_t          dataCount;           
	uint32_t          ErrorCode; 
	
}I2C_Settings;







/* Some Basic Functions-- Starts */
void I2C_Init(I2C_Settings *i2c);

void EV_IRQHandler(I2C_Settings *i2c);
void ER_IRQHandler(I2C_Settings *i2c);

/* Some Basic Functions-- Ends */




/* Interrupt, Start and Stop condition Related functions -- Starts*/


void Enable_I2C_Peripheral(I2C_Settings *i2c);
void Disable_I2C_Peripheral(I2C_Settings *i2c);

void Enable_POS_Bit(I2C_Settings *i2c);
void Disable_POS_Bit(I2C_Settings *i2c);

void Enable_START_CONDITION(I2C_Settings *i2c);
void Disable_START_CONDITION(I2C_Settings *i2c);

void Enable_STOP_CONDITION(I2C_Settings *i2c);
void Disable_STOP_CONDITION(I2C_Settings *i2c);

void Enable_ErrorInterrupt(I2C_Settings *i2c);
void Disable_ErrorInterrupt(I2C_Settings *i2c);

void Enable_EventInterrupt(I2C_Settings *i2c);
void Disable_EventInterrupt(I2C_Settings *i2c);

void Enable_Tx_Rx_BufferInterrupt(I2C_Settings *i2c);
void Disable_Tx_Rx_BufferInterrupt(I2C_Settings *i2c);


void Manage_Acking(I2C_Settings *i2c, uint8_t val);


void I2C_master_tx(I2C_Settings *i2c, uint8_t slave_address, uint8_t *buffer, uint32_t len);
void I2C_master_rx(I2C_Settings *i2c, uint8_t slave_adr, uint8_t *buffer, uint32_t len);

void I2C_slave_tx(I2C_Settings *i2c, uint8_t *buffer, uint32_t len);
void I2C_slave_rx(I2C_Settings *i2c, uint8_t *buffer, uint32_t len);



/* Interrupt, Start and Stop condition Related functions -- Ends*/




#endif




