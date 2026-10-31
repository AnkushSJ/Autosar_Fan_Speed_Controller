# Host demo (PC only)

`mock/` contains a tiny FAKE Adc driver so the Adc_Init tests can be shown running on a PC.
It is NOT the developers' driver and says nothing about the real code. Use it only to demonstrate
how the tests, the Det stub and the pass/fail convention work. With the real driver, replace
`mock/Adc.c`, `mock/Adc.h`, `mock/Adc_Cfg.h` by `src/mcal/adc/*`.

Build and run (needs gcc, e.g. MinGW / MSYS2 on Windows), from the repository root:

    gcc -Wall -Wextra -Itest/host_demo/mock -Itest/stubs test/unit/adc/Test_Adc_Init.c test/stubs/Det_Stub.c test/host_demo/mock/Adc.c test/host_demo/main.c -o demo
    ./demo
