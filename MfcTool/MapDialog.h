#pragma once
#include "afxwin.h"


// CMapDialog 대화 상자입니다.

class CMapDialog : public CDialog
{
	DECLARE_DYNAMIC(CMapDialog)

public:
	CMapDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMapDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox& GetStructList() { return m_StructList; }
	CListBox& GetAddList() { return m_AddList; }

protected:
	void Release();
	void HorizontalScroll();

	// control type
protected:
	CButton						m_TileOption[3];
	CStatic						m_Picture;
	CListBox					m_StructList;
	CStatic						m_Picture_Struct;
	CListBox					m_AddList;

	// generic type
protected:
	bool						m_bStart = TRUE;
	map<CString, CImage*>		m_MapPngImage;
	list<IMGPATH*>				m_PathList;

public:
	afx_msg void OnSelectRadio();
	afx_msg void OnSelectRadio2();
	afx_msg void OnSelectRadio3();
	afx_msg void OnAddObj();
	afx_msg void OnDeleteObj();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnList();
	afx_msg void OnTileSave();
	afx_msg void OnTileLoad();
	afx_msg void OnSaveObject();
	afx_msg void OnLoadObject();
	afx_msg void OnDestroy();
	afx_msg void OnDelete();
	afx_msg void OnListObjDelete();
};
