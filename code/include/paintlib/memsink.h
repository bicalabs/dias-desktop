/*
/--------------------------------------------------------------------
|
|      $Id: memsink.h,v 1.1 2000/10/12 21:57:26 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_MEMSINK
#define INCL_MEMSINK

#include "datasink.h"

//! This is a class which takes a memory region as a destination of picture data.
class CMemSink : public CDataSink
{

public:
  //!
  CMemSink
    ();

  //!
  virtual ~CMemSink
    ();

  //!
  virtual int Open
    ( const char * pszFName,
      int MaxFileSize
    );

  //!
  virtual void Close
    ();

	virtual BYTE* GetBytes();

private:
  FILE * m_pFile;
  BYTE * m_pDataBuf;
};

#endif

/*
/--------------------------------------------------------------------
|
|      $Log: memsink.h,v $
|      Revision 1.1  2000/10/12 21:57:26  uzadow
|      no message
|
|
|
\--------------------------------------------------------------------
*/
