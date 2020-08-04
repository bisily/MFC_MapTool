#pragma once
#include "EffectBridge.h"
class CEffectSplash :
	public CEffectBridge
{
public:
	CEffectSplash();
	CEffectSplash(CObj* pObj);
	virtual ~CEffectSplash();

public:
	// CEffectBridge��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Progress(INFO & rInfo) override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

