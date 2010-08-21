#if !defined(AFX_CAPTUREDLG_H__D624FBE7_FA1B_42E9_A647_B71169C49B5E__INCLUDED_)
#define AFX_CAPTUREDLG_H__D624FBE7_FA1B_42E9_A647_B71169C49B5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CaptureDlg.h : header file
//

#include <grabber/grabber.h>
#include "TxtBtnCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CCaptureDlg dialog

class CCaptureDlg : public CDialog {
friend class CStorageDoc;
// Construction
public:
	CCaptureDlg(CWnd* pParent = NULL);   // standard constructor

	uvar32_64	m_nSize;

protected:
	CStorageDoc	*m_pDoc;

	ubyte	*m_pRaw;
	rtbyte	*m_pIntegr;
	HMODULE m_hDLLModule;
	bool	m_blLive;
	// function pointer of grabber.dll functions
	TgrabOptions		grabOptions;
	TgrabLive		grabLive;
	TgrabStopLive		grabStopLive;
	TgrabSnap		grabSnap;
	TgrabClose		grabClose;
	TgrabSetLiveWindow	grabSetLiveWindow;

	LPIMAGE m_pImage;
	BOOL	m_blVideoOn;

	void CloseGrabberDLL();
	BOOL OpenGrabberDLL();
	void Capture ();

// Dialog Data
	//{{AFX_DATA(CCaptureDlg)
	enum { IDD = IDD_CAPTURE };
	CTxtBtnCtrl	m_btnSave;
	CTxtBtnCtrl	m_btnImport;
	CTxtBtnCtrl	m_btnDelete;
	CEdit	m_ctrlNo;
	CButton	m_btnToggle;
	CStatic	m_wndLive;
	BOOL	m_blAuto;
	CString	m_strName;
	DWORD	m_nNo;
	BOOL	m_blSeq;
	BOOL	m_blSeqUni;
	UINT	m_nSeqNo;
	UINT	m_nStep;
	BOOL	m_blVideo;
	UINT	m_nSec;
	BOOL	m_blIntegr;
	UINT	m_nIntegrNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaptureDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCaptureDlg)
	afx_msg void OnCaptureCapture();
	afx_msg void OnCaptureToggle();
	afx_msg void OnCaptureOptions();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	afx_msg void OnCaptureAutoname();
	afx_msg void OnCapturePostop();
	afx_msg void OnCapturePosend();
	afx_msg void OnCapturePosbefore();
	afx_msg void OnCapturePosafter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPTUREDLG_H__D624FBE7_FA1B_42E9_A647_B71169C49B5E__INCLUDED_)
