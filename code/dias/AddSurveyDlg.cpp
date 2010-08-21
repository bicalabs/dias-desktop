// AddSurveyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dias.h"
#include "AddSurveyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddSurveyDlg dialog


CAddSurveyDlg::CAddSurveyDlg (CWnd* pParent) : CDialog(CAddSurveyDlg::IDD, pParent) {
	m_btnUp.m_nIDOn = m_btnUp.m_nIDOff = IDI_PIC_UP;
	m_btnDown.m_nIDOn = m_btnDown.m_nIDOff = IDI_PIC_DOWN;
	m_btnRemove.m_nIDOn = m_btnRemove.m_nIDOff = IDI_PIC_REMOVE;

	//{{AFX_DATA_INIT(CAddSurveyDlg)
	//}}AFX_DATA_INIT
}


void CAddSurveyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddSurveyDlg)
	DDX_Control(pDX, IDC_DAS_DESCRIPT, m_ctrlDescript);
	DDX_Control(pDX, IDC_DAS_OBJECT, m_ctrlObject);
	DDX_Control(pDX, IDC_DAS_REMOVE, m_btnRemove);
	DDX_Control(pDX, IDC_DAS_DOWN, m_btnDown);
	DDX_Control(pDX, IDC_DAS_UP, m_btnUp);
	DDX_Control(pDX, IDC_DAS_LIST, m_ctrlList);
	DDX_Control(pDX, IDC_DAS_TREE, m_ctrlTree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddSurveyDlg, CDialog)
	//{{AFX_MSG_MAP(CAddSurveyDlg)
	ON_NOTIFY(TVN_SELCHANGED, IDC_DAS_TREE, OnSelChangedTree)
	ON_NOTIFY(NM_SETFOCUS, IDC_DAS_TREE, OnSetFocusTree)
	ON_NOTIFY(NM_SETFOCUS, IDC_DAS_LIST, OnSetFocusList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_DAS_LIST, OnItemChangedList)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_DAS_LIST, OnEndLabelEditList)
	ON_BN_CLICKED(IDC_DAS_UP, OnUp)
	ON_BN_CLICKED(IDC_DAS_DOWN, OnDown)
	ON_BN_CLICKED(IDC_DAS_REMOVE, OnRemove)
	ON_CBN_SELCHANGE(IDC_DAS_OBJECT, OnSelchangeObject)
	ON_BN_CLICKED(IDC_DAS_LOAD, OnLoad)
	ON_BN_CLICKED(IDC_DAS_SAVE, OnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddSurveyDlg message handlers

BOOL CAddSurveyDlg::OnInitDialog () {
	CDialog::OnInitDialog();

	m_ilTypes.Create (16, 16, ILC_COLOR8 | ILC_MASK, 4, 1);
	m_ilTypes.Add (theApp.LoadBitmap (IDB_IL_FIELDTYPES), 0xFFFFFF);
	m_ctrlTree.SetImageList (&m_ilTypes, TVSIL_NORMAL);
	m_ctrlList.SetImageList (&m_ilTypes, LVSIL_SMALL);
	m_ilObjects.Create (16, 16, ILC_COLOR8 | ILC_MASK, 4, 1);
	m_ilObjects.Add (theApp.LoadBitmap (IDB_IL_OBJECTS), 0xFFFFFF);
	m_ctrlObject.SetImageList (&m_ilObjects);

	char pszName[1024];
	COMBOBOXEXITEM cbitem = {CBEIF_TEXT | CBEIF_IMAGE | CBEIF_SELECTEDIMAGE | CBEIF_INDENT, 0, pszName, 1024, 0, 0, 0, 0, 0};
	strcpy (pszName, LPCTSTR (theApp.LoadString (IDS_DLG_DAS_IMG)));
	m_ctrlObject.SetItem (&cbitem);

	cbitem.iIndent = 1;
	strcpy (pszName, LPCTSTR (theApp.LoadString (IDS_DLG_DAS_CHNL)));
	cbitem.iItem = cbitem.iImage = cbitem.iSelectedImage = cbitem.iOverlay = 1;
	m_ctrlObject.SetItem (&cbitem);

	strcpy (pszName, LPCTSTR (theApp.LoadString (IDS_DLG_DAS_PTCH)));
	cbitem.iItem = cbitem.iImage = cbitem.iSelectedImage = cbitem.iOverlay = 2;
	m_ctrlObject.SetItem (&cbitem);

	strcpy (pszName, LPCTSTR (theApp.LoadString (IDS_DLG_DAS_MRK)));
	cbitem.iItem = cbitem.iImage = cbitem.iSelectedImage = cbitem.iOverlay = 3;
	m_ctrlObject.SetItem (&cbitem);
	m_nObject = 1;
	m_ctrlObject.SetCurSel (2);

	m_ctrlList.SetExtendedStyle (LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ctrlList.InsertColumn (0, theApp.LoadString (IDS_DLG_DAS_FIELDCAPTION), LVCFMT_LEFT, 80, 0);
	m_ctrlList.InsertColumn (1, theApp.LoadString (IDS_DLG_DAS_FIELDNAME), LVCFMT_LEFT, 125, 1);
	m_ctrlList.InsertColumn (2, theApp.LoadString (IDS_DLG_DAS_UNIT), LVCFMT_CENTER, 60, 1);
	UpdateTree ();
	return TRUE;
}

void CAddSurveyDlg::OnOK () {
	uvar32_64 n, len = m_ctrlList.GetItemCount ();
	for (n = 0 ; n < len ; ++n) {
		CField *pField = new CField (m_pSurvey, m_ctrlList.GetItemText (n, 0),
		                             theTesla.Variables[m_ctrlTree.GetItemData ((HTREEITEM)(m_ctrlList.GetItemData (n)))].GetName (),
		                             theTesla.Variables[m_ctrlTree.GetItemData ((HTREEITEM)(m_ctrlList.GetItemData (n)))].GetDescr ());
		m_pSurvey->Fields.Add (*pField);
	}
	CDialog::OnOK();
}

void CAddSurveyDlg::OnCancel () {
	CDialog::OnCancel();
}

void CAddSurveyDlg::OnLoad () {
	// #### TODO> Implement
}

void CAddSurveyDlg::OnSave () {
	// #### TODO> Implement
}

void CAddSurveyDlg::OnSelchangeObject () {
	UpdateTree ();
}

void CAddSurveyDlg::OnSelChangedTree (NMHDR* pNMHDR, LRESULT* pResult) {
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	UpdateList ();
	if (!m_ctrlTree.GetSelectedItem() || !m_ctrlTree.GetItemData (m_ctrlTree.GetSelectedItem()))
		return;
	m_ctrlDescript.SetWindowText (theTesla.Variables[m_ctrlTree.GetItemData (m_ctrlTree.GetSelectedItem ())].GetDescr ());
	*pResult = 0;
}

void CAddSurveyDlg::OnItemChangedList(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	svar32_64 i;
	if ((i = aimGetSelListItem (m_ctrlList, 0)) == -1)	return;
	m_ctrlDescript.SetWindowText (theTesla.Variables[m_ctrlTree.GetItemData ((HTREEITEM)(m_ctrlList.GetItemData (i)))].GetDescr ());
	*pResult = 0;
}

void CAddSurveyDlg::OnSetFocusTree (NMHDR* pNMHDR, LRESULT* pResult) {
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;
	if (!m_ctrlTree.GetSelectedItem() || !m_ctrlTree.GetItemData (m_ctrlTree.GetSelectedItem()))
		return;
	m_ctrlDescript.SetWindowText (theTesla.Variables[m_ctrlTree.GetItemData (m_ctrlTree.GetSelectedItem ())].GetDescr ());
}

void CAddSurveyDlg::OnSetFocusList (NMHDR* pNMHDR, LRESULT* pResult) {
	svar32_64 i;
	if ((i = aimGetSelListItem (m_ctrlList, 0)) == -1)	return;
	m_ctrlDescript.SetWindowText (theTesla.Variables[m_ctrlTree.GetItemData ((HTREEITEM)(m_ctrlList.GetItemData (i)))].GetDescr ());
	*pResult = 0;
}

void CAddSurveyDlg::OnEndLabelEditList (NMHDR* pNMHDR, LRESULT* pResult) {
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	*pResult = 0;

	if ((pDispInfo->item.mask & LVIF_TEXT) == 0)
		return;

	uvar32_64 selected = aimGetSelListItem (m_ctrlList, false);
	m_ctrlList.SetItemText (selected, 0, pDispInfo->item.pszText);
}

void CAddSurveyDlg::OnUp () {
	svar32_64 i, n;
	char *text = new char[1024];
	m_btnUp.m_nState = 1;
	if ((i = aimGetSelListItem (m_ctrlList, 0)) == -1 || i == 0)
		return;
	for (n = 0 ; n < m_claItems.GetSize (); ++n)
		if (((CFieldInfo*)(m_ctrlList.GetItemData (i)))->GetName () == m_ctrlTree.GetItemText (m_claItems[n]))
			break;
	LVITEM item = {LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM|LVIF_STATE, i, 0, 0, LVIS_FOCUSED|LVIS_SELECTED, text, 1024, 0, 0, 0};
	m_ctrlList.GetItem (&item);
	m_ctrlList.DeleteItem (i);
	item.iItem = --i;
	m_ctrlList.InsertItem (&item);
	m_ctrlList.SetItemText (i, 1, m_ctrlTree.GetItemText
			              (m_ctrlTree.GetParentItem (m_ctrlTree.GetParentItem
			                                         (m_claItems[n])))
			              + "." + m_ctrlTree.GetItemText (m_claItems[n]));
	m_ctrlList.SetItemText (i, 2, ((CFieldInfo*)(m_ctrlTree.GetItemData (m_claItems[n])))->GetUnits ());
}

void CAddSurveyDlg::OnDown () {
	svar32_64 i, n;
	char *text = new char[1024];
	m_btnDown.m_nState = 1;
	if ((i = aimGetSelListItem (m_ctrlList, 0)) == -1 || i == m_ctrlList.GetItemCount () - 1)
		return;
	for (n = 0 ; n < m_claItems.GetSize (); ++n)
		if (((CFieldInfo*)(m_ctrlList.GetItemData (i)))->GetName () == m_ctrlTree.GetItemText (m_claItems[n]))
			break;
	LVITEM item = {LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM|LVIF_STATE, i, 0, 0, LVIS_FOCUSED|LVIS_SELECTED, text, 1024, 0, 0, 0};
	m_ctrlList.GetItem (&item);
	m_ctrlList.DeleteItem (i);
	item.iItem = ++i;
	m_ctrlList.InsertItem (&item);
	m_ctrlList.SetItemText (i, 1, m_ctrlTree.GetItemText
			              (m_ctrlTree.GetParentItem (m_ctrlTree.GetParentItem
			                                         (m_claItems[n])))
			              + "." + m_ctrlTree.GetItemText (m_claItems[n]));
	m_ctrlList.SetItemText (i, 2, ((CFieldInfo*)(m_ctrlTree.GetItemData (m_claItems[n])))->GetUnits ());
}

void CAddSurveyDlg::OnRemove () {
	m_btnRemove.m_nState = 1;
	svar32_64 i, n;
	if ((i = aimGetSelListItem (m_ctrlList, 0)) == -1)	return;
	for (n = 0 ; n < m_claItems.GetSize (); ++n)
		if (((CFieldInfo*)(m_ctrlList.GetItemData (i)))->GetName () == m_ctrlTree.GetItemText (m_claItems[n])) {
			m_ctrlTree.SetCheck (m_claItems[n], false);
			m_ctrlTree.SetCheck (m_ctrlTree.GetParentItem (m_claItems[n]), false);
			m_ctrlTree.SetCheck (m_ctrlTree.GetParentItem (m_ctrlTree.GetParentItem (m_claItems[n])), false);
		}
	m_ctrlList.DeleteItem (i);
}

void CAddSurveyDlg::UpdateTree () {
	if (m_ctrlObject.GetCurSel () == m_nObject)
		return;
	if (m_ctrlList.GetItemCount () &&
	    MessageBox (theApp.LoadString (IDS_MBTEXT_ADDSRVDLG), theApp.LoadString (IDS_MBTITLE_WARNING), MB_OKCANCEL | MB_ICONWARNING) != IDOK) {
		m_ctrlObject.SetCurSel (m_nObject);
		return;
	}
	m_claRoots.RemoveAll ();
	m_claItems.RemoveAll ();
	m_ctrlTree.DeleteAllItems ();
	m_ctrlList.DeleteAllItems ();

	CString strObject, strName;
	uvar32_64 nIDs[7] = {IDS_DLG_DAS_APP, IDS_DLG_DAS_DOC, IDS_DLG_DAS_IMG, IDS_DLG_DAS_CHNL, IDS_DLG_DAS_PTCH, IDS_DLG_DAS_MRK, IDS_DLG_DAS_USR};
	HTREEITEM hRoot, hChild, hItem;

	m_ctrlObject.GetLBText (m_ctrlObject.GetCurSel (), strObject);

	uvar32_64 n1 = 6, n2, cnt = theTesla.Variables.GetCount ();
	do {
		if (strObject != (strName = theApp.LoadString (nIDs[6 - n1]))
		    && strName != theApp.LoadString (IDS_DLG_DAS_APP)
		    && strName != theApp.LoadString (IDS_DLG_DAS_DOC)
		    && strName != theApp.LoadString (IDS_DLG_DAS_IMG)
		    && strName != theApp.LoadString (IDS_DLG_DAS_USR))
			continue;
		m_claRoots.Add (hRoot = m_ctrlTree.InsertItem (theApp.LoadString (nIDs[6 - n1]), 3, 3));
		m_claRoots.Add (hChild = m_ctrlTree.InsertItem (theApp.LoadString (IDS_DLG_DAS_USR), 5, 5, hRoot));
		for (n2 = 0; n2 < cnt; ++n2) {
			if (theTesla.Variables[n2].GetClassName () != theApp.LoadString (nIDs[6 - n1]))
				continue;
			m_claItems.Add (hItem = m_ctrlTree.InsertItem (theTesla.Variables[n2].GetEndName (),
			                                              (uint)(theTesla.Variables[n2].GetType ()),
			                                              (uint)(theTesla.Variables[n2].GetType ()), hChild));
			m_ctrlTree.SetItemData (hItem, n2);
		}
	} while (n1--);

/*	CFieldInfo *pField;
	HTREEITEM item, child, value;
	for (uvar32_64 n = 0, cnt = theSettings.m_prootFieldInfo->GetCount (); n < cnt; ++n) {
		pField = &(theSettings.m_prootFieldInfo->GetDataAt(n));
		CString curname, name = pField->GetName ();
		m_ctrlObject.GetLBText (m_ctrlObject.GetCurSel (), curname);
		if (name != "Image" && name != "Document" && name != curname)
			continue;
		item = m_ctrlTree.InsertItem (name, 3, 3);
		m_ctrlTree.SetItemData (item, (ulong)pField);
		m_claRoots.Add (item);
		if (theSettings.m_prootFieldInfo->GetAt(n)->GetChild())
			for (uvar32_64 n2 = 0, cnt2 = theSettings.m_prootFieldInfo->GetAt(n)->GetChild()->GetCount (); n2 < cnt2; ++n2) {
				pField = &(theSettings.m_prootFieldInfo->GetAt(n)->GetChild()->GetDataAt(n2));
				child = m_ctrlTree.InsertItem (pField->GetName(), 3, 3, item);
				m_ctrlTree.SetItemData (child, (ulong)pField);
				m_claRoots.Add (child);
				if (theSettings.m_prootFieldInfo->GetAt(n)->GetChild()->GetAt(n2)->GetChild())
					for (uvar32_64 n3 = 0, cnt3 = theSettings.m_prootFieldInfo->GetAt(n)->GetChild()->GetAt(n2)->GetChild()->GetCount (); n3 < cnt3; ++n3) {
						pField = &(theSettings.m_prootFieldInfo->GetAt(n)->GetChild()->GetAt(n2)->GetChild()->GetDataAt(n3));
						value = m_ctrlTree.InsertItem (pField->GetName (), pField->GetType (), pField->GetType (), child);
						m_ctrlTree.SetItemData (value, (ulong)pField);
						m_claItems.Add (value);
					}
			}
		m_ctrlTree.Expand (item, TVE_EXPAND);
	}*/
	m_nObject = m_ctrlObject.GetCurSel ();
}

void CAddSurveyDlg::UpdateList () {
	int i;
	bool bl = false;
	HTREEITEM item;
	uvar32_64 n, pos, lent = m_claItems.GetSize (), lenr = m_claRoots.GetSize ();
	for (n = 0; n < lenr; ++n, bl = false) {
		if (m_ctrlTree.GetCheck (m_claRoots[n])) {
			for (item = m_ctrlTree.GetChildItem (m_claRoots[n]); item; item = m_ctrlTree.GetNextSiblingItem (item)) {
				if (!m_ctrlTree.GetCheck (item))
					bl = true;
				m_ctrlTree.SetCheck (item);
			}
			if (bl) UpdateList ();
		}
	}
	m_ctrlList.DeleteAllItems ();
	for (n = 0; n < lent; ++n) {
		if (m_ctrlTree.GetCheck (m_claItems[n])) {
//			for (m = 0; m < m_ctrlList.GetItemCount (); ++m)
//				if (m_ctrlList.GetItemData (m) == (ulong)(m_claItems[n]))
//					goto cont;
			pos = m_ctrlTree.GetItemData (m_claItems[n]);
			i = m_ctrlList.InsertItem (0, theTesla.Variables[pos].GetEndName (),
			                           theTesla.Variables[pos].GetType ());
			m_ctrlList.SetItemText (i, 1, theTesla.Variables[pos].GetName ());
			m_ctrlList.SetItemText (i, 2, theTesla.Variables[pos].GetUnits ());
			m_ctrlList.SetItemData (i, (ulong)(m_claItems[n]));
		}/* else
			for (m = 0; m < m_ctrlList.GetItemCount (); ++m)
				if (m_ctrlList.GetItemData (m) == (ulong)(m_claItems[n]))
					m_ctrlList.DeleteItem (m);*/
//cont:;
	}
}
