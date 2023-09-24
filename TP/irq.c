#include "irq.h"

#define MAKE_DEFAULT_HANDLER(handler_nom)        \
void __attribute__((weak)) handler_nom(void) {   \
    __disable_irq();  while(1) {} }

/*--- Déclaration et instantiation des handlers ---*/
 
MAKE_DEFAULT_HANDLER(NMI_Handler)
MAKE_DEFAULT_HANDLER(HardFault_Handler)
MAKE_DEFAULT_HANDLER(MemManage_Handler)
MAKE_DEFAULT_HANDLER(BusFault_Handler)
MAKE_DEFAULT_HANDLER(UsageFault_Handler)
MAKE_DEFAULT_HANDLER(SVC_Handler)
MAKE_DEFAULT_HANDLER(PendSV_Handler)
MAKE_DEFAULT_HANDLER(SysTick_Handler)

MAKE_DEFAULT_HANDLER(WWDG_IRQHandler)
MAKE_DEFAULT_HANDLER(PVD_PVM_IRQHandler)
MAKE_DEFAULT_HANDLER(TAMP_STAMP_IRQHandler)
MAKE_DEFAULT_HANDLER(RTC_WKUP_IRQHandler)
MAKE_DEFAULT_HANDLER(FLASH_IRQHandler)
MAKE_DEFAULT_HANDLER(RCC_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI0_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI1_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI2_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI3_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI4_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_Channel1_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_Channel2_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_Channel3_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_Channel4_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_Channel5_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_Channel6_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_Channel7_IRQHandler)
MAKE_DEFAULT_HANDLER(ADC1_2_IRQHandler)
MAKE_DEFAULT_HANDLER(CAN1_TX_IRQHandler)
MAKE_DEFAULT_HANDLER(CAN1_RX0_IRQHandler)
MAKE_DEFAULT_HANDLER(CAN1_RX1_IRQHandler)
MAKE_DEFAULT_HANDLER(CAN1_SCE_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI9_5_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM1_BRK_TIM15_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM1_UP_TIM16_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM1_TRG_COM_TIM17_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM1_CC_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM2_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM3_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM4_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C1_EV_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C1_ER_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C2_EV_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C2_ER_IRQHandler)
MAKE_DEFAULT_HANDLER(SPI1_IRQHandler)
MAKE_DEFAULT_HANDLER(SPI2_IRQHandler)
MAKE_DEFAULT_HANDLER(USART1_IRQHandler)
MAKE_DEFAULT_HANDLER(USART2_IRQHandler)
MAKE_DEFAULT_HANDLER(USART3_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI15_10_IRQHandler)
MAKE_DEFAULT_HANDLER(RTC_Alarm_IRQHandler)
MAKE_DEFAULT_HANDLER(DFSDM1_FLT3_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM8_BRK_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM8_UP_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM8_TRG_COM_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM8_CC_IRQHandler)
MAKE_DEFAULT_HANDLER(ADC3_IRQHandler)
MAKE_DEFAULT_HANDLER(FMC_IRQHandler)
MAKE_DEFAULT_HANDLER(SDMMC1_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM5_IRQHandler)
MAKE_DEFAULT_HANDLER(SPI3_IRQHandler)
MAKE_DEFAULT_HANDLER(UART4_IRQHandler)
MAKE_DEFAULT_HANDLER(UART5_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM6_DAC_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM7_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_Channel1_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_Channel2_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_Channel3_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_Channel4_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_Channel5_IRQHandler)
MAKE_DEFAULT_HANDLER(DFSDM1_FLT0_IRQHandler)
MAKE_DEFAULT_HANDLER(DFSDM1_FLT1_IRQHandler)
MAKE_DEFAULT_HANDLER(DFSDM1_FLT2_IRQHandler)
MAKE_DEFAULT_HANDLER(COMP_IRQHandler)
MAKE_DEFAULT_HANDLER(LPTIM1_IRQHandler)
MAKE_DEFAULT_HANDLER(LPTIM2_IRQHandler)
MAKE_DEFAULT_HANDLER(OTG_FS_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_Channel6_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_Channel7_IRQHandler)
MAKE_DEFAULT_HANDLER(LPUART1_IRQHandler)
MAKE_DEFAULT_HANDLER(QUADSPI_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C3_EV_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C3_ER_IRQHandler)
MAKE_DEFAULT_HANDLER(SAI1_IRQHandler)
MAKE_DEFAULT_HANDLER(SAI2_IRQHandler)
MAKE_DEFAULT_HANDLER(SWPMI1_IRQHandler)
MAKE_DEFAULT_HANDLER(TSC_IRQHandler)
MAKE_DEFAULT_HANDLER(RNG_IRQHandler)
MAKE_DEFAULT_HANDLER(FPU_IRQHandler)

