/*******************************************************************************
 * File     : Test_Adc_SetupResultBuffer.c
 * Module   : ADC driver (AUTOSAR CP R22-11 / R25-11, Infineon AURIX TC397)
 * Function : Adc_SetupResultBuffer() - SWS_ADCDriver (Service ID 0x0C)
 * Author   : Samarth Shirahatti (Validation team)
 *
 * Result convention (Test_Result):
 *     1 -> PASS (TEST_PASS)
 *     0 -> FAIL (TEST_FAIL)
 ******************************************************************************/

#include "Std_Types.h"
#include "Adc.h"
#include "Adc_Cfg.h"
#include "Det.h"            /* Included for DET stub verification */
#include <stddef.h>

/* Service ID for Adc_SetupResultBuffer */
#define ADC_SID_SETUP_RESULT_BUFFER  (0x0Cu)

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
static Adc_ValueGroupType Test_DataBuffer2[10];
static Adc_ValueGroupType *Null_BufferPtr = NULL;

/* External DET Stub helper prototypes for test validation */
extern void DetStub_Reset(void);
extern uint32 DetStub_GetCount(void);
extern uint8 DetStub_GetLastApiId(void);
extern uint8 DetStub_GetLastErrorId(void);
extern void Test_Reset(void);

/* Getter function for test runner to read result */
uint8 Test_Adc_SetupResultBuffer_GetResult(void)
{
    return Test_Result;
}

/*******************************************************************************
 * TC 1: Valid Group & Valid Buffer (Normal Operation)
 * AUTOSAR Req: SWS_Adc_00420, SWS_Adc_91000
 * Description: Checks if API returns E_OK when valid Group (0) and valid Buffer
 *              are passed under normal initialized state.
 ******************************************************************************/
void Test_Adc_SetupResultBuffer_Tc_001(void)
{
    Std_ReturnType status;

    /* Fix: Reset state & clear DET log before executing test */
    Test_Reset();
    DetStub_Reset();

    /* Initialize ADC module */
    Adc_Init(&adcConfig);

    /* Call API with valid Group (0) and valid Buffer */
    status = Adc_SetupResultBuffer(0, Test_DataBuffer);

    if ((status == E_OK) && (DetStub_GetCount() == 0u))
    {
        Test_Result = TEST_PASS;
    }
    else
    {
        Test_Result = TEST_FAIL;
    }
}

/*******************************************************************************
 * TC 2: Module Uninitialized Check (ADC_E_UNINIT = 0x0A)
 * AUTOSAR Req: SWS_Adc_00434, SWS_Adc_91005
 * Description: Calling API before Adc_Init should report development error 
 *              ADC_E_UNINIT (0x0A) to DET and return E_NOT_OK.
 ******************************************************************************/
void Test_Adc_SetupResultBuffer_Tc_002(void)
{
    Std_ReturnType status;

    Test_Reset();
    DetStub_Reset();

    /* Ensure driver is in uninitialized state */
    Adc_DeInit();

    /* Call API prior to Adc_Init */
    status = Adc_SetupResultBuffer(0, Test_DataBuffer);

    /* Fix: Verify both E_NOT_OK status AND DET stub error log */
    if ((status == E_NOT_OK) &&
        (DetStub_GetCount() == 1u) &&
        (DetStub_GetLastApiId() == ADC_SID_SETUP_RESULT_BUFFER) &&
        (DetStub_GetLastErrorId() == ADC_E_UNINIT))
    {
        Test_Result = TEST_PASS;
    }
    else
    {
        Test_Result = TEST_FAIL;
    }
}

/*******************************************************************************
 * TC 3: Invalid Group ID Check (ADC_E_PARAM_GROUP = 0x15)
 * AUTOSAR Req: SWS_Adc_00423, SWS_Adc_91005
 * Description: Passing an out-of-bounds Group ID (99) should report 
 *              ADC_E_PARAM_GROUP (0x15), return E_NOT_OK, and leave 
 *              existing group result buffers unchanged.
 ******************************************************************************/
void Test_Adc_SetupResultBuffer_Tc_003(void)
{
    Std_ReturnType status;

    Test_Reset();
    DetStub_Reset();

    Adc_Init(&adcConfig);

    /* Pre-set valid buffer for Group 0 */
    Adc_SetupResultBuffer(0, Test_DataBuffer);

    /* Group 99 is invalid/unconfigured */
    status = Adc_SetupResultBuffer(99, Test_DataBuffer2);

    /* Fix: Check return E_NOT_OK, DET error 0x15, AND pointer immutability */
    if ((status == E_NOT_OK) &&
        (DetStub_GetCount() == 1u) &&
        (DetStub_GetLastErrorId() == ADC_E_PARAM_GROUP) &&
        (Adc_GroupResultBufferPtr[0] == Test_DataBuffer))
    {
        Test_Result = TEST_PASS;
    }
    else
    {
        Test_Result = TEST_FAIL;
    }
}

