#if !defined(AFX_IMAGE_H__2646CB6B_BCEF_4CDB_A6B0_CF7DEAEB4B26__INCLUDED_)
#define AFX_IMAGE_H__2646CB6B_BCEF_4CDB_A6B0_CF7DEAEB4B26__INCLUDED_

#pragma once

#include "DiasAPIChannels.h"
#include "DiasAPIMarks.h"
#include "DiasAPIPatches.h"

class CImage : public CObject {
friend class CHash<CImage*,CImage>;
friend class CaImAPIRange<CImage>;
friend class CaImAPICollection<CImage>;
friend class CaImAPICollectionExt<CImage>;
friend class CDiasAPIImgRange;
friend class CDiasAPIImages;
friend class CStorageDoc;
friend class CPatch;
// Construction
	DECLARE_SERIAL (CImage);
protected:
	CImage ();
	CImage (const CImage& img);
	CImage (CStorageDoc* pDoc, CString name, CString descr);
public:
	~CImage ();
	CImage& operator= (const CImage&) throw (CaImAPIException);

	CImage operator+ (const CImage& img) { return (Add (img)); };
	CImage operator- (const CImage& img) { return (Sub (img)); };
	CImage operator* (const CImage& img) { return (Mul (img)); };
	CImage operator/ (const CImage& img) { return (Div (img)); };
	CImage operator% (const CImage& img) { return (Mod (img)); };
	CImage operator+= (const CImage& img) { *this = *this + img; return (*this); };
	CImage operator-= (const CImage& img) { *this = *this - img; return (*this); };
	CImage operator*= (const CImage& img) { *this = *this * img; return (*this); };
	CImage operator/= (const CImage& img) { *this = *this / img; return (*this); };
	CImage operator%= (const CImage& img) { *this = *this % img; return (*this); };

	CImage operator+ (const CColor& val) { return (Add (val)); };
	CImage operator- (const CColor& val) { return (Sub (val)); };
	CImage operator* (const CColor& val) { return (Mul (val)); };
	CImage operator/ (const CColor& val) { return (Div (val)); };
	CImage operator% (const CColor& val) { return (Mod (val)); };
	CImage operator+= (const CColor& val) { *this = *this + val; return (*this); };
	CImage operator-= (const CColor& val) { *this = *this - val; return (*this); };
	CImage operator*= (const CColor& val) { *this = *this * val; return (*this); };
	CImage operator/= (const CColor& val) { *this = *this / val; return (*this); };
	CImage operator%= (const CColor& val) { *this = *this % val; return (*this); };

	CImage& operator~ () { return (Not ()); };
	CImage& operator& (const CImage& img) { return (And (img)); };
	CImage& operator| (const CImage& img) { return (Or (img)); };
	CImage operator^ (const CImage& img) { return (Xor (img)); };
	CImage operator&= (const CImage& img) { *this = *this & img; return (*this); };
	CImage operator|= (const CImage& img) { *this = *this | img; return (*this); };
	CImage operator^= (const CImage& img) { *this = *this ^ img; return (*this); };

	CImage& operator& (const CColor& val) { return (And (val)); };
	CImage& operator| (const CColor& val) { return (Or (val)); };
	CImage& operator^ (const CColor& val) { return (Xor (val)); };
	CImage operator&= (const CColor& val) { *this = *this & val; return (*this); };
	CImage operator|= (const CColor& val) { *this = *this | val; return (*this); };
	CImage operator^= (const CColor& val) { *this = *this ^ val; return (*this); };

	CImage& Add (const CImage& img, ubyte nType = 0) throw (CaImAPIException);
	CImage& Sub (const CImage& img, ubyte nType = 0) throw (CaImAPIException);
	CImage& Mul (const CImage& img, ubyte nType = 0, uvar32_64 nCoef = 1) throw (CaImAPIException);
	CImage& Div (const CImage& img, ubyte nType = 0, uvar32_64 nCoef = 1) throw (CaImAPIException);
	CImage& Mod (const CImage& img, ubyte nType = 0) throw (CaImAPIException);
	CImage& Add (const CColor& col, ubyte nType = 0) throw (CaImAPIException);
	CImage& Sub (const CColor& col, ubyte nType = 0) throw (CaImAPIException);
	CImage& Mul (const CColor& col, ubyte nType = 0, uvar32_64 nCoef = 1) throw (CaImAPIException);
	CImage& Div (const CColor& col, ubyte nType = 0, uvar32_64 nCoef = 1) throw (CaImAPIException);
	CImage& Mod (const CColor& col, ubyte nType = 0) throw (CaImAPIException);

