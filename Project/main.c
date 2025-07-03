#include "ads1263.h"
#include "ads1263_2.h"
#include "ads1263_3.h"  // Add new header
#include "delay.h"
#include "gpio.h"
#include "stm32h7xx_hal_tim.h"
#include "system.h"
#include "usart.h"
#include <string.h>
#include <stdlib.h>
#include "rs485_h750.h"
#include "rs485_master.h" 

// 采样配置定义
#define SAMPLES_PER_CHANNEL 100  // 每个通道采样次数

// 发射引脚定义
#define TX_CHANNEL_COUNT 20

#define CMD_START_COLLECTION "S"
#define BUFFER_SIZE 2048

uint8_t slave_data[BUFFER_SIZE]; // Buffer to hold slave data
uint8_t slave_data_len = 0;  


static ADS1263_DR sampling_rate;

const ADS1263_DR sampling_rates[] = {
    ADC1_2_5_SPS,    /* 2.5 SPS */
    ADC1_5_SPS,      /* 5 SPS */
    ADC1_10_SPS,     /* 10 SPS */
    ADC1_16_6_SPS,   /* 16.6 SPS */
    ADC1_20_SPS,     // 4: 20 SPS
    ADC1_50_SPS,     // 5: 50 SPS
    ADC1_60_SPS,     // 6: 60 SPS
    ADC1_100_SPS,    // 7: 100 SPS
    ADC1_400_SPS,    // 8: 400 SPS
    ADC1_1200_SPS,   // 9: 1200 SPS
    ADC1_2400_SPS,   // 10: 2400 SPS
    ADC1_4800_SPS,   // 11: 4800 SPS
    ADC1_7200_SPS,   // 12: 7200 SPS
    ADC1_14400_SPS,  // 13: 14400 SPS
    ADC1_19200_SPS   // 14: 19200 SPS
};

GPIO_TypeDef* TX_PORTS[] = {
    GPIOD, GPIOD, GPIOD, GPIOD, GPIOD,
    GPIOD, GPIOD, GPIOD, GPIOD, GPIOD,
    GPIOD, GPIOD, GPIOD, GPIOD, GPIOD,
    GPIOE, GPIOE, GPIOE, GPIOE, GPIOE
};

uint16_t TX_PINS[] = {
    GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5,
    GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10,
    GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15,
    GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15
};

#if USE_SINGLE_INPUT
  /* 正极通道 */
  ADS1263_Input_Multiplexer adc1_p[] = {
      ADC1_AIN0, ADC1_AIN1, ADC1_AIN2, ADC1_AIN3, ADC1_AIN4,
      ADC1_AIN5, ADC1_AIN6, ADC1_AIN7, ADC1_AIN8, ADC1_AIN9};
  /* 负极通道 */
  ADS1263_Input_Multiplexer adc1_n[] = {
      ADC1_AINCOM, ADC1_AINCOM, ADC1_AINCOM, ADC1_AINCOM, ADC1_AINCOM,
      ADC1_AINCOM, ADC1_AINCOM, ADC1_AINCOM, ADC1_AINCOM, ADC1_AINCOM};
#else
  /* 正极通道 */
  ADS1263_Input_Multiplexer adc1_p[] = {ADC1_AIN0, ADC1_AIN2, ADC1_AIN4,
                                       ADC1_AIN6, ADC1_AIN8};
  /* 负极通道 */
  ADS1263_Input_Multiplexer adc1_n[] = {ADC1_AIN1, ADC1_AIN3, ADC1_AIN5,
                                       ADC1_AIN7, ADC1_AIN9};
#endif

// 函数声明
void DisableAllTxChannels(void);
void ConfigureADCs(void);
void SampleADC1Channels(void);
void SampleADC2Channels(void);
void SampleADC3Channels(void);  // Add new function declaration
void PerformMasterDataCollection(void);
void CollectDataFromSlave(void);
																			 
																			 
void DisableAllTxChannels(void) {
    for(uint8_t i = 0; i < TX_CHANNEL_COUNT; i++) {
        HAL_GPIO_WritePin(TX_PORTS[i], TX_PINS[i], GPIO_PIN_RESET);
    }
}



