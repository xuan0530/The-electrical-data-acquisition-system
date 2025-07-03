/****************************************************************************************************
 * @file        rs485_h750.h
 * @brief       STM32H750 RS485????? - ???USART2
 * @note        ??PA2(TX)?PA3(RX)??, ??USART2
 ****************************************************************************************************
 */

#ifndef __RS485_H750_H
#define __RS485_H750_H

#include "system.h"

/**************************************************************************************************/
/* ???? */

#define RS485_TX_GPIO_PORT                  GPIOA       /* TX????PA2 */
#define RS485_TX_GPIO_PIN                   GPIO_PIN_2
#define RS485_TX_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)

#define RS485_RX_GPIO_PORT                  GPIOA       /* RX????PA3 */
#define RS485_RX_GPIO_PIN                   GPIO_PIN_3
#define RS485_RX_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)

/* ?????USART2 */
#define RS485_UX                            USART2
#define RS485_UX_IRQn                       USART2_IRQn
#define RS485_UX_IRQHandler                 USART2_IRQHandler
#define RS485_UX_CLK_ENABLE()               do{ __HAL_RCC_USART2_CLK_ENABLE(); }while(0)

#define RS485_REC_LEN       220                 /* ??????? */
#define RS485_EN_RX         1                   /* ???? */

extern UART_HandleTypeDef g_rs485_handler;       /* UART?? */
extern uint8_t g_rs485_rx_buf[RS485_REC_LEN];    /* ????? */
extern uint8_t g_rs485_rx_cnt;                   /* ????? */

/******************************************************************************************/

void rs485_init(uint32_t baudrate);                 /* ??? */
void rs485_send_data(uint8_t *buf, uint8_t len);    /* ???? */
void rs485_receive_data(uint8_t *buf, uint8_t *len); /* ???? */
void RS485_UX_IRQHandler(void);                     /* ?????? */
void rs485_master_send_cmd(uint8_t *cmd, uint8_t len); /* ?????? */
uint8_t rs485_slave_process_cmd(void);                 /* ?????? */

#endif
