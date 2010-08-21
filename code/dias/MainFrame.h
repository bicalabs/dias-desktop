// MainFrame.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRAME_H__9BCE11CC_D41E_43DF_86CA_25DF51DCBEF8__INCLUDED_)
#define AFX_MAINFRAME_H__9BCE11CC_D41E_43DF_86CA_25DF51DCBEF8__INCLUDED_

#include "ImgPropBar.h"
#include "MrkPropBar.h"
#include "DiasStatusBar.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDiasApp;
class CDiasStatusBar;

class CMainFrame : public CMDIFrameWnd {
friend class CDiasApp;
friend class CDiasStatusBar;
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:
	void ToolbarMenu (CToolBar& wndToolbar, UINT nID);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
	void Update (udword action);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	UINT		m_nID;
	CImageList	m_ilTbxStd;
	CImageList	m_ilTbxHotStd;
	CImageList	m_ilTbxDisStd;

	CImageList	m_ilTbxImg;
	CImageList	m_ilTbxHotImg;
	CImageList	m_ilTbxDisImg;

	CReBar		m_wndReBar;
	CReBar		m_wndReBox;
	CToolBar	m_wndToolBar;
	CToolBar	m_wndToolBox;

	CImgPropBar	m_barImages;
	CImgPropBar	m_barSurveis;
	CImgPropBar	m_barReports;

	CImgPropBar	m_barPointer;
	CImgPropBar	m_barSelect;
	CImgPropBar	m_barInfo;
	CImgPropBar	m_barZoom;
	CImgPropBar	m_barPatch;
	CImgPropBar	m_barMeter;
	CMrkPropBar	m_barMarkers;
	CImgPropBar	m_barText;

	CDiasStatusBar	m_wndStatusBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg LONG OnColorChange(UINT wParam, LONG lParam);
	afx_msg void OnEditGeomScales();
	afx_msg void OnEditDensScales();
	afx_msg void OnIndGeomScale();
	afx_msg void OnIndDensScale();
	afx_msg void OnUpdate_IndGeomScale(CCmdUI* pCmdUI);
	afx_msg void OnUpdate_IndDensScale(CCmdUI* pCmdUI);
	afx_msg void OnSelectGeomScale (UINT nID);
	afx_msg void OnSelectDensScale (UINT nID);
	afx_msg void OnMarkerStyleAdd();
	afx_msg void OnMarkerStyleDelete();
	afx_msg void OnMarkerStyleExport();
	afx_msg void OnMarkerStyleImport();
	afx_msg void OnMarkerStyleRename();
	afx_msg void OnMarkerStyleDuplicate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRAME_H__9BCE11CC_D41E_43DF_86CA_25DF51DCBEF8__INCLUDED_)
