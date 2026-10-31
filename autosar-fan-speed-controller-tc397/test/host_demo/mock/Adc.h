/* MOCK of the developers' Adc.h - only for the PC demo. NOT the real driver. */
#ifndef ADC_H
#define ADC_H
#include "Std_Types.h"
#define ADC_MODULE_ID (123u)
typedef uint8 Adc_GroupType;
typedef struct { uint8 Dummy; } Adc_ConfigType;
typedef enum { ADC_IDLE = 0, ADC_BUSY, ADC_COMPLETED, ADC_STREAM_COMPLETED } Adc_StatusType;
void           Adc_Init(const Adc_ConfigType* ConfigPtr);
void           Adc_DeInit(void);
Adc_StatusType Adc_GetGroupStatus(Adc_GroupType Group);
#endif
