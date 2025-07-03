/**
 ****************************************************************************************************
 * @file        rs485_master.h
 * @brief       RS485 master controller functions
 ****************************************************************************************************
 */

#ifndef __RS485_MASTER_H
#define __RS485_MASTER_H

#include "rs485_h750.h"

/* Master communication function */
uint8_t rs485_master_communicate(uint8_t *cmd, uint8_t cmd_len, uint8_t *resp, uint8_t *resp_len);

/* Master execution function */
void rs485_master_run(void);

/* Send start command to slave */
uint8_t rs485_send_start_cmd(void);

/* Receive data from slave */
uint8_t rs485_receive_slave_data(uint8_t *data_buf, uint8_t *data_len);

#endif /* __RS485_MASTER_H */
