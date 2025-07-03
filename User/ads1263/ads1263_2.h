#ifndef __ADS1263_2_H__
#define __ADS1263_2_H__

#include <inttypes.h>
#include "ads1263.h"  // 包含原始ads1263.h以使用其中的类型定义

/* Keep the same VREF definition as it's using internal reference */
#define VREF 2500.0

/* Keep the same single/differential input setting */
#define USE_SINGLE_INPUT 1

/* External configuration variables for second ADS1263 chip */
extern ADS1263_INTERFACE_Register INTERFACE_2_Config;
extern ADS1263_INPMUX_Register INPMUX_2_Config;
extern ADS1263_REFMUX_Register REFMUX_2_Config;
extern ADS1263_MODE2_Register MODE2_2_Config;
extern ADS1263_ADC2CFG_Register ADC2CFG_2_Config;
extern ADS1263_ADC2MUX_Register ADC2MUX_2_Config;

/* Function prototypes for second ADS1263 chip */
void ADS1263_2_Init(void);
void ADS1263_2_Hardware_Reset(void);
void ADS1263_2_Set_INTERFACE_Register(ADS1263_INTERFACE_Register *config);
void ADS1263_2_Set_INPMUX_Register(ADS1263_INPMUX_Register *config);
void ADS1263_2_Set_REFMUX_Register(ADS1263_REFMUX_Register *config);
void ADS1263_2_Set_MODE2_Register(ADS1263_MODE2_Register *config);
void ADS1263_2_Set_ADC2CFG_Register(ADS1263_ADC2CFG_Register *config);
void ADS1263_2_Set_ADC2MUX_Register(ADS1263_ADC2MUX_Register *config);
double ADS1263_2_Digital2Voltage(ADS1263_ADC adc, uint32_t data);
void ADS1263_2_Start_ADC(ADS1263_ADC adc);
uint32_t ADS1263_2_Read_ADC(ADS1263_ADC adc);

#endif /* __ADS1263_2_H__ */
