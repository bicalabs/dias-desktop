// ImgPropBar.cpp : implementation file
//

#include "stdafx.h"
#include "dias.h"
#include "ImgPropBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImgPropBar dialog


CImgPropBar::CImgPropBar(CWnd* pParent /*=NULL*/)
	: CDialog(CImgPropBar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImgPropBar)
	//}}AFX_DATA_INIT
}


void CImgPropBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImgPropBar)
	DDX_Control(pDX, IDC_IMGPB_DESCRTEMPL, m_btnDescr);
	DDX_Control(pDX, IDC_IMGPB_NAMETEMPL, m_btnText);
	DDX_Control(pDX, IDC_IMGPB_DESCR, m_ctrlDescr);
	DDX_Control(pDX, IDC_IMGPB_NAME, m_ctrlName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImgPropBar, CDialog)
	//{{AFX_MSG_MAP(CImgPropBar)
	ON_EN_CHANGE(IDC_IMGPB_NAME, OnChangeName)
	ON_EN_CHANGE(IDC_IMGPB_DESCR, OnChangeDescr)
	ON_BN_CLICKED(IDC_IMGPB_SHOW, OnShow)
	ON_BN_CLICKED(IDC_IMGPB_HIDE, OnHide)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImgPropBar message handlers

void CImgPropBar::OnChangeName () {
	if (m_blLock)	return;
	if (theApp.Documents.GetCount() <= 0)
		return;
	m_blLock = true;
	CString strName;
	m_ctrlName.GetWindowText (strName);
	theApp.Documents[aimActive].Images(aimSelected).SetName (strName);
	m_blLock = false;
}

void CImgPropBar::OnChangeDescr () {
	if (m_blLock)	return;
	if (theApp.Documents.GetCount() <= 0)
		return;
	m_blLock = true;
	CString strName;
	m_ctrlDescr.GetWindowText (strName);
	theApp.Documents[aimActive].Images(aimSelected).SetDescription (strName);
	m_blLock = false;
}

BOOL CImgPropBar::OnInitDialog () {
	CDialog::OnInitDialog ();
	
	m_blLock = false;
//	m_ctrlShow.m_strTitle = theApp.LoadString (IDS_IMGPB_SHOW);
//	m_ctrlHide.m_strTitle = theApp.LoadString (IDS_IMGPB_HIDE);
	
	Update ();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CImgPropBar::Update () {
	try {
		if (IsWindow (m_ctrlName.m_hWnd) && theApp.Documents.GetCount () > 0)
			m_ctrlName.SetWindowText (theApp.Documents[aimActive].Images[aimActive].GetName ());
		if (IsWindow (m_ctrlDescr.m_hWnd) && theApp.Documents.GetCount () > 0)
			m_ctrlDescr.SetWindowText (theApp.Documents[aimActive].Images[aimActive].GetDescription ());
	} catch (CaImAPIException e) {
		return;
	}
}

void CImgPropBar::OnShow () {
	// TODO: Add your control notification handler code here
	
}

void CImgPropBar::OnHide () {
	// TODO: Add your control notification handler code here
	
}

void CImgPropBar::OnOK () {
}

void CImgPropBar::OnCancel () {
}
