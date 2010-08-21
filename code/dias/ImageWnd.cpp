// ImageWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Dias.h"
#include "StorageDoc.h"
#include "StorageFrame.h"
#include "ImageWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageWnd
CImageWnd::CImageWnd () {
	m_pFrame = NULL;
	m_pView = NULL;
	m_pDoc = NULL;
	m_pbBits = NULL;
	m_ppenLine = new CPen (PS_SOLID, 3, ::GetSysColor (COLOR_BTNFACE));
	m_ppenBoundary = new CPen (PS_SOLID, 1, 0xFFFFFF);
	m_ppenChord = new CPen (PS_DOT, 1, 0xFFFFFF);
	m_nVScrollPos = 0;
	m_nHScrollPos = 0;

	m_nCaptureMode = 0;
	m_pMarkActive = NULL;
}

CImageWnd::~CImageWnd () {
	delete m_ppenLine;
	delete m_ppenBoundary;
	delete m_ppenChord;
	if (m_bmpImage.m_hObject)
		m_bmpImage.DeleteObject();
}


BEGIN_MESSAGE_MAP(CImageWnd, CWnd)
	//{{AFX_MSG_MAP(CImageWnd)
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CPoint CImageWnd::MapPntToScrCoord (const CPoint pnt) {
	CPoint point;
	CRect rectClient;
	GetClientRect (&rectClient);
	float zoom = m_pView->m_nZoomImg / 100.;
	int cx = (rectClient.Width () < m_pDoc->GetDimX() * zoom) ? (m_nHScrollPos) : ((m_pDoc->GetDimX() * zoom - rectClient.Width ())/2);
	int cy = (rectClient.Height () < m_pDoc->GetDimY() * zoom) ? (m_nVScrollPos) : ((m_pDoc->GetDimY() * zoom - rectClient.Height ())/2);
	point.x = pnt.x * zoom - cx;
	point.y = pnt.y * zoom - cy;
	return (point);
}

void CImageWnd::MapPntToScrCoord (CPoint* ppnt, uvar32_64 cnt) {
	for (uvar32_64 n = 0; n < cnt; ++n)
		ppnt[n] = MapPntToScrCoord (ppnt[n]);
}

void CImageWnd::PaintActiveMark () {
	if (!m_pMarkActive)
		return;

	CClientDC dcThis (this);
	CPen *ppenOld = dcThis.SelectObject (m_ppenBoundary);
	CRect rect (-3, -3, 3, 3), rect2;

	m_pMarkActive->CreateControls ();
	dcThis.SetROP2 (R2_MASKPENNOT);
	CPoint pntCenter = MapPntToScrCoord (CPoint(m_pMarkActive->m_iPosX, m_pMarkActive->m_iPosY));
	dcThis.DrawIcon (pntCenter.x - 16, pntCenter.y - 16, theApp.LoadIcon (IDI_MRK_CENTER));
	rect2 = rect;
	rect2.OffsetRect (MapPntToScrCoord(m_pMarkActive->m_pntAxisX));
	dcThis.InvertRect (rect2);
	rect2 = rect;
	rect2.OffsetRect (MapPntToScrCoord(m_pMarkActive->m_pntAxisY));
	dcThis.InvertRect (rect2);
	rect2 = rect;
	rect2.OffsetRect (MapPntToScrCoord(m_pMarkActive->m_pntAxisXY));
	dcThis.InvertRect (rect2);
	switch (m_pMarkActive->m_nShape) {
		case CMark::shpEllipse:
			MapPntToScrCoord (m_pMarkActive->m_pptPoints, m_pMarkActive->m_nShapeSizeX * 4 + 1);
			dcThis.Polyline (m_pMarkActive->m_pptPoints, m_pMarkActive->m_nShapeSizeX * 4 + 1);
			break;
		case CMark::shpRect:
			MapPntToScrCoord (m_pMarkActive->m_pptPoints, 5);
			dcThis.Polyline (m_pMarkActive->m_pptPoints, 5);
			break;
		case CMark::shpTriangle:
			MapPntToScrCoord (m_pMarkActive->m_pptPoints, 4);
			dcThis.Polyline (m_pMarkActive->m_pptPoints, 4);
			break;
	}
	dcThis.SelectObject (m_ppenChord);
	dcThis.MoveTo (MapPntToScrCoord(CPoint(m_pMarkActive->m_iPosX, m_pMarkActive->m_iPosY)));
	dcThis.LineTo (MapPntToScrCoord(m_pMarkActive->m_pntAxisX));
	dcThis.MoveTo (MapPntToScrCoord(CPoint(m_pMarkActive->m_iPosX, m_pMarkActive->m_iPosY)));
	dcThis.LineTo (MapPntToScrCoord(m_pMarkActive->m_pntAxisY));
	dcThis.MoveTo (MapPntToScrCoord(CPoint(m_pMarkActive->m_iPosX, m_pMarkActive->m_iPosY)));
	dcThis.LineTo (MapPntToScrCoord(m_pMarkActive->m_pntAxisXY));
	dcThis.SelectObject (ppenOld);
}

