#include "stdafx.h"
#include "Dias.h"
#include "DocNewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDocNewDlg dialog

CDocNewDlg::CDocNewDlg (CWnd* pParent /*=NULL*/) : CDialog(CDocNewDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CDocNewDlg)
	m_strDimX = _T("");
	m_strDimY = _T("");
	m_strDescription = _T("");
	m_nCount = 0;
	m_strName = _T("");
	//}}AFX_DATA_INIT
}


void CDocNewDlg::DoDataExchange (CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDocNewDlg)
	DDX_Control(pDX, IDC_DN_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_DN_IMPORT, m_btnImport);
	DDX_Control(pDX, IDC_DN_DELETE, m_btnDelete);
	DDX_Control(pDX, IDC_DN_MODELS, m_ctrlModels);
	DDX_Control(pDX, IDC_DN_SOURCE, m_ctrlSource);
	DDX_CBString(pDX, IDC_DN_DIMX, m_strDimX);
	DDX_CBString(pDX, IDC_DN_DIMY, m_strDimY);
	DDX_Text(pDX, IDC_DN_DESCRIPTION, m_strDescription);
	DDX_Text(pDX, IDC_DN_COUNT, m_nCount);
	DDX_Text(pDX, IDC_DN_NAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDocNewDlg, CDialog)
	//{{AFX_MSG_MAP(CDocNewDlg)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDocNewDlg message handlers

BOOL CDocNewDlg::OnInitDialog () {
	CDialog::OnInitDialog ();
	
	m_imgList.Create (16, 16, ILC_COLOR8 | ILC_MASK, 7, 1);
	m_imgList.Add (theApp.LoadBitmap (IDB_IL_COLORMODELS), 0xFFFFFF);
	m_ctrlModels.SetImageList (&m_imgList, LVSIL_SMALL);
	m_ctrlModels.SetExtendedStyle (LVS_EX_FULLROWSELECT);

	m_ctrlModels.InsertColumn (0, theApp.LoadString (IDS_COLORMODEL), LVCFMT_LEFT, 150);
	m_ctrlModels.InsertColumn (1, theApp.LoadString (IDS_CHANNELS), LVCFMT_RIGHT, 90);
	m_ctrlModels.InsertColumn (2, theApp.LoadString (IDS_BPP), LVCFMT_RIGHT, 90);

	m_ctrlModels.InsertItem (0, theApp.LoadString (IDS_CM_BW), 0);
	m_ctrlModels.InsertItem (1, theApp.LoadString (IDS_CM_GRAY), 1);
	m_ctrlModels.InsertItem (2, theApp.LoadString (IDS_CM_RGB), 2);
	m_ctrlModels.InsertItem (3, theApp.LoadString (IDS_CM_CMY), 3);
	m_ctrlModels.InsertItem (4, theApp.LoadString (IDS_CM_CMYK), 4);
	m_ctrlModels.InsertItem (5, theApp.LoadString (IDS_CM_LAB), 5);
	m_ctrlModels.InsertItem (6, theApp.LoadString (IDS_CM_MULTY), 6);

	// Channels count and BPP for BW model
	m_ctrlModels.SetItemText (0, 1, "1");
	m_ctrlModels.SetItemText (0, 2, "1");

	// Channels count and BPP for Grayscale model
	m_ctrlModels.SetItemText (1, 1, "1");
	m_ctrlModels.SetItemText (1, 2, "8");

	// Channels count and BPP for RGB model
	m_ctrlModels.SetItemText (2, 1, "3");
	m_ctrlModels.SetItemText (2, 2, "8");

	// Channels count and BPP for CMY model
	m_ctrlModels.SetItemText (3, 1, "3");
	m_ctrlModels.SetItemText (3, 2, "8");

	// Channels count and BPP for CMYK model
	m_ctrlModels.SetItemText (4, 1, "4");
	m_ctrlModels.SetItemText (4, 2, "8");

	// Channels count and BPP for Lab model
	m_ctrlModels.SetItemText (5, 1, "3");
	m_ctrlModels.SetItemText (5, 2, "8");

	// Channels count and BPP for Multichannel model
	m_ctrlModels.SetItemText (6, 1, "");
	m_ctrlModels.SetItemText (6, 2, "");

	m_ctrlModels.SetItemState (1, LVIS_SELECTED, LVIS_SELECTED);
	m_ctrlModels.EnsureVisible (1, false);
	
	m_strDimX = "768";
	m_strDimY = "576";

	CButton *btn = (CButton*)GetDlgItem (IDC_DN_CREATE_MANUAL);
	btn->SetCheck (1);

	UpdateData (false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDocNewDlg::OnOK () {
	UpdateData (true);
	m_nModel = aimGetSelListItem (m_ctrlModels, true);
	CDialog::OnOK();
}

void CDocNewDlg::OnDrawItem (int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) {
	uint action = lpDrawItemStruct->itemState;
	CDC* pDC = new CDC ();
	pDC->Attach (lpDrawItemStruct->hDC);
	CRect rectItem = lpDrawItemStruct->rcItem;
/*	switch (nIDCtl) {
	}*/
	pDC->Detach ();
	delete pDC;
}
