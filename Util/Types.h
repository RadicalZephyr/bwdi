#pragma once

typedef unsigned char      u8;
typedef signed char        s8;
typedef unsigned short     u16;
typedef signed short       s16;
typedef signed int         s32;
typedef unsigned long      u32;
typedef unsigned long long u64;
typedef unsigned int       uint;

typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned long       DWORD;
typedef u64                 QWORD;
typedef u8                  _UNKNOWN;

typedef u8  bool8;
typedef u16 bool16;
typedef u32 bool32;
typedef u64 bool64;

#ifdef NULL
#undef NULL
#endif
#define NULL 0
