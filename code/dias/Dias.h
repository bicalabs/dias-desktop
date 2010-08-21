// Dias.h : main header file for the DIAS application
//

#if !defined(AFX_DIAS_H__F221ED01_A898_4346_B0BD_9193F5E92879__INCLUDED_)
#define AFX_DIAS_H__F221ED01_A898_4346_B0BD_9193F5E92879__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#define _AIM_MAINMODULE

#include "resource.h"       // main symbols
#include "DiasAPI.h"
#include "Settings.h"
#include <tesla\tesla.h>


#define	UPDHA_MODE	0x00000001
#define	UPDHA_DENSSCALE	0x00000002
#define	UPDHA_GEOMSCALE	0x00000004
#define	UPDHA_MARKSTYLE	0x00000008
#define	UPDHA_IMAGE	0x00000010
#define	UPDHA_MARK	0x00000020
#define	UPDHA_PATCH	0x00000040
#define	UPDHA_TEXT	0x00000080
#define	UPDHA_METER	0x00000100
#define	UPDHA_SURVEY	0x00001000
#define	UPDHA_FIELD	0x00002000

#define	OBJT_IMAGE	0x00000001
#define	OBJT_CHANNEL	0x00000002
#define	OBJT_PATCH	0x00000003
#define	OBJT_MARK	0x00000004
#define	OBJT_TEXT	0x00000005
#define	OBJT_METER	0x00000006
#define	OBJT_SURVEY	0x00000007
#define	OBJT_FIELD	0x00000008

/////////////////////////////////////////////////////////////////////////////
// CDiasApp:
// See Dias.cpp for the implementation of this class
//

class CMainFrame;

class CDiasApp : public CWinApp {
// Constructors
public:
	CDiasApp();

// Attributes
public:
	CDiasAPIDocs		Documents;
	CDiasAPIDensScales	DensScales;
	CDiasAPIGeomScales	GeomScales;
	CDiasAPIMarkStyles	MarkStyles;

protected:
	CArray<CBitmap*,CBitmap*>	m_bmpaLoad;

public:
	enum EditModes { emiPtr = 000, emiHand = 001,
			 emiSelect = 100,
			 emiInfo = 200,
			 emiIn = 300, emiOut = 301,
	                 emiIobjCreate = 400, emiIobjCng = 401, emiIobjPtr = 402,
			 emiMeter = 500,
			 emiMrkCreate = 600, emiMrkPtr = 601, emiMrkSel = 602,
			 emiTextCreate = 700, emiTextPtr = 701 };
protected:
	EditModes	m_nMode;
	CMainFrame*	m_pMainFrame;
	uvar32_64	m_nObjects[OBJT_FIELD];

// Operations
public:
	CString LoadString (UINT nID);
	CBitmap* LoadBitmap (UINT nID);
	void PrepareMenu (CMenu* pMenu);

	void Update (udword action);

	EditModes GetMode ();
	void SetMode (EditModes mode);
	void MacroStart (CString strName);
	void MacroStop ();
	void MacroPause ();
	void StatusText (CString strText);
	void StatusState (UINT nID);
	void ObjectsAdd (udword type, CObject* obj);
	void ObjectsRemove (udword type, CObject* obj);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiasApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDiasApp)
	afx_msg void OnAppAbout();
	afx_msg void OnToolboxPtr();
	afx_msg void OnToolboxHand();
	afx_msg void OnToolboxSelect();
	afx_msg void OnToolboxInfo();
	afx_msg void OnToolboxZoomIn();
	afx_msg void OnToolboxZoomOut();
	afx_msg void OnToolboxIobjCreate();
	afx_msg void OnToolboxIobjCng();
	afx_msg void OnToolboxIobjPtr();
	afx_msg void OnToolboxMeter();
	afx_msg void OnToolboxMarkCreate();
	afx_msg void OnToolboxMarkPtr();
	afx_msg void OnToolboxMarkSel();
	afx_msg void OnToolboxTextCreate();
	afx_msg void OnToolboxTextPtr();
	afx_msg void OnUpdateToolboxPtr(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolboxHand(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolboxSelect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolboxInfo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolboxZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolboxZoomOut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolboxIobjCreate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolboxIobjCng(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolboxIobjPtr(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolboxMeter(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolboxMarkCreate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolboxMarkPtr(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolboxMarkSel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolboxTextCreate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolboxTextPtr(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#include "../include/util.h"

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIAS_H__F221ED01_A898_4346_B0BD_9193F5E92879__INCLUDED_)
