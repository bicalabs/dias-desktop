// CaptureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dias.h"
#include "CaptureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCaptureDlg dialog


CCaptureDlg::CCaptureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCaptureDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCaptureDlg)
	m_blAuto = FALSE;
	m_strName = _T("");
	m_nNo = 0;
	m_blSeq = FALSE;
	m_blSeqUni = FALSE;
	m_nSeqNo = 0;
	m_nStep = 0;
	m_blVideo = FALSE;
	m_nSec = 0;
	m_blIntegr = FALSE;
	m_nIntegrNo = 1;
	//}}AFX_DATA_INIT
}


void CCaptureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCaptureDlg)
	DDX_Control(pDX, IDC_CAPTURE_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_CAPTURE_IMPORT, m_btnImport);
	DDX_Control(pDX, IDC_CAPTURE_DELETE, m_btnDelete);
	DDX_Control(pDX, IDC_CAPTURE_NO, m_ctrlNo);
	DDX_Control(pDX, IDC_CAPTURE_TOGGLE, m_btnToggle);
	DDX_Control(pDX, IDC_CAPTURE_WND, m_wndLive);
	DDX_Check(pDX, IDC_CAPTURE_AUTONAME, m_blAuto);
	DDX_Text(pDX, IDC_CAPTURE_IMGNAME, m_strName);
	DDX_Text(pDX, IDC_CAPTURE_NO, m_nNo);
	DDX_Check(pDX, IDC_CAPTURE_SEQ, m_blSeq);
	DDX_Check(pDX, IDC_CAPTURE_SEQNAME, m_blSeqUni);
	DDX_Text(pDX, IDC_CAPTURE_SEQNO, m_nSeqNo);
	DDV_MinMaxUInt(pDX, m_nSeqNo, 0, 256);
	DDX_Text(pDX, IDC_CAPTURE_STEP, m_nStep);
	DDV_MinMaxUInt(pDX, m_nStep, 1, 64000);
	DDX_Check(pDX, IDC_CAPTURE_AUTO, m_blVideo);
	DDX_Text(pDX, IDC_CAPTURE_SEC, m_nSec);
	DDV_MinMaxUInt(pDX, m_nSec, 1, 1024);
	DDX_Check(pDX, IDC_CAPTURE_INTEGR, m_blIntegr);
	DDX_Text(pDX, IDC_CAPTURE_INTERGNO, m_nIntegrNo);
	DDV_MinMaxUInt(pDX, m_nIntegrNo, 1, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCaptureDlg, CDialog)
	//{{AFX_MSG_MAP(CCaptureDlg)
	ON_BN_CLICKED(IDC_CAPTURE_CAPTURE, OnCaptureCapture)
	ON_BN_CLICKED(IDC_CAPTURE_TOGGLE, OnCaptureToggle)
	ON_BN_CLICKED(IDC_CAPTURE_OPTIONS, OnCaptureOptions)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CAPTURE_AUTONAME, OnCaptureAutoname)
	ON_BN_CLICKED(IDC_CAPTURE_POSTOP, OnCapturePostop)
	ON_BN_CLICKED(IDC_CAPTURE_POSEND, OnCapturePosend)
	ON_BN_CLICKED(IDC_CAPTURE_POSBEFORE, OnCapturePosbefore)
	ON_BN_CLICKED(IDC_CAPTURE_POSAFTER, OnCapturePosafter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaptureDlg message handlers

void CCaptureDlg::OnCaptureCapture () {
	uvar32_64 n;

	UpdateData (true);

	if (m_blVideo == TRUE) {
		if (m_blVideoOn == TRUE) {
			m_blVideoOn = FALSE;
			KillTimer (2);
			return;
		} else {
			m_blVideoOn = TRUE;
			SetTimer (2, m_nSec * 1000, NULL);
		}
	}
	if (m_blSeq == TRUE)
		for (n = 0; n < m_nSeqNo; ++n) {
			Capture ();
			if (m_blSeqUni == false) m_nNo += m_nStep;
		}
	else
		Capture ();
	m_nNo += m_nStep;

	UpdateData (false);
}

void CCaptureDlg::Capture () {
	CString strName;
	uvar32_64 pos, n, p, i, bl, size = m_pDoc->GetDimX() * m_pDoc->GetDimY();

	if (m_blLive) {
		KillTimer (1);
		grabStopLive ();
	}

	bl = ((m_blIntegr)?m_nIntegrNo:1);
	for (i = 0 ; i < bl ; ++i) {
		m_pImage = grabSnap ();

		if (m_pDoc->GetColorModel() == cmGrayscale) {
			for (n = 0; n < size; ++n) {
				m_pRaw[n] = m_pImage->pData[(n << 2)];
				if (i == 0)
					m_pIntegr[n] = m_pRaw[n];
				else
					m_pIntegr[n] = (m_pIntegr[n] * i + m_pRaw[n]) / (i + 1.);
				m_pRaw[n] = (ubyte)(m_pIntegr[n]);
			}
		}
		else if (m_pDoc->GetColorModel() == cmRGB) {
			for (n = p = 0; n < size; n += 3) {
				m_pRaw[n] = m_pImage->pData[p++];
				m_pRaw[n+1] = m_pImage->pData[p++];
				m_pRaw[n+2] = m_pImage->pData[p+=2];
				if (i == 0) {
					m_pIntegr[n] = m_pRaw[n];
					m_pIntegr[n+1] = m_pRaw[n+1];
					m_pIntegr[n+2] = m_pRaw[n+2];
				} else {
					m_pIntegr[n] = (m_pIntegr[n] * i + m_pRaw[n]) / (i + 1.);
					m_pIntegr[n+1] = (m_pIntegr[n+1] * i + m_pRaw[n+1]) / (i + 1.);
					m_pIntegr[n+2] = (m_pIntegr[n+2] * i + m_pRaw[n+2]) / (i + 1.);
				}
				m_pRaw[n] = (ubyte)(m_pIntegr[n]);
				m_pRaw[n+1] = (ubyte)(m_pIntegr[n+1]);
				m_pRaw[n+2] = (ubyte)(m_pIntegr[n+2]);
			}
		}
	}

	if (m_pDoc->Images(aimActive).GetCount () == 0) {
		pos = m_pDoc->Images.GetCount ();
		m_pDoc->Images.Add ();
	} else {
		pos = m_pDoc->Images[aimActive].GetPos ();
		m_pDoc->Images.Insert (pos++);
	}
	strName.Format (m_strName, m_nNo);
	m_pDoc->Images[pos].SetName ((m_blAuto) ? strName : m_strName);
	// #### TODO: Add image size conversion here
	m_pDoc->Images[pos].Channels(aimAll).SetBits (m_pRaw, size);
	m_pDoc->Frames[aimActive].EnsureVisibleImageNo (pos);

	if (m_blLive) {
		SetTimer (1, 5, NULL);
		grabLive ();
	}
}

void CCaptureDlg::OnCaptureToggle () {
	if (!grabLive || !grabStopLive) 
		return;
	if (m_blLive) {
		KillTimer (1);
		grabStopLive ();
		m_pImage = grabSnap ();
		m_btnToggle.SetWindowText (theApp.LoadString (IDS_DLG_CAPTURE_LIVE));
	} else {
		SetTimer (1, 1, NULL);
		grabLive ();
		m_btnToggle.SetWindowText (theApp.LoadString (IDS_DLG_CAPTURE_STOP));
	}
	m_blLive = !m_blLive;
}

void CCaptureDlg::OnCaptureOptions () {
	if (grabOptions) 
		grabOptions ();
}

BOOL CCaptureDlg::OnInitDialog () {
	CDialog::OnInitDialog ();

	grabOptions = NULL;
	grabLive = NULL;
	grabSnap = NULL;
	grabClose = NULL;
	grabStopLive = NULL;
	grabSetLiveWindow = NULL;
	m_pImage  = NULL;
	m_blLive = false;
	m_blVideo = FALSE;
	m_blVideoOn = FALSE;
	m_nSec = 1;

	OpenGrabberDLL ();
	m_wndLive.SetWindowPos (NULL, 0, 0, 768, 576, SWP_NOMOVE | SWP_NOZORDER);
	m_btnToggle.SetWindowText (theApp.LoadString (IDS_DLG_CAPTURE_LIVE));

	m_nNo = 1;
	m_blAuto = false;
	m_strName = "40x: ___ #%03d";
	m_nStep = 1;
	m_blSeq = true;
	m_blSeqUni = true;
	m_nSeqNo = 4;
	m_blIntegr = false;
	m_nIntegrNo = 1;
	UpdateData (false);
	m_ctrlNo.EnableWindow (false);

	uvar32_64 size = m_pDoc->GetDimX() * m_pDoc->GetDimY();
	if (m_pDoc->GetColorModel() == cmGrayscale) {
		m_pRaw = (ubyte*)aimMemoryCommit (size, "CCaptureDlg::OnInitDialog", "m_pRaw");
		m_pIntegr = (rtbyte*)aimMemoryCommit (size * sizeof (rtbyte), "CCaptureDlg::OnInitDialog", "m_pIntegr");
	} else if (m_pDoc->GetColorModel() == cmRGB) {
		m_pRaw = (ubyte*)aimMemoryCommit (size * 4, "CCaptureDlg::OnInitDialog", "m_pRaw");
		m_pIntegr = (rtbyte*)aimMemoryCommit (size * 4 * sizeof (rtbyte), "CCaptureDlg::OnInitDialog", "m_pIntegr");
	}

	if (grabSetLiveWindow)
		grabSetLiveWindow (m_wndLive.m_hWnd);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CCaptureDlg::OpenGrabberDLL () {
	m_hDLLModule = LoadLibrary ("GRABBER.DLL") ;
//	if (CheckDllVersion (_GRABBER_DLLNAME, _GRABBER_VERSION) < 0)
//		return FALSE;

	if (m_hDLLModule) {
		grabOptions = (TgrabOptions)GetProcAddress( m_hDLLModule, (LPCSTR) "grabOptions" );
		grabLive    = (TgrabLive)   GetProcAddress( m_hDLLModule, (LPCSTR) "grabLive" );
		grabStopLive = (TgrabStopLive)   GetProcAddress( m_hDLLModule, (LPCSTR) "grabStopLive" );
		grabSnap    = (TgrabSnap)   GetProcAddress( m_hDLLModule, (LPCSTR) "grabSnap" );
		grabClose   = (TgrabClose)  GetProcAddress( m_hDLLModule, (LPCSTR) "grabClose" );
		grabSetLiveWindow = (TgrabSetLiveWindow) GetProcAddress( m_hDLLModule, (LPCSTR) "grabSetLiveWindow" );
		return TRUE;
	}
	else
		return FALSE;
}

void CCaptureDlg::CloseGrabberDLL () {
	if (m_hDLLModule) {
		KillTimer (1);
		if (grabStopLive)	grabStopLive();
		if (grabSetLiveWindow)	grabSetLiveWindow(NULL);
		if (grabClose)		grabClose();

		//FreeLibrary(m_hDLLModule); // courses an error under microsoft
		m_hDLLModule = 0;

		grabOptions = NULL;
		grabLive = NULL;
		grabSnap = NULL;
		grabClose = NULL;
		grabStopLive = NULL;
		grabSetLiveWindow = NULL;
	}
}

void CCaptureDlg::OnClose () {
	CloseGrabberDLL();
	m_pDoc->m_pdlgCapture = NULL;
	aimMemoryRelease (m_pRaw, "CCaptureDlg::OnClose", "m_pRaw");
	aimMemoryRelease (m_pIntegr, "CCaptureDlg::OnClose", "m_pIntegr");
	CDialog::OnClose();
}

void CCaptureDlg::OnCancel () {
	CloseGrabberDLL();
	m_pDoc->m_pdlgCapture = NULL;
	CDialog::OnCancel();
}

void CCaptureDlg::OnTimer (UINT nIDEvent) {
	m_wndLive.Invalidate (false);
	m_wndLive.RedrawWindow ();

	if (nIDEvent == 2) {
		if (m_blSeq == TRUE)
			for (DWORD n = 0; n < m_nSeqNo; ++n) {
				Capture ();
				if (m_blSeqUni == false) m_nNo += m_nStep;
			}
		else
			Capture ();
		m_nNo += m_nStep;
	}

	CDialog::OnTimer(nIDEvent);
}

BOOL CCaptureDlg::DestroyWindow () {
	KillTimer (1);
	if (grabStopLive)	grabStopLive();
	if (grabSetLiveWindow)	grabSetLiveWindow(NULL);
	if (grabClose)		grabClose();
	CloseGrabberDLL();
	m_pDoc->m_pdlgCapture = NULL;
	return CDialog::DestroyWindow();
}

void CCaptureDlg::OnCaptureAutoname () {
	UpdateData (true);
	m_ctrlNo.EnableWindow (m_blAuto);
}

void CCaptureDlg::OnCapturePostop() 
{
	// TODO: Add your control notification handler code here
	
}

void CCaptureDlg::OnCapturePosend() 
{
	// TODO: Add your control notification handler code here
	
}

void CCaptureDlg::OnCapturePosbefore() 
{
	// TODO: Add your control notification handler code here
	
}

void CCaptureDlg::OnCapturePosafter() 
{
	// TODO: Add your control notification handler code here
	
}