CRect CImageWnd::GetImageRect (int& width, int& height) {
	CRect rectClient, rectImage;
	GetClientRect (&rectClient);

	width = m_pDoc->GetDimX() * m_pView->m_nZoomImg / 100;
	height = m_pDoc->GetDimY() * m_pView->m_nZoomImg / 100;
	rectImage = CRect ((rectClient.Width() < width) ? (-m_nHScrollPos) : ((rectClient.Width() - width)/2),
	                   (rectClient.Height() < height) ? (-m_nVScrollPos) : ((rectClient.Height() - height)/2),
	                   (rectClient.Width() < width) ? (width - m_nHScrollPos) : ((rectClient.Width() + width)/2),
	                   (rectClient.Height() < height) ? (height - m_nVScrollPos) : ((rectClient.Height() + height)/2));
	return (rectImage);
}

/////////////////////////////////////////////////////////////////////////////
// CImageWnd message handlers

BOOL CImageWnd::OnSetCursor (CWnd* pWnd, UINT nHitTest, UINT message) {
	int iCursor;
	if ( nHitTest != HTCLIENT )
		return CWnd::OnSetCursor(pWnd, nHitTest, message);
	switch (theApp.GetMode ()) {
		case CDiasApp::emiPtr:		iCursor = IDC_POINTER;		break;
		case CDiasApp::emiHand:		iCursor = IDC_HAND;		break;
		case CDiasApp::emiSelect:	iCursor = IDC_POINTER;		break;
		case CDiasApp::emiInfo:		iCursor = IDC_POINTER;		break;
		case CDiasApp::emiIn:		iCursor = IDC_ZOOMIN;		break;
		case CDiasApp::emiOut:		iCursor = IDC_ZOOMOUT;		break;
		case CDiasApp::emiIobjCreate:	iCursor = IDC_IOBJCREATE;	break;
		case CDiasApp::emiIobjCng:	iCursor = IDC_POINTER;		break;
		case CDiasApp::emiIobjPtr:	iCursor = IDC_POINTER;		break;
		case CDiasApp::emiMeter:	iCursor = IDC_POINTER;		break;
		case CDiasApp::emiMrkCreate:	iCursor = IDC_MRKCREATE;	break;
		case CDiasApp::emiMrkPtr:	iCursor = IDC_MRKPTR;		break;
		case CDiasApp::emiMrkSel:	iCursor = IDC_MRKSEL;		break;
		case CDiasApp::emiTextCreate:	iCursor = IDC_TEXTCREATE;	break;
		case CDiasApp::emiTextPtr:	iCursor = IDC_TEXTCNG;		break;
	}
	HCURSOR cursor = theApp.LoadCursor ( iCursor );
	SetCursor ( cursor );
	return (true);
}

