#include "ads1263_2.h"
#include "delay.h"
#include "gpio.h"
#include <stdbool.h>

/**
 * @brief INTERFACE_RegisterĬ��ֵ
 */
ADS1263_INTERFACE_Register INTERFACE_2_Config = {
    .timeout = DisabledTimeout,
    .status = EnableStatus,
    .crc = EnableChecksumMode,
};

/**
 * @brief INPMUX_RegisterĬ��ֵ
 */
ADS1263_INPMUX_Register INPMUX_2_Config = {
    .multiplexer_positive = ADC1_AIN0,
    .multiplexer_negative = ADC1_AIN1,
};

/**
 * @brief REFMUX_RegisterĬ��ֵ
 */
ADS1263_REFMUX_Register REFMUX_2_Config = {
    .positive_reference = Internal_2_5_V_P,
    .negative_reference = Internal_2_5_V_N,
};

/**
 * @brief Mode2_RegisterĬ��ֵ
 */
ADS1263_MODE2_Register MODE2_2_Config = {
    .bypass = PGA_Enabled,
    .gain = ADC1_GAIN_1,
    .dr = ADC1_20_SPS,
};

/**
 * @brief ADC2CFG_RegisterĬ��ֵ
 */
ADS1263_ADC2CFG_Register ADC2CFG_2_Config = {
    .dr2 = ADC2_10_SPS,
    .ref2 = Internal_2_5_V_P_N,
    .gain2 = ADC2_GAIN_1,
};

/**
 * @brief ADC2MUX_RegisterĬ��ֵ
 */
ADS1263_ADC2MUX_Register ADC2MUX_2_Config = {
    .multiplexer_positive = ADC2_AIN0,
    .multiplexer_negative = ADC2_AIN1,
};

/**
 * @brief ??spi??
 */
static void ADS1263_2_SPI_Transmit(uint8_t *data, uint8_t data_size) {
    uint8_t shift = 0x80;
    for (uint8_t i = 0; i < data_size; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            HAL_GPIO_WritePin(ADS1263_2_SCLK_GPIO_Port, ADS1263_2_SCLK_Pin, GPIO_PIN_SET);
            delay_us(1);
            bool level = shift & data[i];
            if (level) {
                HAL_GPIO_WritePin(ADS1263_2_DIO_GPIO_Port, ADS1263_2_DIO_Pin, GPIO_PIN_SET);
            } else {
                HAL_GPIO_WritePin(ADS1263_2_DIO_GPIO_Port, ADS1263_2_DIO_Pin, GPIO_PIN_RESET);
            }
            shift >>= 1;
            HAL_GPIO_WritePin(ADS1263_2_SCLK_GPIO_Port, ADS1263_2_SCLK_Pin, GPIO_PIN_RESET);
        }
        shift = 0x80;
    }
}

/**
 * @brief ??spi??
 */
static void ADS1263_2_SPI_Receive(uint8_t *data, uint8_t data_size) {
    uint8_t shift = 0x80;
    uint8_t input_level = 0;
    for (uint8_t i = 0; i < data_size; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            HAL_GPIO_WritePin(ADS1263_2_SCLK_GPIO_Port, ADS1263_2_SCLK_Pin, GPIO_PIN_SET);
            delay_us(1);
            GPIO_PinState state = HAL_GPIO_ReadPin(ADS1263_2_DOUT_GPIO_Port, ADS1263_2_DOUT_Pin);
            if (state == GPIO_PIN_SET) {
                input_level |= shift;
            } else if (state == GPIO_PIN_RESET) {
                input_level &= (~shift);
            }
            shift >>= 1;
            HAL_GPIO_WritePin(ADS1263_2_SCLK_GPIO_Port, ADS1263_2_SCLK_Pin, GPIO_PIN_RESET);
        }
        data[i] = input_level;
        shift = 0x80;
        input_level = 0;
    }
}
/**
 * @brief ADS1263д����
 */
static void ADS1263_2_Write_Command(uint8_t command) {
    uint8_t spi_data[1] = {0};
    spi_data[0] = command;
    ADS1263_2_SPI_Transmit(spi_data, sizeof(spi_data));
}

