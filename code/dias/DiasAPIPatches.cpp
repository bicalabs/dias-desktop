#include "stdafx.h"
#include "dias.h"
#include "DiasAPIPatches.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiasAPIDocs

CDiasAPIPatches::CDiasAPIPatches () {
	m_pImg = NULL;
	m_pDoc = NULL;
	CaImAPICollectionExt<CPatch>::CaImAPICollectionExt<CPatch> ();
	m_rngInt.m_ppHead = &m_pHashHead;
}

CDiasAPIPatches::~CDiasAPIPatches () {
	CaImAPICollectionExt<CPatch>::~CaImAPICollectionExt<CPatch> ();
}

CDiasAPIPatches& CDiasAPIPatches::operator= (const CDiasAPIPatches& coll) {
	m_pDoc = coll.m_pDoc;
	m_pImg = coll.m_pImg;
	return ((CDiasAPIPatches&) (CaImAPICollection<CPatch>::operator= ( (CaImAPICollection<CPatch>&)coll )));
}

void CDiasAPIPatches::Serialize (CArchive& ar) {
	CaImAPICollection<CPatch>::Serialize (ar);
	uvar32_64 n, pos, size;
	if (ar.IsLoading ()) {
		ar.Read (&size, sizeof (uvar32_64));
		CPatch* p = new CPatch (m_pImg, "", "");
		for (n = 0; n < size; ++n) {
			pos = CaImAPICollectionExt<CPatch>::Add (*p);
			(*this)[pos].Serialize (ar);
		}
		delete p;
	}
}

uvar32_64 CDiasAPIPatches::Add (uvar32_64 nLength, uvar32_64* pnOffsets) {
	CPatch* pPatch = new CPatch (m_pImg, theSettings.GetSetting (ID_PATCH_NAME, CSettings::sqName, UINT(0)), "");
	uvar32_64 pos = CaImAPICollectionExt<CPatch>::Add (*pPatch);
	(*this)[pos].Set (nLength, pnOffsets);
	m_pDoc->Update (CUpdateHint::updtImage, UPDHI_ADDPATCH, m_pImg->GetPos (), pos);
	delete pPatch;
	return (pos);
}

uvar32_64 CDiasAPIPatches::Create (CColor& cBackground) {
	return (Create (*m_pImg, cBackground));
}

uvar32_64 CDiasAPIPatches::Create (CImage& imgSource, CColor& cBackground) throw (CaImAPIException) {
	uvar32_64 nCreated = 0;

	if ((~cBackground) != m_pDoc->GetChannelsCount ())
		throw (CaImAPIException (0));

	uvar32_64 size = m_pDoc->GetDimX () * m_pDoc->GetDimY ();
	uvar32_64 *pdwSizes = (uvar32_64*)aimMemoryCommit (size * sizeof(uvar32_64), "CDiasAPIPatches::Create", "pdwSizes"),
		  **ppdwPatches = (uvar32_64**)aimMemoryCommit (size * sizeof(uvar32_64*), "CDiasAPIPatches::Create", "ppdwPatches");
	CColor	*pcColors = (CColor*)aimMemoryCommit (size * sizeof(CColor), "CDiasAPIPatches::Create", "pcColors");

	uvar32_64 nChnls = imgSource.Channels.GetCount ();
	ubyte	**ppbPixel = (ubyte**)aimMemoryCommit (nChnls * sizeof(ubyte*), "CDiasAPIPatches::Create", "ppbPixel");
	for (int c = 0 ; c < nChnls ; ++c) {
		ppbPixel[c] = (ubyte*)aimMemoryCommit (size, "CDiasAPIPatches::Create", "ppbPixel[c]");
		imgSource.Channels[c].GetBits (ppbPixel[c], size);
	}
	for (uvar32_64 i = 0 , j ; i < size ; ++i) {
		for (c = 0 ; c < nChnls ; ++c)
			if (ppbPixel[c][i] != cBackground[c] && cBackground(c) == true)
				goto listPatches;
		continue;
listPatches:	for (j = 0 ; j < nCreated ; ++j) {
			for (c = 0 ; c < nChnls ; ++c)
				if (ppbPixel[c][i] != pcColors[j][c] && cBackground(c) == true)
					goto nextPatch;
			++pdwSizes[j];
			goto nextPixel;
nextPatch:;
		}
		pcColors[nCreated] = cBackground;
		for (c = 0 ; c < nChnls ; ++c)
			pcColors[nCreated] = ppbPixel[c][i];
		pdwSizes[nCreated++] = 1;
nextPixel:;
	}

	aimMemoryRelease (ppdwPatches,"CDiasAPIPatches::Create", "ppdwPatches");
	ppdwPatches = (uvar32_64**)aimMemoryCommit (nCreated * sizeof(uvar32_64*), "CDiasAPIPatches::Create", "ppdwPatches");
	for (i = 0 ; i < nCreated ; ++i) {
		ppdwPatches[i] = (DWORD*)aimMemoryCommit (pdwSizes[i] * sizeof(DWORD), "CDiasAPIPatches::Create", "ppdwPatches[n]");
		pdwSizes[i] = 0;
	}
	for (i = 0 ; i < size ; ++i) {
		for (c = 0 ; c < nChnls ; ++c)
			if (ppbPixel[c][i] != cBackground[c] && cBackground(c) == true)
				goto listPatches2;
		continue;
listPatches2:	for (j = 0 ; j < nCreated ; ++j) {
			for (c = 0 ; c < nChnls ; ++c)
				if (ppbPixel[c][i] != pcColors[j][c] && cBackground(c) == true)
					goto nextPatch2;
			ppdwPatches[j][pdwSizes[j]++] = i;
			break;
nextPatch2:;	}
	}
	for (c = 0 ; c < nChnls ; ++c)
		aimMemoryRelease (ppbPixel[c], "CDiasAPIPatches::Create", "ppbPixel[c]");
	aimMemoryRelease (ppbPixel,"CDiasAPIPatches::Create", "ppbPixel");

	uvar32_64 pos = 0;
	for (i = 0 ; i < nCreated ; ++i) {
		CPatch* pPatch = new CPatch (&imgSource, theSettings.GetSetting (ID_PATCH_NAME, CSettings::sqName, UINT(0)), "");
		uvar32_64 pos = CaImAPICollectionExt<CPatch>::Add (*pPatch);
		(*this)[pos].Set (pdwSizes[i], ppdwPatches[i]);
		m_pDoc->Update (CUpdateHint::updtImage, UPDHI_ADDPATCH, m_pImg->GetPos (), pos);
	}
	m_pDoc->Update (CUpdateHint::updtImage, UPDHI_ADDPATCH, pos - nCreated + 1, pos);

	aimMemoryRelease (ppdwPatches,"CDiasAPIPatches::Create", "ppdwPatches");
	aimMemoryRelease (pdwSizes,"CDiasAPIPatches::Create", "pdwSizes");
	return (nCreated);
}
