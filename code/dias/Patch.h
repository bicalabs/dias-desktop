#if !defined(AFX_Patch_H__446C63A1_F994_4A04_B6D2_D8128390C5EC__INCLUDED_)
#define AFX_Patch_H__446C63A1_F994_4A04_B6D2_D8128390C5EC__INCLUDED_

#pragma once

class CPatch : public CObject {
friend class CHash<CPatch*,CPatch>;
friend class CaImAPICollection<CPatch>;
friend class CaImAPICollectionExt<CPatch>;
friend class CDiasAPIPatches;
friend class CImage;
// Construction
	DECLARE_SERIAL (CPatch);
public:
	CPatch ();
	CPatch (const CPatch& obj);
	CPatch (CImage* pDoc, CString name, CString descr);
	~CPatch ();

	CPatch& operator= (const CPatch& obj);

public:
	// Attributes
	CRect		m_rectPatch;
	CPoint		m_pntApex;
	uvar32_64	m_nArea;
	rtbyte		m_rArea;
	uvar32_64	m_nPerim;
	uvar32_64	m_nPerimX;
	uvar32_64	m_nPerimY;
	uvar32_64	m_nPerimXY;
	rtbyte		m_rPerim;
	rtbyte		m_rPerimX;
	rtbyte		m_rPerimY;
	rtbyte		m_rPerimXY;
	rtbyte		m_rCscArea;
	rtbyte		m_rCscPerim;
	uvar32_64	m_nFragments;
	CPoint		m_pntGravCnt;
	rtbyte		m_rGravCntX,
			m_rGravCntY;

	rtbyte		m_rSum;
	rtbyte		m_rSum2;
	rtbyte		m_rMin;
	rtbyte		m_rMax;
	rtbyte		m_rMean;
	rtbyte		m_rStdDev;
	rtbyte*		m_prDistrib;

	rtbyte		m_prFeretsX[64],
			m_prFeretsY[64];
	rtbyte		m_prDiameters[32];
	rtbyte		m_prAngles[32];
	ubyte		m_nDiamMax;
	ubyte		m_nDiamMin;
	rtbyte		m_rDiamMean;
	rtbyte		m_rDiamSigma;

	// Content
	uvar16_32	m_nDimX;
	uvar16_32	m_nDimY;
	ubyte*		m_pbMask;
	uvar32_64	m_dwMskLen;
	uvar32_64*	m_pdwContent;
	uvar32_64	m_dwCntLen;
	uvar32_64*	m_pdwContour;
	uvar32_64	m_dwConLen;

protected:
	CImage*		m_pImg;
	CStorageDoc*	m_pDoc;

	CString		m_strName;
	CString		m_strDescript;

// Operations
public:
	void	Get (uvar32_64 nLength, uvar32_64* pnOffsets) throw (CaImAPIException);
	void	Set (uvar32_64 nLength, uvar32_64* pnOffsets) throw (CaImAPIException);
	void	Calculate (ubyte nChnlNo) throw (CaImAPIException);
	void	Measure ();
	void	Paint (CDC& dc);

protected:
	void	CalculatePerimeter (WORD wX, WORD wY);
	void	CalculateFragments (WORD wX, WORD wY);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPatch)
public:
	void Serialize (CArchive& ar);
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Patch_H__446C63A1_F994_4A04_B6D2_D8128390C5EC__INCLUDED_)
