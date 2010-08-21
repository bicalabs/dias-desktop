/*
/--------------------------------------------------------------------
|
|      $Id: pgmdec.h,v 1.4 2000/12/18 22:42:52 uzadow Exp $
|
|      portable graymap Decoder Class
|
|      Original author: Jose Miguel Buenaposada Biencinto.
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PGMDEC
#define INCL_PGMDEC

#ifndef INCL_PICDEC
#include "picdec.h"
#endif

#ifndef INCL_PGM
#include "pgm.h"
#endif

//! Portable Graymap file decoder. Delivers an 8 bpp grayscale image.
class CPGMDecoder : public CPicDecoder
{

public:
  //! Creates a decoder
  CPGMDecoder
    ();

  //! Destroys a decoder
  virtual ~CPGMDecoder
    ();

protected:
  //! Main decoder routine. Reads the header, Creates the bitmap,
  //! reads the palette, and reads the image data.
  virtual void DoDecode
    ( CBmp * pBmp,
      CPixel32 ** ppPal,
      int * pDestBPP,
      CDataSource * pDataSrc
    );

private:

  BYTE m_LastByte;
  bool m_UseLastByte;

  void readPgmHeader (PGMHEADER *pPgmHead,
	  CDataSource * pDataSrc);

  int  readASCIIDecimal(CDataSource * pDataSrc);

  void skipComment(CDataSource * pDataSrc);

  void skipPgmASCIISeparators(CDataSource * pDataSrc);

  BYTE *readASCIILine(CDataSource *pDataSrc);

  void setGrayPalette(CPixel32 ** ppPal);

  void readImage (PGMHEADER * pPgmHead,
                  CBmp * pBmp,
                  CPixel32 ** ppPal,
                  int DestBPP,
                  CDataSource * pDataSrc);

  void readData(PGMHEADER * pPgmHead,
                CBmp * pBmp,
                CPixel32 * pPal,
                int DestBPP,
                CDataSource * pDataSrc);

  void expandASCIILine
    ( BYTE * pDest,
      int MaxGrayValue,
      int Width,
      int bpp,
      CDataSource * pDataSrc,
      CPixel32 * pPal,
      int DestBPP);

  void expandByteLine
    ( BYTE * pDest,
	    int MaxGrayValue,
	    int Width,
      int bpp,
      CDataSource * pDataSrc,
      CPixel32 * pPal,
      int DestBPP
    );


  CPixel32 CPGMDecoder::readASCIIPixel32
    ( int MaxGrayValue,
      int bpp,
      CDataSource * pDataSrc,
      CPixel32 * pPal
    );

  BYTE CPGMDecoder::readASCIIPixel8
    ( int MaxGrayValue,
      int bpp,
      CDataSource * pDataSrc
    );
};

#endif
/*
/--------------------------------------------------------------------
|
|      $Log: pgmdec.h,v $
|      Revision 1.4  2000/12/18 22:42:52  uzadow
|      Replaced RGBAPIXEL with CPixel32.
|
|      Revision 1.3  2000/05/23 10:19:11  Ulrich von Zadow
|      Minor unix compatibility changes.
|
|      Revision 1.2  2000/03/21 10:51:16  Ulrich von Zadow
|      Documentation update.
|
|      Revision 1.1  2000/03/16 13:56:37  Ulrich von Zadow
|      Added pgm decoder by Jose Miguel Buenaposada Biencinto
|
|
\--------------------------------------------------------------------
*/
