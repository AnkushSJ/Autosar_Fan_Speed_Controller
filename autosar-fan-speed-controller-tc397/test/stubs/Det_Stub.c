#include "Det_Stub.h"
static uint32 s_count; static uint16 s_mod; static uint8 s_api; static uint8 s_err;
Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{ (void)InstanceId; s_count++; s_mod = ModuleId; s_api = ApiId; s_err = ErrorId; return E_OK; }
void   DetStub_Reset(void)        { s_count = 0u; s_mod = 0u; s_api = 0u; s_err = 0u; }
uint32 DetStub_CallCount(void)    { return s_count; }
uint16 DetStub_LastModuleId(void) { return s_mod; }
uint8  DetStub_LastApiId(void)    { return s_api; }
uint8  DetStub_LastErrorId(void)  { return s_err; }
