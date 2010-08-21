#include "stdafx.h"
#include "Dias.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMarkStyle

IMPLEMENT_SERIAL (CMarkStyle, CObject, 1);

CMarkStyle::CMarkStyle () {
	;
}
CMarkStyle::CMarkStyle (CString name, CString descr, CMark& mark) :
	m_strName (name), m_strDescr (descr), m_mrkStyle (mark) {
	;
}

CMarkStyle::CMarkStyle (const CMarkStyle& scale) {
	*this = scale;
}
CMarkStyle::~CMarkStyle () {
	;
}

CMarkStyle& CMarkStyle::operator= (const CMarkStyle& scale) {
	m_strName = scale.m_strName;
	m_strDescr = scale.m_strDescr;
	m_mrkStyle = scale.m_mrkStyle;
	return (*this);
}

uvar32_64 CMarkStyle::GetPos () {
	for (CHash<CMarkStyle*,CMarkStyle>* p = theApp.MarkStyles.m_pHashHead; p; p = p->GetNext ())
		if (p->m_hData == this)
			if (theApp.MarkStyles.m_nActive == p->GetPos ())
				return (p->GetPos ());
	return (uvar32_64(-1));
}

CString CMarkStyle::GetName () {
	return (m_strName);
}
void CMarkStyle::SetName (CString name) {
	if (theApp.MarkStyles.NameLookup (name) != (uvar32_64)-1)
		return;
	m_strName = name;
	theApp.Update (UPDHA_MARKSTYLE);
}
CString CMarkStyle::GetDescr () {
	return (m_strDescr);
}
void CMarkStyle::SetDescr (CString descr) {
	m_strDescr = descr;
	theApp.Update (UPDHA_MARKSTYLE);
}
CMark& CMarkStyle::GetStyle () {
	return (m_mrkStyle);
}
void CMarkStyle::SetStyle (CMark mark) {
	m_mrkStyle = mark;
	theApp.Update (UPDHA_MARKSTYLE);
}

void CMarkStyle::Activate () {
	for (CHash<CMarkStyle*,CMarkStyle>* p = theApp.MarkStyles.m_pHashHead; p; p = p->GetNext ())
		if (p->m_hData == this)
			theApp.MarkStyles.m_nActive = p->GetPos ();
	theApp.Update (UPDHA_MARKSTYLE);
}

void CMarkStyle::Serialize (CArchive &ar) {
	if (ar.IsStoring ()) {
		ar << m_strName << m_strDescr;
		m_mrkStyle.Serialize (ar);
	} else {
		ar >> m_strName >> m_strDescr;
		m_mrkStyle.Serialize (ar);
	}
}
