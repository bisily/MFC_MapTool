#pragma once
#include "afxwin.h"


// CUnitDialog 대화 상자입니다.

class CUnitDialog : public CDialog
{
	DECLARE_DYNAMIC(CUnitDialog)

public:
	CUnitDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUnitDialog();

public:
	CListBox&		GetPlayerList() { return m_Player; }
	CListBox&		GetPlayerAddList() { return m_PlayerAddList; }
	CListBox&		GetEnemyList() { return m_Enemy; }
	CListBox&		GetEnemyAddList() { return m_EnemyADD; }
	CButton&		GetMoveMode() { return m_MoveMod[0]; }
	CEdit&			GetRotateEdit() { return m_RotateEdit; }
	list<CObj*>::iterator&	GetiterEnemy() { return begin_EnemyList; }

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.


protected:
	DECLARE_MESSAGE_MAP()
	CString						m_szName;
	CString						m_Name;
	int							m_iHp;
	float						m_fPosX;
	float						m_fPosY;
	bool						m_PlayerCheck = false;
	CListBox					m_Player;
	CListBox					m_Enemy;
	CListBox					m_EnemyADD;
	CListBox					m_PlayerAddList;
	CButton						m_MoveMod[2];
	CStatic						m_PlayerPicture;
	CStatic						m_EnemyPicture;
	map<CString, CImage*>		m_MapPngImage;
	CButton						m_RotateButton;
	CEdit						m_RotateEdit;
	list<CObj*>::iterator		begin_EnemyList;
	list<CObj*>::iterator		end_EnemyList;

protected:

protected:
	virtual BOOL	OnInitDialog();
	afx_msg void	OnPlayerADD();
	afx_msg void	OnPlayerDelete();
	afx_msg void	OnPlayerSave();
	afx_msg void	OnPlayerLoad();
	afx_msg void	OnDeleteWayPoint();
	afx_msg void	OnEnemyADD();
	afx_msg void	OnEnemySelectCancel();
	afx_msg void	OnEnemySave();
	afx_msg void	OnEnemyLoad();
	afx_msg void	OnListClick();
	afx_msg void	OnSelectCancel();
	afx_msg void	OnEnemyListClick();
	afx_msg void	OnEnemyDelete();
	afx_msg void	OnEnemyAddListClick();
	
public:


};
