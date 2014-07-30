#if !defined(AFX_SAMPLEDOCA_H__98DBB216_579E_413E_9BD8_C03B20ACAF3D__INCLUDED_)
#define AFX_SAMPLEDOCA_H__98DBB216_579E_413E_9BD8_C03B20ACAF3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SampleDocA.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSampleDocA document

class CSampleDocA : public CDocument
{
protected:
	CSampleDocA();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSampleDocA)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampleDocA)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSampleDocA();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSampleDocA)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLEDOCA_H__98DBB216_579E_413E_9BD8_C03B20ACAF3D__INCLUDED_)
