#ifndef __ADS1263_H__
#define __ADS1263_H__

#include <inttypes.h>

/* 基准电压：单位毫伏(mv) */
/* 基准电压改变需要修改此参数
 * 否则调用ADS1263_Digital2Voltage接口返回值会不正确*/
/* 使用芯片内部基准为2500.0 */
/* 使用VAVDD、VAVSS基准为VAVDD-VAVSS=5000.0 */
#define VREF 2500.0

/* 差分输入：0  单端输入：1 */
#define USE_SINGLE_INPUT 1

/* ADS1263 ADC */
typedef enum {
  ADS1263_ADC1 = 0x00, /* ADC1 */
  ADS1263_ADC2,        /* ADC2 */
} ADS1263_ADC;

/* ADS1263命令 */
typedef enum {
  NOP = 0x00,     /* No operation */
  _RESET = 0x06,  /* Reset the ADC */
  START1 = 0x08,  /* Start ADC1 conversions */
  STOP1 = 0x0A,   /* Stop ADC1 conversions */
  START2 = 0x0C,  /* Start ADC2 conversions */
  STOP2 = 0x0E,   /* Stop ADC2 conversions */
  RDATA1 = 0x12,  /* Read ADC1 data */
  RDATA2 = 0x14,  /* Read ADC2 data */
  SYOCAL1 = 0x16, /* ADC1 system offset calibration */
  SYGCAL1 = 0x17, /* ADC1 system gain calibration */
  SFOCAL1 = 0x19, /* ADC1 self offset calibration */
  SYOCAL2 = 0x1B, /* ADC2 system offset calibration */
  SYGCAL2 = 0x1C, /* ADC2 system gain calibration */
  SFOCAL2 = 0x1E, /* ADC2 self offset calibration */
  RREG = 0x20,    /* Read registers */
  WREG = 0x40,    /* Write registers  */
} ADS1263_Commands;

/* ADS1263寄存器地址 */
typedef enum {
  ID = 0x00, /* Device Identification Register */
  POWER,     /* Power Register */
  INTERFACE, /* Interface Register */
  MODE0,     /* Mode0 Register */
  MODE1,     /* Mode1 Register */
  MODE2,     /* Mode2 Register */
  INPMUX,    /* Input Multiplexer Register */
  OFCAL0,    /* Offset Calibration Registers */
  OFCAL1,    /* Offset Calibration Registers */
  OFCAL2,    /* Offset Calibration Registers */
  FSCAL0,    /* Full-Scale Calibration Registers */
  FSCAL1,    /* Full-Scale Calibration Registers */
  FSCAL2,    /* Full-Scale Calibration Registers */
  IDACMUX,   /* IDACMUX Register */
  IDACMAG,   /* IDACMAG Register */
  REFMUX,    /* REFMUX Register */
  TDACP,     /* TDACP Control Register */
  TDACN,     /* TDACN Control Register */
  GPIOCON,   /* GPIO Connection Register */
  GPIODIR,   /* GPIO Direction Register */
  GPIODAT,   /* GPIO Data Register */
  ADC2CFG,   /* ADC2 Configuration Register */
  ADC2MUX,   /* ADC2 Input Multiplexer Register */
  ADC2OFC0,  /* ADC2 Offset Calibration Registers */
  ADC2OFC1,  /* ADC2 Offset Calibration Registers */
  ADC2FSC0,  /* ADC2 Full-Scale Calibration Registers */
  ADC2FSC1,  /* ADC2 Full-Scale Calibration Registers */
} ADS1263_Register_Map;

/**
 * @brief INTERFACE寄存器参数定义以及配置
 *
 */
///@{
/* Serial Interface Time-Out Enable */
typedef enum {
  DisabledTimeout = 0, /* Disabled (default) */
  EnableTimeout,       /* Enable the interface automatic time-out */
} ADS1263_TIMEOUT;

/* Status Byte Enable */
typedef enum {
  DisabledStatus = 0, /*Disabled */
  EnableStatus,       /* Status byte included during conversion data
                         read-back(default) */
} ADS1263_STATUS;

/* Checksum Byte Enable */
typedef enum {
  DisabledCRC = 0,    /* Checksum byte disabled */
  EnableChecksumMode, /* Enable Checksum byte in Checksum mode during conversion
                         data read-back (default) */
  EnableCRCMode, /*  Enable Checksum byte in CRC mode during conversion data
                    read-back */
} ADS1263_CRC;

/* INTERFACE寄存器 */
typedef struct {
  ADS1263_TIMEOUT timeout; /* 见TIMEOUT参数 */
  ADS1263_STATUS status;   /* 见STATUS参数 */
  ADS1263_CRC crc;         /* 见CRC参数 */
} ADS1263_INTERFACE_Register;
///@}

/**
 * @brief INPMUX寄存器参数定义以及配置
 *
 */
