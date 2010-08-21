#include "stdafx.h"
#include "Dias.h"
#include "MainFrame.h"

#include "Image.h"
#include "Survey.h"
#include "Report.h"

#include "StorageView.h"
#include "StorageFrame.h"
#include "StorageDoc.h"

// Dialogs
#include "DocNewDlg.h"
#include "AddImagesDlg.h"
#include "AddSurveyDlg.h"
#include "CaptureDlg.h"
#include "3ImgFnDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStorageDoc

IMPLEMENT_DYNCREATE(CStorageDoc, CDocument)

BEGIN_MESSAGE_MAP(CStorageDoc, CDocument)
	//{{AFX_MSG_MAP(CStorageDoc)
	ON_COMMAND(ID_IMAGE_ADD, OnImageAdd)
	ON_COMMAND(ID_IMAGE_ADDSEQ, OnImageAddSequence)
	ON_COMMAND(ID_IMAGE_ACQUIRE_CAMERA, OnImageAcquireCamera)
	ON_COMMAND(ID_IMAGE_IMPORT, OnImageImport)
	ON_COMMAND(ID_IMAGE_EXPORT, OnImageExport)
	ON_COMMAND(ID_SURVEY_ADD, OnSurveyAdd)
	ON_COMMAND(ID_DOC_REMOVE, OnDocRemove)
	ON_COMMAND(ID_DOC_UP, OnDocUp)
	ON_COMMAND(ID_DOC_DOWN, OnDocDown)
	ON_COMMAND(ID_DOC_PREV, OnDocPrev)
	ON_COMMAND(ID_DOC_NEXT, OnDocNext)
	ON_COMMAND(ID_DOC_PROP, OnDocProp)
	ON_COMMAND(ID_DOC_STYLE, OnDocStyle)
	ON_COMMAND(ID_IMAGE_ARITHM_ADD, OnImageArithmAdd)
	ON_COMMAND(ID_TOOLS_PLUGINS_1, OnToolsPlugins1)
	ON_COMMAND(ID_TOOLS_PLUGINS_2, OnToolsPlugins2)
	ON_COMMAND(ID_IMAGE_ADJUST_NORMALIZE, OnImageAdjustNormalize)
	ON_COMMAND(ID_IMAGE_SEG_SEGMENT, OnImageSegSegment)
	ON_COMMAND(ID_IMAGE_SEG_ERODE, OnImageSegErode)
	ON_COMMAND(ID_IMAGE_EDGES_LAPLACIAN, OnImageEdgesLaplacian)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_ACQUIRE_CAMERA, OnUpdateImageAcquireCamera)
	ON_COMMAND(ID_SURVEY_MEASURE, OnSurveyMeasure)
	ON_COMMAND(ID_TOOLS_PLUGINS_3, OnToolsPlugins3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStorageDoc construction/destruction

CStorageDoc::CStorageDoc () {
	Images.m_pDoc = this;
	Surveis.m_pDoc = this;
	Frames.m_pDoc = this;

	m_blAcceptFromView = true;
	m_blForceSettings = false;
	m_blShowImages = true;
	m_blShowPatches = true;
	m_blShowMarks = true;
	m_blShowMeters = true;
	m_blImgVRuler = true;
	m_blImgHRuler = true;
	m_blImgGrid = false;
	m_blRptVRuler = true;
	m_blRptHRuler = true;
	m_blRptGrid = true;
	m_nImgZoom = 1;
	m_nRptZoom = 1;
	m_rectPlacement = CRect (0, 0, 500, 700);
	m_nPanelWidth = 130;
	m_nPanelActive = 1;
	m_blShowNames = true;
	m_nImgNo = 0;
	m_nDataNo = 0;
	m_nRptNo = 0;

	m_pdlgCapture = NULL;
}

CStorageDoc::~CStorageDoc () {
	if (m_pdlgCapture) {
		m_pdlgCapture->DestroyWindow ();
		delete m_pdlgCapture;
		m_pdlgCapture = NULL;
	}
	DeleteContents ();
}

BOOL CStorageDoc::OnNewDocument () {
	if (!CDocument::OnNewDocument())
		return FALSE;

	CDocNewDlg dlg;
	dlg.m_strName = this->GetTitle ();
	if (dlg.DoModal () != IDOK)
		return false;

	m_pdlgCapture = NULL;

	SetTitle (dlg.m_strName);
	m_strName = dlg.m_strName;
	m_strDescript = dlg.m_strDescription;
	m_nColorModel = (ColorModel) dlg.m_nModel;
	m_nDimX = atoi (dlg.m_strDimX);
	m_nDimY = atoi (dlg.m_strDimY);
	m_nBPP = (m_nColorModel == cmMono) ? 1 : 8;
	m_nChannels = (m_nColorModel == cmCMYK) ? 4 : (m_nColorModel == cmMono || m_nColorModel == cmGrayscale) ? 1 : (m_nColorModel == cmMulty) ? 0 : 3;

	m_pImgTmp = new CImage (this, "TemporaryImage", "System image for calculations");
	m_pCnlTmp = new CChannel (this, "TemporaryChannel", "System channel for calculations");

	// #### TODO: Call apopriate dialog here if the color model is set to multy

	if (!theApp.Documents.m_pHashHead)
		theApp.Documents.m_pHashHead = new CHash<CStorageDoc*,CStorageDoc>(this);
	else
		theApp.Documents.m_pHashHead->AddTail (new CHash<CStorageDoc*,CStorageDoc>(this));

//	CButton *btn = (CButton*)(dlg.GetDlgItem (IDC_DN_CREATE_ARCUIRE));
//	if (btn->GetCheck () == 1)
//		OnImageAcquireCamera ();
//	else
		Images.Add (dlg.m_nCount);
	
	return TRUE;
}

BOOL CStorageDoc::OnOpenDocument (LPCTSTR lpszPathName) {
	theApp.StatusState (IDI_INDICATOR_OPEN);

	if (!CDocument::OnOpenDocument(lpszPathName))
		return (false);

	m_pdlgCapture = NULL;
	if (!theApp.Documents.m_pHashHead)
		theApp.Documents.m_pHashHead = new CHash<CStorageDoc*,CStorageDoc>(this);
	else
		theApp.Documents.m_pHashHead->AddTail (new CHash<CStorageDoc*,CStorageDoc>(this));

	m_pImgTmp = new CImage (this, "TemporaryImage", "System image for calculations");
	m_pCnlTmp = new CChannel (this, "TemporaryChannel", "System channel for calculations");

	theApp.StatusState (0);
	return (true);
}

BOOL CStorageDoc::OnSaveDocument (LPCTSTR lpszPathName) {
	BOOL ret;
	theApp.StatusState (IDI_INDICATOR_SAVE);
	ret = CDocument::OnSaveDocument(lpszPathName);
	UpdateAllViews (NULL, 0);
	theApp.StatusState (0);
	return (ret);
}

void CStorageDoc::OnCloseDocument () {
	if (theApp.Documents.GetCount () == 1) {
		theApp.Documents.m_pHashHead->GetAt(theApp.Documents.NameLookup (m_strName))->Remove ();
		theApp.Documents.m_pHashHead = NULL;
	} else if (theApp.Documents.NameLookup (m_strName) != uvar32_64 (-1) && theApp.Documents.NameLookup (m_strName) < theApp.Documents.GetCount ())
		theApp.Documents.m_pHashHead->GetAt(theApp.Documents.NameLookup (m_strName))->Remove ();
	if (m_pdlgCapture) {
		m_pdlgCapture->DestroyWindow ();
		m_pdlgCapture = NULL;
	}
	CDocument::OnCloseDocument ();
}

void CStorageDoc::DeleteContents () {
/*	Images(aimAll).Remove ();
	CDocument::DeleteContents ();
	UpdateAllViews (NULL, 0);*/
}

bool CStorageDoc::GetSetting (CString name) throw (CaImAPIException) {
	if (name == "ShowImages")	return (m_blShowImages);
	else if (name == "ShowPatches")	return (m_blShowPatches);
	else if (name == "ShowMarks")	return (m_blShowMarks);
	else if (name == "ShowMeters")	return (m_blShowMeters);
	else if (name == "ImgVRuler")	return (m_blImgVRuler);
	else if (name == "ImgHRuler")	return (m_blImgHRuler);
	else if (name == "ImgGrid")	return (m_blImgGrid);
	else if (name == "RptVRuler")	return (m_blRptVRuler);
	else if (name == "RptHRuler")	return (m_blRptHRuler);
	else if (name == "RptGrid")	return (m_blRptGrid);
	else	throw (CaImAPIException (0));	// #### TODO: Put aImAPIException number
	return (false);
}

void CStorageDoc::SetSetting (CString name, bool value) {
	if (name == "ShowImages")	m_blShowImages = m_blShowImages;
	else if (name == "ShowPatches")	m_blShowPatches = m_blShowPatches;
	else if (name == "ShowMarks")	m_blShowMarks = m_blShowMarks;
	else if (name == "ShowMeters")	m_blShowMeters = m_blShowMeters;
	else if (name == "ImgVRuler")	m_blImgVRuler = m_blImgVRuler;
	else if (name == "ImgHRuler")	m_blImgHRuler = m_blImgHRuler;
	else if (name == "ImgGrid")	m_blImgGrid = m_blImgGrid;
	else if (name == "RptVRuler")	m_blRptVRuler = m_blRptVRuler;
	else if (name == "RptHRuler")	m_blRptHRuler = m_blRptHRuler;
	else if (name == "RptGrid")	m_blRptGrid = m_blRptGrid;
	else	throw (CaImAPIException (0));	// #### TODO: Put aImAPIException number
}

void CStorageDoc::Serialize (CArchive& ar) {
	CString strCaption = "aIm DIAS Storage v. 2.0";
	if (ar.IsStoring ()) {
		ar << strCaption;
		ar << m_nDimX << m_nDimY << m_nBPP << m_nChannels << (ubyte)m_nColorModel;
		ar << (ubyte)m_blAcceptFromView << (ubyte)m_blForceSettings;
		ar << (ubyte)m_blShowImages << (ubyte)m_blShowPatches << (ubyte)m_blShowMarks << (ubyte)m_blShowMeters;
		ar << (ubyte)m_blImgVRuler << (ubyte)m_blImgHRuler << (ubyte)m_blImgGrid << (ubyte)m_blRptVRuler << (ubyte)m_blRptHRuler << (ubyte)m_blRptGrid;
		ar << m_nImgZoom << m_nRptZoom;
		ar << m_rectPlacement << m_nPanelWidth << m_nPanelActive << (ubyte)m_blShowNames;
		ar << m_nImgNo << m_nDataNo << m_nRptNo;
		Images.Serialize (ar);
		Surveis.Serialize (ar);
		// #### TODO: Add Reports serialization here
	} else {
		DeleteContents ();
		m_strName = ar.GetFile()->GetFileTitle ();
		ar >> strCaption;
		if (strCaption != "aIm DIAS Storage v. 2.0") {
			MessageBox (theApp.m_pMainWnd->m_hWnd, theApp.LoadString (IDS_ERR_DOC_VERSION), theApp.LoadString (IDS_ERR_DOC), MB_OK | MB_ICONERROR);
			return;
		}
		(int&)m_nColorModel = 0;
		ar >> m_nDimX >> m_nDimY >> m_nBPP >> m_nChannels >> (ubyte&)m_nColorModel;
		ar >> (ubyte&)m_blAcceptFromView >> (ubyte&)m_blForceSettings;
		ar >> (ubyte&)m_blShowImages >> (ubyte&)m_blShowPatches >> (ubyte&)m_blShowMarks >> (ubyte&)m_blShowMeters;
		ar >> (ubyte&)m_blImgVRuler >> (ubyte&)m_blImgHRuler >> (ubyte&)m_blImgGrid >> (ubyte&)m_blRptVRuler >> (ubyte&)m_blRptHRuler >> (ubyte&)m_blRptGrid;
		ar >> m_nImgZoom >> m_nRptZoom;
		ar >> m_rectPlacement >> m_nPanelWidth >> m_nPanelActive >> (ubyte&)m_blShowNames;
		ar >> m_nImgNo >> m_nDataNo >> m_nRptNo;
		Images.m_pDoc = this;
		Surveis.m_pDoc = this;
		Images.Serialize (ar);
		Surveis.Serialize (ar);
		UpdateAll ();
		// #### TODO: Add Reports serialization here
	}
}

void CStorageDoc::OnChangedViewList () {
	// #### TODO: Update Frames member
	
	CDocument::OnChangedViewList();
}

void CStorageDoc::Save () {
	OnSaveDocument (GetPathName ());
}

void CStorageDoc::SaveAs (CString name, bool verbal/* = true*/) {
	SetPathName (name);
	OnSaveDocument (verbal ? "" : GetPathName ());
}

void CStorageDoc::Close (bool blAsk/* = true*/, bool blSave/* = true*/) {
	if (blSave)
		OnSaveDocument (GetPathName ());
	if (!blAsk)
		SetModifiedFlag (false);
	OnCloseDocument ();
}

void CStorageDoc::Clear (bool blSave/* = false*/) {
	if (blSave)
		Save ();
	DeleteContents ();
	UpdateAll ();
}

uvar16_32 CStorageDoc::GetDimX () {
	return (m_nDimX);
}

uvar16_32 CStorageDoc::GetDimY () {
	return (m_nDimY);
}

bool CStorageDoc::SetDims (uvar16_32 nDim, bool blStretch, bool blVerbal) {
	// #### TODO: Add conversion code here
	return (true);
}

ColorModel CStorageDoc::GetColorModel () {
	return (m_nColorModel);
}

bool CStorageDoc::SetColorModel (ColorModel cm) {
	// #### TODO: Add conversion code here
	return (true);
}

ubyte CStorageDoc::GetChannelsCount () {
	return (m_nChannels);
}

CString CStorageDoc::GetInfo (const CString name) {
	return (m_mapInfo[CString(name)]);
}

void CStorageDoc::SetInfo (const CString name, const CString value) {
	m_mapInfo[CString(name)] = value;
}

void CStorageDoc::Update (CUpdateHint::UpdateTarget tgt, udword cmd, udword start, udword end) {
	// #### TODO: Chech for global falg of update mode
	CUpdateHint* pHint = new CUpdateHint (tgt, cmd, start, end);
	UpdateAllViews (NULL, NULL, pHint);
}

void CStorageDoc::UpdateAll () {
	// #### TODO: Chech for global falg of update mode
	UpdateAllViews (NULL);
}

/*CStorageFrame& CStorageDoc::GetActiveFrame () {
	return (*((CStorageFrame*)(((CMainFrame*)(theApp.m_pMainWnd))->MDIGetActive())));
}

CStorageView& CStorageDoc::GetActiveView () {
	return (*(CStorageView*)(
		((CStorageFrame*)(((CMainFrame*)(theApp.m_pMainWnd))->MDIGetActive()))->GetActiveView()
		));
}*/

/////////////////////////////////////////////////////////////////////////////
// CStorageDoc diagnostics

#ifdef _DEBUG
void CStorageDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStorageDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStorageDoc commands

void CStorageDoc::OnImageAdd() {
	if (Images(aimActive).GetCount () == 0)
		Images.Add ();
	else
		Images.Insert (Images[aimActive].GetPos ());
}

void CStorageDoc::OnImageAddSequence () {
	CAddImagesDlg	dlg;
	if (dlg.DoModal() != IDOK)
		return;

	if (Images(aimActive).GetCount () == 0)
		Images.Add (dlg.m_nCount);
	else
		Images.Insert (Images[aimActive].GetName (), dlg.m_nCount);
}

void CStorageDoc::OnImageImport () {
	CFile		fImport;
	CFileDialog	dlgOpen (true);
	// #### TODO: Place here initial directory name taken from configuration structures
	dlgOpen.m_ofn.lpstrInitialDir = ".";
	dlgOpen.m_ofn.lpstrFilter = "Kontron Elektronik(C) VIDAS(R) Sequences""\0""*.IMG""\0";
	dlgOpen.m_ofn.nFilterIndex = 1;
//	dlgOpen.SetWindowText (theApp.LoadString (IDS_IMPORTSEQ_DLGCAPTION));
	if (dlgOpen.DoModal () != IDOK)
		return;

	// #### TODO: Add support for video formats
	// #### TODO: Add support for multi-page tif format
	// #### TODO: Create import dialog
	// #### TODO: Add progress control on the status bar

	uvar32_64	selected;
	svar32_64	nImages;
	uvar32_64	dwSize = m_nDimX * m_nDimY;
	BYTE		*pbPixels = (BYTE *)aimMemoryCommit (dwSize, "CStorageDoc::OnDocAddImportseq", "pbPixels");


	if ((selected = Frames[aimActive].GetActiveImageNo()) == -1)
		selected = Images.GetCount () - 1;

	if (dlgOpen.m_ofn.nFilterIndex == 1) {
		if (!fImport.Open (dlgOpen.GetPathName (), CFile::modeRead | CFile::typeBinary | CFile::shareDenyWrite)) {
			MessageBox (theApp.m_pMainWnd->m_hWnd, theApp.LoadString (IDS_IMPORTSEQ_OPENERR), theApp.LoadString (IDS_IMPORTSEQ_DLGCAPTION), MB_OK | MB_ICONERROR);
			return;
		}

		BYTE	*pbHeader = new BYTE[0x80];
		fImport.Read ( pbHeader, 0x80 );
		if (((DWORD*)(pbHeader + 2))[0] != 0xB06D1247) {
			MessageBox  (theApp.m_pMainWnd->m_hWnd, theApp.LoadString (IDS_IMPORTSEQ_TYPEERR), theApp.LoadString (IDS_IMPORTSEQ_DLGCAPTION), MB_OK | MB_ICONERROR);
			return;
		}
		if (((WORD*)pbHeader)[5] != 0x4321) {
			MessageBox  (theApp.m_pMainWnd->m_hWnd, theApp.LoadString (IDS_IMPORTSEQ_TYPEERR), theApp.LoadString (IDS_IMPORTSEQ_DLGCAPTION), MB_OK | MB_ICONERROR);
			return;
		}
		if (((WORD*)pbHeader)[3] != m_nDimX || ((WORD*)pbHeader)[4] != m_nDimY || m_nBPP != 8) {
			MessageBox  (theApp.m_pMainWnd->m_hWnd, theApp.LoadString (IDS_IMPORTSEQ_SIZEERR), theApp.LoadString (IDS_IMPORTSEQ_DLGCAPTION), MB_OK | MB_ICONERROR);
			return;
		}
		nImages = ((WORD*)pbHeader)[6];

		theApp.StatusState (IDI_INDICATOR_IMPORT);
		while (--nImages >= 0) {
			CImage *pImg = new CImage (this, theSettings.GetSetting (ID_IMAGE_NAME, CSettings::sqName, UINT(0)), "");
			fImport.Read (pbPixels, dwSize);
			pImg->Channels(aimAll).SetBits (pbPixels, dwSize);
			Images.Insert (selected++, *pImg);
		}
		nImages = ((WORD*)pbHeader)[6];
		theApp.StatusState (0);

		delete [] pbHeader;
		aimMemoryRelease (pbPixels, "CStorage::OnDocAddImportseq", "pbPixels");
	} else
		return;
}

void CStorageDoc::OnImageExport () {
	CFile		fExport;
	CFileDialog	dlgSave (false);
	// #### TODO: Place here initial directory name taken from configuration structures
	dlgSave.m_ofn.lpstrInitialDir = ".";
	dlgSave.m_ofn.lpstrFilter = "Kontron Elektronik(C) VIDAS(R) Sequences""\0""*.IMG""\0";
	dlgSave.m_ofn.nFilterIndex = 1;
	if (dlgSave.DoModal () != IDOK)
		return;

	// #### TODO: Add support for video formats
	// #### TODO: Add support for multi-page tif format
	// #### TODO: Create import dialog
	// #### TODO: Add progress control on the status bar

	uvar32_64	nPos, nImages = Images(aimSelected).GetCount ();
	uvar32_64	dwSize = m_nDimX * m_nDimY;
	ubyte		*pbPixels = (ubyte*)aimMemoryCommit (dwSize, "CStorageDoc::OnDocAddImportseq", "pbPixels");

	if (dlgSave.m_ofn.nFilterIndex == 1) {
		ubyte	*pbHeader = new ubyte[0x80];
		memset (pbHeader, 0, 0x80);
		((uword*)(pbHeader))[0] = 0x0001;
		((uword*)(pbHeader))[1] = 0x1247;
		((uword*)(pbHeader))[2] = 0xB06D;
		((uword*)(pbHeader))[3] = m_nDimX;
		((uword*)(pbHeader))[4] = m_nDimY;
		((uword*)(pbHeader))[5] = 0x4321;
		((uword*)(pbHeader))[6] = nImages;

		if (!fExport.Open (dlgSave.GetPathName () + ".img", CFile::modeCreate | CFile::modeWrite | CFile::typeBinary | CFile::shareExclusive)) {
			MessageBox (theApp.m_pMainWnd->m_hWnd, theApp.LoadString (IDS_EXPORTSEQ_OPENERR), theApp.LoadString (IDS_EXPORTSEQ_DLGCAPTION), MB_OK | MB_ICONERROR);
			return;
		}
		theApp.StatusState (IDI_INDICATOR_EXPORT);
		fExport.Write (pbHeader, 0x80);
		for (nPos = 0; nPos < nImages; ++nPos) {
			Images(aimSelected)[nPos].Channels(aimAll).GetBits (pbPixels, dwSize);
			fExport.Write (pbPixels, dwSize);
		}
		theApp.StatusState (0);

		delete [] pbHeader;
		aimMemoryRelease (pbPixels, "CStorage::OnDocAddImportseq", "pbPixels");
	} else
		return;
}

void CStorageDoc::OnImageAcquireCamera () {
	if (!m_pdlgCapture) {
		m_pdlgCapture = new CCaptureDlg ();
		m_pdlgCapture->m_pDoc = this;
		m_pdlgCapture->Create (IDD_CAPTURE, NULL);
	} else {
		m_pdlgCapture->DestroyWindow ();
		delete m_pdlgCapture;
		m_pdlgCapture = NULL;
	}
}
void CStorageDoc::OnUpdateImageAcquireCamera (CCmdUI* pCmdUI) {
	pCmdUI->SetCheck (m_pdlgCapture != NULL);
}

void CStorageDoc::OnSurveyAdd () {
	CSurvey *pSurvey = new CSurvey (this, theSettings.GetSetting (ID_SURVEY_NAME, CSettings::sqName, UINT(0)), "");
	CAddSurveyDlg dlg;
	dlg.m_pDoc = this;
	dlg.m_pSurvey = pSurvey;
	if (dlg.DoModal () != IDOK) {
		delete pSurvey;
		return;
	}
	if (Surveis(aimActive).GetCount () == 0)
		Surveis.Add (*pSurvey);
	else
		Surveis.Insert (Surveis[aimActive].GetPos (), *pSurvey);
}

void CStorageDoc::OnSurveyMeasure () {
}

void CStorageDoc::OnDocRemove () {
	UINT n = Frames[aimActive].GetActiveImageNo ();
	Images(aimSelected).Remove ();
	if (Images.GetCount() <= n)
		Frames[aimActive].SetActiveImageNo (Images.GetCount() - 1);
	else
		Frames[aimActive].SetActiveImageNo (n);
}

void CStorageDoc::OnDocUp () {
}

void CStorageDoc::OnDocDown () {
}

void CStorageDoc::OnDocPrev () {
}

void CStorageDoc::OnDocNext () {
}

void CStorageDoc::OnDocProp () {
}

void CStorageDoc::OnDocStyle () {
}

void CStorageDoc::OnImageArithmAdd () {
	C3ImgFnDlg dlg;
	dlg.DoModal ();
}

void CStorageDoc::OnImageAdjustNormalize () {
	Images[aimActive] = Images[aimActive].Normalize ();
}

void CStorageDoc::OnImageSegSegment () {
	Images[aimActive] = Images[aimActive].Segment (CColor (0x80), CColor (0x00), CColor (0xFF));
}

void CStorageDoc::OnImageSegErode () {
	Images[aimActive] = Images[aimActive].ErodeSegs (CColor (0xFF), segSquare);
}

void CStorageDoc::OnImageEdgesLaplacian () {
	Images[aimActive] = Images[aimActive].Laplacian (6, 6);
}

void CStorageDoc::OnToolsPlugins1 () {
	uvar32_64 cnt = Images.GetCount () / 4;
	CString strText;
	theApp.MacroStart ("Noise Remove");
	if (Images.GetCount () % 4 != 0)
		if (MessageBox (Frames[aimActive], "Image count does not proportional to 4!\nDo you wish to continue?", "Remove Noise", MB_ICONWARNING | MB_YESNO) == IDNO)
			return;
	for (svar32_64 n = 0; (Images.GetCount () - n) / 4 > 0; n++) {
		Images[n].Mul (Images[n + 1], 0, 64);
		Images[n + 2].Mul (Images[n + 3], 0, 64);
		Images[n].Median (1, 1);
		Images[n + 2].Median (1, 1);
		Images[n].Avg (Images[n + 2]);
		Images.Delete (n + 1);
		Images.Delete (n + 1);
		Images.Delete (n + 1);
		strText.Format ("%d images processed (%d%%)", n, (n * 100)/cnt);
		theApp.StatusText (strText);
	}
	theApp.MacroStop ();
}

void CStorageDoc::OnToolsPlugins2 () {
	uvar32_64 cnt = Images.GetCount () / 4;
	CString strText;
	theApp.MacroStart ("Noise Remove");
	if (Images.GetCount () % 8 != 0)
		if (MessageBox (Frames[aimActive], "Image count does not proportional to 8!\nDo you wish to continue?", "Remove Noise", MB_ICONWARNING | MB_YESNO) == IDNO)
			return;
	for (svar32_64 n = 0; (Images.GetCount () - n) / 4 > 0; n++) {
		Images[n].Mul (Images[n + 1], 0, 8);
		Images[n + 2].Mul (Images[n + 3], 0, 8);
		Images[n].Median (1, 1);
		Images[n + 2].Median (1, 1);
		Images[n].Avg (Images[n + 2]);
		Images.Delete (n + 1);
		Images.Delete (n + 1);
		Images.Delete (n + 1);
		strText.Format ("%d images processed (%d%%)", n, (n * 100)/cnt/2);
		theApp.StatusText (strText);
	}
	for (n = 0; (Images.GetCount () - n) / 2 > 0; n++) {
		Images[n].Mul (Images[n + 1], 0, 128);
		Images.Delete (n + 1);
		strText.Format ("%d images processed (%d%%)", n, (n * 100)/cnt/2 + 50);
		theApp.StatusText (strText);
	}
	theApp.MacroStop ();
}

void CStorageDoc::OnToolsPlugins3 () {
	uvar32_64 cnt = Images.GetCount () / 4;
	CString strText;
	theApp.MacroStart ("Noise Remove");
	if (Images.GetCount () % 9 != 0)
		if (MessageBox (Frames[aimActive], "Image count does not proportional to 9!\nDo you wish to continue?", "Remove Noise", MB_ICONWARNING | MB_YESNO) == IDNO)
			return;
	for (svar32_64 n = 0, m = 0; (Images.GetCount () - n) / 4 > 0; n++, m++) {
		Images[n].Mul (Images[n + 1], 0, 8);
		Images[n + 2].Mul (Images[n + 3], 0, 8);
		Images[n].Median (1, 1);
		Images[n + 2].Median (1, 1);
		Images[n].Avg (Images[n + 2]);
		Images.Delete (n + 1);
		Images.Delete (n + 1);
		Images.Delete (n + 1);
		strText.Format ("%d images processed (%d%%)", n, (n * 100)/cnt/2);
		theApp.StatusText (strText);
		if (m % 2 == 1) n++;
	}
	for (n = 0; n < Images.GetCount () && (Images.GetCount () - n) / 2 > 0; n+=2) {
		Images[n].Mul (Images[n + 1], 0, 128);
		Images.Delete (n + 1);
		strText.Format ("%d images processed (%d%%)", n, (n * 100)/cnt/2 + 50);
		theApp.StatusText (strText);
	}
	theApp.MacroStop ();
}
