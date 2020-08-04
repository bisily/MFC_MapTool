// SpriteDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MfcTool.h"
#include "SpriteDialog.h"
#include "afxdialogex.h"


// CSpriteDialog 대화 상자입니다.

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


// CSpriteDialog 메시지 처리기입니다.