/**
 * @brief ADS1263д�Ĵ���
 */
static void ADS1263_2_Write_Register(uint8_t address, uint8_t data) {
    uint8_t spi_data[3] = {0};
    spi_data[0] = WREG | address;
    spi_data[1] = 0x00;
    spi_data[2] = data;
    ADS1263_2_SPI_Transmit(spi_data, sizeof(spi_data));
}

/**
 * @brief ADS1263��ADC����
 */
static void ADS1263_2_Read_Data(uint8_t *data, uint8_t data_size) {
    ADS1263_2_SPI_Receive(data, data_size);
}

/**
 * @brief ����INTERFACE�Ĵ���
 */
void ADS1263_2_Set_INTERFACE_Register(ADS1263_INTERFACE_Register *config) {
    uint8_t data = (config->timeout << 3) | (config->status << 2) | config->crc;
    HAL_GPIO_WritePin(ADS1263_2_CS_GPIO_Port, ADS1263_2_CS_Pin, GPIO_PIN_RESET);
    ADS1263_2_Write_Register(INTERFACE, data);
    HAL_GPIO_WritePin(ADS1263_2_CS_GPIO_Port, ADS1263_2_CS_Pin, GPIO_PIN_SET);
}

void ADS1263_2_Set_INPMUX_Register(ADS1263_INPMUX_Register *config) {
    uint8_t data = (config->multiplexer_positive << 4) | config->multiplexer_negative;
    HAL_GPIO_WritePin(ADS1263_2_CS_GPIO_Port, ADS1263_2_CS_Pin, GPIO_PIN_RESET);
    ADS1263_2_Write_Register(INPMUX, data);
    HAL_GPIO_WritePin(ADS1263_2_CS_GPIO_Port, ADS1263_2_CS_Pin, GPIO_PIN_SET);
}

/**
 * @brief ����REFMUX�Ĵ���
 */
void ADS1263_2_Set_REFMUX_Register(ADS1263_REFMUX_Register *config) {
    uint8_t data = (config->positive_reference << 3) | config->negative_reference;
     HAL_GPIO_WritePin(ADS1263_2_CS_GPIO_Port, ADS1263_2_CS_Pin, GPIO_PIN_RESET); // CS
    ADS1263_2_Write_Register(REFMUX, data);
     HAL_GPIO_WritePin(ADS1263_2_CS_GPIO_Port, ADS1263_2_CS_Pin, GPIO_PIN_SET);
}

/**
 * @brief ����MODE2�Ĵ���
 */
void ADS1263_2_Set_MODE2_Register(ADS1263_MODE2_Register *config) {
    uint8_t data = (config->bypass << 7) | (config->gain << 4) | config->dr;
    HAL_GPIO_WritePin(ADS1263_2_CS_GPIO_Port, ADS1263_2_CS_Pin, GPIO_PIN_RESET);// CS
    ADS1263_2_Write_Register(MODE2, data);
    HAL_GPIO_WritePin(ADS1263_2_CS_GPIO_Port, ADS1263_2_CS_Pin, GPIO_PIN_SET);
}

/**
 * @brief ����ADC2CFG�Ĵ���
 */
void ADS1263_2_Set_ADC2CFG_Register(ADS1263_ADC2CFG_Register *config) {
    uint8_t data = (config->dr2 << 6) | (config->ref2 << 3) | config->gain2;
     HAL_GPIO_WritePin(ADS1263_2_CS_GPIO_Port, ADS1263_2_CS_Pin, GPIO_PIN_RESET); // CS
    ADS1263_2_Write_Register(ADC2CFG, data);
     HAL_GPIO_WritePin(ADS1263_2_CS_GPIO_Port, ADS1263_2_CS_Pin, GPIO_PIN_SET);
}

/**
 * @brief ����ADC2MUX�Ĵ���
 */
