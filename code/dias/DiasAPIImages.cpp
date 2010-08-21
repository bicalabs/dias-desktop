#include "stdafx.h"
#include "dias.h"
#include "DiasAPIImages.h"
#include "StorageFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiasAPIDocs

CDiasAPIImages::CDiasAPIImages () {
	CaImAPICollectionExt<CImage>::CaImAPICollectionExt<CImage> ();
	m_rngInt.m_ppHead = &m_pHashHead;
}

CDiasAPIImages::~CDiasAPIImages () {
	CaImAPICollectionExt<CImage>::~CaImAPICollectionExt<CImage> ();
}

CDiasAPIImages& CDiasAPIImages::operator= (const CDiasAPIImages& coll) {
	return ((CDiasAPIImages&) (CaImAPICollection<CImage>::operator= ( (CaImAPICollection<CImage>&)coll )));
}

CImage& CDiasAPIImages::operator[] (uvar32_64 pos) {
	return (CaImAPICollectionExt<CImage>::operator[] (pos));
}

CImage& CDiasAPIImages::operator[] (aImAPIRngType t) {
	if (t != aimActive)
		throw (CaImAPIException (0));
	int sel = m_pDoc->Frames[aimActive].GetActiveImageNo ();
	if (sel == -1)	throw (CaImAPIException(0));
	return (*(m_pHashHead->GetAt(sel)->m_hData));
}

CDiasAPIImgRange& CDiasAPIImages::operator() (aImAPIRngType type) {
	uvar32_64 sel;
	POSITION pos;
	m_rngInt.Reset ();
	if (!m_pHashHead)
		return (m_rngInt);
	CHash<CImage*, CImage>* p;
	switch (type) {
		case aimAll:
			for (p = m_pHashHead ; !p ; p = p->GetNext ())
				m_rngInt.Include (p);
			break;
		case aimVisible:
			// #### TODO: Place code here
			break;
		case aimActive:
			if ((sel = m_pDoc->Frames[aimActive].GetActiveImageNo()) != -1)
				m_rngInt.Include (m_pHashHead->GetAt(sel));
			break;
		case aimSelected:
			pos = m_pDoc->Frames[aimActive].GetFirstSelectedImageNo ();
			while (pos)
			   m_rngInt.Include (m_pHashHead->GetAt (m_pDoc->Frames[aimActive].GetNextSelectedImageNo (pos)) );
			break;
		default:
			throw (CaImAPIException (0));
	}
	return (m_rngInt);
}

CDiasAPIImgRange& CDiasAPIImages::operator() (int no, ...) {
	m_rngInt.Reset ();
	int n = no;
	va_list items;
	va_start (items, no);
	while (n != -1)
		m_rngInt.Include (m_pHashHead->GetAt(n));
	va_end (items);
	return (m_rngInt);
}

CDiasAPIImgRange& CDiasAPIImages::operator() (char* name, ...) {
	m_rngInt.Reset ();
	char* n = name;
	va_list items;
	va_start (items, name);
	while (!n)
		m_rngInt.Include (m_pHashHead->GetAt(NameLookup(n)));
	va_end (items);
	return (m_rngInt);
}

void CDiasAPIImages::Serialize (CArchive& ar) {
	CaImAPICollection<CImage>::Serialize (ar);
	uvar32_64 n, size;
	if (ar.IsLoading ()) {
		ar.Read (&size, sizeof (uvar32_64));
		Add (size);
		for (n = 0; n < size; ++n)
			(*this)[n].Serialize (ar);
	}
}