///@{
/* Input Multiplexer */
typedef enum {
  ADC1_AIN0 = 0,          /* AIN0 */
  ADC1_AIN1,              /* AIN1 */
  ADC1_AIN2,              /* AIN2 */
  ADC1_AIN3,              /* AIN3 */
  ADC1_AIN4,              /* AIN4 */
  ADC1_AIN5,              /* AIN5 */
  ADC1_AIN6,              /* AIN6 */
  ADC1_AIN7,              /* AIN7 */
  ADC1_AIN8,              /* AIN8 */
  ADC1_AIN9,              /* AIN9 */
  ADC1_AINCOM,            /* AINCOM */
  ADC1_TemperatureSensor, /* Temperature sensor monitor */
  ADC1_AnalogPower,       /*  Analog power supply monitor */
  ADC1_DigitalPower,      /* Digital power supply monitor */
  ADC1_TDAC,              /* TDAC test signal */
  ADC1_Float,             /* Float (open connection) */
} ADS1263_Input_Multiplexer;

/* INPMUX寄存器 */
typedef struct {
  ADS1263_Input_Multiplexer
      multiplexer_positive; /* 见ADS1263_Input_Multiplexer参数 */
  ADS1263_Input_Multiplexer
      multiplexer_negative; /* 见ADS1263_Input_Multiplexer参数 */
} ADS1263_INPMUX_Register;
///@}

/**
 * @brief REFMUX寄存器参数定义以及配置
 *
 */
///@{
/* Reference Positive Input */
typedef enum {
  Internal_2_5_V_P = 0x00, /* Internal 2.5 V reference - P (default) */
  External_AIN0,           /* External AIN0 */
  External_AIN2,           /* External AIN2 */
  External_AIN4,           /* External AIN4 */
  VAVDD,                   /* Internal analog supply (VAVDD) */
} ADS1263_RMUXP;

/* Reference Negative Input */
typedef enum {
  Internal_2_5_V_N = 0x00, /* Internal 2.5 V reference - N (default) */
  External_AIN1,           /* External AIN1 */
  External_AIN3,           /* External AIN3 */
  External_AIN5,           /* External AIN5 */
  VAVSS,                   /* Internal analog supply (VAVSS) */
} ADS1263_RMUXN;

/* REFMUX寄存器 */
typedef struct {
  ADS1263_RMUXP positive_reference; /* 见ADS1263_RMUXP参数 */
  ADS1263_RMUXN negative_reference; /* 见ADS1263_RMUXN参数 */
} ADS1263_REFMUX_Register;
///@}

/**
 * @brief MODE2寄存器参数定义以及配置
 *
 */
///@{
/* PGA Bypass Mode */
typedef enum {
  PGA_Enabled = 0x00, /* PGA enabled (default) */
  PGA_Bypassed,       /* PGA bypassed */
} ADS1263_BYPASS;

/* PGA Gain */
typedef enum {
  ADC1_GAIN_1 = 0x00, /* 1 V/V (default) */
  ADC1_GAIN_2,        /* 2 V/V */
  ADC1_GAIN_4,        /* 4 V/V */
  ADC1_GAIN_8,        /* 8 V/V */
  ADC1_GAIN_16,       /* 16 V/V */
  ADC1_GAIN_32,       /* 32 V/V */
} ADS1263_GAIN;

/* Data Rate */
typedef enum {
  ADC1_2_5_SPS = 0x00, /* 2.5 SPS */
  ADC1_5_SPS,          /* 5 SPS */
  ADC1_10_SPS,         /* 10 SPS */
  ADC1_16_6_SPS,       /* 16.6 SPS */
  ADC1_20_SPS,         /* 20 SPS */
  ADC1_50_SPS,         /* 50 SPS */
  ADC1_60_SPS,         /* 60 SPS */
  ADC1_100_SPS,        /* 100 SPS */
  ADC1_400_SPS,        /* 400 SPS */
  ADC1_1200_SPS,       /* 1200 SPS */
  ADC1_2400_SPS,       /* 2400 SPS */
  ADC1_4800_SPS,       /* 4800 SPS */
  ADC1_7200_SPS,       /* 7200 SPS */
  ADC1_14400_SPS,      /* 14400 SPS */
  ADC1_19200_SPS,      /* 19200 SPS */
  ADC1_38400_SPS,      /* 38400 SPS */
} ADS1263_DR;

/**
 * @brief MODE2寄存器
 *
 */
typedef struct {
  ADS1263_BYPASS bypass; /* 见ADS1263_BYPASS参数 */
  ADS1263_GAIN gain;     /* 见ADS1263_GAIN参数 */
  ADS1263_DR dr;         /* 见ADS1263_DR参数 */
} ADS1263_MODE2_Register;
///@}

/**
 * @brief ADC2CFG寄存器参数定义以及配置
 *
 */
