// MrkPropBar.cpp : implementation file
//

#include "stdafx.h"
#include "dias.h"
#include "CaptureDlg.h"
#include "MrkPropBar.h"
#include "AimComboDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMrkPropBar dialog

void OnOK (CDialog* dlg) {
	CMrkPropBar *bar = (CMrkPropBar*)dlg;
	CMark &mrk = theApp.MarkStyles[aimActive].GetStyle();
	mrk.SetKernelSize ((uvar32_64)bar->m_numKernel.GetValue ());
	mrk.SetShapeSize (CSize ((uvar32_64)bar->m_numShpX.GetValue (), (uvar32_64)bar->m_numShpY.GetValue ()));
	mrk.SetAngle ((uvar32_64)bar->m_numRot.GetValue ());
	mrk.SetSizeLock ((bool)bar->m_lockSize.m_nState);
	mrk.SetAngleLock ((bool)bar->m_lockShpCol.m_nState);
}


CMrkPropBar::CMrkPropBar(CWnd* pParent /*=NULL*/)
	: CDialog(CMrkPropBar::IDD, pParent) {
	//{{AFX_DATA_INIT(CMrkPropBar)
	//}}AFX_DATA_INIT
	m_icoKrnlSize.m_nID = IDI_PIC_SIZE;
	m_icoKrnlCol.m_nID = IDI_PIC_FILL;
	m_icoShpX.m_nID = IDI_PIC_SIZEX;
	m_icoShpY.m_nID = IDI_PIC_SIZEY;
	m_icoShpRot.m_nID = IDI_PIC_ROTATE;
	m_icoShpCol.m_nID = IDI_PIC_FILL;
	m_icoFillCol.m_nID = IDI_PIC_FILL;

	m_lockSize.m_nIDOn = IDI_PIC_LOCKED;
	m_lockShpCol.m_nIDOn = IDI_PIC_LOCKED;
	m_lockSize.m_nIDOff = IDI_PIC_UNLOCKED;
	m_lockShpCol.m_nIDOff = IDI_PIC_UNLOCKED;
}


void CMrkPropBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMrkPropBar)
	DDX_Control(pDX, IDC_MRKPB_SHPCOL, m_colShp);
	DDX_Control(pDX, IDC_MRKPB_KRNLCOLOR, m_colKrnl);
	DDX_Control(pDX, IDC_MRKPB_FILLCOL, m_colFill);
	DDX_Control(pDX, IDC_MRKPB_SIZE_LOCK, m_lockSize);
	DDX_Control(pDX, IDC_MRKPB_STYLE, m_cmbStyle);
	DDX_Control(pDX, IDC_MRKPB_KERNEL, m_cmbKernel);
	DDX_Control(pDX, IDC_MRKPB_SHAPE, m_cmbShape);
	DDX_Control(pDX, IDC_MRKPB_SHPROT, m_numRot);
	DDX_Control(pDX, IDC_MRKPB_SHPY, m_numShpY);
	DDX_Control(pDX, IDC_MRKPB_SHPX, m_numShpX);
	DDX_Control(pDX, IDC_MRKPB_KRNLSIZE, m_numKernel);
	DDX_Control(pDX, IDC_MRKPB_SHPROT_LOCK, m_lockShpCol);
	DDX_Control(pDX, IDC_MRKPB_ICO_KRNLSIZE, m_icoKrnlSize);
	DDX_Control(pDX, IDC_MRKPB_ICO_SHPROT, m_icoShpRot);
	DDX_Control(pDX, IDC_MRKPB_ICO_FILLCOL, m_icoFillCol);
	DDX_Control(pDX, IDC_MRKPB_ICO_SHPCOL, m_icoShpCol);
	DDX_Control(pDX, IDC_MRKPB_ICO_SHPY, m_icoShpY);
	DDX_Control(pDX, IDC_MRKPB_ICO_SHPX, m_icoShpX);
	DDX_Control(pDX, IDC_MRKPB_ICO_KRNLCOL, m_icoKrnlCol);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMrkPropBar, CDialog)
	//{{AFX_MSG_MAP(CMrkPropBar)
	ON_BN_CLICKED(IDC_MRKPB_KRNLCOLOR, OnKrnlColor)
	ON_BN_CLICKED(IDC_MRKPB_SHPCOL, OnShpColor)
	ON_BN_CLICKED(IDC_MRKPB_FILLCOL, OnFillColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMrkPropBar message handlers

BOOL CMrkPropBar::OnInitDialog () {
	CDialog::OnInitDialog ();
	// #### TODO: Change
	CMark &mrk = theApp.MarkStyles[aimActive].GetStyle();

	m_numKernel.Init (mrk.GetKernelSize (), 0, theApp.LoadString (IDS_METRICS_PX),
	                  theApp.LoadString (IDS_METRICS_PIXELS),
	                  theApp.GeomScales[aimActive].GetUnits(), theApp.GeomScales[aimActive].GetUnits());
	m_numShpX.Init (mrk.GetShapeSize ().cx, 0, theApp.LoadString (IDS_METRICS_PX),
	                theApp.LoadString (IDS_METRICS_PIXELS),
	                theApp.GeomScales[aimActive].GetUnits(), theApp.GeomScales[aimActive].GetUnits());
	m_numShpY.Init (mrk.GetShapeSize ().cy, 0, theApp.LoadString (IDS_METRICS_PX),
	                theApp.LoadString (IDS_METRICS_PIXELS),
	                theApp.GeomScales[aimActive].GetUnits(), theApp.GeomScales[aimActive].GetUnits());
	m_numRot.Init (mrk.GetAngle (), theApp.LoadString (IDS_METRICS_DEGR),
	               theApp.LoadString (IDS_METRICS_DEGREES));
	m_numKernel.Update = &(::OnOK);
	m_numShpX.Update = &(::OnOK);
	m_numShpY.Update = &(::OnOK);
	m_numRot.Update = &(::OnOK);
	m_lockSize.Update = &(::OnOK);
	m_lockShpCol.Update = &(::OnOK);

	m_cmbKernel.Update ();
	m_cmbShape.Update ();
	m_cmbStyle.Update ();

	m_colKrnl.SetColor (mrk.GetKernelColor ());
	m_colShp.SetColor (mrk.GetShapeColor ());
	m_colFill.SetColor (mrk.GetFillColor ());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMrkPropBar::Update () {
	// #### TODO: Change
	CMark &mrk = theApp.MarkStyles[aimActive].GetStyle();

	m_numKernel.SetValue (mrk.GetKernelSize ());
	m_numShpX.SetValue (mrk.GetShapeSize ().cx);
	m_numShpY.SetValue (mrk.GetShapeSize ().cy);
	m_numRot.SetValue (mrk.GetAngle ());

	m_lockSize.m_nState = mrk.GetSizeLock ();
	m_lockSize.RedrawWindow ();
	m_lockShpCol.m_nState = mrk.GetAngleLock ();
	m_lockShpCol.RedrawWindow ();

	m_cmbKernel.Update ();
	m_cmbShape.Update ();
	m_cmbStyle.Update ();

	m_colKrnl.SetColor (mrk.GetKernelColor ());
	m_colShp.SetColor (mrk.GetShapeColor ());
	m_colFill.SetColor (mrk.GetFillColor ());
}

void CMrkPropBar::OnKrnlColor () {
	m_colKrnl.OnClicked ();
	if (theApp.Documents.GetCount () != 0 &&
	    theApp.Documents[aimActive].Images(aimActive).GetCount () != 0 &&
	    theApp.Documents[aimActive].Images[aimActive].Marks(aimSelected).GetCount () != 0)
		theApp.Documents[aimActive].Images[aimActive].Marks(aimSelected).SetKernelColors (m_colKrnl.GetColor ());
	else
		theApp.MarkStyles[aimActive].GetStyle ().SetKernelColor (m_colKrnl.GetColor ());
	Update ();
}

void CMrkPropBar::OnShpColor () {
	m_colShp.OnClicked ();
	if (theApp.Documents.GetCount () != 0 &&
	    theApp.Documents[aimActive].Images(aimActive).GetCount () != 0 &&
	    theApp.Documents[aimActive].Images[aimActive].Marks(aimSelected).GetCount () != 0)
		theApp.Documents[aimActive].Images[aimActive].Marks(aimSelected).SetShapeColors (m_colShp.GetColor ());
	else
		theApp.MarkStyles[aimActive].GetStyle ().SetShapeColor (m_colShp.GetColor ());
	Update ();
}

void CMrkPropBar::OnFillColor () {
	m_colFill.OnClicked ();
	if (theApp.Documents.GetCount () != 0 &&
	    theApp.Documents[aimActive].Images(aimActive).GetCount () != 0 &&
	    theApp.Documents[aimActive].Images[aimActive].Marks(aimSelected).GetCount () != 0)
		theApp.Documents[aimActive].Images[aimActive].Marks(aimSelected).SetFillColors (m_colFill.GetColor ());
	else
		theApp.MarkStyles[aimActive].GetStyle ().SetFillColor (m_colFill.GetColor ());
	Update ();
}

void CMrkPropBar::OnOK () {
	::OnOK (this);
}

void CMrkPropBar::OnCancel () {
}
