/*
/--------------------------------------------------------------------
|
|      $Id: bitmap.h,v 1.23 2000/12/18 22:42:52 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_BITMAP
#define INCL_BITMAP

#include "plobject.h"
#include "plpoint.h"
#include "debug.h"
#include "pixel32.h"

//! Device- and OS-independent bitmap class. Manipulates uncompressed
//! bitmaps of all color depths.
//!
//! This class is an abstract base class. It exists to define a
//! format-independent interface for bitmap manipulation and to
//! provide common routines. Derived classes must support at least
//! the color depths 1, 8 and 32 bpp. CBmp defines a public interface
//! for general use and a protected interface for use by derived
//! classes.
//!
//! For 32 bpp, alpha channel information is stored in one byte
//! (RGBA_ALPHA) of each 4-byte pixel. To allow for optimizations
//! when no alpha channel is present, a flag is set whenever the
//! alpha information is valid. The complete alpha channel of a
//! bitmap can be replaced by a different one by calling
//! SetAlphaChannel(). A 0 in an alpha channel entry is completely
//! transparent; a 255 is completely opaque.
class CBmp : public CPLObject
{

public:

  //! Empty constructor. Constructors in derived classes create a
  //! small empty bitmap to ensure that the object is always in a
  //! sane state.
  CBmp
    ();

  //! Empty destructor.
  virtual ~CBmp
    ();

  //! Assignment operator. Note that assignment between different derived
  //! classes is possible and results in a format conversion.
  CBmp &operator=
    ( CBmp const &Orig
    );

  //! Test for equality. This functions actually tests every pixel, so
  //! it's not fast. It's meant mainly for use in asserts and such.
  bool const operator ==
    ( CBmp const &Other
    );

#ifdef _DEBUG
  virtual void AssertValid
    () const;    // Tests internal object state
#endif

  // CBmp creation

  //! Creates a new empty bitmap. Memory for the bits is allocated
  //! but not initialized. Previous contents of the bitmap object are
  //! discarded. If bAlphaChannel is true, the bitmap is assumed to
  //! contain a valid alpha channel.
  virtual void Create
    ( LONG Width,
      LONG Height,
      WORD BitsPerPixel,
      BOOL bAlphaChannel
    );

  //! Creates a copy of rSrcBmp, converting color depth if nessesary.
  //! Supports 1, 8 and 32 BPP. Alpha channel information is preserved.
  void CreateCopy
    ( const CBmp & rSrcBmp,
      int BPPWanted = 0
    );

  //! Creates a copy of rSrcBmp, converting color information to grayscale
  //! in the process. The resulting bitmap is an 8-bit bitmap.
  void CreateGrayscaleCopy
    ( CBmp & rSrcBmp
    );

  //!
  void CreateRotatedCopy
    ( CBmp & rSrcBmp,
      double angle,
      CPixel32 color
    );

  //! Rotates bitmap around Point. Pos is the current upper-left corner of
  //! the bitmap. Returns the new position of the upper-left corner.
  CPLPoint CreateRotatedCopyPoint
    ( CBmp & rSrcBmp,
      double angle,
      CPixel32 color,
      CPLPoint Point,
      CPLPoint Pos
    );

  //! Creates a bitmap containing only the alpha channel of rSrcBmp.
  void CreateFromAlphaChannel
    ( CBmp & rSrcBmp
    );

  //!
  void CreateResizedBilinear
    ( CBmp& rSrcBmp,
      int NewXSize,
      int NewYSize
    );

  //!
  void CreateResizedBox
    ( CBmp& rSrcBmp,
      int NewXSize,
      int NewYSize,
      double NewRadius
    );

  //!
  void CreateResizedGaussian
    ( CBmp& rSrcBmp,
      int NewXSize,
      int NewYSize,
      double NewRadius
    );

  //!
  void CreateResizedHamming
    ( CBmp& rSrcBmp,
      int NewXSize,
      int NewYSize,
      double NewRadius
    );

  //!
  void CreateCropped
    ( CBmp& rSrcBmp,
      int XMin,
      int XMax,
      int YMin,
      int YMax
    );

  // CBmp manipulation

  //! Sets quality of conversion to 8 bpp. Valid parameters are
  //! defined in FilterQuantize.h.
  void SetQuantizationMode
    ( int DitherType,
      int DitherPaletteType
    );

  //! Fills the color table with a grayscale palette. This function
  //! is only useable for bitmaps containing a color table. Index 0
  //! contains black (0) and the last index contains white (255). The
  //! alpha channel is set to opaque (255) for every palette entry.
  void SetGrayPalette
    ();

  //! Sets the color table to pPal. The contents or pPal are copied.
  void SetPalette
    ( CPixel32 * pPal
    );

  //! Sets one entry in the color table. The function may only be
  //! called if there is a color table stored with the bitmap. The
  //! color table entry is set to the red, green, blue, and alpha
  //! values specified.
  void SetPaletteEntry
    ( BYTE Entry,
      BYTE r,
      BYTE g,
      BYTE b,
      BYTE a
    );

  //! Replaces the alpha channel of the bitmap with a new one. This
  //! only works for bitmaps with 32 bpp. pAlphaBmp must point to an
  //! 8 bpp bitmap with the same dimensions as the object. The alpha
  //! channel information is physically copied into the bitmap.
  void SetAlphaChannel
    ( CBmp * pAlphaBmp
    );

  //!
  void ResizeBilinear
    ( int NewXSize,
      int NewYSize
    );

  //!
  void ResizeBox
    ( int NewXSize,
      int NewYSize,
      double NewRadius
    );

  //!
  void ResizeGaussian
    ( int NewXSize,
      int NewYSize,
      double NewRadius
    );

  //!
  void ResizeHamming
    ( int NewXSize,
      int NewYSize,
      double NewRadius
    );

  //!
  void Crop
    ( int XMin,
      int XMax,
      int YMin,
      int YMax
    );

  //!
  void Threshold
		(int threshold_min,
		int threshold_max,
		int channel
		);

  //!
  void MakeGrayscale
    ();

  //!
  void Rotate
    ( double angle,
      CPixel32 color
    );

  //!
  void Invert
    ();

  //! Slow but simple function to set a single pixel. 32 bpp only.
  void SetPixel
    ( int x,
      int y,
      CPixel32 pixel
    );

  //! Slow but simple function to get a single pixel. 32 bpp only.
  CPixel32 GetPixel
    ( int x,
      int y
    );

  //! Find the nearest color to cr in the palette used by this bitmap
  //! Only works for 8 bpp bitmaps.
  BYTE FindNearestColor
    ( CPixel32 cr
    );

  // CBmp information.

  //!
  int GetWidth
    () const;

  //!
  int GetHeight
    () const;

  //!
  virtual long GetMemUsed
    () = 0;

  //!
  int GetNumColors
    ();

  //!
  int GetBitsPerPixel
    () const;

  //!
  BOOL HasAlpha
    () const;

  //!
  void SetHasAlpha
    (BOOL b
    );

  //! Returns number of bytes used per line.
  virtual long GetBytesPerLine
    () = 0;

  // CBmp direct manipulation

  //! Returns the address of the color table of the bitmap or NULL if
  //! no color table exists. The color table is stored as an array of
  //! consecutive CPixel32 objects.
  CPixel32 * GetPalette
    () const;

  //! Returns pointer to an array containing the starting addresses of
  //! the bitmap lines. This array should be used whenever the bitmap
  //! bits need to be manipulated directly.
  BYTE ** GetLineArray
    () const;

  //! Locks bitmap. GetLineArray() and other direct-access methods should
  //! only be called if the bitmap is locked. Lock and Unlock keep a lock
  //! count. In most cases (currently: all but CDDrawBmp), the lock count
  //! will always be >= 1, so access is always possible.
  virtual void Lock
    ( bool bReadable,
      bool bWriteable
    );

  //! Unlocks the Bitmap surface.
  virtual void Unlock
    ();

  bool IsLocked
    () const;

protected:


  //! Create a new bitmap with uninitialized bits. (Assume no memory
  //! is allocated yet.)
  virtual void internalCreate
    ( LONG Width,
      LONG Height,
      WORD BitsPerPixel,
      BOOL bAlphaChannel
    ) = 0;

  //! Delete memory allocated by member variables.
  virtual void freeMembers
    () = 0;

  //! Initialize internal table of line addresses.
  virtual void initLineArray
    () = 0;

  //! Creates a new CBmp as copy of rSrcBmp. Assumes there is no memory
  //! allocated yet.
  void internalCopy 
    ( const CBmp & rSrcBmp
    );

  //! Can be called from internalCreate() to initialize object state.
  void initLocals
    ( LONG Width,
      LONG Height,
      WORD BitsPerPixel,
      BOOL bAlphaChannel
    );

  void create32BPPCopy
    ( const CBmp & rSrcBmp
    );

  void create8BPPCopy
    ( const CBmp & rSrcBmp
    );

  void create1BPPCopy
    ( const CBmp & rSrcBmp
    );

  // Member variables

  int m_Width;
  int m_Height;
  WORD m_bpp;

  CPixel32 * m_pClrTab;      // Pointer to the color table.
  BOOL       m_bAlphaChannel;
  BYTE    ** m_pLineArray;   // Table of the starting addresses of
                             // the lines.
  int        m_LockCount;    // Number of times the bitmap was locked.
                             // Default is m_LockCount always >= 1, so
                             // access to bits is always possible.
  int m_DitherType;
  int m_DitherPaletteType;

};

inline CBmp & CBmp::operator=
    ( CBmp const &Orig
    )
{
  if (this != &Orig)
    CreateCopy(Orig);
  return *this;
}

inline void CBmp::SetPaletteEntry
    ( BYTE Entry,
      BYTE r,
      BYTE g,
      BYTE b,
      BYTE a
    )
{
  m_pClrTab[Entry].Set (r, g, b, a);
}


// CBmp information

inline int CBmp::GetWidth
    () const
{
  PLASSERT_VALID (this);

  return m_Width;

}


inline int CBmp::GetHeight
    () const
{
  PLASSERT_VALID (this);

  return m_Height;
}


inline int CBmp::GetNumColors
    ()
{
  PLASSERT_VALID (this);

  if (m_bpp == 32)
    return 1 << 24;
   else
    return 1 << m_bpp;
}


inline int CBmp::GetBitsPerPixel
    () const
{
  PLASSERT_VALID (this);

  return m_bpp;
}


inline BOOL CBmp::HasAlpha
    () const
{
  PLASSERT_VALID (this);

  return m_bAlphaChannel;
}


inline void CBmp::SetHasAlpha
    (BOOL b
    )
{
  PLASSERT_VALID (this);
  m_bAlphaChannel = b;
}

// CBmp direct manipulation


inline BYTE ** CBmp::GetLineArray
    () const
{
  PLASSERT (m_pLineArray);
  return m_pLineArray;
}


inline CPixel32 * CBmp::GetPalette
    () const
    // Returns adress of the color table of the bitmap or NULL if no
    // color table exists.
{
  PLASSERT_VALID (this);

  return m_pClrTab;
}

inline bool CBmp::IsLocked
    () const
{
  return (m_LockCount >= 1);
}


#endif
/*
/--------------------------------------------------------------------
|
|      $Log: bitmap.h,v $
|      Revision 1.23  2000/12/18 22:42:52  uzadow
|      Replaced RGBAPIXEL with CPixel32.
|
|      Revision 1.22  2000/11/21 20:18:03  uzadow
|      Added operator ==
|
|      Revision 1.21  2000/11/07 15:40:46  jmbuena
|      Changes related to paintlibdefs.h and pixeldefs.h
|
|      Revision 1.20  2000/11/02 21:28:47  uzadow
|      Fixed copy constructors.
|
|      Revision 1.19  2000/10/24 16:46:34  uzadow
|      Fixed build problems
|
|      Revision 1.18  2000/10/23 17:45:03  jmbuena
|      Linux compatibility changes
|
|      Revision 1.17  2000/09/26 14:28:47  Administrator
|      Added Threshold filter
|
|      Revision 1.16  2000/09/26 12:14:51  Administrator
|      Refactored quantization.
|
|      Revision 1.15  2000/08/13 12:11:43  Administrator
|      Added experimental DirectDraw-Support
|
|      Revision 1.14  2000/07/11 17:11:00  Ulrich von Zadow
|      Added support for RGBA pixel ordering (Jose Miguel Buenaposada Biencinto).
|
|      Revision 1.13  2000/03/31 12:20:05  Ulrich von Zadow
|      Video invert filter (beta)
|
|      Revision 1.12  2000/03/31 11:53:30  Ulrich von Zadow
|      Added quantization support.
|
|      Revision 1.11  2000/01/16 20:43:12  anonymous
|      Removed MFC dependencies
|
|      Revision 1.10  1999/12/10 01:27:26  Ulrich von Zadow
|      Added assignment operator and copy constructor to
|      bitmap classes.
|
|      Revision 1.9  1999/12/09 16:35:22  Ulrich von Zadow
|      no message
|
|      Revision 1.8  1999/12/08 15:39:45  Ulrich von Zadow
|      Unix compatibility changes
|
|      Revision 1.7  1999/12/02 17:07:34  Ulrich von Zadow
|      Changes by bdelmee.
|
|      Revision 1.6  1999/10/22 21:25:51  Ulrich von Zadow
|      Removed buggy octree quantization
|
\--------------------------------------------------------------------
*/
