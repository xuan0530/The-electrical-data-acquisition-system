#ifndef __ADS1263_3_H__
#define __ADS1263_3_H__

#include <inttypes.h>
#include "ads1263.h"  // Include original ads1263.h to use its type definitions

/* Keep the same VREF definition as it's using internal reference */
#define VREF 2500.0

/* Keep the same single/differential input setting */
#define USE_SINGLE_INPUT 1

/* External configuration variables for third ADS1263 chip */
extern ADS1263_INTERFACE_Register INTERFACE_3_Config;
extern ADS1263_INPMUX_Register INPMUX_3_Config;
extern ADS1263_REFMUX_Register REFMUX_3_Config;
extern ADS1263_MODE2_Register MODE2_3_Config;
extern ADS1263_ADC2CFG_Register ADC2CFG_3_Config;
extern ADS1263_ADC2MUX_Register ADC2MUX_3_Config;

/* Function prototypes for third ADS1263 chip */
void ADS1263_3_Init(void);
void ADS1263_3_Hardware_Reset(void);
void ADS1263_3_Set_INTERFACE_Register(ADS1263_INTERFACE_Register *config);
void ADS1263_3_Set_INPMUX_Register(ADS1263_INPMUX_Register *config);
void ADS1263_3_Set_REFMUX_Register(ADS1263_REFMUX_Register *config);
void ADS1263_3_Set_MODE2_Register(ADS1263_MODE2_Register *config);
void ADS1263_3_Set_ADC2CFG_Register(ADS1263_ADC2CFG_Register *config);
void ADS1263_3_Set_ADC2MUX_Register(ADS1263_ADC2MUX_Register *config);
double ADS1263_3_Digital2Voltage(ADS1263_ADC adc, uint32_t data);
void ADS1263_3_Start_ADC(ADS1263_ADC adc);
uint32_t ADS1263_3_Read_ADC(ADS1263_ADC adc);

#endif /* __ADS1263_3_H__ */
