// MyForm.cpp : 구현 파일입니다.
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


// CMyForm 진단입니다.

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


// CMyForm 메시지 처리기입니다.


void CMyForm::OnMapTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_MapDialog.GetSafeHwnd() == NULL)
	{
		m_MapDialog.Create(IDD_MAPDIALOG);
	}

	m_MapDialog.ShowWindow(SW_SHOW);
}


void CMyForm::OnUnitTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_UnitDialog.GetSafeHwnd() == NULL)
	{
		m_UnitDialog.Create(IDD_UNITDIALOG);
	}

	m_UnitDialog.ShowWindow(SW_SHOW);
}


void CMyForm::OnSprite()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_SpriteDialog.GetSafeHwnd() == NULL)
	{
		m_SpriteDialog.Create(IDD_SPRITEDIALOG);
	}

	m_SpriteDialog.ShowWindow(SW_SHOW);
}
