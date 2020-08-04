#pragma once
#include "EffectBridge.h"
class CEffectBigExplosion :
	public CEffectBridge
{
public:
	CEffectBigExplosion();
	CEffectBigExplosion(CObj* pObj);
	virtual ~CEffectBigExplosion();

public:
	// CEffectBridge을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Progress(INFO & rInfo) override;
	virtual	void Render(HDC hDC) override;
	virtual void Release() override;
};

