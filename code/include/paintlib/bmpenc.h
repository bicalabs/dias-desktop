/*
/--------------------------------------------------------------------
|
|      Windows bitmap file encoder. Encodes 1, 4, 8, 24 and 32 bpp
|      bitmaps to a 1, 4, 8 or 24 bpp uncompressed BMP file
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_BMPENC
#define INCL_BMPENC

#ifndef INCL_PICENC
#include "picenc.h"
#endif

class CBmpEncoder : public CPicEncoder
{

public:
  //! Creates an encoder
  CBmpEncoder
    ();

  //! Destroys a encoder
  ~CBmpEncoder
    ();

  // todo: Notification not yet implemented for encoding - ms 3.6.99
  /*
  static void JNotification
    (j_common_ptr cinfo
    );
  */

protected:
  // encodes in bmp format
  void DoEncode
    ( CBmp * pBmp,
      CDataSink * pDataSink
    );

  int GetLineMemNeeded(LONG width, WORD BitsPerPixel);
};

#endif

/*
/--------------------------------------------------------------------
|
|      $Log: bmpenc.h,v $
|      Revision 1.4  2000/12/08 12:32:00  uzadow
|      Added gif decoder by Michael Salzlechner.
|
|      Revision 1.3  2000/12/02 19:50:01  uzadow
|      Added Logging.
|
\--------------------------------------------------------------------
*/
