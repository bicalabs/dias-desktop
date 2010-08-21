// Dias.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include <winsock2.h>
#include "Dias.h"
//#include "DiasKs.h"
#include "DocList.h"
#include "MainFrame.h"
#include "Mark.h"
#include "Image.h"
#include "Survey.h"
#include "Report.h"
#include "ImageWnd.h"
#include "DataWnd.h"
#include "ReportWnd.h"
#include "StorageFrame.h"
#include "StorageView.h"
#include "StorageDoc.h"

#include "StartDlg.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

rtbyte _math_power (rtbyte a, UINT p) {
  if (p == 0)
    return (1);
  if (p == 20) {
    --a;
    return (1 + a/2 - a*a/8 + a*a*a/16 - 5*a*a*a*a/128 + 7*a*a*a*a*a/156 - 21*a*a*a*a*a*a/1024);
  }
  else
    for (UINT i = 0 ; i < p ; ++i)
      a *= a;
  return (a);
}

/////////////////////////////////////////////////////////////////////////////
// CDiasApp

BEGIN_MESSAGE_MAP(CDiasApp, CWinApp)
	//{{AFX_MSG_MAP(CDiasApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_TOOLBOX_PTR, OnToolboxPtr)
	ON_COMMAND(ID_TOOLBOX_HAND, OnToolboxHand)
	ON_COMMAND(ID_TOOLBOX_SELECT, OnToolboxSelect)
	ON_COMMAND(ID_TOOLBOX_INFO, OnToolboxInfo)
	ON_COMMAND(ID_TOOLBOX_ZOOMIN, OnToolboxZoomIn)
	ON_COMMAND(ID_TOOLBOX_ZOOMOUT, OnToolboxZoomOut)
	ON_COMMAND(ID_TOOLBOX_OBJ, OnToolboxIobjCreate)
	ON_COMMAND(ID_TOOLBOX_OBJCNG, OnToolboxIobjCng)
	ON_COMMAND(ID_TOOLBOX_OBJPTR, OnToolboxIobjPtr)
	ON_COMMAND(ID_TOOLBOX_METER, OnToolboxMeter)
	ON_COMMAND(ID_TOOLBOX_MARK, OnToolboxMarkCreate)
	ON_COMMAND(ID_TOOLBOX_MARKPTR, OnToolboxMarkPtr)
	ON_COMMAND(ID_TOOLBOX_MARKSEL, OnToolboxMarkSel)
	ON_COMMAND(ID_TOOLBOX_TEXT, OnToolboxTextCreate)
	ON_COMMAND(ID_TOOLBOX_TEXTPTR, OnToolboxTextPtr)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_PTR, OnUpdateToolboxPtr)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_HAND, OnUpdateToolboxHand)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_SELECT, OnUpdateToolboxSelect)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_INFO, OnUpdateToolboxInfo)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_ZOOMIN, OnUpdateToolboxZoomIn)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_ZOOMOUT, OnUpdateToolboxZoomOut)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_OBJ, OnUpdateToolboxIobjCreate)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_OBJCNG, OnUpdateToolboxIobjCng)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_OBJPTR, OnUpdateToolboxIobjPtr)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_METER, OnUpdateToolboxMeter)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_MARK, OnUpdateToolboxMarkCreate)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_MARKPTR, OnUpdateToolboxMarkPtr)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_MARKSEL, OnUpdateToolboxMarkSel)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_TEXT, OnUpdateToolboxTextCreate)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_TEXTPTR, OnUpdateToolboxTextPtr)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// The one and only CDiasApp and CTesla object

CDiasApp	theApp;
//CDiasKs		theKs;
CTesla		theTesla;

/////////////////////////////////////////////////////////////////////////////
// CDiasApp construction

CDiasApp::CDiasApp () {
}

/////////////////////////////////////////////////////////////////////////////
// CDiasApp initialization