// 初始化三个ADC配置
void ConfigureADCs(void) {
    // 初始化第一片ADS1263
    ADS1263_Init();                                    
    ADS1263_Hardware_Reset();                          
    INTERFACE_Config.crc = DisabledCRC;                
    ADS1263_Set_INTERFACE_Register(&INTERFACE_Config); 
    REFMUX_Config.positive_reference = Internal_2_5_V_P; 
    REFMUX_Config.negative_reference = Internal_2_5_V_N; 
    ADS1263_Set_REFMUX_Register(&REFMUX_Config); 
    MODE2_Config.dr = sampling_rate;             
    ADS1263_Set_MODE2_Register(&MODE2_Config);   
    ADS1263_Start_ADC(ADS1263_ADC1);             

   
    ADS1263_2_Init();
    ADS1263_2_Hardware_Reset();
    INTERFACE_2_Config.crc = DisabledCRC;
    ADS1263_2_Set_INTERFACE_Register(&INTERFACE_2_Config);
    REFMUX_2_Config.positive_reference = Internal_2_5_V_P;
    REFMUX_2_Config.negative_reference = Internal_2_5_V_N;
    ADS1263_2_Set_REFMUX_Register(&REFMUX_2_Config);
    MODE2_2_Config.dr = sampling_rate;
    ADS1263_2_Set_MODE2_Register(&MODE2_2_Config);
    ADS1263_2_Start_ADC(ADS1263_ADC1);


    ADS1263_3_Init();
    ADS1263_3_Hardware_Reset();
    INTERFACE_3_Config.crc = DisabledCRC;
    ADS1263_3_Set_INTERFACE_Register(&INTERFACE_3_Config);
    REFMUX_3_Config.positive_reference = Internal_2_5_V_P;
    REFMUX_3_Config.negative_reference = Internal_2_5_V_N;
    ADS1263_3_Set_REFMUX_Register(&REFMUX_3_Config);
    MODE2_3_Config.dr = sampling_rate;
    ADS1263_3_Set_MODE2_Register(&MODE2_3_Config);
    ADS1263_3_Start_ADC(ADS1263_ADC1);
}


void SampleADC1Channels(void) {
    char output_buf[512] = {0};
    strcat(output_buf, " ");
    
    for (uint8_t i = 0; i < sizeof(adc1_p)/sizeof(ADS1263_Input_Multiplexer); i++) {
        INPMUX_Config.multiplexer_positive = adc1_p[i];
        INPMUX_Config.multiplexer_negative = adc1_n[i];
        ADS1263_Set_INPMUX_Register(&INPMUX_Config);
        
        double voltage_sum = 0;
        for (int j = 0; j < SAMPLES_PER_CHANNEL; j++) {
            uint32_t adc1_data = ADS1263_Read_ADC(ADS1263_ADC1);
            voltage_sum += ADS1263_Digital2Voltage(ADS1263_ADC1, adc1_data);
        }
        double avg_voltage = voltage_sum / SAMPLES_PER_CHANNEL;
        
        char channel_buf[32];
        sprintf(channel_buf, "%.6f%s", avg_voltage, 
                i < sizeof(adc1_p)/sizeof(ADS1263_Input_Multiplexer) - 1 ? ", " : "");
        strcat(output_buf, channel_buf);
    }
    
    printf("%s", output_buf);
}
/*

以下部分为采集函数，三个一样的


*/
void SampleADC2Channels(void) {
    char output_buf[512] = {0};
    strcat(output_buf, " ");
    
    for (uint8_t i = 0; i < sizeof(adc1_p)/sizeof(ADS1263_Input_Multiplexer); i++) {
        INPMUX_2_Config.multiplexer_positive = adc1_p[i];
        INPMUX_2_Config.multiplexer_negative = adc1_n[i];
        ADS1263_2_Set_INPMUX_Register(&INPMUX_2_Config);
        
        double voltage_sum = 0;
        for (int j = 0; j < SAMPLES_PER_CHANNEL; j++) {
            uint32_t adc2_data = ADS1263_2_Read_ADC(ADS1263_ADC1);
            voltage_sum += ADS1263_2_Digital2Voltage(ADS1263_ADC1, adc2_data);
        }
        double avg_voltage = voltage_sum / SAMPLES_PER_CHANNEL;
        
        char channel_buf[32];
        sprintf(channel_buf, "%.6f%s", avg_voltage, 
                i < sizeof(adc1_p)/sizeof(ADS1263_Input_Multiplexer) - 1 ? ", " : "");
        strcat(output_buf, channel_buf);
    }
    
    printf("%s", output_buf);
}

