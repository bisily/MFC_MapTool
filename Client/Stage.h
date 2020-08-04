#pragma once
#include "Scene.h"
#include "Back.h"

class CStage :
	public CScene
{
public:
	CStage();
	virtual ~CStage();

public:
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Progress() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	CBack*		m_pBack;
};

