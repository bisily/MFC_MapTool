#pragma once
#include "EffectBridge.h"
class CEffectDead :
	public CEffectBridge
{
public:
	CEffectDead();
	CEffectDead(CObj* pObj);
	virtual ~CEffectDead();

public:
	// CEffectBridge��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Progress(INFO & rInfo) override;
	virtual	void Render(HDC hDC) override;
	virtual void Release() override;
};

