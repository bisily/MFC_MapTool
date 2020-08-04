#pragma once



// CMyForm �� ���Դϴ�.

#include "MapDialog.h"
#include "UnitDialog.h"
#include "SpriteDialog.h"

class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMyForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	CMapDialog& GetMapDialog() { return m_MapDialog; }
	CUnitDialog& GetUnitDialog() { return m_UnitDialog; }


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

protected:
	CMapDialog		m_MapDialog;
	CUnitDialog		m_UnitDialog;
	CSpriteDialog	m_SpriteDialog;

public:
	afx_msg void OnMapTool();
	afx_msg void OnUnitTool();
	afx_msg void OnSprite();
};


