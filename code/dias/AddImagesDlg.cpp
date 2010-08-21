// AddImagesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Dias.h"
#include "AddImagesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddImagesDlg dialog


CAddImagesDlg::CAddImagesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddImagesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddImagesDlg)
	m_nCount = 0;
	//}}AFX_DATA_INIT
}


void CAddImagesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddImagesDlg)
	DDX_Text(pDX, IDC_DAI_COUNT, m_nCount);
	DDV_MinMaxUInt(pDX, m_nCount, 1, 10000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddImagesDlg, CDialog)
	//{{AFX_MSG_MAP(CAddImagesDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddImagesDlg message handlers

void CAddImagesDlg::OnOK () {
	UpdateData (true);
	CDialog::OnOK();
}
