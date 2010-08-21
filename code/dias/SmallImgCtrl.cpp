// SmallImgCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "dias.h"
#include "SmallImgCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmallImgCtrl

CSmallImgCtrl::CSmallImgCtrl () {
}

CSmallImgCtrl::~CSmallImgCtrl () {
}


BEGIN_MESSAGE_MAP(CSmallImgCtrl, CStatic)
	//{{AFX_MSG_MAP(CSmallImgCtrl)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmallImgCtrl message handlers

void CSmallImgCtrl::OnPaint () {
	CPaintDC dc (this);
	dc.DrawIcon (0, 0, theApp.LoadIcon (m_nID));
}