void CImageWnd::OnPaint () {
	CDC      dcMem;
	CPaintDC dcThis(this);
	dcMem.CreateCompatibleDC (&dcThis);

	int width, height;
	CRect rectClient, rectImage = GetImageRect (width, height);
	GetClientRect (&rectClient);

	if ((m_nImage = m_pFrame->GetActiveImageNo ()) == -1) {
		dcThis.FillSolidRect ( &rectClient, ::GetSysColor ( COLOR_WINDOW ) );
		CPen *pPen = dcThis.SelectObject (m_ppenLine);
		dcThis.MoveTo ( rectClient.right / 3, rectClient.bottom / 3 );
		dcThis.LineTo ( rectClient.right * 2 / 3, rectClient.bottom * 2 / 3 );
		dcThis.MoveTo ( rectClient.right / 3, rectClient.bottom * 2 / 3 );
		dcThis.LineTo ( rectClient.right * 2 / 3, rectClient.bottom / 3 );
		dcThis.SelectObject (pPen);
		return;
	}

	if (!m_bmpImage.m_hObject)
		return;

	dcThis.SetROP2 (R2_NOP);

	if (rectClient.Height() > height) {
		dcThis.FillSolidRect (CRect (0, 0, rectClient.right, rectImage.top),
				       ::GetSysColor (COLOR_WINDOW));
		dcThis.FillSolidRect (CRect (0, rectImage.bottom, rectClient.right, rectClient.bottom),
				       ::GetSysColor (COLOR_WINDOW));
	}
	if (rectClient.Width() > width) {
		dcThis.FillSolidRect (CRect (0, 0, rectImage.left, rectClient.bottom),
				       ::GetSysColor (COLOR_WINDOW));
		dcThis.FillSolidRect (CRect (rectImage.right, 0, rectClient.right, rectClient.bottom),
				       ::GetSysColor (COLOR_WINDOW));
	}

	m_pbmpOld = dcMem.GetCurrentBitmap ();
	if (m_pDoc->GetSetting ("ShowImages"))
		dcMem.SelectObject (&m_bmpImage);
	if (m_pDoc->GetSetting ("ShowPatches"))
		for (uvar32_64 n = 0; n < m_pDoc->Images[m_nImage].Patches.GetCount (); ++n)
			m_pDoc->Images[m_nImage].Patches[n].Paint (dcMem);
	if (m_pDoc->GetSetting ("ShowMarks"))
		for (uvar32_64 n = 0; n < m_pDoc->Images[m_nImage].Marks.GetCount (); ++n)
			m_pDoc->Images[m_nImage].Marks[n].Paint (dcMem);

	dcThis.SetStretchBltMode (STRETCH_HALFTONE);
	dcThis.StretchBlt (rectImage.left, rectImage.top, rectImage.Width (), rectImage.Height (), 
	                    &dcMem, 0, 0, m_pDoc->GetDimX(), m_pDoc->GetDimY(), SRCCOPY);
	dcMem.SelectObject (m_pbmpOld);
	dcMem.DeleteDC ();

	PaintActiveMark ();
}

void CImageWnd::PaintMark (uvar32_64 n) {
	int	x;
	CDC     dcMem;
	CRect	rectImage = GetImageRect (x,x);
	CClientDC dcThis (this);
	dcMem.CreateCompatibleDC (&dcThis);
	m_pDoc->Images[m_nImage].Marks[n].Paint (dcMem);
	dcThis.SetROP2 (R2_NOP);
	dcThis.SetStretchBltMode (STRETCH_HALFTONE);
	dcThis.StretchBlt (rectImage.left, rectImage.top, rectImage.Width (), rectImage.Height (), 
			   &dcMem, 0, 0, m_pDoc->GetDimX(), m_pDoc->GetDimY(), SRCCOPY);
	dcMem.DeleteDC ();
//	PaintActiveMark ();
}

void CImageWnd::CreateImage (CPaintDC* dcThis) {
	m_pMarkActive = NULL;

	bool del = false;
	if (m_bmpImage.m_hObject)
		m_bmpImage.DeleteObject();
	if (m_pDoc->Images(aimSelected).GetCount () != 1)
		return;
	if (del = (!dcThis))
		dcThis = new CPaintDC (this);

	DWORD size = m_pDoc->GetDimX () * m_pDoc->GetDimY ();
	RGBQUAD q = {0,0,0};
	LPBITMAPINFO lpbi;
	lpbi = (LPBITMAPINFO) new BYTE[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)];
	lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	lpbi->bmiHeader.biWidth = m_pDoc->GetDimX ();
	lpbi->bmiHeader.biHeight = m_pDoc->GetDimY ();
	lpbi->bmiHeader.biPlanes = 1;
	lpbi->bmiHeader.biBitCount = 24;
	lpbi->bmiHeader.biCompression = BI_RGB;
	lpbi->bmiHeader.biSizeImage = size;
	lpbi->bmiHeader.biXPelsPerMeter = 0;
	lpbi->bmiHeader.biYPelsPerMeter = 0;
	lpbi->bmiHeader.biClrUsed = 0;
	lpbi->bmiHeader.biClrImportant = 0;
	lpbi->bmiColors[0] = q;

	// #### TODO: Add lut support here

	// #### TODO: This is only creation of bitmap for images with 256-color LU tables. Add support for true color images

	ubyte* pbBits = (ubyte*)aimMemoryCommit (size, "CImageWnd::CreateImage", "pbBits");
	HBITMAP hBitmap = CreateDIBSection (dcThis->m_hDC, lpbi, DIB_RGB_COLORS, (void **)&m_pbBits, NULL, 0);
	m_pDoc->Images[aimActive].Channels(aimAll).GetBits (pbBits, size, true);
	for (uvar32_64 x, y = 0, dx = m_pDoc->GetDimX (), dy = m_pDoc->GetDimY (), t; y < dy; ++y)
		for (x = 0; x < dx; ++x) {
			t = pbBits[(dy-y-1)*dx + x];
			m_pbBits[(y*dx + x) * 3 + 0] = t;
			m_pbBits[(y*dx + x) * 3 + 1] = t;
			m_pbBits[(y*dx + x) * 3 + 2] = t;
		}
	aimMemoryRelease (pbBits, "CImageWnd::CreateImage", "pbBits");
	m_bmpImage.Attach (hBitmap);
	delete [] (BYTE *)lpbi;

	if (del)
		delete dcThis;
}

