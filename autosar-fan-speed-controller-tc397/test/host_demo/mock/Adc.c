/* MOCK of the developers' Adc.c - only enough behaviour to demonstrate the tests. */
#include "Adc.h"
#include "Det_Stub.h"
const Adc_ConfigType adcConfig = { 0u };
static uint8 s_init;
static Adc_StatusType s_status[2];
void Adc_Init(const Adc_ConfigType* ConfigPtr)
{
    if (s_init != 0u)            { (void)Det_ReportError(ADC_MODULE_ID, 0u, 0x00u, 0x0Du); return; }
    if (ConfigPtr == NULL_PTR)   { (void)Det_ReportError(ADC_MODULE_ID, 0u, 0x00u, 0x14u); return; }
    s_status[0] = ADC_IDLE; s_status[1] = ADC_IDLE; s_init = 1u;
}
void Adc_DeInit(void) { s_init = 0u; }
Adc_StatusType Adc_GetGroupStatus(Adc_GroupType Group)
{
    if (s_init == 0u) { (void)Det_ReportError(ADC_MODULE_ID, 0u, 0x15u, 0x0Au); return ADC_IDLE; }
    return s_status[Group];
}
