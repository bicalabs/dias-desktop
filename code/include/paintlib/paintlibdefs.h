/*
/--------------------------------------------------------------------
|
|      $Id: paintlibdefs.h,v 1.2 2000/11/09 22:23:36 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

//! Windows Bitmap Struct Definitions
//!
//! Contains the windows defines for non windows compilations.
//!

#ifndef INCL_PAINTLIBDEFS
#define INCL_PAINTLIBDEFS

#ifndef _WINDOWS
#include <stdarg.h>

// max & min definitions
#include <algorithm> // STL

typedef void                VOID;
typedef int                 BOOL;
typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned char       BYTE;
typedef BYTE *              LPBYTE;
typedef unsigned char       UCHAR;
typedef unsigned short      WORD;         // This is 16 bit.
typedef unsigned long       DWORD;        // This is 32 bit.
typedef long                LONG;         // This is 32 bit.
typedef unsigned long       ULONG;

typedef int (*FARPROC)();

#ifndef FAR
#define FAR
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifndef TRUE
#define TRUE    1
#endif

#ifndef NULL
#define NULL    0
#endif

#define HIBYTE(w)   ((BYTE) (((WORD) (w) >> 8) & 0xFF))
#endif //#ifndef _WINDOWS

//
// Include the pixel related definitions
//
#include "pixeldefs.h"

#endif
/*
/--------------------------------------------------------------------
|
|      $Log: paintlibdefs.h,v $
|      Revision 1.2  2000/11/09 22:23:36  uzadow
|      no message
|
|      Revision 1.1  2000/11/07 15:33:44  jmbuena
|      Windows type defines for non windows systems
|
|
\--------------------------------------------------------------------
*/
