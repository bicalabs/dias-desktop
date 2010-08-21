// StorageFrame.h : interface of the CStorageFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STORAGEFRAME_H__4724ABC7_761B_4A98_95BD_197CD7EC3639__INCLUDED_)
#define AFX_STORAGEFRAME_H__4724ABC7_761B_4A98_95BD_197CD7EC3639__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DocList.h"
#include "DocPane.h"
#include "StorageView.h"

class CImageWnd;
class CDataWnd;
class CReportWnd;

class CStorageFrame : public CMDIChildWnd {
friend class CHash<CStorageFrame,CStorageFrame>;
friend class CaImAPICollection<CStorageFrame>;
friend class CDiasAPIFrames;
friend class CStorageDoc;
friend class CStorageView;
friend class CImageWnd;
friend class CDataWnd;
friend class CReportWnd;
	DECLARE_DYNCREATE(CStorageFrame)
public:
	CStorageFrame();
	~CStorageFrame();
	CStorageFrame& operator= (const CStorageFrame&) throw (CaImAPIException) { throw (CaImAPIException(0)); };

// Attributes
protected:
	CString		m_strName;
	CString		m_strDescript;

	CStorageView	*m_pView;
	CDocPane	m_barShortcuts;
	CDocList	m_barImages;
	CDocList	m_barData;
	CDocList	m_barReports;

	CImageList	m_imgTypesBig;
	CImageList	m_imgTypesSmall;

	CReBar		m_wndReBar;
	CToolBar	m_wndToolBar;
	CStatusBar	m_wndStatusBar;
	CSplitterWnd	m_wndSplitter;

public:

// Operations
public:
	CStorageDoc& GetDocument ();
	UINT GetActiveImageNo ();
	void SetActiveImageNo (UINT no);
	void EnsureVisibleImageNo (UINT no);
	UINT GetActiveSurveyNo ();
	UINT GetActiveReportNo ();
	POSITION GetFirstSelectedImageNo ();
	int GetNextSelectedImageNo (POSITION& pos);
	POSITION GetFirstSelectedSurveyNo ();
	int GetNextSelectedSurveyNo (POSITION& pos);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStorageFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CStorageFrame)
	afx_msg void OnEditRename();
	afx_msg void OnUpdateEditRename(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePane(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STORAGEFRAME_H__4724ABC7_761B_4A98_95BD_197CD7EC3639__INCLUDED_)
