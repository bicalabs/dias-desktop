// ImageCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "dias.h"
#include "ImageCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageCtrl

CImageCtrl::CImageCtrl()
{
}

CImageCtrl::~CImageCtrl()
{
}


BEGIN_MESSAGE_MAP(CImageCtrl, CStatic)
	//{{AFX_MSG_MAP(CImageCtrl)
	ON_WM_PAINT()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageCtrl message handlers

void CImageCtrl::OnPaint () {
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CStatic::OnPaint() for painting messages
}

void CImageCtrl::OnChar (UINT nChar, UINT nRepCnt, UINT nFlags) {
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnChar(nChar, nRepCnt, nFlags);
}
