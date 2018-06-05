#ifndef SPI_H
#define SPI_H

#include "stdint.h"
#include "stm32f10x.h"
#include "GPIO_Config.h"
#include "delay.h"


/* Required definations */

#define SPI_PCLK_DIV_2   							( ( uint32_t)  0 << 3 )
#define SPI_PCLK_DIV_4   							( ( uint32_t)  1 << 3 ) 
#define SPI_PCLK_DIV_8   							( ( uint32_t)  2 << 3 ) 
#define SPI_PCLK_DIV_16  							( ( uint32_t)  3 << 3 ) 
#define SPI_PCLK_DIV_32  							( ( uint32_t)  4 << 3 ) 
#define SPI_PCLK_DIV_64  							( ( uint32_t)  5 << 3 ) 
#define SPI_PCLK_DIV_128  						( ( uint32_t)  6 << 3 ) 
#define SPI_PCLK_DIV_256  						( ( uint32_t)  7 << 3 )

/* ---------------------------------------------------------------- */
#define SPI_CPhase_High             				( ( uint32_t) 1 << 0 )
#define SPI_CPhase_Low             			  	( ( uint32_t) 0 << 0 )
#define SPI_CPol_High             					( ( uint32_t) 1 << 1 )
#define SPI_CPol_Low             					  ( ( uint32_t) 0 << 1 )
#define SPI_Mode_Master                   	( ( uint32_t) 1 << 2 )
#define SPI_Mode_Slave                    	( ( uint32_t) 0 << 2 )
#define SPI_SSM_High             						( ( uint32_t) 1 << 9 )
#define SPI_SSM_Low             						( ( uint32_t) 0 << 9 )
#define SPI_SSI_High             						( ( uint32_t) 1 << 8 )
#define SPI_SSI_Low             						( ( uint32_t) 0 << 8 )
#define SPI_Direction_2line_uni             ( ( uint32_t) 0 << 15 )
#define SPI_Direction_1line_Bid_dont        ( ( uint32_t) 1 << 15 )
#define SPI_MSB                             ( ( uint32_t) 0 << 7 )
#define SPI_LSB                             ( ( uint32_t) 1 << 7 )

#define SPI_DataSize_8Bit                   ( ( uint32_t) 0 << 11 )
#define SPI_DataSize_16Bit                  ( ( uint32_t) 1 << 11 )

#define SPI_NSS_Software                     0
#define SPI_NSS_Hardware                     1

typedef enum
{
	Irq_State_No_Interrupt   = 0x00,
  Irq_State_TXE_Pending    = 0x01, 
  Irq_State_TXE_Clear      = 0x02,  
  Irq_State_RXE_Pending    = 0x03, 
  Irq_State_RXE_Clear      = 0x04,  
	
}Irq_State;



typedef enum
{
  SPI_STATE_RESET      = 0x00,  /*  SPI not yet initialized or disabled                */
  SPI_STATE_READY      = 0x01,  /*  SPI initialized and ready for use                  */
  SPI_STATE_BUSY       = 0x02,  /*  SPI process is ongoing                             */
  SPI_STATE_BUSY_TX    = 0x12,  /*  Data Transmission process is ongoing               */
  SPI_STATE_BUSY_RX    = 0x22,  /*  Data Reception process is ongoing                  */
  SPI_STATE_BUSY_TX_RX = 0x32,  /*  Data Transmission and Reception process is ongoing */
  SPI_STATE_ERROR      = 0x03   /*  SPI error state                                    */
}State;


typedef struct
{
	SPI_TypeDef   *SPIx;         /*  Specifies SPI1 or SPI2 or SPI3 */
	
  uint32_t Mode;               /*  Specifies the SPI operating mode.  */
                                   

  uint32_t Direction;          /*  Specifies the SPI Directional mode state. */
                                  
  uint32_t DataSize;           /*  Specifies the SPI data size. */
                                   

  uint32_t CPol;        /*  Specifies the serial clock steady state. */
                                   

  uint32_t CPhase;           /*  Specifies the clock active edge for the bit capture. */
                                 

  uint32_t NSS;                /*  Specifies whether the NSS signal is managed by
                                    hardware (NSS pin) or by software using the SSI bit. */
                                  

  uint32_t BaudRatePrescaler;  /*  Specifies the Baud Rate prescaler value which will be
                                    used to configure the transmit and receive SCK clock. */
                                    

  uint32_t MSBorLSB;           /*  Specifies whether data transfers start from MSB or LSB bit. */
	
}SPI_Settings;



typedef struct
{
	uint8_t      *Tx_data;      // pointer which takes the address of transmitting data variable or array
	uint8_t     Tx_data_size;  //Tx data size
	

	uint8_t      *Rx_data;      // pointer which takes the address of received data variable or array
	uint8_t     Rx_data_size;  //Rx data size
	
}Transceiver;



typedef struct
{
  SPI_Settings               SPI_Settings;       /* SPI registers base address */

	State                      State;
	
	Irq_State                  Irq_State;
  
  Transceiver                Transciver;	
	
}SPI_Properties;







void SPI_Init(SPI_Properties *propSPI);
void Enable_Txe_Interrupt(SPI_Properties *propSPI);
void Disable_Txe_Interrupt(SPI_Properties *propSPI);
void Enable_Rxe_Interrupt(SPI_Properties *propSPI);
void Disable_Rxe_Interrupt(SPI_Properties *propSPI);
void Enable_Spi(SPI_Properties *propSPI);
void Disable_Spi(SPI_Properties *propSPI);

void Tx_Master(SPI_Properties *propSPI, uint8_t *Tx_Data, uint32_t length);
void Rx_Master(SPI_Properties *propSPI, uint8_t *Rx_Data, uint32_t length);

void SPI_Slave_Tx(SPI_Properties *propSPI, uint8_t *Tx_Data, uint32_t length);
void SPI_Slave_Rx(SPI_Properties *propSPI, uint8_t *Rx_Data, uint32_t length);


void SPI_Irqn(SPI_Properties *propSPI);

static void Rx_Interrupt_Handle(SPI_Properties *propSPI);
static void Tx_Interrupt_Handle(SPI_Properties *propSPI);

void SPI_Master_Tx(SPI_Properties *propSPI, uint8_t Tx_Data);
uint8_t  SPI_Master_Rx(SPI_Properties *propSPI);

static void Tx_Handle(SPI_Properties *propSPI);
static void Rx_Handle(SPI_Properties *propSPI);


#endif
