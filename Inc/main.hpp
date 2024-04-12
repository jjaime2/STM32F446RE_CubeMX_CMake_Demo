#pragma once

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

#define LED1_PIN LL_GPIO_PIN_0
#define LED1_GPIO_PORT GPIOB
#define LED1_GPIO_CLK_ENABLE()                                                 \
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB)

/**
 * @brief LED2
 */

#define LED2_PIN LL_GPIO_PIN_7
#define LED2_GPIO_PORT GPIOB
#define LED2_GPIO_CLK_ENABLE()                                                 \
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB)

/**
 * @brief LED3
 */

#define LED3_PIN LL_GPIO_PIN_14
#define LED3_GPIO_PORT GPIOB
#define LED3_GPIO_CLK_ENABLE()                                                 \
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB)

/**
 * @brief Key push-button
 */
#define USER_BUTTON_PIN LL_GPIO_PIN_13
#define USER_BUTTON_GPIO_PORT GPIOC
#define USER_BUTTON_GPIO_CLK_ENABLE()                                          \
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC)
#define USER_BUTTON_EXTI_LINE LL_EXTI_LINE_13
#define USER_BUTTON_EXTI_IRQn EXTI15_10_IRQn
#define USER_BUTTON_EXTI_LINE_ENABLE()                                         \
  LL_EXTI_EnableIT_0_31(USER_BUTTON_EXTI_LINE)
#define USER_BUTTON_EXTI_FALLING_TRIG_ENABLE()                                 \
  LL_EXTI_EnableFallingTrig_0_31(USER_BUTTON_EXTI_LINE)
#define USER_BUTTON_SYSCFG_SET_EXTI()                                          \
  do {                                                                         \
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);                      \
    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE13);      \
  } while (0)
#define USER_BUTTON_IRQHANDLER EXTI15_10_IRQHandler

/* ==============   BOARD SPECIFIC CONFIGURATION CODE END      ============== */

/**
 * @brief Toggle periods for various blinking modes
 */
#define LED_BLINK_FAST 200
#define LED_BLINK_SLOW 500
#define LED_BLINK_ERROR 1000

void SystemClock_Config();