// 新增第三片ADC的采样函数
void SampleADC3Channels(void) {
    char output_buf[512] = {0};
    strcat(output_buf, " ");
    
    for (uint8_t i = 0; i < sizeof(adc1_p)/sizeof(ADS1263_Input_Multiplexer); i++) {
        INPMUX_3_Config.multiplexer_positive = adc1_p[i];
        INPMUX_3_Config.multiplexer_negative = adc1_n[i];
        ADS1263_3_Set_INPMUX_Register(&INPMUX_3_Config);
        
        double voltage_sum = 0;
        for (int j = 0; j < SAMPLES_PER_CHANNEL; j++) {
            uint32_t adc3_data = ADS1263_3_Read_ADC(ADS1263_ADC1);
            voltage_sum += ADS1263_3_Digital2Voltage(ADS1263_ADC1, adc3_data);
        }
        double avg_voltage = voltage_sum / SAMPLES_PER_CHANNEL;
        
        char channel_buf[32];
        sprintf(channel_buf, "%.6f%s", avg_voltage, 
                i < sizeof(adc1_p)/sizeof(ADS1263_Input_Multiplexer) - 1 ? ", " : "");
        strcat(output_buf, channel_buf);
    }
    
    printf("%s\r\n", output_buf);
}



void PerformMasterDataCollection(void) {
    printf("--- Master starting data collection ---\r\n");
    
    // 为了简化测试，先使用printf输出，不实际采集
    printf("Master collecting data from CD4067_1-4 (channels 1-4)\r\n");
    // TODO: 后续取消注释原始采集代码
    
    // 模拟采集延时
    HAL_Delay(500);
    
    printf("--- Master data collection complete ---\r\n");
}



void CollectDataFromSlave(void) {
    printf("--- Master sending START command to slave ---\r\n");
    
    // 发送启动命令给从机
    uint8_t cmd_sent = rs485_send_start_cmd();
    if (!cmd_sent) {
        printf("Error: Failed to send start command to slave\r\n");
        return;
    }
    
    // 给从机足够时间进行采集
    printf("Waiting for slave to complete data collection...\r\n");
    HAL_Delay(1000);  // 可以根据实际从机采集时间调整
    
    // 接收从机数据
    printf("Receiving data from slave...\r\n");
    uint8_t receive_success = rs485_receive_slave_data(slave_data, &slave_data_len);
    
    if (receive_success && slave_data_len > 0) {
        printf("Successfully received data from slave: \r\n");
        printf("Data length: %d bytes\r\n", slave_data_len);
        printf("Data content: ");
        for (uint8_t i = 0; i < slave_data_len; i++) {
            printf("%c", slave_data[i]);
        }
        printf("\r\n");
    } else {
        printf("Failed to receive data from slave\r\n");
    }
}