void CImageWnd::OnVScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
//	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
	CRect rectClient;
	GetClientRect (&rectClient);
	switch (nSBCode) {
		case SB_LINEUP:		m_nVScrollPos-=2; break;
		case SB_LINEDOWN:	m_nVScrollPos+=2; break;
		case SB_PAGEUP:		m_nVScrollPos-=20; break;
		case SB_PAGEDOWN:	m_nVScrollPos+=20; break;
		case SB_TOP:		m_nVScrollPos=0; break;
		case SB_BOTTOM:		m_nVScrollPos=m_pDoc->GetDimY() * m_pView->m_nZoomImg / 100 - rectClient.Height (); break;
		case SB_THUMBPOSITION:	m_nVScrollPos=nPos; break;
	}
	m_nVScrollPos = (m_nVScrollPos < 0) ? 0 : ((m_nVScrollPos > (m_pDoc->GetDimY() * m_pView->m_nZoomImg / 100 - rectClient.Height ())) ? (m_pDoc->GetDimY() * m_pView->m_nZoomImg / 100 - rectClient.Height ()) : m_nVScrollPos);
	SetScrollPos (SB_VERT, m_nVScrollPos);
	RedrawWindow ();
}

void CImageWnd::OnHScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
//	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
	CRect rectClient;
	GetClientRect (&rectClient);
	switch (nSBCode) {
		case SB_LINEUP:		m_nHScrollPos-=2; break;
		case SB_LINEDOWN:	m_nHScrollPos+=2; break;
		case SB_PAGEUP:		m_nHScrollPos-=20; break;
		case SB_PAGEDOWN:	m_nHScrollPos+=20; break;
		case SB_TOP:		m_nHScrollPos=0; break;
		case SB_BOTTOM:		m_nHScrollPos=m_pDoc->GetDimX() * m_pView->m_nZoomImg / 100 - rectClient.Width (); break;
		case SB_THUMBPOSITION:	m_nHScrollPos=nPos; break;
	}
	m_nHScrollPos = (m_nHScrollPos < 0) ? 0 : ((m_nHScrollPos > (m_pDoc->GetDimX() * m_pView->m_nZoomImg / 100 - rectClient.Width ())) ? (m_pDoc->GetDimX() * m_pView->m_nZoomImg / 100 - rectClient.Width ()) : m_nHScrollPos);
	SetScrollPos (SB_HORZ, m_nHScrollPos);
	RedrawWindow ();
}

void CImageWnd::OnSize (UINT nType, int cx, int cy) {
	CWnd::OnSize(nType, cx, cy);
	UpdateScroll ();
}

