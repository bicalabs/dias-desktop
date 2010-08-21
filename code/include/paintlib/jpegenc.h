/*
/--------------------------------------------------------------------
|
|      $Id: jpegenc.h,v 1.5 2000/05/22 17:43:25 Ulrich von Zadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_JPEGENC
#define INCL_JPEGENC

#ifndef INCL_PICENC
#include "picenc.h"
#endif

struct jpeg_compress_struct;
struct jpeg_error_mgr;

//! JPEG file encoder. Uses the independent JPEG group's library
//! to do the actual conversion.
class CJPEGEncoder : public CPicEncoder
{

public:
  //! Creates an encoder
  CJPEGEncoder
    ();

  //! Destroys a encoder
  ~CJPEGEncoder
    ();

  // todo: Notification not yet implemented for encoding - ms 3.6.99
  /*
  static void JNotification
    (j_common_ptr cinfo
    );
  */

  //! Set the compression quality on a scale from 0 to 100.
  void SetQuality(int iQuality);
  //! Enable or disable the generation of optimal Huffmann coding tables.
  void SetOptimizeCoding(bool bOptimizeCoding);
  //! Set the smoothing factor (<=100). 0 turns it off.
  void SetSmoothingFactor(int iSmoothingFactor);
  //! Set the resolution information (DPI) for the image.
  void SetDensity(unsigned int uiX, unsigned int uiY);

protected:
  // Sets up the jpeg library data source and error handler and
  // calls the jpeg encoder.
  void DoEncode
    ( CBmp * pBmp,
      CDataSink * pDataSink
    );

private:
  jpeg_compress_struct * m_pcinfo;  // IJPEG encoder state.
  jpeg_error_mgr       * m_pjerr;   // Custom error manager.

  int iQuality_;
  bool bOptimizeCoding_;
  int iSmoothingFactor_;
  unsigned int uiDensityX_;
  unsigned int uiDensityY_;

  // Assumes IJPEG decoder is already set up.
  void encodeRGB
    ( CBmp * pBmp,
      int iScanLines
    );

};

#endif

/*
/--------------------------------------------------------------------
|
|      $Log: jpegenc.h,v $
|      Revision 1.5  2000/05/22 17:43:25  Ulrich von Zadow
|      Added SetQuality(), SetDensity(), SetOptimizeCoding() and
|      SetSmoothingFactor().
|
|      Revision 1.4  2000/01/16 20:43:13  anonymous
|      Removed MFC dependencies
|
|      Revision 1.3  1999/12/08 15:39:45  Ulrich von Zadow
|      Unix compatibility changes
|
|      Revision 1.2  1999/11/27 18:45:48  Ulrich von Zadow
|      Added/Updated doc comments.
|
|      Revision 1.1  1999/10/19 21:28:05  Ulrich von Zadow
|      Added jpeg encoder
|
|
\--------------------------------------------------------------------
*/
