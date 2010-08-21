/*
/--------------------------------------------------------------------
|
|      $id$
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_BMPDEC
#define INCL_BMPDEC

#ifndef INCL_PICDEC
#include "picdec.h"
#endif

#ifndef INCL_WINDEFS
#include "windefs.h"
#endif

//! Windows bitmap file decoder. Decodes bitmap files (compressed and
//! uncompressed) of all bit depths. Returns an 8
//! or 32 bpp bitmap.
class CBmpDecoder : public CPicDecoder
{

public:
  //! Creates a decoder
  CBmpDecoder
    ();

  //! Destroys a decoder
  virtual ~CBmpDecoder
    ();

protected:
  //! Does the actual decoding of bitmap data.
  virtual void DoDecode
    ( CBmp * pBmp,
      CPixel32 ** ppPal,
      int * pDestBPP,
      CDataSource * pDataSrc
    );

private:

  // Decodes the bitmap file & info headers
  WINBITMAPINFOHEADER * getInfoHeader
    ( CDataSource * pDataSrc,
      CPixel32 ** ppPal
    );

  // Decodes a 2-color bitmap. Ignores the palette & just uses
  // black & white as 'colors'
  void decode1bpp
    ( CDataSource * pDataSrc,
      CBmp * pBmp,
      int DestBPP
    );

  // Decodes an uncompressed 16-color-bitmap.
  void decode4bpp
    ( CDataSource * pDataSrc,
      CBmp * pBmp,
      CPixel32 * pPal,
      int DestBPP
    );

  // Decodes an uncompressed 256-color-bitmap.
  void decode8bpp
    ( CDataSource * pDataSrc,
      CBmp * pBmp,
      CPixel32 * pPal,
      int DestBPP
    );

  // Decodes a compressed 16-color-bitmap.
  void decodeRLE4
    ( CDataSource * pDataSrc,
      CBmp * pBmp,
      CPixel32 * pPal,
      int DestBPP
    );

  // Decodes a compressed 256-color-bitmap.
  void decodeRLE8
    ( CDataSource * pDataSrc,
      CBmp * pBmp,
      CPixel32 * pPal,
      int DestBPP
    );

  void decodeHiColor
    ( CDataSource * pDataSrc,
      CBmp * pBmp,
      WINBITMAPINFOHEADER * pBMI
    );

  // Decodes true-color bitmap
  void decodeTrueColor
    ( CDataSource * pDataSrc,
      CBmp * pBmp,
      int SrcBPP
    );

  void decode15bppLine
    ( CDataSource * pDataSrc,
      CBmp * pBmp,
      BYTE * pDest
    );

  void decode16bppLine
    ( CDataSource * pDataSrc,
      CBmp * pBmp,
      BYTE * pDest
    );

  void decode24bppLine
    ( CDataSource * pDataSrc,
      CBmp * pBmp,
      BYTE * pDest
    );

  void decode32bppLine
    ( CDataSource * pDataSrc,
      CBmp * pBmp,
      BYTE * pDest
    );


  // Decodes two 4-bit pixels using a palette & puts them in pDest
  // and pDest+4.
  void decode2Nibbles
    ( BYTE * pDest,
      BYTE SrcByte,
      CPixel32 * pPal,
      int DestBPP
    );

  // Makes a private copy of the palette in the file and sets the
  // alpha channel. Returns the size of the palette in bytes.
  int readPalette
    ( WINBITMAPINFOHEADER * pBMI,     // Pointer to bitmapinfoheader in file.
      CDataSource * pDataSrc,
      CPixel32 ** ppPal
    );

};

#endif
/*
/--------------------------------------------------------------------
|
|      $log$
|
--------------------------------------------------------------------
*/
