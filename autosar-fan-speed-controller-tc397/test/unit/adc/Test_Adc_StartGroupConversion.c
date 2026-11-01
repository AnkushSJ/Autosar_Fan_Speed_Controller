/*******************************************************************************
 * File     : Test_Adc_StartGroupConversion.c
 * Module   : ADC driver (AUTOSAR CP R22-11, Infineon AURIX TC397)
 * Function : Adc_StartGroupConversion()
 * Author   : Validation team
 *
 * Result convention:
 *     1    -> PASS
 *     0    -> FAIL
 *     0xFF -> NOT IMPLEMENTED
 ******************************************************************************/

#include "Std_Types.h"
#include "Adc.h"
#include "Adc_Cfg.h"
#include "Det_Stub.h"

#define TEST_PASS             (1u)
#define TEST_FAIL             (0u)
#define TEST_NOT_IMPLEMENTED  (0xFFu)

#define ADC_START_GROUP_API_ID (0x02u)

static uint8 Test_Result;

extern const Adc_ConfigType adcConfig;

/*
 * This pointer must be exposed by the driver for TC 3.
 * If it is private, add a test-only accessor in Adc.c instead.
 */
extern Adc_ValueGroupType *Adc_GroupResultBufferPtr[];

/* Test data buffer */
static Adc_ValueGroupType Test_DataBuffer[3];

/*******************************************************************************
 * Getter function
 ******************************************************************************/
uint8 Test_Adc_StartGroupConversion_GetResult(void)
{
    return Test_Result;
}

/*******************************************************************************
 * Common reset function
 ******************************************************************************/
static void Test_Reset(void)
{
    Adc_DeInit();
    DetStub_Reset();

    Adc_Init(&adcConfig);

    DetStub_Reset();
}

/*******************************************************************************
 * TC 1: Successful conversion
 * Requirement: REQ_ADC_017 / SWS_Adc_00367
 *
 * Description:
 * Checks whether a valid software-triggered group starts conversion.
 ******************************************************************************/
void Test_Adc_StartGroupConversion_Tc_001(void)
{
    Test_Reset();

    (void)Adc_SetupResultBuffer(0u, Test_DataBuffer);
    DetStub_Reset();

    Adc_StartGroupConversion(0u);

    if ((DetStub_CallCount() == 0u) &&
        (Adc_GetGroupStatus(0u) == ADC_BUSY))
    {
        Test_Result = TEST_PASS;
    }
    else
    {
        Test_Result = TEST_FAIL;
    }
}

/*******************************************************************************
 * TC 2: Invalid group ID
 * Requirement: REQ_ADC_017
 *
 * Description:
 * Checks whether an invalid group ID is detected.
 ******************************************************************************/
void Test_Adc_StartGroupConversion_Tc_002(void)
{
    Test_Reset();

    Adc_StartGroupConversion(5u);

    if ((DetStub_CallCount() == 1u) &&
        (DetStub_LastErrorId() == ADC_E_PARAM_GROUP))
    {
        Test_Result = TEST_PASS;
    }
    else
    {
        Test_Result = TEST_FAIL;
    }
}

/*******************************************************************************
 * TC 3: Result buffer not initialized
 * Requirement: REQ_ADC_018 / SWS_Adc_00061
 *
 * Description:
 * Checks whether the driver detects an uninitialized result buffer.
 *
 * Assumption:
 * Group 0 has no default buffer configured.
 ******************************************************************************/
void Test_Adc_StartGroupConversion_Tc_003(void)
{
    Test_Reset();

    /* Remove the result buffer for group 0. */
    Adc_GroupResultBufferPtr[0] = NULL_PTR;

    DetStub_Reset();

    Adc_StartGroupConversion(0u);

    if ((DetStub_CallCount() == 1u) &&
        (DetStub_LastErrorId() == ADC_E_BUFFER_UNINIT))
    {
        Test_Result = TEST_PASS;
    }
    else
    {
        Test_Result = TEST_FAIL;
    }
}

/*******************************************************************************
 * TC 4: Wrong trigger source
 * Requirement: REQ_ADC_017
 *
 * Description:
 * Checks whether a hardware-triggered group is rejected by the
 * software-trigger API.
 *
 * Requires a separate hardware-triggered ADC configuration.
 ******************************************************************************/
void Test_Adc_StartGroupConversion_Tc_004(void)
{
    /*
     * TODO:
     * 1. Initialize ADC with a hardware-triggered group 0.
     * 2. Reset DET stub.
     * 3. Call Adc_StartGroupConversion(0u).
     * 4. Check ADC_E_WRONG_TRIGG_SRC.
     */
    Test_Result = TEST_NOT_IMPLEMENTED;
}

/*******************************************************************************
 * TC 5: Group already busy
 * Requirement: REQ_ADC_019 / SWS_Adc_00424
 *
 * Description:
 * Checks the behavior when a conversion request is made while the group
 * is already busy.
 *
 * Note:
 * The result depends on the configured queue policy. A second request
 * may be queued instead of reporting an error.
 ******************************************************************************/
void Test_Adc_StartGroupConversion_Tc_005(void)
{
    /*
     * TODO:
     * 1. Initialize ADC and configure a valid result buffer.
     * 2. Start conversion for group 0.
     * 3. Call Adc_StartGroupConversion(0u) again.
     * 4. Verify the behavior against the configured queue policy.
     */
    Test_Result = TEST_NOT_IMPLEMENTED;
}