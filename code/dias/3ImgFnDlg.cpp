// 3ImgFnDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dias.h"
#include "3ImgFnDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3ImgFnDlg dialog


C3ImgFnDlg::C3ImgFnDlg(CWnd* pParent) : CDialog(C3ImgFnDlg::IDD, pParent) {
	m_btnPreview.m_nIDOn = m_btnPreview.m_nIDOff = IDI_PIC_PREVIEW;
	m_btnAuto.m_nIDOn = IDI_PIC_UNLOCKED; m_btnAuto.m_nIDOff = IDI_PIC_LOCKED;
	m_btnHand.m_nIDOn = m_btnHand.m_nIDOff = IDI_PIC_HAND;
	m_btnZoom.m_nIDOn = m_btnZoom.m_nIDOff = IDI_PIC_ZOOM;
	m_btnZoom1.m_nIDOn = m_btnZoom1.m_nIDOff = IDI_PIC_ZOOM1;
	m_btnFit.m_nIDOn = m_btnFit.m_nIDOff = IDI_PIC_ZOOMFIT;
	m_btnToggle.m_nIDOn = m_btnToggle.m_nIDOff = IDI_PIC_TOGGLE;
	//{{AFX_DATA_INIT(C3ImgFnDlg)
	//}}AFX_DATA_INIT
}


void C3ImgFnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C3ImgFnDlg)
	DDX_Control(pDX, IDC_3IFN_TOGGLE, m_btnToggle);
	DDX_Control(pDX, IDC_3IFN_ZOOMFIT, m_btnFit);
	DDX_Control(pDX, IDC_3IFN_ZOOM1, m_btnZoom1);
	DDX_Control(pDX, IDC_3IFN_ZOOM, m_btnZoom);
	DDX_Control(pDX, IDC_3IFN_HAND, m_btnHand);
	DDX_Control(pDX, IDC_3IFN_AUTO, m_btnAuto);
	DDX_Control(pDX, IDC_3IFN_PREVIEW, m_btnPreview);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C3ImgFnDlg, CDialog)
	//{{AFX_MSG_MAP(C3ImgFnDlg)
	ON_WM_CHAR()
	ON_BN_CLICKED(IDC_3IFN_RESET, OnReset)
	ON_BN_CLICKED(IDC_3IFN_APPLY, OnApply)
	ON_BN_CLICKED(IDC_3IFN_PREVIEW, OnPreview)
	ON_BN_CLICKED(IDC_3IFN_AUTO, OnAuto)
	ON_BN_CLICKED(IDC_3IFN_HAND, OnHand)
	ON_BN_CLICKED(IDC_3IFN_ZOOM, OnZoom)
	ON_BN_CLICKED(IDC_3IFN_ZOOM1, OnZoom1)
	ON_BN_CLICKED(IDC_3IFN_ZOOMFIT, OnZoomFit)
	ON_BN_CLICKED(IDC_3IFN_TOGGLE, OnToggle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3ImgFnDlg message handlers

BOOL C3ImgFnDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void C3ImgFnDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

void C3ImgFnDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void C3ImgFnDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void C3ImgFnDlg::OnReset() 
{
	// TODO: Add your control notification handler code here
	
}

void C3ImgFnDlg::OnApply() 
{
	// TODO: Add your control notification handler code here
	
}

void C3ImgFnDlg::OnPreview() 
{
	// TODO: Add your control notification handler code here
	
}

void C3ImgFnDlg::OnAuto() 
{
	// TODO: Add your control notification handler code here
	
}

void C3ImgFnDlg::OnHand() 
{
	// TODO: Add your control notification handler code here
	
}

void C3ImgFnDlg::OnZoom() 
{
	// TODO: Add your control notification handler code here
	
}

void C3ImgFnDlg::OnZoom1() 
{
	// TODO: Add your control notification handler code here
	
}

void C3ImgFnDlg::OnZoomFit() 
{
	// TODO: Add your control notification handler code here
	
}

void C3ImgFnDlg::OnToggle() 
{
	// TODO: Add your control notification handler code here
	
}