/*-------------------------------------------------*/

// https://developer.arm.com/documentation/dui0474/f/using-scatter-files/using---attribute----section--name-----to-place-code-and-data

void __attribute__((section(".table_section_flash"))) *vector_table[] = {
    // Stack and Reset Handler
    &_stack_start,                    /* Top of stack */
    &_start,                           /* Reset handler */

    // ARM internal exceptions
    NMI_Handler,                      /* NMI handler */
    HardFault_Handler,                /* Hard Fault handler */
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,                                /* Reserved */
    0,                                /* Reserved */
    0,                                /* Reserved */
    0,                                /* Reserved */
    SVC_Handler,                      /* SVC handler */
    0,                                /* Reserved */
    0,                                /* Reserved */
    PendSV_Handler,                   /* Pending SVC handler */
    SysTick_Handler,                  /* SysTick handler */

    // STM32L475 External interrupts
    WWDG_IRQHandler,                  /* Window WatchDog Interrupt                                         */
    PVD_PVM_IRQHandler,               /* PVD/PVM1/PVM2/PVM3/PVM4 through EXTI Line detection Interrupts    */
    TAMP_STAMP_IRQHandler,            /* Tamper and TimeStamp interrupts through the EXTI line             */
    RTC_WKUP_IRQHandler,              /* RTC Wakeup interrupt through the EXTI line                        */
    FLASH_IRQHandler,                 /* FLASH global Interrupt                                            */
    RCC_IRQHandler,                   /* RCC global Interrupt                                              */
    EXTI0_IRQHandler,                 /* EXTI Line0 Interrupt                                              */
    EXTI1_IRQHandler,                 /* EXTI Line1 Interrupt                                              */
    EXTI2_IRQHandler,                 /* EXTI Line2 Interrupt                                              */
    EXTI3_IRQHandler,                 /* EXTI Line3 Interrupt                                              */
    EXTI4_IRQHandler,                 /* EXTI Line4 Interrupt                                              */
    DMA1_Channel1_IRQHandler,         /* DMA1 Channel 1 global Interrupt                                   */
    DMA1_Channel2_IRQHandler,         /* DMA1 Channel 2 global Interrupt                                   */
    DMA1_Channel3_IRQHandler,         /* DMA1 Channel 3 global Interrupt                                   */
    DMA1_Channel4_IRQHandler,         /* DMA1 Channel 4 global Interrupt                                   */
    DMA1_Channel5_IRQHandler,         /* DMA1 Channel 5 global Interrupt                                   */
    DMA1_Channel6_IRQHandler,         /* DMA1 Channel 6 global Interrupt                                   */
    DMA1_Channel7_IRQHandler,         /* DMA1 Channel 7 global Interrupt                                   */
    ADC1_2_IRQHandler,                /* ADC1, ADC2 SAR global Interrupts                                  */
    CAN1_TX_IRQHandler,               /* CAN1 TX Interrupt                                                 */
    CAN1_RX0_IRQHandler,              /* CAN1 RX0 Interrupt                                                */
    CAN1_RX1_IRQHandler,              /* CAN1 RX1 Interrupt                                                */
    CAN1_SCE_IRQHandler,              /* CAN1 SCE Interrupt                                                */
    EXTI9_5_IRQHandler,               /* External Line[9:5] Interrupts                                     */
    TIM1_BRK_TIM15_IRQHandler,        /* TIM1 Break interrupt and TIM15 global interrupt                   */
    TIM1_UP_TIM16_IRQHandler,         /* TIM1 Update Interrupt and TIM16 global interrupt                  */
    TIM1_TRG_COM_TIM17_IRQHandler,    /* TIM1 Trigger and Commutation Interrupt and TIM17 global interrupt */
    TIM1_CC_IRQHandler,               /* TIM1 Capture Compare Interrupt                                    */
    TIM2_IRQHandler,                  /* TIM2 global Interrupt                                             */
    TIM3_IRQHandler,                  /* TIM3 global Interrupt                                             */
    TIM4_IRQHandler,                  /* TIM4 global Interrupt                                             */
    I2C1_EV_IRQHandler,               /* I2C1 Event Interrupt                                              */
    I2C1_ER_IRQHandler,               /* I2C1 Error Interrupt                                              */
    I2C2_EV_IRQHandler,               /* I2C2 Event Interrupt                                              */
    I2C2_ER_IRQHandler,               /* I2C2 Error Interrupt                                              */
    SPI1_IRQHandler,                  /* SPI1 global Interrupt                                             */
    SPI2_IRQHandler,                  /* SPI2 global Interrupt                                             */
    USART1_IRQHandler,                /* USART1 global Interrupt                                           */
    USART2_IRQHandler,                /* USART2 global Interrupt                                           */
    USART3_IRQHandler,                /* USART3 global Interrupt                                           */
    EXTI15_10_IRQHandler,             /* External Line[15:10] Interrupts                                   */
    RTC_Alarm_IRQHandler,             /* RTC Alarm (A and B) through EXTI Line Interrupt                   */
    DFSDM1_FLT3_IRQHandler,           /* DFSDM1 Filter 3 global Interrupt                                  */
    TIM8_BRK_IRQHandler,              /* TIM8 Break Interrupt                                              */
    TIM8_UP_IRQHandler,               /* TIM8 Update Interrupt                                             */
    TIM8_TRG_COM_IRQHandler,          /* TIM8 Trigger and Commutation Interrupt                            */
    TIM8_CC_IRQHandler,               /* TIM8 Capture Compare Interrupt                                    */
    ADC3_IRQHandler,                  /* ADC3 global  Interrupt                                            */
    FMC_IRQHandler,                   /* FMC global Interrupt                                              */
    SDMMC1_IRQHandler,                /* SDMMC1 global Interrupt                                           */
    TIM5_IRQHandler,                  /* TIM5 global Interrupt                                             */
    SPI3_IRQHandler,                  /* SPI3 global Interrupt                                             */
    UART4_IRQHandler,                 /* UART4 global Interrupt                                            */
    UART5_IRQHandler,                 /* UART5 global Interrupt                                            */
    TIM6_DAC_IRQHandler,              /* TIM6 global and DAC1&2 underrun error  interrupts                 */
    TIM7_IRQHandler,                  /* TIM7 global interrupt                                             */
    DMA2_Channel1_IRQHandler,         /* DMA2 Channel 1 global Interrupt                                   */
    DMA2_Channel2_IRQHandler,         /* DMA2 Channel 2 global Interrupt                                   */
    DMA2_Channel3_IRQHandler,         /* DMA2 Channel 3 global Interrupt                                   */
    DMA2_Channel4_IRQHandler,         /* DMA2 Channel 4 global Interrupt                                   */
    DMA2_Channel5_IRQHandler,         /* DMA2 Channel 5 global Interrupt                                   */
    DFSDM1_FLT0_IRQHandler,           /* DFSDM1 Filter 0 global Interrupt                                  */
    DFSDM1_FLT1_IRQHandler,           /* DFSDM1 Filter 1 global Interrupt                                  */
    DFSDM1_FLT2_IRQHandler,           /* DFSDM1 Filter 2 global Interrupt                                  */
    COMP_IRQHandler,                  /* COMP1 and COMP2 Interrupts                                        */
    LPTIM1_IRQHandler,                /* LP TIM1 interrupt                                                 */
    LPTIM2_IRQHandler,                /* LP TIM2 interrupt                                                 */
    OTG_FS_IRQHandler,                /* USB OTG FS global Interrupt                                       */
    DMA2_Channel6_IRQHandler,         /* DMA2 Channel 6 global interrupt                                   */
    DMA2_Channel7_IRQHandler,         /* DMA2 Channel 7 global interrupt                                   */
    LPUART1_IRQHandler,               /* LP UART1 interrupt                                                */
    QUADSPI_IRQHandler,               /* Quad SPI global interrupt                                         */
    I2C3_EV_IRQHandler,               /* I2C3 event interrupt                                              */
    I2C3_ER_IRQHandler,               /* I2C3 error interrupt                                              */
    SAI1_IRQHandler,                  /* Serial Audio Interface 1 global interrupt                         */
    SAI2_IRQHandler,                  /* Serial Audio Interface 2 global interrupt                         */
    SWPMI1_IRQHandler,                /* Serial Wire Interface 1 global interrupt                          */
    TSC_IRQHandler,                   /* Touch Sense Controller global interrupt                           */
    RNG_IRQHandler,                   /* RNG global interrupt                                              */
    FPU_IRQHandler                    /* FPU global interrupt                                              */

};

void irq_init() {

    SCB->VTOR = (uint32_t) vector_table;

}