BOOL CDiasApp::InitInstance () {

	m_nMode = emiPtr;

/*	if (!AfxSocketInit ()) {
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}*/

	AfxEnableControlContainer();
	AfxOleInit ();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey (_T(theApp.LoadString (IDS_REG_ROOT)));

	LoadStdProfileSettings ();  // Load standard INI file options (including MRU)
	if (!theSettings.Load ())
		return (false);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_DISTYPE,
		RUNTIME_CLASS(CStorageDoc),
		RUNTIME_CLASS(CStorageFrame), // custom MDI child frame
		RUNTIME_CLASS(CStorageView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	m_pMainFrame = new CMainFrame;
	if (!m_pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = m_pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Dispatch commands specified on the command line
//	if (!ProcessShellCommand(cmdInfo))
//		return FALSE;

	// The main window has been initialized, so show and update it.
	m_pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainFrame->UpdateWindow();

	Update (0xFFFFFFFFL);

//	if (theKs.Connect ())
		MessageBox (NULL, theApp.LoadString (IDS_MBTEXT_DIASKS_NO), theApp.LoadString (IDS_MBTITLE_APP), MB_OK | MB_ICONWARNING);

	// #### TODO: Add registry setting check for default action
/*	CStartDlg dlgStart;
	if (dlgStart.DoModal () == IDCANCEL)
		return (false);*/
	// #### TODO: Process start dialog info
	// #### TODO: Update registry settings

	return TRUE;
}

int CDiasApp::ExitInstance () {
	for (int i = 0 ; i < m_bmpaLoad.GetSize () ; ++i)
		delete m_bmpaLoad[i];
	m_bmpaLoad.RemoveAll ();

	if (Documents.m_pHashHead) {
		Documents.m_pHashHead->RemoveTail ();
		Documents.m_pHashHead->Remove ();
		delete Documents.m_pHashHead;
	}

//	theKs.Disconnect ();
	theSettings.Save ();
	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CDiasApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDiasApp message handlers

BOOL CDiasApp::PreTranslateMessage (MSG* pMsg) {
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;
	return CWinApp::PreTranslateMessage(pMsg);
}

CString CDiasApp::LoadString (UINT nID) {
	CString strLoad;
	strLoad.LoadString (nID);
	return (_T(strLoad));
}

CBitmap* CDiasApp::LoadBitmap (UINT nID) {
	CBitmap *bmp = new CBitmap;
	bmp->LoadBitmap (nID);
	m_bmpaLoad.Add (bmp);
	return (bmp);
}

void CDiasApp::PrepareMenu (CMenu *pMenu) {
	// #### TODO: Add prepare menu method
	return;
}

void CDiasApp::Update (udword action) {
	m_pMainFrame->Update (action);
}

CDiasApp::EditModes CDiasApp::GetMode () {
	return (m_nMode);
}

void CDiasApp::SetMode (CDiasApp::EditModes mode) {
	if (m_nMode == mode)
		return;
	m_nMode = mode;
	Update (UPDHA_MODE);
}

void CDiasApp::MacroStart (CString strName) {
	m_pMainFrame->m_wndStatusBar.SetPaneText (10, strName);
	m_pMainFrame->m_wndStatusBar.GetStatusBarCtrl().SetIcon (9, theApp.LoadIcon (IDI_INDICATOR_PRG_START));
}

void CDiasApp::MacroStop () {
	CString strText;
	m_pMainFrame->m_wndStatusBar.SetPaneText (10, "");
	m_pMainFrame->m_wndStatusBar.GetStatusBarCtrl().SetIcon (9, theApp.LoadIcon (IDI_INDICATOR_PRG_STOP));
	strText.LoadString (IDS_STATUS_READY);
	StatusText (strText);
}

void CDiasApp::MacroPause () {
	m_pMainFrame->m_wndStatusBar.GetStatusBarCtrl().SetIcon (9, theApp.LoadIcon (IDI_INDICATOR_PRG_PAUSE));
}

void CDiasApp::StatusText (CString strText) {
	m_pMainFrame->m_wndStatusBar.SetWindowText (strText);
}

void CDiasApp::StatusState (UINT nID) {
	if (nID == 0)
		m_pMainFrame->m_wndStatusBar.GetStatusBarCtrl().SetIcon (6, NULL);
	else
		m_pMainFrame->m_wndStatusBar.GetStatusBarCtrl().SetIcon (6, theApp.LoadIcon (nID));
}

void CDiasApp::ObjectsAdd (udword type, CObject* obj) {
	CString strText;
	if (type > OBJT_FIELD)
		return;
	strText.Format ("%d", ++m_nObjects[type]);
	if (m_pMainFrame != NULL)
		m_pMainFrame->m_wndStatusBar.SetPaneText (10 + type * 2, strText, TRUE);
}

void CDiasApp::ObjectsRemove (udword type, CObject* obj) {
	CString strText;
	if (type > OBJT_FIELD || m_nObjects[type] == 0)
		return;
	strText.Format ("%d", --m_nObjects[type]);
	if (m_pMainFrame != NULL && IsWindow (m_pMainFrame->m_hWnd) && IsWindow (m_pMainFrame->m_wndStatusBar.m_hWnd))
		m_pMainFrame->m_wndStatusBar.SetPaneText (10 + type * 2, strText, TRUE);
}

void CDiasApp::OnToolboxPtr ()		{ m_nMode = emiPtr; Update (UPDHA_MODE); }
void CDiasApp::OnToolboxHand ()		{ m_nMode = emiHand; Update (UPDHA_MODE); }
void CDiasApp::OnToolboxSelect ()	{ m_nMode = emiSelect; Update (UPDHA_MODE); }
void CDiasApp::OnToolboxInfo ()		{ m_nMode = emiInfo; Update (UPDHA_MODE); }
void CDiasApp::OnToolboxZoomIn ()	{ m_nMode = emiIn; Update (UPDHA_MODE); }
void CDiasApp::OnToolboxZoomOut ()	{ m_nMode = emiOut; Update (UPDHA_MODE); }
void CDiasApp::OnToolboxIobjCreate ()	{ m_nMode = emiIobjCreate; Update (UPDHA_MODE); }
void CDiasApp::OnToolboxIobjCng ()	{ m_nMode = emiIobjCng; Update (UPDHA_MODE); }
void CDiasApp::OnToolboxIobjPtr ()	{ m_nMode = emiIobjPtr; Update (UPDHA_MODE); }
void CDiasApp::OnToolboxMeter ()	{ m_nMode = emiMeter; Update (UPDHA_MODE); }
void CDiasApp::OnToolboxMarkCreate ()	{ m_nMode = emiMrkCreate; Update (UPDHA_MODE); }
void CDiasApp::OnToolboxMarkPtr ()	{ m_nMode = emiMrkPtr; Update (UPDHA_MODE); }
void CDiasApp::OnToolboxMarkSel ()	{ m_nMode = emiMrkSel; Update (UPDHA_MODE); }
void CDiasApp::OnToolboxTextCreate ()	{ m_nMode = emiTextCreate; Update (UPDHA_MODE); }
void CDiasApp::OnToolboxTextPtr ()	{ m_nMode = emiTextPtr; Update (UPDHA_MODE); }

void CDiasApp::OnUpdateToolboxPtr (CCmdUI* pCmdUI)		{ pCmdUI->SetCheck (m_nMode == emiPtr); }
void CDiasApp::OnUpdateToolboxHand (CCmdUI* pCmdUI)		{ pCmdUI->SetCheck (m_nMode == emiHand); }
void CDiasApp::OnUpdateToolboxSelect (CCmdUI* pCmdUI)		{ pCmdUI->SetCheck (m_nMode == emiSelect); }
void CDiasApp::OnUpdateToolboxInfo (CCmdUI* pCmdUI)		{ pCmdUI->SetCheck (m_nMode == emiInfo); }
void CDiasApp::OnUpdateToolboxZoomIn (CCmdUI* pCmdUI)		{ pCmdUI->SetCheck (m_nMode == emiIn); }
void CDiasApp::OnUpdateToolboxZoomOut (CCmdUI* pCmdUI)		{ pCmdUI->SetCheck (m_nMode == emiOut); }
void CDiasApp::OnUpdateToolboxIobjCreate (CCmdUI* pCmdUI)	{ pCmdUI->SetCheck (m_nMode == emiIobjCreate); }
void CDiasApp::OnUpdateToolboxIobjCng (CCmdUI* pCmdUI)		{ pCmdUI->SetCheck (m_nMode == emiIobjCng); }
void CDiasApp::OnUpdateToolboxIobjPtr (CCmdUI* pCmdUI)		{ pCmdUI->SetCheck (m_nMode == emiIobjPtr); }
void CDiasApp::OnUpdateToolboxMeter (CCmdUI* pCmdUI)		{ pCmdUI->SetCheck (m_nMode == emiMeter); }
void CDiasApp::OnUpdateToolboxMarkCreate (CCmdUI* pCmdUI)	{ pCmdUI->SetCheck (m_nMode == emiMrkCreate); }
void CDiasApp::OnUpdateToolboxMarkPtr (CCmdUI* pCmdUI)		{ pCmdUI->SetCheck (m_nMode == emiMrkPtr); }
void CDiasApp::OnUpdateToolboxMarkSel (CCmdUI* pCmdUI)		{ pCmdUI->SetCheck (m_nMode == emiMrkSel); }
void CDiasApp::OnUpdateToolboxTextCreate (CCmdUI* pCmdUI)	{ pCmdUI->SetCheck (m_nMode == emiTextCreate); }
void CDiasApp::OnUpdateToolboxTextPtr (CCmdUI* pCmdUI)		{ pCmdUI->SetCheck (m_nMode == emiTextPtr); }
