#pragma once


// CSpriteDialog ��ȭ �����Դϴ�.

class CSpriteDialog : public CDialog
{
	DECLARE_DYNAMIC(CSpriteDialog)

public:
	CSpriteDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSpriteDialog();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPRITEDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
