/*
/--------------------------------------------------------------------
|
|      $Id: gifdec.h,v 1.2 2000/12/18 22:42:52 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_GIFDEC
#define INCL_GIFDEC

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "picdec.h"

class CGIFDecoder : public CPicDecoder  
{
public:
  void DoDecode (CBmp * pBmp, CPixel32 ** ppPal, int * pDestBPP, CDataSource * pDataSrc);
  CGIFDecoder();
  virtual ~CGIFDecoder();

};

#endif 

/*
/--------------------------------------------------------------------
|
|      $Log: gifdec.h,v $
|      Revision 1.2  2000/12/18 22:42:52  uzadow
|      Replaced RGBAPIXEL with CPixel32.
|
|      Revision 1.1  2000/12/08 13:41:23  uzadow
|      Added gif support by Michael Salzlechner.
|
|
\--------------------------------------------------------------------
*/
