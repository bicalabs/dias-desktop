// MenuCntDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dias.h"
#include "MenuCntDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMenuCntDlg dialog


CMenuCntDlg::CMenuCntDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMenuCntDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMenuCntDlg)
	//}}AFX_DATA_INIT
}


void CMenuCntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMenuCntDlg)
	DDX_Control(pDX, IDC_MC_SLIDER, m_ctrlSlider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMenuCntDlg, CDialog)
	//{{AFX_MSG_MAP(CMenuCntDlg)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_MC_SLIDER, OnSliderChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMenuCntDlg message handlers

BOOL CMenuCntDlg::OnInitDialog () {
	CDialog::OnInitDialog();

	SetWindowPos (NULL, m_nX, m_nY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	m_ctrlSlider.SetRange (m_nMin, m_nMax, true);
	UpdateData (false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMenuCntDlg::OnOK () {
	UpdateData (true);
	
	CDialog::OnOK();
}

void CMenuCntDlg::OnSliderChanged (NMHDR* pNMHDR, LRESULT* pResult) {
	
	*pResult = 0;
}
