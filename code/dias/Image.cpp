#include "stdafx.h"
#include "Dias.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImage

IMPLEMENT_SERIAL (CImage, CObject, 1);

CImage::CImage () :
	m_strName (""), m_strDescript ("") {

	m_pDoc = NULL;
	Patches.m_pImg = this;
	Marks.m_pImg = this;

	theApp.ObjectsAdd (OBJT_IMAGE, this);
};

CImage::CImage (CStorageDoc *pDoc, CString name, CString descr) {
	Channels.m_pDoc = pDoc;
	Patches.m_pDoc = pDoc;
	Patches.m_pImg = this;
	Marks.m_pDoc = pDoc;
	Marks.m_pImg = this;

	m_pDoc = pDoc;
	m_strName = name;
	m_strDescript = descr;
	m_pnColorModel = &(pDoc->m_nColorModel);
	m_pnBPP = &(pDoc->m_nBPP);
	m_pnDimX = &(pDoc->m_nDimX);
	m_pnDimY = &(pDoc->m_nDimY);

	Channels.Add (pDoc->m_nChannels);
	// #### TODO: Set default names for channels

	theApp.ObjectsAdd (OBJT_IMAGE, this);
}

CImage::~CImage () {
	theApp.ObjectsRemove (OBJT_IMAGE, this);

	m_pDoc = NULL;
	m_pnColorModel = NULL;
	m_pnBPP = NULL;
	m_pnDimX = NULL;
	m_pnDimY = NULL;
}

CImage::CImage (const CImage& img) {
	m_pDoc = NULL;
	theApp.ObjectsAdd (OBJT_IMAGE, this);
	*this = img;
}

CImage& CImage::operator= (const CImage& img) {
	theApp.ObjectsRemove (OBJT_IMAGE, this);
	Channels.~CDiasAPIChannels ();
	Patches.~CDiasAPIPatches ();
	Marks.~CDiasAPIMarks ();

	m_pDoc = img.m_pDoc;
	m_strName = img.m_strName;
	m_strDescript = img.m_strDescript;
	m_pnColorModel = &(m_pDoc->m_nColorModel);
	m_pnBPP = &(m_pDoc->m_nBPP);
	m_pnDimX = &(m_pDoc->m_nDimX);
	m_pnDimY = &(m_pDoc->m_nDimY);
	Channels = img.Channels;
	Marks = img.Marks;
	Patches = img.Patches;
	Patches.m_pImg = this;
	Marks.m_pImg = this;

	theApp.ObjectsAdd (OBJT_IMAGE, this);
	return (*this);
}

void CImage::Serialize (CArchive& ar) {
	CObject::Serialize (ar);
	if (ar.IsStoring ())
		ar << m_strName << m_strDescript;
	else
		ar >> m_strName >> m_strDescript;
	Channels.m_pDoc = m_pDoc;
	Marks.m_pDoc = m_pDoc;
	Marks.m_pImg = this;
	Patches.m_pDoc = m_pDoc;
	Patches.m_pImg = this;
	Channels.Serialize (ar);
	Marks.Serialize (ar);
	Patches.Serialize (ar);
}

svar32_64 CImage::GetPos () {
	m_pDoc->Images.m_pHashHead = m_pDoc->Images.m_pHashHead->GetHead ();
	for (CHash<CImage*,CImage>* p = m_pDoc->Images.m_pHashHead; p; p = p->GetNext ())
		if (p->m_hData == this)
			return (p->GetPos ());
	return (-1);
}

CString CImage::GetName () {
	return (m_strName);
}

CString CImage::GetDescription () {
	return (m_strDescript);
}

void CImage::SetPos (uvar32_64 pos) {
	// #### TODO: Place code here
}

void CImage::SetName (CString name) {
	m_strName = name;
	m_pDoc->Update (CUpdateHint::updtList, UPDHL_IMAGES | UPDHL_NAME, GetPos (), GetPos ());
	theApp.Update (UPDHA_IMAGE);
}

void CImage::SetDescription (CString descr) {
	m_strDescript = descr;
	m_pDoc->Update (CUpdateHint::updtList, UPDHL_IMAGES | UPDHL_NAME, GetPos (), GetPos ());
	theApp.Update (UPDHA_IMAGE);
}

CColor CImage::GetPixel (uvar16_32 nX, uvar16_32 nY) {
	ubyte n, cnt = Channels.GetCount ();
	CColor col (NULL, cnt);
	for (n = 0; n < cnt; ++n)
		col.m_pdwValues[n] = Channels[n].GetPixel (nX, nY);
	return (col);
}

