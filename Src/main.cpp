#include "main.hpp"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_system.h"

int main() {
  SystemClock_Config();

  while (true) {
    continue;
  }
}

/**
 * System Clock Configuration
 *
 *   System Clock Source = PLL (HSE)
 *   SYSCLK (Hz) = 180000000
 *   HCLK (Hz) = 180000000
 *   AHB Prescaler = 1
 *   APB1 Prescaler = 4
 *   APB2 Prescaler = 2
 *   HSE Frequency (Hz) = 8000000
 *   PLL_M = 8
 *   PLL_N = 360
 *   PLL_P = 2
 *   VDD (V) = 3.3
 *   Main regulator output voltage = Scale1 mode
 *   Flash Latency (WS) = 5
 */
void SystemClock_Config() {
  // Enable HSE Oscillator
  LL_RCC_HSE_Enable();
  while (LL_RCC_HSE_IsReady() != 1) {
    continue;
  }

  // Set flash latency
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);

  // Enable PWR clock
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  // Activate Overdrive mode
  LL_PWR_EnableOverDriveMode();
  while (LL_PWR_IsActiveFlag_OD() != 1) {
    continue;
  }

  // Active Overdrive switching
  LL_PWR_EnableOverDriveSwitching();
  while (LL_PWR_IsActiveFlag_ODSW() != 1) {
    continue;
  }

  // Main PLL configuration and activation
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_8, 360,
                              LL_RCC_PLLP_DIV_2);
  LL_RCC_PLL_Enable();
  while (LL_RCC_PLL_IsReady() != 1) {
    continue;
  }

  // Activate system clock on the main PLL
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {
    continue;
  }

  // Set APB1 and APB2 prescaler
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);

  // Set systick to 1ms
  SysTick_Config(180000000 / 1000);

  // Update CMSIS SystemCoreClock variable
  SystemCoreClock = 180000000;
}

#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line) {
  /* User can add his own implementation to report the file name and line
     number, ex: printf("Wrong parameters value: file %s on line %d", file,
     line) */
  /* Infinite loop */
  while (1) {
  }
}
#endif
