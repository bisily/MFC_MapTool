// SpriteDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MfcTool.h"
#include "SpriteDialog.h"
#include "afxdialogex.h"


// CSpriteDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSpriteDialog, CDialog)

CSpriteDialog::CSpriteDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SPRITEDIALOG, pParent)
{

}

CSpriteDialog::~CSpriteDialog()
{
}

void CSpriteDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSpriteDialog, CDialog)
END_MESSAGE_MAP()


// CSpriteDialog �޽��� ó�����Դϴ�.