///@{
/* ADC2 Data Rate */
typedef enum {
  ADC2_10_SPS = 0x00, /* 10 SPS (default) */
  ADC2_100_SPS,       /* 100 SPS */
  ADC2_400_SPS,       /* 400 SPS */
  ADC2_800_SPS,       /* 800 SPS */
} ADS1263_DR2;

/* ADC2 Reference Input */
typedef enum {
  Internal_2_5_V_P_N =
      0x00, /* Internal 2.5 V reference, positive and negative (default) */
  External_AIN0_AIN1_P_N,   /* External AIN0 and AIN1 pin pairs as positive and
                              negative */
  External_AIN2_AIN3_P_N,   /* External AIN2 and AIN3 pin pairs as positive and
                              negative */
  External_AIN4_AIN5_P_N,   /* External AIN4 and AIN5 pin pairs as positive and
                              negative */
  Internal_VAVDD_VAVSS_P_N, /* Internal VAVDD and VAVSS */
} ADS1263_REF2;

/* ADC2 Gain */
typedef enum {
  ADC2_GAIN_1 = 0x00, /* 1 V/V (default) */
  ADC2_GAIN_2,        /* 2 V/V */
  ADC2_GAIN_4,        /* 4 V/V */
  ADC2_GAIN_8,        /* 8 V/V */
  ADC2_GAIN_16,       /* 16 V/V */
  ADC2_GAIN_32,       /* 32 V/V */
  ADC2_GAIN_64,       /* 64 V/V */
  ADC2_GAIN_128,      /* 128 V/V */
} ADS1263_GAIN2;

/* ADC2CFG寄存器 */
typedef struct {
  ADS1263_DR2 dr2;     /* 见ADS1263_DR2参数 */
  ADS1263_REF2 ref2;   /* 见ADS1263_REF2参数 */
  ADS1263_GAIN2 gain2; /* 见ADS1263_GAIN2参数 */
} ADS1263_ADC2CFG_Register;
///@}

/**
 * @brief ADC2MUX寄存器参数定义以及配置
 *
 */
///@{
/* ADC2 Input Multiplexer */
typedef enum {
  ADC2_AIN0 = 0,          /* AIN0 */
  ADC2_AIN1,              /* AIN1 */
  ADC2_AIN2,              /* AIN2 */
  ADC2_AIN3,              /* AIN3 */
  ADC2_AIN4,              /* AIN4 */
  ADC2_AIN5,              /* AIN5 */
  ADC2_AIN6,              /* AIN6 */
  ADC2_AIN7,              /* AIN7 */
  ADC2_AIN8,              /* AIN8 */
  ADC2_AIN9,              /* AIN9 */
  ADC2_AINCOM,            /* AINCOM */
  ADC2_TemperatureSensor, /* Temperature sensor monitor */
  ADC2_AnalogPower,       /*  Analog power supply monitor */
  ADC2_DigitalPower,      /* Digital power supply monitor */
  ADC2_TDAC,              /* TDAC test signal */
  ADC2_Open_Connection,   /* open connection */
} ADS1263_ADC2_Input_Multiplexer;

/* ADC2MUX寄存器 */
typedef struct {
  ADS1263_ADC2_Input_Multiplexer
      multiplexer_positive; /* 见ADS1263_ADC2_Input_Multiplexer参数 */
  ADS1263_ADC2_Input_Multiplexer
      multiplexer_negative; /* 见ADS1263_ADC2_Input_Multiplexer参数 */
} ADS1263_ADC2MUX_Register;
///@}

extern ADS1263_INTERFACE_Register INTERFACE_Config;
extern ADS1263_INPMUX_Register INPMUX_Config;
extern ADS1263_REFMUX_Register REFMUX_Config;
extern ADS1263_MODE2_Register MODE2_Config;
extern ADS1263_ADC2CFG_Register ADC2CFG_Config;
extern ADS1263_ADC2MUX_Register ADC2MUX_Config;

void ADS1263_Init(void);
void ADS1263_Hardware_Reset(void);
void ADS1263_Set_INTERFACE_Register(ADS1263_INTERFACE_Register *config);
void ADS1263_Set_INPMUX_Register(ADS1263_INPMUX_Register *config);
void ADS1263_Set_REFMUX_Register(ADS1263_REFMUX_Register *config);
void ADS1263_Set_MODE2_Register(ADS1263_MODE2_Register *config);
void ADS1263_Set_ADC2CFG_Register(ADS1263_ADC2CFG_Register *config);
void ADS1263_Set_ADC2MUX_Register(ADS1263_ADC2MUX_Register *config);
double ADS1263_Digital2Voltage(ADS1263_ADC adc, uint32_t data);
void ADS1263_Start_ADC(ADS1263_ADC adc);
uint32_t ADS1263_Read_ADC(ADS1263_ADC adc);

#endif
