/****************************************************************************************************
 * @file        rs485_h750.c
 * @brief       STM32H750 RS485????
 * @note        ??PA2(TX)?PA3(RX)??, ??USART2
 ****************************************************************************************************
 */

#include "rs485_h750.h"
#include "delay.h"
#include <string.h>

UART_HandleTypeDef g_rs485_handler;      /* UART?? */
uint8_t g_rs485_rx_buf[RS485_REC_LEN];   /* ????? */
uint8_t g_rs485_rx_cnt = 0;              /* ????? */

#ifdef RS485_EN_RX

/**
 * @brief       USART2??????
 */
void USART2_IRQHandler(void)
{
    uint8_t res;
    if (__HAL_UART_GET_FLAG(&g_rs485_handler, UART_FLAG_RXNE) != RESET)
    {
        res = (uint8_t)(g_rs485_handler.Instance->RDR & 0x00FF);
        if (g_rs485_rx_cnt < RS485_REC_LEN)
        {
            g_rs485_rx_buf[g_rs485_rx_cnt] = res;
            g_rs485_rx_cnt++;
        }
    }
    __HAL_UART_CLEAR_FLAG(&g_rs485_handler, UART_FLAG_RXNE);
}
#endif

/**
 * @brief       ???USART2?RS485
 * @param       baudrate: ???
 */
void rs485_init(uint32_t baudrate)
{
    GPIO_InitTypeDef gpio_init_struct;

    RS485_TX_GPIO_CLK_ENABLE();    /* ??GPIOA?? */
    RS485_RX_GPIO_CLK_ENABLE();
    RS485_UX_CLK_ENABLE();         /* ??USART2?? */

    /* ??TX?? (PA2) */
    gpio_init_struct.Pin = RS485_TX_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init_struct.Alternate = GPIO_AF7_USART2;  /* ???USART2 */
    HAL_GPIO_Init(RS485_TX_GPIO_PORT, &gpio_init_struct);

    /* ??RX?? (PA3) */
    gpio_init_struct.Pin = RS485_RX_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    HAL_GPIO_Init(RS485_RX_GPIO_PORT, &gpio_init_struct);

    /* ??USART2?? */
    g_rs485_handler.Instance = USART2;
    g_rs485_handler.Init.BaudRate = baudrate;
    g_rs485_handler.Init.WordLength = UART_WORDLENGTH_8B;
    g_rs485_handler.Init.StopBits = UART_STOPBITS_1;
    g_rs485_handler.Init.Parity = UART_PARITY_NONE;
    g_rs485_handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    g_rs485_handler.Init.Mode = UART_MODE_TX_RX;
    g_rs485_handler.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&g_rs485_handler);

#if RS485_EN_RX
    __HAL_UART_ENABLE_IT(&g_rs485_handler, UART_IT_RXNE);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
    HAL_NVIC_SetPriority(USART2_IRQn, 3, 3);
#endif
}

/**
 * @brief       ????(?????)
 */
void rs485_send_data(uint8_t *buf, uint8_t len)
{
    // Clear receive buffer before sending
    g_rs485_rx_cnt = 0;
    memset(g_rs485_rx_buf, 0, RS485_REC_LEN);
    
    // Add better timing control
    delay_ms(5);
    HAL_UART_Transmit(&g_rs485_handler, buf, len, 200);  // Increased timeout
    delay_ms(10);  // Increased post-transmission delay
}

void rs485_receive_data(uint8_t *buf, uint8_t *len)
{
    uint8_t rxlen = g_rs485_rx_cnt;
    *len = 0;
    
    // Wait longer for stable data
    delay_ms(50);
    
    // Check if receive count is stable
    if (rxlen == g_rs485_rx_cnt && rxlen > 0)
    {
        memcpy(buf, g_rs485_rx_buf, rxlen);
        *len = rxlen;
        g_rs485_rx_cnt = 0;  // Reset counter after copying
        memset(g_rs485_rx_buf, 0, RS485_REC_LEN);  // Clear buffer
    }
}

/**
 * @brief       ??????(?????)
 */
void rs485_master_send_cmd(uint8_t *cmd, uint8_t len)
{
    rs485_send_data(cmd, len);
}

/**
 * @brief       ??????(?????)
 */
uint8_t rs485_slave_process_cmd(void)
{
    uint8_t buf[RS485_REC_LEN];
    uint8_t len = 0;
    rs485_receive_data(buf, &len);
    if (len > 0)
    {
        rs485_send_data(buf, len);
        return 1;
    }
    return 0;
}
