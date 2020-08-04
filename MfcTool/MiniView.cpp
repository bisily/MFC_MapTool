// MiniView.cpp : 구현 파일입니다.
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


// CMiniView 그리기입니다.

void CMiniView::OnDraw(CDC* pDC)
{
	// TODO: 여기에 그리기 코드를 추가합니다.
	CBackGround* m_pBackGround = ((CMainFrame*)AfxGetMainWnd())->GetToolView()->GetBackGround();

	if (nullptr == m_pBackGround)
		return;

	CDevice::GetInstance()->Render_Begin();

	m_pBackGround->MiniViewRender();

	//CObjMgr::GetInstance()->RenderMini();

	CDevice::GetInstance()->Render_End(m_hWnd);
}


// CMiniView 진단입니다.

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


// CMiniView 메시지 처리기입니다.


void CMiniView::OnInitialUpdate()
{

	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}
