/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#ifdef STM32L0xx
#include "stm32l0xx.h"
#include "stm32l0xx_hal.h"
#include "stm32l0xx_ll_gpio.h"
#include "stm32l0xx_ll_usart.h"
#elif defined(STM32L1xx)
#include "stm32l1xx.h"
#include "stm32l1xx_hal.h"
#include "stm32l1xx_ll_gpio.h"
#include "stm32l1xx_ll_usart.h"
#elif defined(STM32F1)
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_usart.h"
#elif defined(STM32F3xx)
#include "stm32f3xx.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx_ll_gpio.h"
#include "stm32f3xx_ll_usart.h"
#elif defined(STM32L4xx)
#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_usart.h"
#else
#error "Not supported CPU type!"
#endif

#define STRINGIFY(str) #str
#define BUILD_VERSION(ver) STRINGIFY(ver)
#define BUILD_MCU_TYPE(type) STRINGIFY(BL_TYPE: type)

#ifndef GPIO_USE_LL
#define GPIO_USE_LL 0
#endif

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

enum duplex_state
{
  DUPLEX_RX,
  DUPLEX_TX,
};

enum {
  IO_PORT_A = 'A',
  IO_PORT_B = 'B',
  IO_PORT_C = 'C',
  IO_PORT_D = 'D',
  IO_PORT_E = 'E',
  IO_PORT_F = 'F'
};
#define CONCAT(_P) IO_PORT_ ## _P
#define IO_CREATE_IMPL(port, pin) ((CONCAT(port) * 16) + pin)
#define IO_CREATE(...)  IO_CREATE_IMPL(__VA_ARGS__)
#define IO_GET_PORT(_p) (((_p) / 16) - 'A')
#define IO_GET_PIN(_p)  ((_p) % 16)

enum led_states
{
  LED_OFF,
  LED_BOOTING,
  LED_FLASHING,
  LED_FLASHING_ALT,
  LED_STARTING,
};

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void led_state_set(uint32_t state);
void duplex_state_set(const enum duplex_state state);
int8_t timer_end(void);

void gpio_port_pin_get(uint32_t io, void ** port, uint32_t * pin);
void gpio_port_clock(uint32_t port);

#if GPIO_USE_LL
#define GPIO_WritePin(port, pin, _state) \
  (_state) ? LL_GPIO_SetOutputPin(port, pin) : \
  LL_GPIO_ResetOutputPin(port, pin)
#else
#define GPIO_WritePin(...) HAL_GPIO_WritePin(__VA_ARGS__)
#endif

/* Private defines -----------------------------------------------------------*/
#if !defined(XMODEM) && !STK500 && !FRSKY
#define XMODEM 1 // Default is XMODEM protocol
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
