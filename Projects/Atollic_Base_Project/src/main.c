/**
 * @author  Pedro Henrique Bonifacio
 * @email   pedrobonifa@gmail.com
 * @github  https://github.com/PHBonifacio/STM32F4_Discovery
 * @ide     Atollic TrueSTUDIO
 * @license GNU GPL v3
 *	
@verbatim
   ----------------------------------------------------------------------
    Copyright (C) Pedro Henrique Bonifacio, 2018
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
     
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------
@endverbatim
 */

/* Includes */
#include "stm32f4xx.h"
/* Defines */
#define TICK ( 168e3 )
/* Private variables */
uint32_t delay_time = 0;
uint32_t systick_time = 0;
/* Private function prototypes */
void HardwareConfig();
void Delay_ms( uint32_t milis);
/* Private functions */

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{

	HardwareConfig();

	while (1)
	{
		Delay_ms(500);
		if( ( GPIOD->ODR&GPIO_ODR_ODR_12 ) != 0x0)
		{
			SET_BIT( GPIOD->BSRRH, ( GPIO_BSRR_BS_12|GPIO_BSRR_BS_13|GPIO_BSRR_BS_14|GPIO_BSRR_BS_15 ));
		}
		else
		{
			SET_BIT( GPIOD->BSRRL, ( GPIO_BSRR_BS_12|GPIO_BSRR_BS_13|GPIO_BSRR_BS_14|GPIO_BSRR_BS_15 ));
		}
	}
}
void SysTick_Handler(void)
{
	systick_time++;
	delay_time++;
}
void HardwareConfig()
{
  SysTick_Config(SystemCoreClock / 1000);
  /*  enable clock for GPIOD  */
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
  /*  set PD12, PD13, PD14 and PD15 as output */
  GPIOD->MODER |= ( GPIO_MODER_MODER12_0|GPIO_MODER_MODER13_0|GPIO_MODER_MODER14_0|GPIO_MODER_MODER15_0 );
  /*  set ports as push-pull  */
  GPIOD->OTYPER = 0;
  /*  configure ports as high speed */
  GPIOD->OSPEEDR |= ( GPIO_OSPEEDER_OSPEEDR12|GPIO_OSPEEDER_OSPEEDR13|GPIO_OSPEEDER_OSPEEDR14|GPIO_OSPEEDER_OSPEEDR15 );
  /* turn on leds */
  GPIOD->BSRRL |= ( GPIO_BSRR_BS_12|GPIO_BSRR_BS_13|GPIO_BSRR_BS_14|GPIO_BSRR_BS_15 );
}
void Delay_ms( uint32_t milis)
{
	delay_time = 0;
	while (delay_time < milis);
}