	CImage& Not () throw (CaImAPIException);
	CImage& And (const CImage& img) throw (CaImAPIException);
	CImage& Or  (const CImage& img) throw (CaImAPIException);
	CImage& Xor (const CImage& img) throw (CaImAPIException);
	CImage& And (const CColor& col) throw (CaImAPIException);
	CImage& Or  (const CColor& col) throw (CaImAPIException);
	CImage& Xor (const CColor& col) throw (CaImAPIException);

	CImage& Min (const CImage& img) throw (CaImAPIException);
	CImage& Max (const CImage& img) throw (CaImAPIException);
	CImage& Avg (const CImage& img) throw (CaImAPIException);
	CImage& Min (const CColor& col) throw (CaImAPIException);
	CImage& Max (const CColor& col) throw (CaImAPIException);
	CImage& Avg (const CColor& col) throw (CaImAPIException);

//	CImage& Statistics (DiasChannelStat& stat);
	CImage& Normalize () throw (CaImAPIException);
//	CImage& Linearize () throw (CaImAPIException);
//	CImage& Scale (...) throw (CaImAPIException);

	CImage& Segment (CColor nThreshold, CColor nLowValue, CColor nHighValue);
//	CImage& Segment (CColor* pnThresholds, CColor* pnValues, CColor dwCount);
	CImage& ErodeSegs (CColor nSegment, Parameter nType, uint nRepeat = 1);
//	CImage& DilateSegs (CColor nSegment, Parameter nType, uint nRepeat = 1);
//	CImage& OpenSegs (CColor nSegment, Parameter nType, uint nRepeat = 1);
//	CImage& CloseSegs (CColor nSegment, Parameter nType, uint nRepeat = 1);
//	CImage& FillHoles (CColor nThreshold);
//	CImage& ExtractHoles (CColor nThreshold);
//	CImage& FilterSegs (CColor nMinSize, CColor nMaxSize, Parameter nType);
//	CImage& FilterSegs (CImage& chnlMask, ubyte nType, Parameter nType);
//	CImage& Segregate (CColor nThreshold);
//	CImage& Segregate (CColor nThreshold, CMark& markBoundary, Parameter nType);

	CImage& Laplacian (uvar16_32 nX, uvar16_32 nY);
	CImage& Median (uvar16_32 nX, uvar16_32 nY);

// Attributes
public:
	CDiasAPIChannels	Channels;
	CDiasAPIMarks		Marks;
	CDiasAPIPatches		Patches;

protected:
	CStorageDoc*	m_pDoc;

	CString		m_strName;
	CString		m_strDescript;
	ColorModel*	m_pnColorModel;
	ubyte*		m_pnBPP;
	uvar16_32*	m_pnDimX;
	uvar16_32*	m_pnDimY;

// Operations
public:
	CStorageDoc&	GetDoc () { return (*m_pDoc); };
	svar32_64	GetPos ();
	CString		GetName ();
	CString		GetDescription ();
	void		SetPos (uvar32_64 before);
	void		SetName (CString name);
	void		SetDescription (CString descr);

	CColor		GetPixel (uvar16_32 nX, uvar16_32 nY);
	udword		GetPixel (uvar32_64 nOffset);
	void		SetPixel (uvar16_32 nX, uvar16_32 nY, CColor& col);
	void		SetPixel (uvar32_64 nOffset, CColor& col);
protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImage)
public:
	void Serialize (CArchive& ar);
	//}}AFX_VIRTUAL
};
/////////////////////////////////////////////////////////////////////////////


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGE_H__2646CB6B_BCEF_4CDB_A6B0_CF7DEAEB4B26__INCLUDED_)
