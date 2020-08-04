#pragma once


// CSpriteDialog 대화 상자입니다.

class CSpriteDialog : public CDialog
{
	DECLARE_DYNAMIC(CSpriteDialog)

public:
	CSpriteDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSpriteDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPRITEDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
