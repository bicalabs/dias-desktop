// AimComboDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dias.h"
#include "AimComboDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAimComboDlg dialog


CAimComboDlg::CAimComboDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAimComboDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAimComboDlg)
	//}}AFX_DATA_INIT
}


void CAimComboDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAimComboDlg)
	DDX_Control(pDX, IDC_CD_UP, m_btnUp);
	DDX_Control(pDX, IDC_CD_TOP, m_btnTop);
	DDX_Control(pDX, IDC_CD_NEW, m_btnNew);
	DDX_Control(pDX, IDC_CD_MENU, m_btnMenu);
	DDX_Control(pDX, IDC_CD_DOWN, m_btnDown);
	DDX_Control(pDX, IDC_CD_DELETE, m_btnDelete);
	DDX_Control(pDX, IDC_CD_BOTTOM, m_btnBottom);
	DDX_Control(pDX, IDC_CD_LIST, m_ctrlList);
	DDX_Control(pDX, IDC_CD_GRIPPER, m_ctrlGripper);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAimComboDlg, CDialog)
	//{{AFX_MSG_MAP(CAimComboDlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CD_LIST, OnItemChangedList)
	ON_NOTIFY(HDN_ITEMCLICK, IDC_CD_LIST, OnHeaderClickList)
	ON_WM_SIZE()
	ON_WM_KILLFOCUS()
	ON_BN_CLICKED(IDC_CD_MENU, OnMenu)
	ON_BN_CLICKED(IDC_CD_NEW, OnNew)
	ON_BN_CLICKED(IDC_CD_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_CD_TOP, OnTop)
	ON_BN_CLICKED(IDC_CD_UP, OnUp)
	ON_BN_CLICKED(IDC_CD_DOWN, OnDown)
	ON_BN_CLICKED(IDC_CD_BOTTOM, OnBottom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAimComboDlg message handlers

void CAimComboDlg::OnItemChangedList (NMHDR* pNMHDR, LRESULT* pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	for (int i = 0 ; i <= 100000 ; ++i);
	DestroyWindow ();

	*pResult = 0;
}

void CAimComboDlg::OnHeaderClickList (NMHDR* pNMHDR, LRESULT* pResult) {
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

BOOL CAimComboDlg::OnInitDialog () {
	CDialog::OnInitDialog();

	m_ctrlList.SetExtendedStyle (LVS_EX_FULLROWSELECT);

	m_btnMenu.m_nIDOn = m_btnMenu.m_nIDOff = IDI_PIC_RIGTHARROW;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAimComboDlg::OnSize (UINT nType, int cx, int cy) {
	CDialog::OnSize(nType, cx, cy);

	if (!this || !m_ctrlList.m_hWnd || !m_ctrlGripper.m_hWnd || !m_btnMenu.m_hWnd)
		return;
	CRect rect;
	GetClientRect (&rect);
	m_ctrlList.SetWindowPos (NULL, 0, 0, rect.Width() - 20, rect.Height (), SWP_NOMOVE | SWP_NOZORDER);
	m_ctrlGripper.SetWindowPos (NULL, rect.Width() - 32, rect.Height() - 32, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	m_btnMenu.SetWindowPos (NULL, rect.Width() - 16, rect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void CAimComboDlg::OnKillFocus (CWnd* pNewWnd) {
	CDialog::OnKillFocus (pNewWnd);
	ReleaseCapture ();
	DestroyWindow ();
}

void CAimComboDlg::OnMenu () {
	CRect rect;
	GetWindowRect (&rect);

	CMenu menu, *popup;
	menu.LoadMenu (m_nMenu);
	popup = menu.GetSubMenu (0);
	popup->TrackPopupMenu (TPM_LEFTALIGN, rect.right - 4, rect.top + 4, this);
}

void CAimComboDlg::OnNew () {
}

void CAimComboDlg::OnDelete () {
}

void CAimComboDlg::OnTop () {
}

void CAimComboDlg::OnUp () {
}

void CAimComboDlg::OnDown () {
}

void CAimComboDlg::OnBottom () {
}
