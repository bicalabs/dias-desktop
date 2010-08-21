// StartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dias.h"
#include "StartDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStartDlg dialog


CStartDlg::CStartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStartDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStartDlg)
	m_blDefault = FALSE;
	//}}AFX_DATA_INIT
}


void CStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStartDlg)
	DDX_Control(pDX, IDC_START_LIST, m_ctrlList);
	DDX_Check(pDX, IDC_START_DEFAULT, m_blDefault);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStartDlg, CDialog)
	//{{AFX_MSG_MAP(CStartDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStartDlg message handlers