udword CImage::GetPixel (uvar32_64 nOffset) {
	uvar32_64 zero = 0;
	switch (*m_pnColorModel) {
		case cmMono:		return ((Channels[zero].GetPixel (nOffset) == 1) ? 0xFFFFFF : 0);
		case cmGrayscale:	return (RGB(Channels[zero].GetPixel (nOffset), Channels[zero].GetPixel (nOffset), Channels[zero].GetPixel (nOffset)));
		case cmRGB:		return (RGB(Channels["Red"].GetPixel (nOffset), Channels["Green"].GetPixel (nOffset), Channels["Blue"].GetPixel (nOffset)));
	}
	return (0);
}

void CImage::SetPixel (uvar16_32 nX, uvar16_32 nY, CColor& col) {
	ubyte n, cnt = Channels.GetCount ();
	if (col.m_bChannels != cnt)
		return;
	for (n = 0; n < cnt; ++n)
		if (col.m_pbMask[n])
			Channels[n].SetPixel (nX, nY, col.m_pdwValues[n]);
}

void CImage::SetPixel (uvar32_64 nOffset, CColor& col) {
	ubyte n, cnt = Channels.GetCount ();
	if (col.m_bChannels != cnt)
		return;
	for (n = 0; n < cnt; ++n)
		if (col.m_pbMask[n])
			Channels[n].SetPixel (nOffset, col.m_pdwValues[n]);
}

#define	PROC_MACRO(x)	\
	CImage *result = m_pDoc->m_pImgTmp;\
	if (((CImage)(img)).Channels.GetCount() != Channels.GetCount ())\
		throw (CaImAPIException (0));\
	for (uvar32_64 n = 0, cnt = Channels.GetCount (); n < cnt; ++n) {\
		result->Channels[n] = Channels[n].x;\
		this->Channels[n].CopyData (result->Channels[n]);\
	}\
	return (*this);

CImage& CImage::Add (const CImage& img, ubyte nType) { PROC_MACRO (Add (((CImage)(img)).Channels[n], nType)); }
CImage& CImage::Sub (const CImage& img, ubyte nType) { PROC_MACRO (Sub (((CImage)(img)).Channels[n], nType)); }
CImage& CImage::Mul (const CImage& img, ubyte nType, uvar32_64 nCoef) { PROC_MACRO (Mul (((CImage)(img)).Channels[n], nType, nCoef)); }
CImage& CImage::Div (const CImage& img, ubyte nType, uvar32_64 nCoef) { PROC_MACRO (Div (((CImage)(img)).Channels[n], nType, nCoef)); }
CImage& CImage::Mod (const CImage& img, ubyte nType) { PROC_MACRO (Mod (((CImage)(img)).Channels[n], nType)); }

#undef	PROC_MACRO
#define	PROC_MACRO(x)	\
	CImage *result = m_pDoc->m_pImgTmp;\
	if (((CImage)(img)).Channels.GetCount() != Channels.GetCount ())\
		throw (CaImAPIException (0));\
	for (uvar32_64 n = 0, cnt = Channels.GetCount (); n < cnt; ++n) {\
		result->Channels[n] = Channels[n].x (((CImage)(img)).Channels[n]);\
		this->Channels[n].CopyData (result->Channels[n]);\
	}\
	return (*this);

CImage& CImage::And (const CImage& img) { PROC_MACRO (And); }
CImage& CImage::Or  (const CImage& img) { PROC_MACRO (Or); }
CImage& CImage::Xor (const CImage& img) { PROC_MACRO (Xor); }
CImage& CImage::Min (const CImage& img) { PROC_MACRO (Min); }
CImage& CImage::Max (const CImage& img) { PROC_MACRO (Max); }
CImage& CImage::Avg (const CImage& img) { PROC_MACRO (Avg); }

#undef	PROC_MACRO
#define	PROC_MACRO(x)	\
	CImage *result = m_pDoc->m_pImgTmp;\
	if (col.m_bChannels != Channels.GetCount ())\
		throw (CaImAPIException (0));\
	for (uvar32_64 n = 0, cnt = Channels.GetCount (); n < cnt; ++n) {\
		if (((CColor)(col))(n))\
			result->Channels[n] = Channels[n].x;\
		else\
			result->Channels[n] = Channels[n];\
		this->Channels[n].CopyData (result->Channels[n]);\
	}\
	return (*this);

