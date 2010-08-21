// TxtBtnCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "dias.h"
#include "TxtBtnCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTxtBtnCtrl

CTxtBtnCtrl::CTxtBtnCtrl () {
	m_fntText.CreateFont (12, 0, 0, 0, FW_NORMAL, false, false, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
	                      CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
}

CTxtBtnCtrl::~CTxtBtnCtrl () {
}


BEGIN_MESSAGE_MAP(CTxtBtnCtrl, CStatic)
	//{{AFX_MSG_MAP(CTxtBtnCtrl)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTxtBtnCtrl message handlers

void CTxtBtnCtrl::OnPaint () {
	CRect rect;
	CFont *pFont;
	CPaintDC dc(this);
	GetClientRect (&rect);
	dc.FillSolidRect (rect, ::GetSysColor (COLOR_BTNFACE));
//	dc.DrawEdge (rect, BDR_RAISEDINNER, BF_RECT);
	pFont = dc.SelectObject (&m_fntText);
	dc.DrawText (m_strTitle, rect, DT_VCENTER | DT_END_ELLIPSIS | DT_CENTER | DT_SINGLELINE);
	dc.SelectObject (pFont);
}
