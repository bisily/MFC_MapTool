#pragma once
#include "Obj.h"

template <typename T>
class CObjFactory
{
public:
	static CObj*	CreateObj()
	{
		CObj*	pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*	CreateObj(D3DXVECTOR3	vPos, const wstring& FileName)
	{
		CObj*	pObj = new T;

		pObj->SetObjKey(FileName);
		pObj->Initialize();
		pObj->SetPos(vPos);

		return pObj;
	}
	
	static CObj*	CreateObj(D3DXVECTOR3	vPos, CString& szObjKey, const wstring& szStateKey)
	{
		CObj*	pObj = new T;

		pObj->SetObjKey(szObjKey.operator LPCWSTR());
		pObj->SetStateKey(szStateKey);
		pObj->Initialize();
		pObj->SetPos(vPos);
	
		return pObj;
	}

	// Enemy ���� �� list���� ã�� Index�� �߰���
	static CObj*	CreateObj(D3DXVECTOR3	vPos, CString& szObjKey, const wstring& szStateKey, int index)
	{
		CObj*	pObj = new T;

		if (index != 0)
		{
			pObj->SetIndex(index);
		}

		pObj->SetObjKey(szObjKey.operator LPCWSTR());
		pObj->SetStateKey(szStateKey);
		pObj->Initialize();
		pObj->SetPos(vPos);

		return pObj;
	}

	/*
	// �ҷ������
	static CObj*	CreateObj(INFO* pInfo, const TCHAR* szFilePath)
	{
		CObj*	pObj = new T;

		pObj->Initialize();
		pObj->SetPos(pInfo->vPos);
		pObj->SetUniData(szFilePath);

		return pObj;
	}
	*/


public:
	CObjFactory(){}
	~CObjFactory(){}
};