#pragma once
#include "Scene.h"
class CEnding :
	public CScene
{
public:
	CEnding();
	virtual ~CEnding();

public:
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Progress() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

