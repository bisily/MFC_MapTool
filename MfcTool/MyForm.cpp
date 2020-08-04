// MyForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MfcTool.h"
#include "MyForm.h"


// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_MYFORM)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyForm::OnMapTool)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyForm::OnUnitTool)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyForm::OnSprite)
END_MESSAGE_MAP()


// CMyForm �����Դϴ�.

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm �޽��� ó�����Դϴ�.


void CMyForm::OnMapTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if (m_MapDialog.GetSafeHwnd() == NULL)
	{
		m_MapDialog.Create(IDD_MAPDIALOG);
	}

	m_MapDialog.ShowWindow(SW_SHOW);
}


void CMyForm::OnUnitTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_UnitDialog.GetSafeHwnd() == NULL)
	{
		m_UnitDialog.Create(IDD_UNITDIALOG);
	}

	m_UnitDialog.ShowWindow(SW_SHOW);
}


void CMyForm::OnSprite()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_SpriteDialog.GetSafeHwnd() == NULL)
	{
		m_SpriteDialog.Create(IDD_SPRITEDIALOG);
	}

	m_SpriteDialog.ShowWindow(SW_SHOW);
}