void CImageWnd::UpdateScroll () {
	if (!m_pFrame || !m_pView || !m_pDoc)
		return;

	bool blHorz, blVert;
	CRect rectClient;
	GetClientRect (&rectClient);
	SCROLLINFO info;
	info.cbSize = sizeof (SCROLLINFO);
	info.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
	if (::IsWindow (m_pFrame->m_barImages.m_hWnd) && m_pFrame->GetActiveImageNo () == -1) {
		ShowScrollBar (SB_VERT, false);
		ShowScrollBar (SB_HORZ, false);
		return;
	}
	m_nHScrollPos = (m_nHScrollPos < 0) ? 0 : m_nHScrollPos;
	m_nVScrollPos = (m_nVScrollPos < 0) ? 0 : m_nVScrollPos;
	m_nHScrollPos = (m_nHScrollPos > (m_pDoc->GetDimX() * m_pView->m_nZoomImg / 100 - rectClient.Width ())) ? (m_pDoc->GetDimX() * m_pView->m_nZoomImg / 100 - rectClient.Width ()) : m_nHScrollPos;
	m_nVScrollPos = (m_nVScrollPos > (m_pDoc->GetDimY() * m_pView->m_nZoomImg / 100 - rectClient.Height ())) ? (m_pDoc->GetDimY() * m_pView->m_nZoomImg / 100 - rectClient.Height ()) : m_nVScrollPos;
	if (blVert = (rectClient.Height () < (m_pDoc->GetDimY() * m_pView->m_nZoomImg / 100))) {
		info.nMin = 0;
		info.nMax = (m_pDoc->GetDimY() * m_pView->m_nZoomImg / 100);
		info.nPage = rectClient.Height ();
		info.nPos = m_nVScrollPos;
		SetScrollInfo (SB_VERT, &info, true);
	} else m_nVScrollPos = 0;
	if (blHorz = (rectClient.Width () < (m_pDoc->GetDimX() * m_pView->m_nZoomImg / 100))) {
		info.nMin = 0;
		info.nMax = (m_pDoc->GetDimX() * m_pView->m_nZoomImg / 100);
		info.nPage = rectClient.Width ();
		info.nPos = m_nHScrollPos;
		SetScrollInfo (SB_HORZ, &info, true);
	} else m_nHScrollPos = 0;
	ShowScrollBar (SB_VERT, blVert);
	ShowScrollBar (SB_HORZ, blHorz);
	RedrawWindow ();
}

void CImageWnd::OnLButtonDown (UINT nFlags, CPoint point) {
	if (m_pFrame->GetActiveImageNo () == -1)
		return;

	CRect rectClient;
	GetClientRect (&rectClient);
	float zoom = m_pView->m_nZoomImg / 100.;
	int cx = (rectClient.Width () < m_pDoc->GetDimX() * zoom) ? (m_nHScrollPos) : ((m_pDoc->GetDimX() * zoom - rectClient.Width ())/2);
	int cy = (rectClient.Height () < m_pDoc->GetDimY() * zoom) ? (m_nVScrollPos) : ((m_pDoc->GetDimY() * zoom - rectClient.Height ())/2);
	point.x = (point.x + cx) / zoom;
	point.y = (point.y + cy) / zoom;

	uvar32_64 cnt;
	switch (theApp.GetMode ()) {
		case CDiasApp::emiHand:
			m_nCaptureMode = 1;
			break;
		case CDiasApp::emiMrkCreate:
			m_pDoc->Images[aimActive].Marks.Add (point);
			break;
		case CDiasApp::emiMrkPtr:
			if ((cnt = m_pDoc->Images[aimActive].Marks.GetCount ()) == 0)
				break;
			if (m_pMarkActive) {
				m_nStart = m_pMarkActive->m_nShapeAngle;
				switch (m_pMarkActive->GetPointType (point)) {
					case CMark::pntNone:
						PaintActiveMark ();
						m_pMarkActive->Select (false);
						m_pMarkActive = NULL;
						break;
					case CMark::pntCenter:
						m_nCaptureMode = 1;
						break;
					case CMark::pntAxisX:
						m_nCaptureMode = 2;
						break;
					case CMark::pntAxisY:
						m_nCaptureMode = 3;
						break;
					case CMark::pntAxisXY:
						m_nCaptureMode = 4;
						break;
				}
			}
			if (!m_pMarkActive) {
				m_nCaptureMode = 0;
				m_pMarkActive = &(m_pDoc->Images[aimActive].Marks[point]);
				if (m_pMarkActive)
					m_pMarkActive->Select ();
				PaintActiveMark ();
			}
			break;
	}
	m_pntOld = point;
	m_pntStart = point;
	SetCapture ();
	CWnd::OnLButtonDown(nFlags, point);
}

