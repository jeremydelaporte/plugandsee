/****************************************************************************
 *   $Id:: adc.c 5901 2010-12-14 19:09:02Z usb00423                         $
 *   Project: NXP LPC13Uxx ADC example
 *
 *   Description:
 *     This file contains ADC code example which include ADC 
 *     initialization, ADC interrupt handler, and APIs for ADC
 *     reading.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#include "LPC13Uxx.h"			/* LPC13Uxx Peripheral Registers */
#include "adc.h"

#ifndef _BV
#define _BV(_x_) (1UL << (_x_))
#endif

volatile uint32_t ADCValue[ADC_NUM];
volatile uint32_t ADCIntDone = 0;
volatile uint32_t OverRunCounter = 0;

#if BURST_MODE
volatile uint32_t channel_flag = 0; 
#endif

#if ADC_INTERRUPT_FLAG
/******************************************************************************
** Function name:		ADC_IRQHandler
**
** Descriptions:		ADC interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void ADC_IRQHandler (void) 
{
  uint32_t regVal;
  volatile uint32_t dummy;
  int i;
  
  regVal = LPC_ADC->STAT;		/* Read ADC will clear the interrupt */
  if ( regVal & 0x0000FF00 )	/* check OVERRUN error first */
  {
  	OverRunCounter++;
  	for ( i = 0; i < ADC_NUM; i++ )
  	{
  	  regVal = (regVal & 0x0000FF00) >> 0x08;
  	  /* if overrun, just read ADDR to clear */
  	  /* regVal variable has been reused. */
      if ( regVal & _BV(i) )
  	  {
        dummy = LPC_ADC->DR[i];
  	  }
  	}
	LPC_ADC->CR &= ~((0x7<<24)|(0x1<<16));	/* stop ADC now, turn off BURST bit. */ 
  	ADCIntDone = 1;
  	return;	
  }
    
  for ( i = 0; i < ADC_NUM; i++ )
  {
    if ( regVal & _BV(i) )
#if TENBIT_MODE
      ADCValue[i] = ( LPC_ADC->DR[i] >> 6 ) & 0x3FF;
#else
      ADCValue[i] = ( LPC_ADC->DR[i] >> 4 ) & 0xFFF;
#endif
  }

#if BURST_MODE
  channel_flag |= (regVal & 0xFF);
  if ( (channel_flag & 0xFF) == 0xFF )
  {
  	/* All the bits in have been set, it indicates all the ADC 
  	channels have been converted. */
  	LPC_ADC->CR &= 0xF8FeFFFF;	/* stop ADC now */
#if ADGINTEN
    dummy = LPC_ADC->GDR;
#endif
  	channel_flag = 0; 
  	ADCIntDone = 1;
  }
#else
  LPC_ADC->CR &= ~(0x7<<24);	/* stop ADC now */ 
  ADCIntDone = 1;
#endif
  return;
}
#endif

/*****************************************************************************
** Function name:		ADCInit
**
** Descriptions:		initialize ADC channel
**
** parameters:			ADC clock rate
** Returned value:		None
** 
*****************************************************************************/
void ADCInit( uint32_t ADC_Clk ) {

	// Disable Power down bit to the ADC block
	LPC_SYSCON->PDRUNCFG &= ~(1<<4);
	// Enable AHB clock to the ADC
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);

	LPC_IOCON->PIO0_16 &= ~(1<<7); // Clear bit7, change to analog mode
	LPC_IOCON->PIO0_16 |= 1; // ADC IN5

	LPC_ADC->CR = (1<<5);  // Select channel 5 on ADC0
	LPC_ADC->CR |= ((SystemCoreClock/ADC_Clk -1) << 8);
}

/*****************************************************************************
** Function name:		ADCRead
**
** Descriptions:		Read ADC channel
**
** parameters:			Channel number
** Returned value:		Value read, if interrupt driven, return channel #
** 
*****************************************************************************/
uint32_t ADCRead( uint8_t channelNum )
{
#if !ADC_INTERRUPT_FLAG
  uint32_t regVal, ADC_Data;
#endif

  LPC_ADC->CR |= (1 << 24); // Start A/D convert

#if !ADC_INTERRUPT_FLAG
  while ( 1 ) // Wait until end of A/D convert
  {
  	/* read result of A/D conversion */
  	if ( LPC_ADC->DR5 & ADC_DONE )
  	{
  	  break;
  	}
  }	
        
  //LPC_ADC->CR &= 0xF8FFFFFF;	/* stop ADC now */
  /*if ( regVal & ADC_OVERRUN )	/* save data when it's not overrun, otherwise, return zero */
  //{
	//  return ( 0 );
  //}
#if TENBIT_MODE
  ADC_Data = ( regVal >> 6 ) & 0x3FF;
#else
  ADC_Data = ( LPC_ADC->DR5 >> 4 ) & 0xFFF;
#endif
  return ( ADC_Data );	/* return A/D conversion value */
#else
  return ( channelNum );	/* if it's interrupt driven, the ADC reading is 
							done inside the handler. so, return channel number */
#endif
}

/*****************************************************************************
** Function name:		ADC0BurstRead
**
** Descriptions:		Use burst mode to convert multiple channels once.
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void ADCBurstRead( void )
{
  if ( LPC_ADC->CR & (0x7<<24) )
  {
	  LPC_ADC->CR &= ~(0x7<<24);
  }
  /* Read all channels, 0 through 7. Be careful that if the ADCx pins is shared
  with SWD CLK or SWD IO. */
  LPC_ADC->CR |= (0xFF);
  LPC_ADC->CR |= (0x1<<16);		/* Set burst mode and start A/D convert */
  return;						/* the ADC reading is done inside the 
								handler, return 0. */
}

/*********************************************************************************
**                            End Of File
*********************************************************************************/
