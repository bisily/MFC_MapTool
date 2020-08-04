
// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once

#include "MfcToolView.h"
#include "MiniView.h"
#include "MyForm.h"

class CMainFrame : public CFrameWnd
{
	
protected: // serialization������ ��������ϴ�.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
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

protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	CSplitterWnd	  m_MainSplitter;
	CSplitterWnd	  m_SubSplitter;
	
	// generic type
protected:
	CMfcToolView*		m_pToolView = nullptr;
	CMiniView*			m_pMiniview = nullptr;
	CMyForm*			m_pMyForm = nullptr;

// ������ �޽��� �� �Լ�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

};


