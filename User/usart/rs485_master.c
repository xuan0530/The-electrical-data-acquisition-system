/**
 ****************************************************************************************************
 * @file        rs485_master.c
 * @brief       RS485??????
 ****************************************************************************************************
 */
#include "rs485_h750.h"
#include "delay.h"
#include <string.h>

// ??????
#define CMD_START_COLLECTION "S"
#define BUFFER_SIZE 2048

// ?????????
uint8_t slave_data_buffer[BUFFER_SIZE];
uint16_t slave_data_length = 0;
uint8_t slave_data_ready = 0;
/**
 * @brief       Send start collection command to slave
 * @param       None
 * @retval      0: Failed; 1: Success
 */
uint8_t rs485_send_start_cmd(void)
{
    uint8_t cmd[2] = "S";     // Send 'S' command to start slave collection
    printf("Master sending start command 'S' to slave\r\n");
    rs485_send_data(cmd, 1);  // Send only one character 'S'
    return 1;
}

/**
 * @brief       Receive collected data from slave
 * @param       data_buf: Buffer to store received data
 * @param       data_len: Length of received data
 * @retval      0: Failed; 1: Success
 */
uint8_t rs485_receive_slave_data(uint8_t *data_buf, uint8_t *data_len)
{
    uint8_t retry = 0;
    
    // Try to receive data up to 10 times
    while(retry < 10)
    {
        rs485_receive_data(data_buf, data_len);
        if(*data_len > 0)
        {
            printf("Master received data from slave, length=%d\r\n", *data_len);
            return 1;  // Successfully received data
        }
        delay_ms(100);  // Wait 100ms before trying again
        retry++;
    }
    
    printf("Failed to receive data from slave after 10 attempts\r\n");
    return 0;  // Failed to receive
}
/**
 * @brief       RS485??????
 * @param       cmd: ??????
 * @param       cmd_len: ????
 * @param       resp: ????????
 * @param       resp_len: ??????
 * @retval      0: ?????; 1: ????
 */
uint8_t rs485_master_communicate(uint8_t *cmd, uint8_t cmd_len, uint8_t *resp, uint8_t *resp_len)
{
    printf("Master sending: ");
    for(uint8_t i = 0; i < cmd_len; i++) {
        printf("%c", cmd[i]);
    }
    printf("\r\n");
    
    rs485_send_data(cmd, cmd_len);      /* ???? */
    
    // Increase delay to give slave more time to process and respond
    delay_ms(200);                       /* ???? */
    
    rs485_receive_data(resp, resp_len);  /* ???? */
    
    if (*resp_len > 0) {
        printf("Master received %d bytes: ", *resp_len);
        for(uint8_t i = 0; i < *resp_len; i++) {
            printf("%c", resp[i]);
        }
        printf("\r\n");
    } else {
        printf("Master received no response\r\n");
    }
    
    return (*resp_len > 0) ? 1 : 0;
}


/**
 * @brief       RS485??????
 * @param       ?
 * @retval      ?
 */
void rs485_master_run(void)
{
    static uint8_t communication_stage = 0;
    uint8_t cmd[20] = {0};
    uint8_t resp[RS485_REC_LEN] = {0};
    uint8_t resp_len = 0;
    
    switch(communication_stage) {
        case 0:  // ????????
            printf("Master: Sending START_COLLECTION command to slave\r\n");
            if(rs485_send_start_cmd()) {
                communication_stage = 1;
                printf("Master: START command sent successfully\r\n");
            } else {
                printf("Master: Failed to send START command\r\n");
            }
            break;
            
        case 1:  // ??????
            printf("Master: Waiting for data from slave\r\n");
            if(rs485_receive_slave_data(resp, &resp_len)) {
                printf("Master: Successfully received data from slave\r\n");
                printf("Data: ");
                for(uint8_t i = 0; i < resp_len; i++) {
                    printf("%c", resp[i]);
                }
                printf("\r\n");
                
                // ?????????(????1)
                printf("Master: Forwarding slave data to PC\r\n");
                printf("SLAVE_DATA: %.*s\r\n", resp_len, resp);
                
                communication_stage = 0;  // ????,???????
            }
            break;
            
        default:
            communication_stage = 0;
            break;
    }
}