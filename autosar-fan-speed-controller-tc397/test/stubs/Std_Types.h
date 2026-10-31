/* PC-only stub so the tests can be compiled without the TC397 toolchain.
 * Remove / ignore when the project's real Std_Types.h is on the include path. */
#ifndef STD_TYPES_H
#define STD_TYPES_H
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef uint8 Std_ReturnType;
#define E_OK      ((Std_ReturnType)0x00u)
#define E_NOT_OK  ((Std_ReturnType)0x01u)
#define NULL_PTR  ((void*)0)
#endif
