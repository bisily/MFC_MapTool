#pragma once
#include "EffectBridge.h"
class CEffectExplosion :
	public CEffectBridge
{
public:
	CEffectExplosion();
	CEffectExplosion(CObj* pObj);
	virtual ~CEffectExplosion();


public:
	// CEffectBridge을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void Render(HDC hDC) override;
	virtual int Progress(INFO & rInfo) override;
	virtual void Release() override;
};

