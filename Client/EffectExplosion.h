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
	// CEffectBridge��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void Render(HDC hDC) override;
	virtual int Progress(INFO & rInfo) override;
	virtual void Release() override;
};

