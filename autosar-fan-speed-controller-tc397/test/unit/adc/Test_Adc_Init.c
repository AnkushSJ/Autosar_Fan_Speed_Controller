/*******************************************************************************
 * File     : Test_Adc_Init.c
 * Module   : ADC driver (AUTOSAR CP R22-11, Infineon AURIX TC397)
 * Function : Adc_Init()  - SWS_ADCDriver section 8.3.1, service ID 0x00
 * Author   : Ankush S Jalasandi (Validation team)
 *
 * Result convention (Test_Result):
 *     1    -> PASS
 *     0    -> FAIL
 *     0xFF -> not implemented yet (needs register mock / ISR simulation)
 ******************************************************************************/
#include "Adc.h"
#include "Adc_Cfg.h"
#include "Det_Stub.h"

#define TEST_PASS             (1u)
#define TEST_FAIL             (0u)
#define TEST_NOT_IMPLEMENTED  (0xFFu)

#define ADC_INIT_API_ID       (0x00u)   /* service ID of Adc_Init                         */
#define ADC_ERR_UNINIT        (0x0Au)   /* ADC_E_UNINIT              (error table p.42)   */
#define ADC_ERR_ALREADY_INIT  (0x0Du)   /* ADC_E_ALREADY_INITIALIZED (error table p.42)   */

static uint8 Test_Result;

extern const Adc_ConfigType adcConfig;

/* Brings the driver back to "not initialised" so every test starts clean */
static void Test_Reset(void)
{
    Adc_DeInit();
    DetStub_Reset();
}

/* Lets a test runner read the result of the last test case */
uint8 Test_Adc_Init_GetResult(void)
{
    return Test_Result;
}

/*******************************************************************************
 * TC 1: All groups are IDLE after initialisation
 * Requirement Spec: SWS_Adc_00307   (REQ_ADC_013)
 * Description: Adc_Init shall set all groups to ADC_IDLE.
 ******************************************************************************/
void Test_Adc_Init_Tc_001(void)
{
    Test_Reset();

    Adc_Init(&adcConfig);

    if (Adc_GetGroupStatus(0) == ADC_IDLE)
    {
        Test_Result = TEST_PASS;
    }
    else
    {
        Test_Result = TEST_FAIL;
    }
}

/*******************************************************************************
 * TC 2: Second Adc_Init call raises ADC_E_ALREADY_INITIALIZED
 * Requirement Spec: SWS_Adc_00107 (REQ_ADC_014), SWS_BSW_00231
 * Description: With DET enabled, calling Adc_Init on an initialised driver
 *              shall report error 0x0D for service 0x00 and do nothing else.
 ******************************************************************************/
void Test_Adc_Init_Tc_002(void)
{
    Test_Reset();

    Adc_Init(&adcConfig);
    DetStub_Reset();                    /* ignore anything from the first call */
    Adc_Init(&adcConfig);               /* second call */

    if ((DetStub_CallCount()    == 1u) &&
        (DetStub_LastModuleId() == ADC_MODULE_ID) &&
        (DetStub_LastApiId()    == ADC_INIT_API_ID) &&
        (DetStub_LastErrorId()  == ADC_ERR_ALREADY_INIT) &&
        (Adc_GetGroupStatus(0)  == ADC_IDLE))
    {
        Test_Result = TEST_PASS;
    }
    else
    {
        Test_Result = TEST_FAIL;
    }
}

/*******************************************************************************
 * TC 3: Notifications and hardware trigger are disabled after Adc_Init
 * Requirement Spec: SWS_Adc_00077
 * Description: Needs an ISR simulation and a notification-callback counter.
 ******************************************************************************/
void Test_Adc_Init_Tc_003(void)
{
    /* TODO: 1. configure a group with notification + hardware trigger
     *       2. Adc_Init(&adcConfig)
     *       3. simulate end of conversion (call the ADC ISR)
     *       4. expected: callback counter == 0, hardware trigger inactive */
    Test_Result = TEST_NOT_IMPLEMENTED;
}

/*******************************************************************************
 * TC 4: Only configured resources are initialised
 * Requirement Spec: SWS_Adc_00056   (REQ_ADC_003)
 * Description: Needs a register mock to snapshot an unconfigured ADC unit.
 ******************************************************************************/
void Test_Adc_Init_Tc_004(void)
{
    /* TODO: 1. snapshot registers of a unit that is not in adcConfig
     *       2. Adc_Init(&adcConfig)
     *       3. snapshot again; expected: both snapshots identical */
    Test_Result = TEST_NOT_IMPLEMENTED;
}

/*******************************************************************************
 * TC 5: Configuration is applied to the hardware
 * Requirement Spec: SWS_Adc_00054   (REQ_ADC_002)
 * Description: Needs the register values from the TC397 User Manual.
 ******************************************************************************/
void Test_Adc_Init_Tc_005(void)
{
    /* TODO: 1. Adc_Init(&adcConfig)
     *       2. read every configured register (mock or target)
     *       3. expected: each register equals the value in adcConfig */
    Test_Result = TEST_NOT_IMPLEMENTED;
}

/*******************************************************************************
 * TC 6: NULL configuration pointer is rejected
 * Requirement Spec: SWS_BSW_00050 (BSW General, init parameter check)
 * Description: Post-build variant with DET on: Adc_Init(NULL_PTR) shall be
 *              reported and the driver shall stay uninitialised.
 ******************************************************************************/
void Test_Adc_Init_Tc_006(void)
{
    Test_Reset();

    Adc_Init(NULL_PTR);

    if (DetStub_CallCount() == 1u)
    {
        DetStub_Reset();
        (void)Adc_GetGroupStatus(0);    /* still uninitialised -> must report ADC_E_UNINIT */

        if (DetStub_LastErrorId() == ADC_ERR_UNINIT)
        {
            Test_Result = TEST_PASS;
        }
        else
        {
            Test_Result = TEST_FAIL;
        }
    }
    else
    {
        Test_Result = TEST_FAIL;
    }
}

/*******************************************************************************
 * TC 7: Module state is "initialised" after Adc_Init
 * Requirement Spec: SWS_BSW_00071
 * Description: After Adc_Init other APIs must not report ADC_E_UNINIT.
 ******************************************************************************/
void Test_Adc_Init_Tc_007(void)
{
    Test_Reset();

    Adc_Init(&adcConfig);
    DetStub_Reset();
    (void)Adc_GetGroupStatus(0);

    if (DetStub_CallCount() == 0u)
    {
        Test_Result = TEST_PASS;
    }
    else
    {
        Test_Result = TEST_FAIL;
    }
}

/*******************************************************************************
 * TC 8: API called before Adc_Init reports ADC_E_UNINIT
 * Requirement Spec: SWS_Adc_00301, SWS_BSW_00230
 * Description: Adc_GetGroupStatus before Adc_Init shall raise error 0x0A and
 *              return ADC_IDLE (shows the state BEFORE initialisation).
 ******************************************************************************/
void Test_Adc_Init_Tc_008(void)
{
    Adc_StatusType status;

    Test_Reset();

    status = Adc_GetGroupStatus(0);

    if ((DetStub_CallCount()   == 1u) &&
        (DetStub_LastErrorId() == ADC_ERR_UNINIT) &&
        (status                == ADC_IDLE))
    {
        Test_Result = TEST_PASS;
    }
    else
    {
        Test_Result = TEST_FAIL;
    }
}
