/*
/--------------------------------------------------------------------
|
|      $Id: pixeldefs.vc,v 1.3 2000/12/18 22:42:52 uzadow Exp $
|
|      Pixel format definitions for MS Visual C++
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/


#ifndef INCL_PIXELDEFS
#define INCL_PIXELDEFS

#undef PIXEL_BGRA_ORDER  // MS Windows ordering
#undef PIXEL_RGBA_ORDER // GNU/Linux (at least)

// Define the pixel format for RGB-bitmaps. Change this if you change
// the order of the color components. 

// We have this pixel byte ordering
#define PIXEL_BGRA_ORDER

#ifdef PIXEL_RGBA_ORDER
 // To access in RGBA order
 #define RGBA_RED    0
 #define RGBA_GREEN  1
 #define RGBA_BLUE   2
 #define RGBA_ALPHA  3
#elif defined(PIXEL_BGRA_ORDER)
 #define RGBA_BLUE   0
 #define RGBA_GREEN  1
 #define RGBA_RED    2
 #define RGBA_ALPHA  3
#else
  #error Pixel RGB bytes order not selected
#endif

// Note that the preceeding #defines aren't static const ints because
// this breaks preprocessor tests in several places.

#endif

/*
/--------------------------------------------------------------------
|
|      $Log: pixeldefs.vc,v $
|      Revision 1.3  2000/12/18 22:42:52  uzadow
|      Replaced RGBAPIXEL with CPixel32.
|
|      Revision 1.2  2000/11/09 22:23:36  uzadow
|      no message
|
|
\--------------------------------------------------------------------
*/
