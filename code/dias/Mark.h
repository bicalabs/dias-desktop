#if !defined(AFX_MARK_H__747203DB_E4EA_4C7D_840E_37FC8D867847__INCLUDED_)
#define AFX_MARK_H__747203DB_E4EA_4C7D_840E_37FC8D867847__INCLUDED_

#pragma once

class CImageWnd;

class CMark : public CObject {
friend class CMrkPropBar;
friend class CHash<CMark*,CMark>;
friend class CaImAPICollection<CMark>;
friend class CaImAPICollectionExt<CMark>;
friend class CDiasAPIMarks;
friend class CImage;
friend class CSettings;
friend class CImageWnd;
// Construction
	DECLARE_SERIAL (CMark);
public:
	enum	MarkKernel { krnlNone = 0, krnlRound = 1, krnlX = 2, krnlPlus = 3 };
	enum	MarkShape { shpNone = 0, shpEllipse = 1, shpTriangle = 2, shpRect = 3 };
	enum	MarkPoint { pntNone, pntCenter, pntAxisX, pntAxisY, pntAxisXY };
public:
	CMark ();
	CMark (CImage* pImg, svar16_32 x, svar16_32 y, const CMark& deflt);
	CMark (CImage* pImg, CPoint& pos, const CMark& deflt);
	CMark (CImage* pImg, CPoint& pos, MarkKernel krnl, uvar16_32 ksize, COLORREF kc, 
	       MarkShape shp, CSize& ssize, ubyte angle, bool slock, bool alock, COLORREF sc, COLORREF fc);
	CMark (const CMark& mrk);
	~CMark ();

	CMark& operator= (const CMark& src);

// Attributes
protected:
	CImage*		m_pImg;

	bool		m_blSelected;
	bool		m_blVisible;

	svar16_32	m_iPosX;
	svar16_32	m_iPosY;

	MarkKernel	m_nKernel;
	uvar16_32	m_nKrnlSize;
	COLORREF	m_dwKrnlColor;

	MarkShape	m_nShape;
	uvar16_32	m_nShapeSizeX;
	uvar16_32	m_nShapeSizeY;
	sword		m_nShapeAngle;
	bool		m_blShapeSizeLock;
	bool		m_blShapeAngleLock;
	COLORREF	m_dwShapeColor;
	COLORREF	m_dwShapeFill;

	CPoint		*m_pptPoints;
	CPoint		m_pntAxisX;
	CPoint		m_pntAxisY;
	CPoint		m_pntAxisXY;

// Operations
public:
	svar32_64	GetPos ();
	void		Show (bool blShow = true);
	void		Select (bool blSelect = true);
	void		Paint (CDC& dc);
	void		PaintKernel (CDC& pDC);
	void		PaintShape (CDC& pDC);
	void		PaintFill (CDC& pDC);
	MarkPoint	GetPointType (CPoint pnt);

	inline MarkKernel	GetKernel () { return (m_nKernel); };
	inline MarkShape	GetShape () { return (m_nShape); };
	inline uvar16_32	GetKernelSize () { return (m_nKrnlSize); };
	inline CSize	GetShapeSize () { return (CSize(m_nShapeSizeX,m_nShapeSizeY)); };
	inline CPoint	GetPoint () { return (CPoint (m_iPosX, m_iPosY)); };
	inline sword	GetAngle () { return (m_nShapeAngle); };
	inline bool	GetSizeLock () { return (m_blShapeSizeLock); };
	inline bool	GetAngleLock () { return (m_blShapeAngleLock); };
	inline COLORREF	GetKernelColor () { return (m_dwKrnlColor); };
	inline COLORREF	GetShapeColor () { return (m_dwShapeColor); };
	inline COLORREF	GetFillColor () { return (m_dwShapeFill); };

	void	SetKernel (MarkKernel krnl);
	void	SetShape (MarkShape shape);
	void	SetKernelSize (uvar16_32 size);
	void	SetShapeSize (CSize size);
	void	SetPoint (CPoint point);
	void	SetAngle (sword angle);
	void	SetSizeLock (bool lock = true);
	void	SetAngleLock (bool lock = true);
	void	SetKernelColor (COLORREF color);
	void	SetShapeColor (COLORREF color);
	void	SetFillColor (COLORREF color);

protected:
	void		CreateControls ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMark)
public:
	void Serialize (CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARK_H__747203DB_E4EA_4C7D_840E_37FC8D867847__INCLUDED_)
