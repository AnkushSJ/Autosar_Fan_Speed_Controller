# Traceability Matrix: Requirement -> Classification -> Test

Source: `docs/requirements/Adc_Init_Requirements.xlsx`. ADC spec: AUTOSAR CP R22-11; BSW General: R25-11.
Test IDs: `TC_ADC_INIT_xxx` = function `Test_Adc_Init_Tc_xxx` in `test/unit/adc/Test_Adc_Init.c`; `RV_xx` = review check.

| Req ID | AUTOSAR ID | Type | Scope | Implementability | Testability | Test / Review ID |
|---|---|---|---|---|---|---|
| REQ_ADC_001 | SWS_Adc_00365 | API definition | In | Code | Review/Inspection | RV_01 |
| REQ_ADC_002 | SWS_Adc_00054 | Functional behaviour | In | Code | Unit test | TC_ADC_INIT_005 |
| REQ_ADC_003 | SWS_Adc_00056 | Functional behaviour | In | Code | Unit test | TC_ADC_INIT_004 |
| REQ_ADC_004 | SWS_Adc_00246 | Design rule | In | Code | Review/Inspection | RV_02 |
| REQ_ADC_005 | SWS_Adc_00247 | Design rule | In | Other module/startup | Review/Inspection | RV_03 |
| REQ_ADC_006 | SWS_Adc_00248 | Design rule | In | Other module/startup | Review/Inspection | RV_04 |
| REQ_ADC_007 | SWS_Adc_00249 | Design rule | In | Other module/startup | Review/Inspection | RV_05 |
| REQ_ADC_008 | SWS_Adc_00250 | Design rule | In | Other module/startup | Review/Inspection | RV_05 |
| NEW_01 | SWS_Adc_00077 | Functional behaviour | In | Code | Unit test | TC_ADC_INIT_003 |
| REQ_ADC_013 | SWS_Adc_00307 | Functional behaviour | In | Code | Unit test | TC_ADC_INIT_001 |
| REQ_ADC_014 | SWS_Adc_00107 | Error / DET | In | Code | Unit test | TC_ADC_INIT_002 |
| REQ_ADC_009 | ECUC_Adc_00242 | Configuration parameter | In | Config only | Review/Inspection | RV_06 |
| REQ_ADC_010 | ECUC_Adc_00087 | Configuration parameter | In | Config only | Review/Inspection | RV_07 |
| REQ_ADC_011 | ECUC_Adc_00088 | Configuration parameter | In | Config only | Review/Inspection | RV_07 |
| REQ_ADC_012 | SWS_Adc_00138 | Functional behaviour | Partial | Config only | Review/Inspection | RV_06 |
| REQ_ADC_041 | ECUC_Adc_00019 | Configuration parameter | In | Config only | Review/Inspection | RV_08 |
| REQ_ADC_042 | ECUC_Adc_00290 | Configuration parameter | In | Config only | Review/Inspection | RV_08 |
| REQ_ADC_039 | SWS_Adc_00122 | Functional behaviour | In | Code | Unit test | Not mine (Adc_ReadGroup) |
| REQ_ADC_045 | SWS_Adc_00060 | Functional behaviour | In | Code | Integration test | TC_ADC_INT_001 (later) |
| REQ_ADC_060 | SWS_Adc_91005 | Error / DET | In | Code | Review/Inspection | RV_09 |
| - | SWS_Adc_00505 | Data type | In | Code | Review/Inspection | RV_10 |
| - | SWS_Adc_00413 | Design rule | In | Code | Review/Inspection | RV_11 |
| - | SWS_Adc_00228 | Configuration parameter | Partial | Config only | Review/Inspection | RV_12 |
| - | SWS_Adc_00483 | Design rule | Out | Code | Review/Inspection | None (out of scope) |
| - | SWS_Adc_00434, 00294-00302, 00154 | Error / DET | In | Code | Unit test | TC_ADC_INIT_008 |
| - | Fig 9.1 / Fig 7.4 | Informative | In | Info only | Not testable | None (background) |
| - | SWS_BSW_00150 | Assumption on caller | In | Not on driver (caller/env) | Review/Inspection | RV_13 |
| - | SWS_BSW_00050 | Error / DET | In | Code | Unit test | TC_ADC_INIT_006 |
| - | SWS_BSW_00071 | Functional behaviour | In | Code | Unit test | TC_ADC_INIT_007 |
| - | SWS_BSW_00230 | Assumption on caller | In | Not on driver (caller/env) | Integration test | TC_ADC_INIT_008 |
| - | SWS_BSW_00231 | Assumption on caller | In | Not on driver (caller/env) | Unit test | TC_ADC_INIT_002 |
| - | SWS_BSW_00188 | Design rule | Partial | Config only | Review/Inspection | RV_14 |