void CImageWnd::OnLButtonUp (UINT nFlags, CPoint point) {
	if (GetCapture () != this) {
		CWnd::OnLButtonUp(nFlags, point);
		return;
	}
	m_nCaptureMode = 0;
	ReleaseCapture ();
	CMark *p = m_pMarkActive;
	switch (theApp.GetMode ()) {
		case CDiasApp::emiHand:
			m_nCaptureMode = 0;
			break;
		case CDiasApp::emiMrkPtr:
			if (m_pMarkActive) {
				CreateImage ();
				m_pMarkActive = p;
				RedrawWindow ();
			}
			break;
	}
}

void CImageWnd::OnMouseMove (UINT nFlags, CPoint point) {
	if (m_pFrame->GetActiveImageNo () == -1)
		return;

	rtbyte b2, d2, l2, sign;
	CRect rectClient;
	GetClientRect (&rectClient);
	float zoom = m_pView->m_nZoomImg / 100.;
	int cx = (rectClient.Width () < m_pDoc->GetDimX() * zoom) ? (m_nHScrollPos) : ((m_pDoc->GetDimX() * zoom - rectClient.Width ())/2);
	int cy = (rectClient.Height () < m_pDoc->GetDimY() * zoom) ? (m_nVScrollPos) : ((m_pDoc->GetDimY() * zoom - rectClient.Height ())/2);
	point.x = (point.x + cx) / zoom;
	point.y = (point.y + cy) / zoom;

	if (m_pntOld == point)
		return;
	switch (theApp.GetMode ()) {
		case CDiasApp::emiHand:
			if (!m_nCaptureMode)
				break;
			SetCursor (theApp.LoadCursor (IDC_HANDSHAKE));
			m_nHScrollPos += (point.x - m_pntOld.x);
			m_nVScrollPos += (point.y - m_pntOld.y);
			UpdateScroll ();
			break;
		case CDiasApp::emiMrkPtr:
			if (!m_pMarkActive)
				break;
			if (m_nCaptureMode)
				PaintActiveMark ();
			switch (m_nCaptureMode) {
				case 1:	m_pMarkActive->m_iPosX += point.x - m_pntOld.x;
					m_pMarkActive->m_iPosY += point.y - m_pntOld.y;
					break;
				case 2:	m_pMarkActive->m_nShapeSizeX = point.x - m_pMarkActive->m_iPosX;
					break;
				case 3:	m_pMarkActive->m_nShapeSizeY = m_pMarkActive->m_iPosY - point.y;
					break;
				case 4:	
					b2 = m_pMarkActive->m_nShapeSizeX * m_pMarkActive->m_nShapeSizeX + m_pMarkActive->m_nShapeSizeY * m_pMarkActive->m_nShapeSizeY;
					d2 = (point.x - m_pntStart.x) * (point.x - m_pntStart.x) + (point.y - m_pntStart.y) * (point.y - m_pntStart.y);
					l2 = (point.x - m_pMarkActive->m_iPosX) * (point.x - m_pMarkActive->m_iPosX) + (point.y - m_pMarkActive->m_iPosY) * (point.y - m_pMarkActive->m_iPosY);
					if (point.y - m_pntStart.y == 0) sign = 2;
					else sign = 2 * abs (point.y - m_pntStart.y) / (point.y - m_pntStart.y);
					m_pMarkActive->m_nShapeAngle = m_nStart + acos ((b2 + l2 - d2)/(sign*pow(b2,0.5)*pow(l2,0.5))) * 180 / 3.1415;
					break;
			}
			m_pMarkActive->CreateControls ();
			if (m_nCaptureMode)
				PaintActiveMark ();
			switch (m_pMarkActive->GetPointType (point)) {
				case CMark::pntNone:
					SetCursor (theApp.LoadCursor (IDC_MRKPTR));
					break;
				case CMark::pntCenter:
					SetCursor (theApp.LoadCursor (IDC_MRKPTR_MOVE));
					break;
				case CMark::pntAxisX:
					SetCursor (theApp.LoadCursor (IDC_MRKPTR_SIZEX));
					break;
				case CMark::pntAxisY:
					SetCursor (theApp.LoadCursor (IDC_MRKPTR_SIZEY));
					break;
				case CMark::pntAxisXY:
					SetCursor (theApp.LoadCursor (IDC_MRKPTR_SIZEXY));
					break;
			}
			break;
	}
	m_pntOld = point;
	CWnd::OnMouseMove(nFlags, point);
}

BOOL CImageWnd::OnMouseWheel (UINT nFlags, short zDelta, CPoint pt) {

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}