int main(void)
{
    // 系统初始化
    CPU_CACHE_Enable();      
    HAL_Init();             
    MPU_Memory_Protection(); 
    SystemClock_Config();    
    SysTick_clkconfig(400);  
    uart_init(115200);      
    rs485_init(115200); 
    HAL_Delay(100);         

    // 等待串口开始指令
    printf("waiting start\r\n");
    while(1) {
        if(USART_RX_STA & 0x8000) {
            if(USART_RX_BUF[0] == 'S') {
                printf("start\r\n");
                USART_RX_STA = 0;
                break;
            }
            USART_RX_STA = 0;
        }
        HAL_Delay(10);
    }

    // 初始化ADC，默认使用2400 SPS
    sampling_rate = ADC1_2400_SPS;
    ConfigureADCs();
    
    // 初始化所有CD4067为禁用状态
    HAL_GPIO_WritePin(CD4067_1_E_GPIO_Port, CD4067_1_E_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(CD4067_2_E_GPIO_Port, CD4067_2_E_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(CD4067_3_E_GPIO_Port, CD4067_3_E_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(CD4067_4_E_GPIO_Port, CD4067_4_E_Pin, GPIO_PIN_SET);

		 printf("System initialized, ready for data collection\r\n");
    HAL_Delay(1000);
		
    while (1) {
        // 检查采样率更改
        if(USART_RX_STA & 0x8000) {
            int rate_index = 0;
            for(uint16_t k = 0; k < (USART_RX_STA & 0x3FFF); k++) {
                rate_index = rate_index * 10 + (USART_RX_BUF[k] - '0');
            }
            
            if(rate_index >= 0 && rate_index <= 14) {
                sampling_rate = sampling_rates[rate_index];
                ConfigureADCs();
                printf("Sampling rate changed to index %d successfully!\r\n", rate_index);
            }
            USART_RX_STA = 0;
        }
//				printf("\n--- Master starting data acquisition ---\n");

				  // 1. 执行主机数据采集
        PerformMasterDataCollection();
        
        // 2. 确保所有通道关闭
        DisableAllTxChannels();
        printf("All channels disabled\r\n");
        
        // 3. 从从机收集数据
        CollectDataFromSlave();
        
        // 4. 上报数据到PC
        printf("Sending combined data to PC\r\n");
        // 这里可以将主机数据和从机数据组合后一起发送给PC
        
        HAL_Delay(5000);  // 等待5秒再开始下一个采集周期
		
//        // 首先循环CD4067_1的全部16个引脚
//        for(uint8_t i = 0; i < 16; i++) {
//            // 设置CD4067_1的通道
//            HAL_GPIO_WritePin(CD4067_1_S0_GPIO_Port, CD4067_1_S0_Pin, (i & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(CD4067_1_S1_GPIO_Port, CD4067_1_S1_Pin, (i & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(CD4067_1_S2_GPIO_Port, CD4067_1_S2_Pin, (i & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(CD4067_1_S3_GPIO_Port, CD4067_1_S3_Pin, (i & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//            
//            // 启用CD4067_1
//            HAL_GPIO_WritePin(CD4067_1_E_GPIO_Port, CD4067_1_E_Pin, GPIO_PIN_RESET);
//            
//            // 从CD4067_3的(i+1)通道开始循环
//            for(uint8_t j = i + 1; j < 16; j++) {
//                // 设置CD4067_3的通道
//                HAL_GPIO_WritePin(CD4067_3_S0_GPIO_Port, CD4067_3_S0_Pin, (j & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//                HAL_GPIO_WritePin(CD4067_3_S1_GPIO_Port, CD4067_3_S1_Pin, (j & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//                HAL_GPIO_WritePin(CD4067_3_S2_GPIO_Port, CD4067_3_S2_Pin, (j & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//                HAL_GPIO_WritePin(CD4067_3_S3_GPIO_Port, CD4067_3_S3_Pin, (j & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//                
//                // 启用CD4067_3
//                HAL_GPIO_WritePin(CD4067_3_E_GPIO_Port, CD4067_3_E_Pin, GPIO_PIN_RESET);
//                
//                printf("CD4067_1 CH%d - CD4067_3 CH%d:", i, j);
//                SampleADC1Channels();
//                SampleADC2Channels();
//                SampleADC3Channels();
//                
//                // 禁用CD4067_3
//                HAL_GPIO_WritePin(CD4067_3_E_GPIO_Port, CD4067_3_E_Pin, GPIO_PIN_SET);
//            }
//            
//            // CD4067_4只循环到第12个通道
//            for(uint8_t j = 0; j < 12; j++) {
//                // 设置CD4067_4的通道
//                HAL_GPIO_WritePin(CD4067_4_S0_GPIO_Port, CD4067_4_S0_Pin, (j & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//                HAL_GPIO_WritePin(CD4067_4_S1_GPIO_Port, CD4067_4_S1_Pin, (j & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//                HAL_GPIO_WritePin(CD4067_4_S2_GPIO_Port, CD4067_4_S2_Pin, (j & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//                HAL_GPIO_WritePin(CD4067_4_S3_GPIO_Port, CD4067_4_S3_Pin, (j & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//                
//                // 启用CD4067_4
//                HAL_GPIO_WritePin(CD4067_4_E_GPIO_Port, CD4067_4_E_Pin, GPIO_PIN_RESET);
//                
//                printf("CD4067_1 CH%d - CD4067_4 CH%d:", i, j);
//                SampleADC1Channels();
//                SampleADC2Channels();
//                SampleADC3Channels();
//                
//                // 禁用CD4067_4
//                HAL_GPIO_WritePin(CD4067_4_E_GPIO_Port, CD4067_4_E_Pin, GPIO_PIN_SET);
//            }
//            
//            // 禁用CD4067_1
//            HAL_GPIO_WritePin(CD4067_1_E_GPIO_Port, CD4067_1_E_Pin, GPIO_PIN_SET);
//            
//            HAL_Delay(10);
//        }

//        // CD4067_1循环完成后，循环CD4067_2的12个引脚
//        for(uint8_t i = 0; i < 12; i++) {
//            // 设置CD4067_2的通道
//            HAL_GPIO_WritePin(CD4067_2_S0_GPIO_Port, CD4067_2_S0_Pin, (i & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(CD4067_2_S1_GPIO_Port, CD4067_2_S1_Pin, (i & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(CD4067_2_S2_GPIO_Port, CD4067_2_S2_Pin, (i & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(CD4067_2_S3_GPIO_Port, CD4067_2_S3_Pin, (i & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//            
//            // 启用CD4067_2
//            HAL_GPIO_WritePin(CD4067_2_E_GPIO_Port, CD4067_2_E_Pin, GPIO_PIN_RESET);
//            
//            // 从CD4067_3的(i+1)通道开始循环
//            for(uint8_t j = i + 1; j < 16; j++) {
//                // 设置CD4067_3的通道
//                HAL_GPIO_WritePin(CD4067_3_S0_GPIO_Port, CD4067_3_S0_Pin, (j & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//                HAL_GPIO_WritePin(CD4067_3_S1_GPIO_Port, CD4067_3_S1_Pin, (j & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//                HAL_GPIO_WritePin(CD4067_3_S2_GPIO_Port, CD4067_3_S2_Pin, (j & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//                HAL_GPIO_WritePin(CD4067_3_S3_GPIO_Port, CD4067_3_S3_Pin, (j & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//                
//                // 启用CD4067_3
//                HAL_GPIO_WritePin(CD4067_3_E_GPIO_Port, CD4067_3_E_Pin, GPIO_PIN_RESET);
//                
//                printf("CD4067_2 CH%d - CD4067_3 CH%d:", i, j);
//                SampleADC1Channels();
//                SampleADC2Channels();
//                SampleADC3Channels();
//                
//                // 禁用CD4067_3
//                HAL_GPIO_WritePin(CD4067_3_E_GPIO_Port, CD4067_3_E_Pin, GPIO_PIN_SET);
//            }
//            
//            // CD4067_4只循环到第12个通道
//            for(uint8_t j = 0; j < 12; j++) {
//                // 设置CD4067_4的通道
//                HAL_GPIO_WritePin(CD4067_4_S0_GPIO_Port, CD4067_4_S0_Pin, (j & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//                HAL_GPIO_WritePin(CD4067_4_S1_GPIO_Port, CD4067_4_S1_Pin, (j & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//                HAL_GPIO_WritePin(CD4067_4_S2_GPIO_Port, CD4067_4_S2_Pin, (j & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//                HAL_GPIO_WritePin(CD4067_4_S3_GPIO_Port, CD4067_4_S3_Pin, (j & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//                
//                // 启用CD4067_4
//                HAL_GPIO_WritePin(CD4067_4_E_GPIO_Port, CD4067_4_E_Pin, GPIO_PIN_RESET);
//                
//                printf("CD4067_2 CH%d - CD4067_4 CH%d:", i, j);
//                SampleADC1Channels();
//                SampleADC2Channels();
//                SampleADC3Channels();
//                
//                // 禁用CD4067_4
//                HAL_GPIO_WritePin(CD4067_4_E_GPIO_Port, CD4067_4_E_Pin, GPIO_PIN_SET);
//            }
//            
//            // 禁用CD4067_2
//            HAL_GPIO_WritePin(CD4067_2_E_GPIO_Port, CD4067_2_E_Pin, GPIO_PIN_SET);
//            
//            HAL_Delay(10);
//        }
//				DisableAllTxChannels();
//        
//       
//        HAL_Delay(5000);  // 等待5秒再开始下一个采集周期
    }
}
