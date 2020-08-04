#pragma once

#include "Scene.h"

class CLogo :
	public CScene
{
public:
	CLogo();
	virtual ~CLogo();

public:
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Progress() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	CRITICAL_SECTION	GetCrt() { return m_Crt; }

private:
	HANDLE				m_hThread = nullptr;
	CRITICAL_SECTION	m_Crt;
};

