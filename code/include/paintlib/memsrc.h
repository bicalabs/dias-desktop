/*
/--------------------------------------------------------------------
|
|      $Id: memsrc.h,v 1.1 2000/03/17 10:51:38 Ulrich von Zadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_MEMSRC
#define INCL_MEMSRC

#ifndef INCL_DATASRC
#include "datasrc.h"
#endif

//! This is a class which takes a memory pointer as a source of
//! picture data.
class CMemSource : public CDataSource
{
public:
  //!
  CMemSource
    ();

  //!
  virtual ~CMemSource
    ();

  //!
  virtual int Open( unsigned char *pek, int size);

  //!
  virtual void Close
    ();

  virtual BYTE * ReadNBytes
    ( int n
    );

  //! Read but don't advance file pointer.
  virtual BYTE * GetBufferPtr
    ( int MinBytesInBuffer
    );

  //! This is a legacy routine that interferes with progress notifications.
  //! Don't call it!
  virtual BYTE * ReadEverything
    ();

private:
  BYTE * m_pCurPos;
};

#endif
/*
/--------------------------------------------------------------------
|
|      $Log: memsrc.h,v $
|      Revision 1.1  2000/03/17 10:51:38  Ulrich von Zadow
|      no message
|
|
|
\--------------------------------------------------------------------
*/
