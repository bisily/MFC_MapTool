
// MfcTool.h : MfcTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMfcToolApp:
// �� Ŭ������ ������ ���ؼ��� MfcTool.cpp�� �����Ͻʽÿ�.
//

class CMfcToolApp : public CWinAppEx
{
public:
	CMfcToolApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMfcToolApp theApp;
