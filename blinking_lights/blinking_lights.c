/* This program is a blinking light example in Discovering 
   the STM32 microcontroller (Chapter 4) by Geoffrey Brown.*/
#include <stdio.h>
#include <stdlib.h>
#include <stm32f10x.h> 
#include <stm32f10x_rcc.h> 
#include <stm32f10x_gpio.h>

void Delay(uint32_t nTime);

int main(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // (1) Enable Peripheral Clocks 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // (2) Configure Pins for PORTC to be output 
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // (3) Configure SysTick Timer 
    if(SysTick_Config(SystemCoreClock / 1000)) {    // timer interrupt = 1msec
        while (1);
    }

    while (1) {
        static int ledval = 0;

        // (4) toggle led 
        GPIO_WriteBit(GPIOC, GPIO_Pin_9, (ledval) ? Bit_SET : Bit_RESET);
        ledval = 1 - ledval;

        Delay(250);     // wait 250ms
    }
}

// (5) Timer code
static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime) {
    TimingDelay = nTime;
    while(TimingDelay !=0);
}

void SysTick_Handler(void) {
    if (TimingDelay != 0x00) {
        TimingDelay--;
    }
}

#ifdef  USE_FULL_ASSERT

/**
 *   * @brief  Reports the name of the source file and the source line number
 *     *         where the assert_param error has occurred.
 *       * @param  file: pointer to the source file name
 *         * @param  line: assert_param error line source number
 *           * @retval None
 *             */
void assert_failed(uint8_t* file, uint32_t line)
{
      /* User can add his own implementation to report the file name and line number,
       *      ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
      /* Infinite loop */
      while (1) {           
      }
}

#endif

