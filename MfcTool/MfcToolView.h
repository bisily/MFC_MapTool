
// MfcToolView.h : CMfcToolView Ŭ������ �������̽�
//

#pragma once

#include "BackGround.h"

class CDevice;
class CMfcToolDoc;
class CMfcToolView : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	CMfcToolView();
	DECLARE_DYNCREATE(CMfcToolView)

	// Ư���Դϴ�.
public:
	CMfcToolDoc* GetDocument() const;

	// �۾��Դϴ�.
public:

	// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// �����Դϴ�.
public:
	virtual ~CMfcToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Getter
public:
	CDevice*		GetDevice() { return m_pDevice; }
	CBackGround*	GetBackGround() { return m_pBackGround; }
	map<CString, CImage*>&	GetMapPngImage() { return m_MapPngImage; }
	

	// Setter
public:
	void			SetTileOption(int iOption) { m_iTileOpSion = iOption; }
	void			SetDrawID(int iDrawID) { m_iDrawID = iDrawID; }
	void 			SetObjkey(CString ObjKey) { szObjkey = ObjKey; }
	void			SetMinusIndex() { --m_iIndex; }
	void			SetCount(int iCnt) { m_iIndex = iCnt; }

protected:
	D3DXVECTOR3		GetImageSenter();
	void			DrawSelectImage();
	void			CreateObj();
	void			LoadUseImage();

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

protected:
	CDevice*			m_pDevice		= nullptr;
	CBackGround*		m_pBackGround	= nullptr;
	TCHAR				m_szFPS[MIN_STR]{};
	int					m_iTileOpSion	= 0;
	int					m_iDrawID		= 0;
	int					m_iIndex		= 0;

	// generic type
protected:
	CString	szBuffer, szName, szNumber, szObjkey;
	map<CString, CImage*>				m_MapPngImage;
	D3DXVECTOR3							m_vMovePos;
	vector<D3DXVECTOR2>*				m_vecLine;
	vector<D3DXVECTOR2>::iterator		begin;

public:
	afx_msg void OnDestroy();
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MfcToolView.cpp�� ����� ����
inline CMfcToolDoc* CMfcToolView::GetDocument() const
   { return reinterpret_cast<CMfcToolDoc*>(m_pDocument); }
#endif

