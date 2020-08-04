// MiniView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MfcTool.h"
#include "MiniView.h"
#include "MainFrm.h"
#include "MfcToolView.h"
#include "BackGround.h"

// CMiniView

IMPLEMENT_DYNCREATE(CMiniView, CView)

CMiniView::CMiniView()
{

}

CMiniView::~CMiniView()
{
}

BEGIN_MESSAGE_MAP(CMiniView, CView)
END_MESSAGE_MAP()


// CMiniView �׸����Դϴ�.

void CMiniView::OnDraw(CDC* pDC)
{
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
	CBackGround* m_pBackGround = ((CMainFrame*)AfxGetMainWnd())->GetToolView()->GetBackGround();

	if (nullptr == m_pBackGround)
		return;

	CDevice::GetInstance()->Render_Begin();

	m_pBackGround->MiniViewRender();

	//CObjMgr::GetInstance()->RenderMini();

	CDevice::GetInstance()->Render_End(m_hWnd);
}


// CMiniView �����Դϴ�.

#ifdef _DEBUG
void CMiniView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniView �޽��� ó�����Դϴ�.


void CMiniView::OnInitialUpdate()
{

	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}
