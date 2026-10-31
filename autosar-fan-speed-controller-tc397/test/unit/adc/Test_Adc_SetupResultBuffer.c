/*******************************************************************************
 * File     : Test_Adc_SetupResultBuffer.c
 * Module   : ADC driver (AUTOSAR CP R22-11, Infineon AURIX TC397)
 * Function : Adc_SetupResultBuffer() - SWS_ADCDriver
 * Author   : Samarth (Validation team)
 *
 * Result convention (Test_Result):
 *     1 -> PASS
 *     0 -> FAIL
 ******************************************************************************/

#include "Std_Types.h"
#include "Adc.h"
#include "Adc_Cfg.h"
#include <stddef.h>

/* Define test result macros matching project conventions */
#define TEST_PASS (1u)
#define TEST_FAIL (0u)

/* Shared Test Result Variable */
static uint8 Test_Result;

/* External dependencies provided by the driver and configuration */
extern const Adc_ConfigType adcConfig;
extern Adc_ValueGroupType* Adc_GroupResultBufferPtr[];

/* Test Buffers */
static Adc_ValueGroupType Test_DataBuffer[10];
static Adc_ValueGroupType *Null_BufferPtr = NULL;

/* Getter function for test runner to read result */
uint8 Test_Adc_SetupResultBuffer_GetResult(void)
{
    return Test_Result;
}

/*******************************************************************************
 * TC 1: Valid Group & Valid Buffer (Normal Operation)
 * Requirement Spec: SWS_Adc_00421
 * Description: Checks if API returns E_OK when valid Group and Buffer are passed.
 ******************************************************************************/
void Test_Adc_SetupResultBuffer_Tc_001(void)
{
    Std_ReturnType status;

    /* Initialize ADC module first */
    Adc_Init(&adcConfig);

    /* Call API with valid Group (0) and valid Buffer */
    status = Adc_SetupResultBuffer(0, Test_DataBuffer);

    if (status == E_OK)
    {
        Test_Result = TEST_PASS;
    }
    else
    {
        Test_Result = TEST_FAIL;
    }
}

/*******************************************************************************
 * TC 2: Module Uninitialized Check (ADC_E_UNINIT)
 * Requirement Spec: SWS_Adc_00125
 * Description: Calling API before Adc_Init should return E_NOT_OK or DET error.
 ******************************************************************************/
void Test_Adc_SetupResultBuffer_Tc_002(void)
{
    Std_ReturnType status;

    /* Intentionally DO NOT call Adc_Init() */
    status = Adc_SetupResultBuffer(0, Test_DataBuffer);

    if (status == E_NOT_OK)
    {
        Test_Result = TEST_PASS;
    }
    else
    {
        Test_Result = TEST_FAIL;
    }
}

/*******************************************************************************
 * TC 3: Invalid Group ID Check (ADC_E_PARAM_GROUP)
 * Requirement Spec: SWS_Adc_00126
 * Description: Passing an out-of-bounds Group ID (e.g., 99) should return E_NOT_OK.
 ******************************************************************************/
void Test_Adc_SetupResultBuffer_Tc_003(void)
{
    Std_ReturnType status;

    Adc_Init(&adcConfig);

    /* Group 99 is invalid/unconfigured */
    status = Adc_SetupResultBuffer(99, Test_DataBuffer);

    if (status == E_NOT_OK)
    {
        Test_Result = TEST_PASS;
    }
    else
    {
        Test_Result = TEST_FAIL;
    }
}

/*******************************************************************************
 * TC 4: NULL Pointer Check for DataBufferPtr (ADC_E_PARAM_POINTER)
 * Requirement Spec: SWS_Adc_00358
 * Description: Passing NULL pointer as buffer parameter should return E_NOT_OK.
 ******************************************************************************/
void Test_Adc_SetupResultBuffer_Tc_004(void)
{
    Std_ReturnType status;

    Adc_Init(&adcConfig);

    /* Pass NULL pointer */
    status = Adc_SetupResultBuffer(0, Null_BufferPtr);

    if (status == E_NOT_OK)
    {
        Test_Result = TEST_PASS;
    }
    else
    {
        Test_Result = TEST_FAIL;
    }
}

/*******************************************************************************
 * TC 5: Buffer Allocation when Group is Busy (ADC_E_BUSY)
 * Requirement Spec: SWS_Adc_00318
 * Description: Cannot update buffer while continuous conversion is ongoing.
 ******************************************************************************/
void Test_Adc_SetupResultBuffer_Tc_005(void)
{
    Std_ReturnType status;

    Adc_Init(&adcConfig);
    
    /* Start conversion to put group in ADC_BUSY state */
    Adc_StartGroupConversion(0);

    /* Attempt to reconfigure buffer while busy */
    status = Adc_SetupResultBuffer(0, Test_DataBuffer);

    if (status == E_NOT_OK)
    {
        Test_Result = TEST_PASS;
    }
    else
    {
        Test_Result = TEST_FAIL;
    }
    
    /* Cleanup / Stop conversion */
    Adc_StopGroupConversion(0);
}

/*******************************************************************************
 * TC 6: Register Hardware Address Buffer Pointer Verification
 * Requirement Spec: SWS_Adc_00422
 * Description: Verifies that internal driver pointer points to target buffer address.
 ******************************************************************************/
void Test_Adc_SetupResultBuffer_Tc_006(void)
{
    Adc_Init(&adcConfig);

    Adc_SetupResultBuffer(0, Test_DataBuffer);

    /* Check if internal driver/hardware buffer address matches passed buffer */
    if (Adc_GroupResultBufferPtr[0] == Test_DataBuffer)
    {
        Test_Result = TEST_PASS;
    }
    else
    {
        Test_Result = TEST_FAIL;
    }
}