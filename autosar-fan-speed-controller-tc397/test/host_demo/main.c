/* Demo runner: calls each test case and prints the result. */
#include <stdio.h>
#include "Std_Types.h"
extern void  Test_Adc_Init_Tc_001(void);  extern void Test_Adc_Init_Tc_002(void);
extern void  Test_Adc_Init_Tc_003(void);  extern void Test_Adc_Init_Tc_004(void);
extern void  Test_Adc_Init_Tc_005(void);  extern void Test_Adc_Init_Tc_006(void);
extern void  Test_Adc_Init_Tc_007(void);  extern void Test_Adc_Init_Tc_008(void);
extern uint8 Test_Adc_Init_GetResult(void);
static void Run(const char* name, void (*tc)(void))
{
    uint8 r; tc(); r = Test_Adc_Init_GetResult();
    printf("%-22s %s\n", name, (r == 1u) ? "PASS" : (r == 0xFFu) ? "NOT IMPLEMENTED (skeleton)" : "FAIL");
}
int main(void)
{
    Run("Test_Adc_Init_Tc_001", Test_Adc_Init_Tc_001); Run("Test_Adc_Init_Tc_002", Test_Adc_Init_Tc_002);
    Run("Test_Adc_Init_Tc_003", Test_Adc_Init_Tc_003); Run("Test_Adc_Init_Tc_004", Test_Adc_Init_Tc_004);
    Run("Test_Adc_Init_Tc_005", Test_Adc_Init_Tc_005); Run("Test_Adc_Init_Tc_006", Test_Adc_Init_Tc_006);
    Run("Test_Adc_Init_Tc_007", Test_Adc_Init_Tc_007); Run("Test_Adc_Init_Tc_008", Test_Adc_Init_Tc_008);
    return 0;
}
