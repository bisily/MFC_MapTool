#pragma once

#include "Bridge.h"
#include "Obj.h"

template<typename T>
class CBridgeFactory
{
public:
	static CObj*	CreateEffect()
	{
		CObj*		pObj = new CEffect;
		CBridge*	pBridge = new T(pObj);

		pObj->SetBridge(pBridge);
		pObj->Initialize();
		pBridge->Initialize();

		return pObj;
	}

	static CObj*	CreateEffect(wstring wstrStateKey, D3DXVECTOR3 vPos)
	{
		CObj*		pObj = new CEffect;
		CBridge*	pBridge = new T(pObj);

		pObj->SetBridge(pBridge);
		pObj->Initialize();
		pObj->SetPos(vPos);

		pBridge->Initialize();
		pBridge->SetFrame(wstrStateKey);

		return pObj;
	}

	static CObj*	CreateEffect(wstring wstrStateKey, D3DXVECTOR3 vPos, float _fCX, float _fCY)
	{
		CObj*		pObj = new CEffect;
		CBridge*	pBridge = new T(pObj);

		pObj->SetBridge(pBridge);
		pObj->Initialize();
		pObj->SetPos(vPos);
		pObj->SetCX(_fCX);
		pObj->SetCY(_fCY);

		pBridge->Initialize();
		pBridge->SetFrame(wstrStateKey);

		return pObj;
	}

public:
	CBridgeFactory() {}
	~CBridgeFactory() {}
};