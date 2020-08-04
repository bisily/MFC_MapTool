#pragma once
#include "EffectBridge.h"
class CEffectFire :
	public CEffectBridge
{
public:
	CEffectFire();
	CEffectFire(CObj* pObj);
	~CEffectFire();

public:
	// CEffectBridge��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Progress(INFO & rInfo) override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

};

