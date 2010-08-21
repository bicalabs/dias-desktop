// AimStatusBar.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\Dias\dias.h"
#include "AimStatusBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAimStatusBar

CAimStatusBar::CAimStatusBar()
{
}

CAimStatusBar::~CAimStatusBar()
{
}


BEGIN_MESSAGE_MAP(CAimStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(CAimStatusBar)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAimStatusBar message handlers

void CAimStatusBar::OnDrawItem (int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) {
/*	if (m_pBitmaps[nIDCtl] == NULL) {
		CStatusBar::OnDrawItem(nIDCtl, lpDrawItemStruct);
		return;
	}

	CDC dc, dcSrc;
	CRect rect (&lpDrawItemStruct->rcItem);
	dc.Attach (lpDrawItemStruct->hDC);
	dcSrc.CreateCompatibleDC (NULL);

	CBitmap* pOldBitmap = dcSrc.SelectObject(m_pBitmaps[nIDCtrl]);
	dc.BitBlt (rect.left, rect.top, rect.Width(), rect.Height(),
                   &srcDC, 0, 0, SRCCOPY);
	dcSrc.SelectObject(pOldBitmap);
	dc.Detach();*/
}