CImage& CImage::Add (const CColor& col, ubyte nType) { PROC_MACRO (Add (((CColor)(col))[n], nType)); }
CImage& CImage::Sub (const CColor& col, ubyte nType) { PROC_MACRO (Sub (((CColor)(col))[n], nType)); }
CImage& CImage::Mul (const CColor& col, ubyte nType, uvar32_64 nCoef) { PROC_MACRO (Mul (((CColor)(col))[n], nType, nCoef)); }
CImage& CImage::Div (const CColor& col, ubyte nType, uvar32_64 nCoef) { PROC_MACRO (Div (((CColor)(col))[n], nType, nCoef)); }
CImage& CImage::Mod (const CColor& col, ubyte nType) { PROC_MACRO (Mod (((CColor)(col))[n], nType)); }

#undef	PROC_MACRO
#define	PROC_MACRO(x)	\
	CImage *result = m_pDoc->m_pImgTmp;\
	if (col.m_bChannels != Channels.GetCount ())\
		throw (CaImAPIException (0));\
	for (uvar32_64 n = 0, cnt = Channels.GetCount (); n < cnt; ++n) {\
		if (((CColor)(col))(n))\
			result->Channels[n] = Channels[n].x (((CColor)(col))[n]);\
		else\
			result->Channels[n] = Channels[n];\
		this->Channels[n].CopyData (result->Channels[n]);\
	}\
	return (*this);

CImage& CImage::And (const CColor& col) { PROC_MACRO (And); }
CImage& CImage::Or  (const CColor& col) { PROC_MACRO (Or); }
CImage& CImage::Xor (const CColor& col) { PROC_MACRO (Xor); }
CImage& CImage::Min (const CColor& col) { PROC_MACRO (Min); }
CImage& CImage::Max (const CColor& col) { PROC_MACRO (Max); }
CImage& CImage::Avg (const CColor& col) { PROC_MACRO (Avg); }

#undef	PROC_MACRO

CImage& CImage::Not () {
	CImage *result = m_pDoc->m_pImgTmp;
	for (uvar32_64 n = 0, cnt = Channels.GetCount (); n < cnt; ++n) {
		result->Channels[n] = Channels[n].Not ();
		this->Channels[n].CopyData (result->Channels[n]);
	}
	return (*this);
}


CImage& CImage::Normalize () {
	CImage *result = m_pDoc->m_pImgTmp;
	for (uvar32_64 n = 0, cnt = Channels.GetCount (); n < cnt; ++n) {
		result->Channels[n] = Channels[n].Normalize ();
		this->Channels[n].CopyData (result->Channels[n]);
	}
	return (*this);
}

CImage& CImage::Segment (CColor nThreshold, CColor nLowValue, CColor nHighValue) {
	CImage *result = m_pDoc->m_pImgTmp;
	for (uvar32_64 n = 0, cnt = Channels.GetCount (); n < cnt; ++n) {
		result->Channels[n] = Channels[n].Segment (nThreshold[n], nLowValue[n], nHighValue[n]);
		this->Channels[n].CopyData (result->Channels[n]);
	}
	return (*this);
}

CImage& CImage::ErodeSegs (CColor nSegment, Parameter nType, uint nRepeat) {
	CImage *result = m_pDoc->m_pImgTmp;
	for (uvar32_64 n = 0, cnt = Channels.GetCount (); n < cnt; ++n) {
		result->Channels[n] = Channels[n].ErodeSegs (nSegment[n], nType, nRepeat);
		this->Channels[n].CopyData (result->Channels[n]);
	}
	return (*this);
}

CImage& CImage::Laplacian (uvar16_32 nX, uvar16_32 nY) {
	CImage *result = m_pDoc->m_pImgTmp;
	for (uvar32_64 n = 0, cnt = Channels.GetCount (); n < cnt; ++n) {
		result->Channels[n] = Channels[n].Laplacian (nX, nY);
		this->Channels[n].CopyData (result->Channels[n]);
	}
	return (*this);
}

CImage& CImage::Median (uvar16_32 nX, uvar16_32 nY) {
	CImage *result = m_pDoc->m_pImgTmp;
	for (uvar32_64 n = 0, cnt = Channels.GetCount (); n < cnt; ++n) {
		result->Channels[n] = Channels[n].Median (nX, nY);
		this->Channels[n].CopyData (result->Channels[n]);
	}
	return (*this);
}