void ADS1263_2_Set_ADC2MUX_Register(ADS1263_ADC2MUX_Register *config) {
    uint8_t data = (config->multiplexer_positive << 4) | config->multiplexer_negative;
     HAL_GPIO_WritePin(ADS1263_2_CS_GPIO_Port, ADS1263_2_CS_Pin, GPIO_PIN_RESET); // CS
    ADS1263_2_Write_Register(ADC2MUX, data);
    HAL_GPIO_WritePin(ADS1263_2_CS_GPIO_Port, ADS1263_2_CS_Pin, GPIO_PIN_SET);
}

/**
 * @brief ����ADC�ɼ�
 */
void ADS1263_2_Start_ADC(ADS1263_ADC adc) {
    HAL_GPIO_WritePin(ADS1263_2_CS_GPIO_Port, ADS1263_2_CS_Pin, GPIO_PIN_RESET);
    if (adc == ADS1263_ADC1) {
        ADS1263_2_Write_Command(START1);
    } else if (adc == ADS1263_ADC2) {
        ADS1263_2_Write_Command(START2);
    }
    HAL_GPIO_WritePin(ADS1263_2_CS_GPIO_Port, ADS1263_2_CS_Pin, GPIO_PIN_SET);
}

/**
 * @brief ��ȡADC����
 */
uint32_t ADS1263_2_Read_ADC(ADS1263_ADC adc) {
    uint8_t data[5] = {0};
    uint32_t u32_data = 0;
     HAL_GPIO_WritePin(ADS1263_2_CS_GPIO_Port, ADS1263_2_CS_Pin, GPIO_PIN_RESET);// CS
    if (adc == ADS1263_ADC1) {
        do {
            ADS1263_2_Write_Command(RDATA1);
            ADS1263_2_Read_Data(data, sizeof(data));
        } while (!(*data & 0x40));
        u32_data = (data[1] << 24) | (data[2] << 16) | (data[3] << 8) | data[4];
    } else if (adc == ADS1263_ADC2) {
        do {
            ADS1263_2_Write_Command(RDATA2);
            ADS1263_2_Read_Data(data, sizeof(data));
        } while (!(*data & 0x80));
        u32_data = (data[1] << 16) | (data[2] << 8) | data[3];
    }
     HAL_GPIO_WritePin(ADS1263_2_CS_GPIO_Port, ADS1263_2_CS_Pin, GPIO_PIN_SET);
    return u32_data;
}

/**
 * @brief uint32_tתdouble
 */
double ADS1263_2_Digital2Voltage(ADS1263_ADC adc, uint32_t data) {
    int32_t signed_data = data;
    uint8_t adc1_gain = 1;
    switch (MODE2_2_Config.gain) {
        case ADC1_GAIN_1: {
            adc1_gain = 1;
            break;
        }
        case ADC1_GAIN_2: {
            adc1_gain = 2;
            break;
        }
        case ADC1_GAIN_4: {
            adc1_gain = 4;
            break;
        }
        case ADC1_GAIN_8: {
            adc1_gain = 8;
            break;
        }
        case ADC1_GAIN_16: {
            adc1_gain = 16;
            break;
        }
        case ADC1_GAIN_32: {
            adc1_gain = 32;
            break;
        }
    }
    if (adc == ADS1263_ADC1) {
        return (double)signed_data * VREF / (double)0x7FFFFFFF / adc1_gain;
    } else if (adc == ADS1263_ADC2) {
        return (double)signed_data * VREF / (double)0x7FFFFF;
    }
    return 0;
}

/**
 * @brief ADS1263Ӳ����λ
 */
void ADS1263_2_Hardware_Reset(void) {
    HAL_GPIO_WritePin(ADS1263_2_RESET_GPIO_Port, ADS1263_2_RESET_Pin, GPIO_PIN_RESET);
    HAL_Delay(300);
    HAL_GPIO_WritePin(ADS1263_2_RESET_GPIO_Port, ADS1263_2_RESET_Pin, GPIO_PIN_SET);
    HAL_Delay(300);
}

void ADS1263_2_Init(void) {
    HAL_GPIO_WritePin(ADS1263_2_CS_GPIO_Port, ADS1263_2_CS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(ADS1263_2_RESET_GPIO_Port, ADS1263_2_RESET_Pin, GPIO_PIN_SET);
}
