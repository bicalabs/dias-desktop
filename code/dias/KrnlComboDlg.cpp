// KrnlComboDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dias.h"
#include "KrnlComboDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKrnlComboDlg dialog

CKrnlComboDlg::CKrnlComboDlg(CWnd* pParent /*=NULL*/)
	: CAimComboDlg(pParent) {
	//{{AFX_DATA_INIT(CKrnlComboDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_ilKernels.Create (16, 16, ILC_COLOR8 | ILC_MASK, 4, 1);
	m_ilKernels.Add (theApp.LoadBitmap (IDB_MARKER_KRNLSTYLE_NONE), 0xFFFFFF);
	m_ilKernels.Add (theApp.LoadBitmap (IDB_MARKER_KRNLSTYLE_ROUND), 0xFFFFFF);
	m_ilKernels.Add (theApp.LoadBitmap (IDB_MARKER_KRNLSTYLE_X), 0xFFFFFF);
	m_ilKernels.Add (theApp.LoadBitmap (IDB_MARKER_KRNLSTYLE_CROSS), 0xFFFFFF);

	m_nMenu = IDR_POPUP_MARKER_KRNLSTYLE;
}


void CKrnlComboDlg::DoDataExchange(CDataExchange* pDX)
{
	CAimComboDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKrnlComboDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKrnlComboDlg, CAimComboDlg)
	//{{AFX_MSG_MAP(CKrnlComboDlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CD_LIST, OnItemChangedList)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKrnlComboDlg message handlers

BOOL CKrnlComboDlg::OnInitDialog () {
	CAimComboDlg::OnInitDialog();

	ModifyStyle (WS_CAPTION | WS_SYSMENU, 0);
	ModifyStyleEx (WS_EX_TOOLWINDOW, 0);

	m_blLock = true;
	m_ctrlList.SetImageList (&m_ilKernels, LVSIL_SMALL);
	m_ctrlList.InsertColumn (0, theApp.LoadString (IDS_MRKKRNL_NAME), LVCFMT_LEFT, 75, 0);
	m_ctrlList.InsertItem (0, theApp.LoadString (IDS_MARKER_KRNLSTYLE_NONE), 0);
	m_ctrlList.InsertItem (1, theApp.LoadString (IDS_MARKER_KRNLSTYLE_ROUND), 1);
	m_ctrlList.InsertItem (2, theApp.LoadString (IDS_MARKER_KRNLSTYLE_X), 2);
	m_ctrlList.InsertItem (3, theApp.LoadString (IDS_MARKER_KRNLSTYLE_CROSS), 3);

	m_ctrlList.SetItemState (int(theApp.MarkStyles[aimActive].GetStyle().GetKernel ()), LVIS_SELECTED, LVIS_SELECTED);
	m_ctrlList.EnsureVisible (int(theApp.MarkStyles[aimActive].GetStyle().GetKernel ()), false);
	m_blLock = false;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CKrnlComboDlg::OnItemChangedList (NMHDR* pNMHDR, LRESULT* pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;

	CMark mrk = theApp.MarkStyles[aimActive].GetStyle ();
	theApp.MarkStyles[aimActive].SetStyle (CMark (NULL, mrk.GetPoint (), (CMark::MarkKernel)(aimGetSelListItem (m_ctrlList, false)),
	                                              mrk.GetKernelSize (), mrk.GetKernelColor (),
	                                              mrk.GetShape (), mrk.GetShapeSize (), mrk.GetAngle (),
	                                              mrk.GetSizeLock (), mrk.GetAngleLock (),
	                                              mrk.GetShapeColor (), mrk.GetFillColor ()));

	if (m_blLock)	return;
	SetTimer (1, 500, NULL);
}

void CKrnlComboDlg::OnTimer (UINT nIDEvent) {
	CAimComboDlg::OnTimer(nIDEvent);
	ShowWindow (false);
	KillTimer (nIDEvent);
}


void CKrnlComboDlg::Update () {
}
