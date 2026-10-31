# AUTOSAR-Compliant Electronic Fan Speed Controller (Infineon AURIX TC397)

AUTOSAR Classic Platform project: a potentiometer-controlled fan built around an **EV-ADC MCAL driver**,
**IoHwAb** signal abstraction and **ISO 26262 ASIL B** measures, targeting the **Infineon AURIX TC397**.
Developed within the KLE Technological University x Infineon mentorship programme.

## Signal chain
```
Potentiometer (3 ch) -> EV-ADC (MCAL) -> IoHwAb (0-4095 -> 0-5 V) -> Fan speed SWC -> PWM (MCAL) -> Fan
```

## Repository layout
```
docs/            requirements (team matrix + Adc_Init analysis), architecture, design, notes
src/             development team: asw, iohwab, mcal/{adc,pwm,mcu,port,interrupt}, scheduling, startup, config
test/            validation team: unit/, integration/, stubs/ (Std_Types, Det), host_demo/ (PC demo with a mock driver)
traceability/    requirement -> classification -> test
```

## Validation approach
1. Requirements are read from the AUTOSAR specs and classified by **scope, implementability and testability**
   (`docs/requirements/Adc_Init_Requirements.xlsx`).
2. Each testable requirement gets a test case tagged with its AUTOSAR ID (`test/unit/adc/Test_Adc_Init.c`).
3. Requirements that are ownership rules or configuration values are checked by review (RV_xx in the matrix).
4. Everything is tracked in `traceability/Traceability_Matrix.md`.

## Try the tests on a PC (mock driver, not the real one)
See `test/host_demo/README.md`.

## Team
| Member | Role | Contribution |
|---|---|---|
| Ankush S Jalasandi | Validation | Adc_Init requirement analysis, repository structure, Adc_Init test cases |
| (add teammates) | | |

*AUTOSAR specification PDFs are copyrighted and are not included in this repository.*
