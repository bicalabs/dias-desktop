#if !defined(AFX_MARKSTYLE_H__F7FA55DC_271F_42E5_9ACD_E8333817DD8C__INCLUDED_)
#define AFX_MARKSTYLE_H__F7FA55DC_271F_42E5_9ACD_E8333817DD8C__INCLUDED_

#pragma once

class CMarkStyle : public CObject {
friend class CHash<CMarkStyle*,CMarkStyle>;
friend class CaImAPICollection<CMarkStyle>;
friend class CaImAPICollectionExt<CMarkStyle>;
friend class CDiasAPIMarkStyles;
	DECLARE_SERIAL (CMarkStyle);
// Construction
public:
	CMarkStyle ();
	CMarkStyle (CString name, CString descr, CMark& mark);
	CMarkStyle (const CMarkStyle& scale);
	~CMarkStyle ();
	
	CMarkStyle& operator= (const CMarkStyle& scale);

// Attributes
protected:
	CString		m_strName;
	CString		m_strDescr;
	CMark		m_mrkStyle;

// Operations
public:
	uvar32_64	GetPos ();
	CString		GetName ();
	void		SetName (CString name);
	CString		GetDescr ();
	void		SetDescr (CString descr);
	CMark&		GetStyle ();
	void		SetStyle (CMark mark);
	void		Activate ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarkStyle)
public:
	void Serialize (CArchive& ar);
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKSTYLE_H__F7FA55DC_271F_42E5_9ACD_E8333817DD8C__INCLUDED_)
