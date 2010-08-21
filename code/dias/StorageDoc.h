#if !defined(AFX_STORAGEDOC_H__5342298A_EAA3_4A71_A950_0E88A2C270A5__INCLUDED_)
#define AFX_STORAGEDOC_H__5342298A_EAA3_4A71_A950_0E88A2C270A5__INCLUDED_

#pragma once

#include "DiasAPIImages.h"
#include "DiasAPISurveis.h"
#include "DiasAPIFrames.h"

class CStorageFrame;
class CStorageView;

class CCaptureDlg;

class CStorageDoc : public CDocument {
friend class CCaptureDlg;
friend class CHash<CStorageDoc,CStorageDoc&>;
friend class CaImAPICollection<CStorageDoc>;
friend class CPatch;
friend class CImage;
friend class CSurvey;
friend class CReport;
friend class CChannel;
friend class CMark;
friend class CPatch;
// Contstruction
protected: // create from serialization only
	CStorageDoc ();
	DECLARE_DYNCREATE(CStorageDoc)
public:
	virtual ~CStorageDoc ();

	CDiasAPIImages	Images;
	CDiasAPISurveis	Surveis;
//	CDiasAPIReports	Reports;
	CDiasAPIFrames	Frames;

// Configuration
protected:
	// Pure document settings for all views
	bool		m_blAcceptFromView;
	bool		m_blForceSettings;
	bool		m_blShowImages;
	bool		m_blShowPatches;
	bool		m_blShowMarks;
	bool		m_blShowMeters;
	bool		m_blImgVRuler;
	bool		m_blImgHRuler;
	bool		m_blImgGrid;
	bool		m_blRptVRuler;
	bool		m_blRptHRuler;
	bool		m_blRptGrid;
	// View owened settings copied to document from the last closed view
	ubyte		m_nImgZoom;
	ubyte		m_nRptZoom;
	CRect		m_rectPlacement;
	uint		m_nPanelWidth;
	ubyte		m_nPanelActive;
	bool		m_blShowNames;
	uvar32_64	m_nImgNo;
	uvar32_64	m_nDataNo;
	uvar32_64	m_nRptNo;

	CImage			*m_pImgTmp;
	CChannel		*m_pCnlTmp;
	CPatch			*m_pPchTmp;
	CMark			*m_pMrkTmp;

	// Internal structures
	CCaptureDlg	*m_pdlgCapture;

// Attributes
protected:
	// #### TODO: Add LUT table support
	CString		m_strName;
	CString		m_strDescript;
	CMapStringToString	m_mapInfo;
	ColorModel	m_nColorModel;
	ubyte		m_nChannels;
	ubyte		m_nBPP;
	uvar16_32	m_nDimX;
	uvar16_32	m_nDimY;

// Operations
public:
	bool		GetSetting (CString name) throw (CaImAPIException);
	void		SetSetting (CString name, bool value) throw (CaImAPIException);
	uvar16_32	GetDimX ();
	uvar16_32	GetDimY ();
	bool		SetDims (uvar16_32 nDim, bool blStretch, bool blVerbal = false);
	ubyte		GetChannelsCount ();
	ColorModel	GetColorModel ();
	bool		SetColorModel (ColorModel cm);

	void	Save ();
	void	SaveAs (CString name, bool verbal = true);
	void	Close (bool blAsk = true, bool blSave = true);
	void	Clear (bool blSave = false);
	CString	GetInfo (const CString name);
	void	SetInfo (const CString name, const CString value);
	void	Update (CUpdateHint::UpdateTarget tgt, udword cmd, udword start = 0, udword end = 0);
	void	UpdateAll ();

protected:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStorageDoc)
	public:
	virtual void DeleteContents();
	virtual void Serialize(CArchive& ar);
	virtual void OnChangedViewList();
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CStorageDoc)
	afx_msg void OnImageAdd();
	afx_msg void OnImageAddSequence();
	afx_msg void OnImageAcquireCamera();
	afx_msg void OnImageImport();
	afx_msg void OnImageExport();
	afx_msg void OnSurveyAdd();
	afx_msg void OnDocRemove();
	afx_msg void OnDocUp();
	afx_msg void OnDocDown();
	afx_msg void OnDocPrev();
	afx_msg void OnDocNext();
	afx_msg void OnDocProp();
	afx_msg void OnDocStyle();
	afx_msg void OnImageArithmAdd();
	afx_msg void OnToolsPlugins1();
	afx_msg void OnToolsPlugins2();
	afx_msg void OnImageAdjustNormalize();
	afx_msg void OnImageSegSegment();
	afx_msg void OnImageSegErode();
	afx_msg void OnImageEdgesLaplacian();
	afx_msg void OnUpdateImageAcquireCamera(CCmdUI* pCmdUI);
	afx_msg void OnSurveyMeasure();
	afx_msg void OnToolsPlugins3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STORAGEDOC_H__5342298A_EAA3_4A71_A950_0E88A2C270A5__INCLUDED_)