/*******************************************************************************
 * TC 4: NULL Pointer Check for DataBufferPtr (ADC_E_PARAM_POINTER = 0x14)
 * AUTOSAR Req: SWS_Adc_00457, SWS_Adc_91005
 * Description: Passing NULL pointer as DataBufferPtr parameter should report 
 *              ADC_E_PARAM_POINTER (0x14) and return E_NOT_OK.
 ******************************************************************************/
void Test_Adc_SetupResultBuffer_Tc_004(void)
{
    Std_ReturnType status;

    Test_Reset();
    DetStub_Reset();

    Adc_Init(&adcConfig);

    /* Pass NULL pointer */
    status = Adc_SetupResultBuffer(0, Null_BufferPtr);

    /* Fix: Verify DET stub records ADC_E_PARAM_POINTER (0x14) */
    if ((status == E_NOT_OK) &&
        (DetStub_GetCount() == 1u) &&
        (DetStub_GetLastErrorId() == ADC_E_PARAM_POINTER))
    {
        Test_Result = TEST_PASS;
    }
    else
    {
        Test_Result = TEST_FAIL;
    }
}

/*******************************************************************************
 * TC 5: Buffer Allocation when Group is Busy (ADC_E_BUSY = 0x0B)
 * AUTOSAR Req: SWS_Adc_00433, SWS_Adc_91006
 * Description: If called while group is not in ADC_IDLE state (conversion ongoing),
 *              API should report runtime error ADC_E_BUSY (0x0B) and return E_NOT_OK.
 ******************************************************************************/
void Test_Adc_SetupResultBuffer_Tc_005(void)
{
    Std_ReturnType status;

    Test_Reset();
    DetStub_Reset();

    Adc_Init(&adcConfig);

    /* Fix: Setup valid result buffer FIRST so Adc_StartGroupConversion doesn't fail */
    (void)Adc_SetupResultBuffer(0, Test_DataBuffer);
    
    /* Start conversion to put group in ADC_BUSY state */
    Adc_StartGroupConversion(0);

    /* Attempt to reconfigure buffer while group is BUSY */
    status = Adc_SetupResultBuffer(0, Test_DataBuffer2);

    /* Fix: Verify status E_NOT_OK and runtime error 0x0B reported */
    if ((status == E_NOT_OK) &&
        (DetStub_GetLastErrorId() == ADC_E_BUSY))
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
 * TC 6: Internal Result Buffer Address Verification
 * AUTOSAR Req: SWS_Adc_00420, SWS_Adc_91000
 * Description: Verifies that the internal driver buffer pointer variable 
 *              (Adc_GroupResultBufferPtr[0]) holds the memory address of 
 *              the passed application buffer, and API returns E_OK.
 ******************************************************************************/
void Test_Adc_SetupResultBuffer_Tc_006(void)
{
    Std_ReturnType status;

    Test_Reset();
    DetStub_Reset();

    Adc_Init(&adcConfig);

    status = Adc_SetupResultBuffer(0, Test_DataBuffer);

    /* Fix: Check API return value E_OK AND internal pointer match */
    if ((status == E_OK) && 
        (Adc_GroupResultBufferPtr[0] == Test_DataBuffer))
    {
        Test_Result = TEST_PASS;
    }
    else
    {
        Test_Result = TEST_FAIL;
    }
}

/*******************************************************************************
 * TC 7: Buffer Re-assignment for IDLE Group (Coverage Enhancement)
 * AUTOSAR Req: SWS_Adc_00420
 * Description: Verifies that calling Adc_SetupResultBuffer a second time on an 
 *              IDLE group correctly updates the pointer to the new buffer address.
 ******************************************************************************/
void Test_Adc_SetupResultBuffer_Tc_007(void)
{
    Std_ReturnType status1, status2;

    Test_Reset();
    DetStub_Reset();

    Adc_Init(&adcConfig);

    /* Initial buffer assignment */
    status1 = Adc_SetupResultBuffer(0, Test_DataBuffer);

    /* Re-assign buffer for the same idle group */
    status2 = Adc_SetupResultBuffer(0, Test_DataBuffer2);

    if ((status1 == E_OK) && 
        (status2 == E_OK) && 
        (Adc_GroupResultBufferPtr[0] == Test_DataBuffer2))
    {
        Test_Result = TEST_PASS;
    }
    else
    {
        Test_Result = TEST_FAIL;
    }
}