
// MainFrm.h : CMainFrame 클래스의 인터페이스
//

#pragma once

#include "MfcToolView.h"
#include "MiniView.h"
#include "MyForm.h"

class CMainFrame : public CFrameWnd
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Gettor
public:
	CMfcToolView*	GetToolView() { return m_pToolView; }
	CMiniView*		GetMiniView() { return m_pMiniview; }
	CMyForm*		GetMyForm()		{ return m_pMyForm; }

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	CSplitterWnd	  m_MainSplitter;
	CSplitterWnd	  m_SubSplitter;
	
	// generic type
protected:
	CMfcToolView*		m_pToolView = nullptr;
	CMiniView*			m_pMiniview = nullptr;
	CMyForm*			m_pMyForm = nullptr;

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

};


