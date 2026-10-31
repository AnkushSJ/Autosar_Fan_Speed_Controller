/* Fake Default Error Tracer: records what the driver reports so a test can check it. */
#ifndef DET_STUB_H
#define DET_STUB_H
#include "Std_Types.h"
Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);
void   DetStub_Reset(void);
uint32 DetStub_CallCount(void);
uint16 DetStub_LastModuleId(void);
uint8  DetStub_LastApiId(void);
uint8  DetStub_LastErrorId(void);
#endif
