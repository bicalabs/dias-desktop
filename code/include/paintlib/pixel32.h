/*
/--------------------------------------------------------------------
|
|      $Id: pixel32.h,v 1.1 2000/12/18 22:42:52 uzadow Exp $
|      
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PIXEL
#define INCL_PIXEL

#include "pixeldefs.h"

//! 32 bit pixel class. A pixel in this class contains 8 bits each of 
//! red, green, blue and alpha. The order of the color components is 
//! OS-dependent and defined in config.h. This class is meant to be 
//! fast, so all methods are inlined.
class CPixel32
{
	public:
    //!
		CPixel32 ();
    //!
		CPixel32 (BYTE r, BYTE g, BYTE b, BYTE a);
    //!
		void Set (BYTE r, BYTE g, BYTE b, BYTE a);
    //!
		void SetR (BYTE R);
    //!
		void SetG (BYTE g);
    //!
		void SetB (BYTE b);
    //!
		void SetA (BYTE a);
    //!
		BYTE GetR ();
    //!
		BYTE GetG ();
    //!
		BYTE GetB ();
    //!
		BYTE GetA ();

    //!
    bool operator ==(const CPixel32&);

    //!
    bool operator !=(const CPixel32&);

    //! Simple and fast 'distance' between two pixels. Just adds the
    //! distances between the color components and treats colors
    //! equally.
    int BoxDist (CPixel32 Pix);

	private:
		BYTE m_Data[4];  
};

inline CPixel32::CPixel32()
{
}


inline CPixel32::CPixel32(BYTE r, BYTE g, BYTE b, BYTE a)
{
  Set (r, b, g, a);
}


inline void CPixel32::Set(BYTE r, BYTE g, BYTE b, BYTE a)
{
  m_Data[RGBA_RED] = r;
  m_Data[RGBA_GREEN] = g;
  m_Data[RGBA_BLUE] = b;
  m_Data[RGBA_ALPHA] = a;
}


inline void CPixel32::SetR(BYTE r)
{
  m_Data[RGBA_RED] = r;
}


inline void CPixel32::SetG(BYTE g)
{
  m_Data[RGBA_GREEN] = g;
}


inline void CPixel32::SetB(BYTE b)
{
  m_Data[RGBA_BLUE] = b;
}


inline void CPixel32::SetA(BYTE a)
{
  m_Data[RGBA_ALPHA] = a;
}


inline BYTE CPixel32::GetR()
{
  return m_Data[RGBA_RED];
}


inline BYTE CPixel32::GetG()
{
  return m_Data[RGBA_GREEN];
}


inline BYTE CPixel32::GetB()
{
  return m_Data[RGBA_BLUE];
}


inline BYTE CPixel32::GetA()
{
  return m_Data[RGBA_ALPHA];
}

inline int CPixel32::BoxDist (CPixel32 Pix)
{
  return (abs ((int)GetR()-Pix.GetR()) + 
          abs ((int)GetG()-Pix.GetG()) +
          abs ((int)GetB()-Pix.GetB()));
}

inline bool CPixel32::operator ==(const CPixel32& Pix)
{
  return (*(const LONG *)this == *(const LONG*)&Pix);
}

inline bool CPixel32::operator !=(const CPixel32& Pix)
{
  return (!(*this == Pix));
}


#endif

/*
/--------------------------------------------------------------------
|
|      $Log: pixel32.h,v $
|      Revision 1.1  2000/12/18 22:42:52  uzadow
|      Replaced RGBAPIXEL with CPixel32.
|
|
\--------------------------------------------------------------------
*/