uvar32_64 CDiasAPIImages::Add (CImage& item) {
	uvar32_64 cnt = CaImAPICollectionExt<CImage>::Add (item);
	m_pDoc->Update (CUpdateHint::updtList, UPDHL_IMAGES | UPDHL_ADDED, cnt, cnt);
	return (cnt);
}
uvar32_64 CDiasAPIImages::Add (CaImAPIRange<CImage>& item) {
	uvar32_64 start = GetCount ();
	uvar32_64 cnt = CaImAPICollectionExt<CImage>::Add (item);
	m_pDoc->Update (CUpdateHint::updtList, UPDHL_IMAGES | UPDHL_ADDED, start, start + cnt);
	return (cnt);
}
uvar32_64 CDiasAPIImages::Insert (uvar32_64 pos, CImage& item) {
	uvar32_64 cnt = CaImAPICollectionExt<CImage>::Insert (pos, item);
	m_pDoc->Update (CUpdateHint::updtList, UPDHL_IMAGES | UPDHL_ADDED, cnt, cnt);
	return (cnt);
}
uvar32_64 CDiasAPIImages::Insert (CString name, CImage& item) {
	uvar32_64 cnt = CaImAPICollectionExt<CImage>::Insert (name, item);
	m_pDoc->Update (CUpdateHint::updtList, UPDHL_IMAGES | UPDHL_ADDED, cnt, cnt);
	return (cnt);
}
uvar32_64 CDiasAPIImages::Insert (uvar32_64 pos, CaImAPIRange<CImage>& item) {
	uvar32_64 cnt = CaImAPICollectionExt<CImage>::Insert (pos, item);
	m_pDoc->Update (CUpdateHint::updtList, UPDHL_IMAGES | UPDHL_ADDED, pos, pos + cnt);
	return (cnt);
}
uvar32_64 CDiasAPIImages::Insert (CString name, CaImAPIRange<CImage>& item) {
	uvar32_64 pos = NameLookup (name);
	uvar32_64 cnt = CaImAPICollectionExt<CImage>::Insert (name, item);
	m_pDoc->Update (CUpdateHint::updtList, UPDHL_IMAGES | UPDHL_ADDED, pos, pos + cnt);
	return (cnt);
}
void CDiasAPIImages::Delete (uvar32_64 pos) {
	CaImAPICollectionExt<CImage>::Delete (pos);
	m_pDoc->Update (CUpdateHint::updtList, UPDHL_IMAGES | UPDHL_ALL);
}
uvar32_64 CDiasAPIImages::DeleteAll () {
	uvar32_64 cnt = CaImAPICollectionExt<CImage>::DeleteAll ();
	m_pDoc->Update (CUpdateHint::updtList, UPDHL_IMAGES | UPDHL_ALL);
	return (cnt);
}

uvar32_64 CDiasAPIImages::Add (uvar32_64 cnt) {
	uvar32_64 pos;
	for (uvar32_64 n = 0 ; n < cnt ; ++n) {
		CImage* pImg = new CImage (m_pDoc, theSettings.GetSetting (ID_IMAGE_NAME, CSettings::sqName, UINT(0)), "");
		pos = CaImAPICollectionExt<CImage>::Add (*pImg);
	}
	m_pDoc->Update (CUpdateHint::updtList, UPDHL_IMAGES | UPDHL_ADDED, pos - cnt + 1, pos);
	return (cnt);
}

uvar32_64 CDiasAPIImages::Insert (svar32_64 pos, uvar32_64 cnt) {
	for (uvar32_64 n = 0 ; n < cnt ; ++n) {
		CImage* pImg = new CImage (m_pDoc, theSettings.GetSetting (ID_IMAGE_NAME, CSettings::sqName, UINT(0)), "");
		CaImAPICollectionExt<CImage>::Insert (pos, *pImg);
	}
	m_pDoc->Update (CUpdateHint::updtList, UPDHL_IMAGES | UPDHL_ADDED, pos - cnt + 1, pos);
	return (cnt);
}

uvar32_64 CDiasAPIImages::Insert (CString pos, uvar32_64 cnt) {
	uvar32_64 pos2;
	for (uvar32_64 n = 0 ; n < cnt ; ++n) {
		CImage* pImg = new CImage (m_pDoc, theSettings.GetSetting (ID_IMAGE_NAME, CSettings::sqName, UINT(0)), "");
		pos2 = CaImAPICollectionExt<CImage>::Insert (pos, *pImg);
	}
	m_pDoc->Update (CUpdateHint::updtList, UPDHL_IMAGES | UPDHL_ADDED, pos2 - cnt + 1, pos2);
	return (cnt);
}
